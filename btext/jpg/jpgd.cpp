// jpgd.cpp - C++ class for JPEG decompression.
// Public domain, Rich Geldreich <richgel99@gmail.com>
// Alex Evans: Linear memory allocator (taken from jpge.h).
// v1.04, May. 19, 2012: Code tweaks to fix VS2008 static code analysis warnings (all looked harmless)
//
// Supports progressive and baseline sequential JPEG image files, and the most common chroma subsampling factors: Y, H1V1, H2V1, H1V2, and H2V2.
//
// Chroma upsampling quality: H2V2 is upsampled in the frequency domain, H2V1 and H1V2 are upsampled using point sampling.
// Chroma upsampling reference: "Fast Scheme for Image Size Change in the Compressed Domain"
// http://vision.ai.uiuc.edu/~dugad/research/dct/index.html

#if defined(CSAD_JPEG) || defined(JPEG_CSAD)
#include "jpgd.h"
#include <bt.h>
#include <platform/log.h>

#include <assert.h>
#define JPGD_ASSERT(x) assert(x)

#ifdef _MSC_VER
#pragma warning (disable : 4611) // warning C4611: interaction between '_setjmp' and C++ object destruction is non-portable
#endif

// Set to 1 to enable freq. domain chroma upsampling on images using H2V2 subsampling (0=faster nearest neighbor sampling).
// This is slower, but results in higher quality on images with highly saturated colors.
#define JPGD_SUPPORT_FREQ_DOMAIN_UPSAMPLING 1

#define JPGD_TRUE (1)
#define JPGD_FALSE (0)

#define JPGD_MAX(a,b) (((a)>(b)) ? (a) : (b))
#define JPGD_MIN(a,b) (((a)<(b)) ? (a) : (b))

OPTIMIZE_ON;

namespace jpgd {

static _FORCEINLINE void *jpgd_malloc(unsigned int nSize) { return malloc(nSize); }
static _FORCEINLINE void jpgd_free(void *p) { free(p); }

// DCT coefficients are stored in this sequence.
static int g_ZAG[64] = {  0,1,8,16,9,2,3,10,17,24,32,25,18,11,4,5,12,19,26,33,40,48,41,34,27,20,13,6,7,14,21,28,35,42,49,56,57,50,43,36,29,22,15,23,30,37,44,51,58,59,52,45,38,31,39,46,53,60,61,54,47,55,62,63 };

enum JPEG_MARKER
{
  M_SOF0  = 0xC0, M_SOF1  = 0xC1, M_SOF2  = 0xC2, M_SOF3  = 0xC3, M_SOF5  = 0xC5, M_SOF6  = 0xC6, M_SOF7  = 0xC7, M_JPG   = 0xC8,
  M_SOF9  = 0xC9, M_SOF10 = 0xCA, M_SOF11 = 0xCB, M_SOF13 = 0xCD, M_SOF14 = 0xCE, M_SOF15 = 0xCF, M_DHT   = 0xC4, M_DAC   = 0xCC,
  M_RST0  = 0xD0, M_RST1  = 0xD1, M_RST2  = 0xD2, M_RST3  = 0xD3, M_RST4  = 0xD4, M_RST5  = 0xD5, M_RST6  = 0xD6, M_RST7  = 0xD7,
  M_SOI   = 0xD8, M_EOI   = 0xD9, M_SOS   = 0xDA, M_DQT   = 0xDB, M_DNL   = 0xDC, M_DRI   = 0xDD, M_DHP   = 0xDE, M_EXP   = 0xDF,
  M_APP0  = 0xE0, M_APP15 = 0xEF, M_JPG0  = 0xF0, M_JPG13 = 0xFD, M_COM   = 0xFE, M_TEM   = 0x01, M_ERROR = 0x100, RST0   = 0xD0
};

enum JPEG_SUBSAMPLING { JPGD_GRAYSCALE = 0, JPGD_YH1V1, JPGD_YH2V1, JPGD_YH1V2, JPGD_YH2V2 };

#define CONST_BITS  13
#define PASS1_BITS  2
#define SCALEDONE ((int)1)

#define FIX_0_298631336  ((signed int)2446)       /* FIX(0.298631336) */
#define FIX_0_390180644  ((signed int)3196)       /* FIX(0.390180644) */
#define FIX_0_541196100  ((signed int)4433)       /* FIX(0.541196100) */
#define FIX_0_765366865  ((signed int)6270)       /* FIX(0.765366865) */
#define FIX_0_899976223  ((signed int)7373)       /* FIX(0.899976223) */
#define FIX_1_175875602  ((signed int)9633)       /* FIX(1.175875602) */
#define FIX_1_501321110  ((signed int)12299)       /* FIX(1.501321110) */
#define FIX_1_847759065  ((signed int)15137)       /* FIX(1.847759065) */
#define FIX_1_961570560  ((signed int)16069)       /* FIX(1.961570560) */
#define FIX_2_053119869  ((signed int)16819)       /* FIX(2.053119869) */
#define FIX_2_562915447  ((signed int)20995)       /* FIX(2.562915447) */
#define FIX_3_072711026  ((signed int)25172)       /* FIX(3.072711026) */

#define DESCALE(x,n)  (((x) + (SCALEDONE << ((n)-1))) >> (n))
#define DESCALE_ZEROSHIFT(x,n)  (((x) + (128 << (n)) + (SCALEDONE << ((n)-1))) >> (n))

#define MULTIPLY(var, cnst)  ((var) * (cnst))

#define CLAMP(i) ((static_cast<unsigned int>(i) > 255) ? (((~i) >> 31) & 0xFF) : (i))

//int idctMatrix1[16]= {8192, 8192, 8192,8192, 11363,  9633, 6437,2260, 10703,  4433,-4433,-10703, 9633,-2259,-11362, -6436};
//int idctMatrix2[16]= {8192,-8192,-8192,8192,  6437,-11362, 2261,9633,  4433,-10704,10704, -4433, 2260,-6436,  9633,-13809};

float idctMatrix1[16]= {8192, 8192,8192,8192, 10703.5,4433, -4433,-10703.5,  8192, -8192,-8192,8192, 4433,-10703.5,10703.5, -4433};
float idctMatrix2[16]= {11362.5,9633,6436.5,2260, 9633,-2260,-11362, -6436.5,  6437,-11362.5, 2260,9633, 2260,-6436.5,  9633,-11362.5};

void _FASTCALL Row_idct_sub(int* pTemp,float *t)
{
	bt::vector4f t3;

	vecFunctions.V4FTransform(&t[0],idctMatrix1,&t[0]);
	vecFunctions.V4FTransform(&t[4],idctMatrix2,&t[4]);

	vecFunctions.V4FAdd(&t[0],&t[4],&t3);
	vecFunctions.V4FSub(&t[0],&t[4],&t[4]);
	vecFunctions.V4R32(&t[4],&t[4]);

	vecFunctions.V4Fmul2NRound(&t3,&pTemp[0],PASS1_BITS-CONST_BITS);
	vecFunctions.V4Fmul2NRound(&t[4],&pTemp[4],PASS1_BITS-CONST_BITS);
}

// Compiler creates a fast path 1D IDCT for X non-zero columns
template <int NONZERO_COLS>
struct Row
{
	static void idct(int* pTemp, const jpgd_block_t* pSrc)
	{
		#define ACCESS_COL(x) (((x) < NONZERO_COLS) ? (int)pSrc[x] : 0)

		float t1[8];
		bt::vector4f t2;
		bt::vector4f t3;
		t1[0]=(float)ACCESS_COL(0);
		t1[1]=(float)ACCESS_COL(2);
		t1[2]=(float)ACCESS_COL(4);
		t1[3]=(float)ACCESS_COL(6);
		t1[4]=(float)ACCESS_COL(1);
		t1[5]=(float)ACCESS_COL(3);
		t1[6]=(float)ACCESS_COL(5);
		t1[7]=(float)ACCESS_COL(7);

		Row_idct_sub(pTemp,t1);
	}
};

template <>
struct Row<0>
{
  static void idct(int* , const jpgd_block_t* )
  {
  }
};

template <>
struct Row<1>
{
  static void idct(int* pTemp, const jpgd_block_t* pSrc)
  {
    const int dcval = (pSrc[0] << PASS1_BITS);

    pTemp[0] = dcval;
    pTemp[1] = dcval;
    pTemp[2] = dcval;
    pTemp[3] = dcval;
    pTemp[4] = dcval;
    pTemp[5] = dcval;
    pTemp[6] = dcval;
    pTemp[7] = dcval;
  }
};

template <>
struct Row<2>
{
	static void idct(int* pTemp, const jpgd_block_t* pSrc)
	{
		float t1[8];
		bt::vector4f t3;
		t1[0]=pSrc[0];
		t1[1]=0.0f;
		t1[2]=0.0f;
		t1[3]=0.0f;
		t1[4]=pSrc[1];
		t1[5]=0.0f;
		t1[6]=0.0f;
		t1[7]=0.0f;

		Row_idct_sub(pTemp,t1);
	}
};

template <>
struct Row<3>
{
	static void idct(int* pTemp, const jpgd_block_t* pSrc)
	{
		float t1[8];
		t1[0]=pSrc[0];
		t1[1]=pSrc[2];
		t1[2]=0.0f;
		t1[3]=0.0f;
		t1[4]=pSrc[1];
		t1[5]=0.0f;
		t1[6]=0.0f;
		t1[7]=0.0f;

		Row_idct_sub(pTemp,t1);
	}
};

template <>
struct Row<4>
{
	static void idct(int* pTemp, const jpgd_block_t* pSrc)
	{
		float t1[8];
		t1[0]=pSrc[0];
		t1[1]=pSrc[2];
		t1[2]=0.0f;
		t1[3]=0.0f;
		t1[4]=pSrc[1];
		t1[5]=pSrc[3];
		t1[6]=0.0f;
		t1[7]=0.0f;

		Row_idct_sub(pTemp,t1);
	}
};

bt::vector4i fix128(128,128,128,128);

void _FASTCALL Col_idct_sub(unsigned char* pDst_ptr,float *t1)
{
	vecFunctions.V4FTransform(&t1[0],idctMatrix1,&t1[0]);
	vecFunctions.V4FTransform(&t1[4],idctMatrix2,&t1[4]);

	bt::vector4f t3;

	vecFunctions.V4FAdd(&t1[0],&t1[4],&t3);
	vecFunctions.V4FSub(&t1[0],&t1[4],&t1[4]);

	bt::vector4i rez;

	vecFunctions.V4Fmul2NRound(&t3,&rez,-CONST_BITS-PASS1_BITS-3);
	vecFunctions.V4IAdd(&rez,&fix128,&rez);

	pDst_ptr[0] = (unsigned char)CLAMP(rez.x);
	pDst_ptr[8] = (unsigned char)CLAMP(rez.y);
	pDst_ptr[16] = (unsigned char)CLAMP(rez.z);
	pDst_ptr[24] = (unsigned char)CLAMP(rez.w);

	vecFunctions.V4Fmul2NRound(&t1[4],&rez,-CONST_BITS-PASS1_BITS-3);
	vecFunctions.V4IAdd(&rez,&fix128,&rez);

	pDst_ptr[8*7] = (unsigned char)CLAMP(rez.x);
	pDst_ptr[8*6] = (unsigned char)CLAMP(rez.y);
	pDst_ptr[8*5] = (unsigned char)CLAMP(rez.z);
	pDst_ptr[8*4] = (unsigned char)CLAMP(rez.w);
}

// Compiler creates a fast path 1D IDCT for X non-zero rows
template <int NONZERO_ROWS>
struct Col
{
  static void idct(unsigned char* pDst_ptr, const int* pTemp)
  {
    // ACCESS_ROW() will be optimized at compile time to either an array access, or 0.
		#define ACCESS_ROW(x) (((x) < NONZERO_ROWS) ? pTemp[x * 8] : 0)

		float t1[8];

		t1[0]=(float)ACCESS_ROW(0);
		t1[1]=(float)ACCESS_ROW(2);
		t1[2]=(float)ACCESS_ROW(4);
		t1[3]=(float)ACCESS_ROW(6);
		t1[4]=(float)ACCESS_ROW(1);
		t1[5]=(float)ACCESS_ROW(3);
		t1[6]=(float)ACCESS_ROW(5);
		t1[7]=(float)ACCESS_ROW(7);

		Col_idct_sub(pDst_ptr,t1);
	}
};

template <>
struct Col<1>
{
  static void idct(unsigned char* pDst_ptr, const int* pTemp)
  {
    int dcval = DESCALE_ZEROSHIFT(pTemp[0], PASS1_BITS+3);
    const unsigned char dcval_clamped = (unsigned char)CLAMP(dcval);
    pDst_ptr[0*8] = dcval_clamped;
    pDst_ptr[1*8] = dcval_clamped;
    pDst_ptr[2*8] = dcval_clamped;
    pDst_ptr[3*8] = dcval_clamped;
    pDst_ptr[4*8] = dcval_clamped;
    pDst_ptr[5*8] = dcval_clamped;
    pDst_ptr[6*8] = dcval_clamped;
    pDst_ptr[7*8] = dcval_clamped;
  }
};

template <>
struct Col<2>
{
	static void idct(unsigned char* pDst_ptr, const int* pTemp)
	{
		float t1[8];

		t1[0]=(float)pTemp[0];
		t1[1]=0;
		t1[2]=0;
		t1[3]=0;
		t1[4]=(float)pTemp[8];
		t1[5]=0;
		t1[6]=0;
		t1[7]=0;

		Col_idct_sub(pDst_ptr,t1);
	}
};

template <>
struct Col<3>
{
	static void idct(unsigned char* pDst_ptr, const int* pTemp)
	{
		float t1[8];

		t1[0]=(float)pTemp[0];
		t1[1]=(float)pTemp[16];
		t1[2]=0;
		t1[3]=0;
		t1[4]=(float)pTemp[8];
		t1[5]=0;
		t1[6]=0;
		t1[7]=0;

		Col_idct_sub(pDst_ptr,t1);
	}
};

template <>
struct Col<4>
{
	static void idct(unsigned char* pDst_ptr, const int* pTemp)
	{
		float t1[8];

		t1[0]=(float)pTemp[0];
		t1[1]=(float)pTemp[16];
		t1[2]=0;
		t1[3]=0;
		t1[4]=(float)pTemp[8];
		t1[5]=(float)pTemp[24];
		t1[6]=0;
		t1[7]=0;

		Col_idct_sub(pDst_ptr,t1);
	}
};

static const unsigned char s_idct_row_table[] =
{
  1,0,0,0,0,0,0,0, 2,0,0,0,0,0,0,0, 2,1,0,0,0,0,0,0, 2,1,1,0,0,0,0,0, 2,2,1,0,0,0,0,0, 3,2,1,0,0,0,0,0, 4,2,1,0,0,0,0,0, 4,3,1,0,0,0,0,0,
  4,3,2,0,0,0,0,0, 4,3,2,1,0,0,0,0, 4,3,2,1,1,0,0,0, 4,3,2,2,1,0,0,0, 4,3,3,2,1,0,0,0, 4,4,3,2,1,0,0,0, 5,4,3,2,1,0,0,0, 6,4,3,2,1,0,0,0,
  6,5,3,2,1,0,0,0, 6,5,4,2,1,0,0,0, 6,5,4,3,1,0,0,0, 6,5,4,3,2,0,0,0, 6,5,4,3,2,1,0,0, 6,5,4,3,2,1,1,0, 6,5,4,3,2,2,1,0, 6,5,4,3,3,2,1,0,
  6,5,4,4,3,2,1,0, 6,5,5,4,3,2,1,0, 6,6,5,4,3,2,1,0, 7,6,5,4,3,2,1,0, 8,6,5,4,3,2,1,0, 8,7,5,4,3,2,1,0, 8,7,6,4,3,2,1,0, 8,7,6,5,3,2,1,0,
  8,7,6,5,4,2,1,0, 8,7,6,5,4,3,1,0, 8,7,6,5,4,3,2,0, 8,7,6,5,4,3,2,1, 8,7,6,5,4,3,2,2, 8,7,6,5,4,3,3,2, 8,7,6,5,4,4,3,2, 8,7,6,5,5,4,3,2,
  8,7,6,6,5,4,3,2, 8,7,7,6,5,4,3,2, 8,8,7,6,5,4,3,2, 8,8,8,6,5,4,3,2, 8,8,8,7,5,4,3,2, 8,8,8,7,6,4,3,2, 8,8,8,7,6,5,3,2, 8,8,8,7,6,5,4,2,
  8,8,8,7,6,5,4,3, 8,8,8,7,6,5,4,4, 8,8,8,7,6,5,5,4, 8,8,8,7,6,6,5,4, 8,8,8,7,7,6,5,4, 8,8,8,8,7,6,5,4, 8,8,8,8,8,6,5,4, 8,8,8,8,8,7,5,4,
  8,8,8,8,8,7,6,4, 8,8,8,8,8,7,6,5, 8,8,8,8,8,7,6,6, 8,8,8,8,8,7,7,6, 8,8,8,8,8,8,7,6, 8,8,8,8,8,8,8,6, 8,8,8,8,8,8,8,7, 8,8,8,8,8,8,8,8,
};

static const unsigned char s_idct_col_table[] = { 1, 1, 2, 3, 3, 3, 3, 3, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 };

_HIDE void idct(const jpgd_block_t* pSrc_ptr, unsigned char* pDst_ptr, int block_max_zag)
{
	JPGD_ASSERT(block_max_zag >= 1);
	JPGD_ASSERT(block_max_zag <= 64);

	if (block_max_zag <= 1)
	{
		int k = ((pSrc_ptr[0] + 4) >> 3) + 128;
		k = CLAMP(k);
		k = k | (k<<8);
		k = k | (k<<16);

		arvFunctions.A4BMove(&k,pDst_ptr,0,4,16);
		return;
	}

	int temp[64];

	const jpgd_block_t* pSrc = pSrc_ptr;
	int* pTemp = temp;

	//long long s=extFunctions.TSC();

	const unsigned char* pRow_tab = &s_idct_row_table[(block_max_zag - 1) * 8];
	int i;
	for (i = 8; i > 0; i--, pRow_tab++)
	{
    switch (*pRow_tab)
    {
      case 0: Row<0>::idct(pTemp, pSrc); break;
      case 1: Row<1>::idct(pTemp, pSrc); break;
      case 2: Row<2>::idct(pTemp, pSrc); break;
      case 3: Row<3>::idct(pTemp, pSrc); break;
      case 4: Row<4>::idct(pTemp, pSrc); break;
      case 5: Row<5>::idct(pTemp, pSrc); break;
      case 6: Row<6>::idct(pTemp, pSrc); break;
      case 7: Row<7>::idct(pTemp, pSrc); break;
      case 8: Row<8>::idct(pTemp, pSrc); break;
    }

    pSrc += 8;
    pTemp += 8;
  }

  pTemp = temp;

  const int nonzero_rows = s_idct_col_table[block_max_zag - 1];
  for (i = 8; i > 0; i--)
  {
    switch (nonzero_rows)
    {
      case 1: Col<1>::idct(pDst_ptr, pTemp); break;
      case 2: Col<2>::idct(pDst_ptr, pTemp); break;
      case 3: Col<3>::idct(pDst_ptr, pTemp); break;
      case 4: Col<4>::idct(pDst_ptr, pTemp); break;
      case 5: Col<5>::idct(pDst_ptr, pTemp); break;
      case 6: Col<6>::idct(pDst_ptr, pTemp); break;
      case 7: Col<7>::idct(pDst_ptr, pTemp); break;
      case 8: Col<8>::idct(pDst_ptr, pTemp); break;
    }

    pTemp++;
    pDst_ptr++;
  }

	/*s=extFunctions.TSC()-s;
	double ds=s;
	csad::Log::console("-- %f",ds);*/

}

void idct_4x4(const jpgd_block_t* pSrc_ptr, unsigned char* pDst_ptr)
{
  int temp[64];
  int* pTemp = temp;
  const jpgd_block_t* pSrc = pSrc_ptr;

  for (int i = 4; i > 0; i--)
  {
    Row<4>::idct(pTemp, pSrc);
    pSrc += 8;
    pTemp += 8;
  }

  pTemp = temp;
  for (int i = 8; i > 0; i--)
  {
    Col<4>::idct(pDst_ptr, pTemp);
    pTemp++;
    pDst_ptr++;
  }
}

// Retrieve one character from the input stream.
inline unsigned int jpeg_decoder::get_char()
{
  // Any bytes remaining in buffer?
  if (!m_in_buf_left)
  {
    // Try to get more bytes.
    prep_in_buffer();
    // Still nothing to get?
    if (!m_in_buf_left)
    {
      // Pad the end of the stream with 0xFF 0xD9 (EOI marker)
      int t = m_tem_flag;
      m_tem_flag ^= 1;
      if (t)
        return 0xD9;
      else
        return 0xFF;
    }
  }

  unsigned int c = *m_pIn_buf_ofs++;
  m_in_buf_left--;

  return c;
}

// Same as previous method, except can indicate if the character is a pad character or not.
inline unsigned int jpeg_decoder::get_char(bool *pPadding_flag)
{
  if (!m_in_buf_left)
  {
    prep_in_buffer();
    if (!m_in_buf_left)
    {
      *pPadding_flag = true;
      int t = m_tem_flag;
      m_tem_flag ^= 1;
      if (t)
        return 0xD9;
      else
        return 0xFF;
    }
  }

  *pPadding_flag = false;

  unsigned int c = *m_pIn_buf_ofs++;
  m_in_buf_left--;

  return c;
}

// Inserts a previously retrieved character back into the input buffer.
_FORCEINLINE void jpeg_decoder::stuff_char(unsigned char q)
{
	*(--m_pIn_buf_ofs) = q;
	m_in_buf_left++;
}

// Retrieves one character from the input stream, but does not read past markers. Will continue to return 0xFF when a marker is encountered.
inline unsigned char jpeg_decoder::get_octet()
{
	bool padding_flag;
	int c = get_char(&padding_flag);

	if (c == 0xFF)
	{
		if (padding_flag)
			return 0xFF;

		c = get_char(&padding_flag);
		if (padding_flag)
		{
			stuff_char(0xFF);
			return 0xFF;
		}

		if (c == 0x00)
		return 0xFF;
		else
		{
			stuff_char(static_cast<unsigned char>(c));
			stuff_char(0xFF);
			return 0xFF;
		}
	}

	return static_cast<unsigned char>(c);
}

// Retrieves a variable number of bits from the input stream. Does not recognize markers.
inline unsigned int jpeg_decoder::get_bits(int num_bits)
{
  if (!num_bits)
    return 0;

  unsigned int i = m_bit_buf >> (32 - num_bits);

  if ((m_bits_left -= num_bits) <= 0)
  {
    m_bit_buf <<= (num_bits += m_bits_left);

    unsigned int c1 = get_char();
    unsigned int c2 = get_char();
    m_bit_buf = (m_bit_buf & 0xFFFF0000) | (c1 << 8) | c2;

    m_bit_buf <<= -m_bits_left;

    m_bits_left += 16;

    JPGD_ASSERT(m_bits_left >= 0);
  }
  else
    m_bit_buf <<= num_bits;

  return i;
}

// Retrieves a variable number of bits from the input stream. Markers will not be read into the input bit buffer. Instead, an infinite number of all 1's will be returned when a marker is encountered.
inline unsigned int jpeg_decoder::get_bits_no_markers(int num_bits)
{
  if (!num_bits)
    return 0;

  unsigned int i = m_bit_buf >> (32 - num_bits);

  if ((m_bits_left -= num_bits) <= 0)
  {
    m_bit_buf <<= (num_bits += m_bits_left);

    if ((m_in_buf_left < 2) || (m_pIn_buf_ofs[0] == 0xFF) || (m_pIn_buf_ofs[1] == 0xFF))
    {
      unsigned int c1 = get_octet();
      unsigned int c2 = get_octet();
      m_bit_buf |= (c1 << 8) | c2;
    }
    else
    {
      m_bit_buf |= ((unsigned int)m_pIn_buf_ofs[0] << 8) | m_pIn_buf_ofs[1];
      m_in_buf_left -= 2;
      m_pIn_buf_ofs += 2;
    }

    m_bit_buf <<= -m_bits_left;

    m_bits_left += 16;

    JPGD_ASSERT(m_bits_left >= 0);
  }
  else
    m_bit_buf <<= num_bits;

  return i;
}

// Decodes a Huffman encoded symbol.
inline int jpeg_decoder::huff_decode(huff_tables *pH)
{
  int symbol;

  // Check first 8-bits: do we have a complete symbol?
  if ((symbol = pH->look_up[m_bit_buf >> 24]) < 0)
  {
    // Decode more bits, use a tree traversal to find symbol.
    int ofs = 23;
    do
    {
      symbol = pH->tree[-(int)(symbol + ((m_bit_buf >> ofs) & 1))];
      ofs--;
    } while (symbol < 0);

    get_bits_no_markers(8 + (23 - ofs));
  }
  else
    get_bits_no_markers(pH->code_size[symbol]);

  return symbol;
}

// Decodes a Huffman encoded symbol.
inline int jpeg_decoder::huff_decode(huff_tables *pH, int& extra_bits)
{
  int symbol;

  // Check first 8-bits: do we have a complete symbol?
  if ((symbol = pH->look_up2[m_bit_buf >> 24]) < 0)
  {
    // Use a tree traversal to find symbol.
    int ofs = 23;
    do
    {
      symbol = pH->tree[-(int)(symbol + ((m_bit_buf >> ofs) & 1))];
      ofs--;
    } while (symbol < 0);

    get_bits_no_markers(8 + (23 - ofs));

    extra_bits = get_bits_no_markers(symbol & 0xF);
  }
  else
  {
    JPGD_ASSERT(((symbol >> 8) & 31) == pH->code_size[symbol & 255] + ((symbol & 0x8000) ? (symbol & 15) : 0));

    if (symbol & 0x8000)
    {
      get_bits_no_markers((symbol >> 8) & 31);
      extra_bits = symbol >> 16;
    }
    else
    {
      int code_size = (symbol >> 8) & 31;
      int num_extra_bits = symbol & 0xF;
      int bits = code_size + num_extra_bits;
      if (bits <= (m_bits_left + 16))
        extra_bits = get_bits_no_markers(bits) & ((1 << num_extra_bits) - 1);
      else
      {
        get_bits_no_markers(code_size);
        extra_bits = get_bits_no_markers(num_extra_bits);
      }
    }

    symbol &= 0xFF;
  }

  return symbol;
}

// Tables and macro used to fully decode the DPCM differences.
static const int s_extend_test[16] = { 0, 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000 };
static const int s_extend_offset[16] = { 0, ((-1)<<1) + 1, ((-1)<<2) + 1, ((-1)<<3) + 1, ((-1)<<4) + 1, ((-1)<<5) + 1, ((-1)<<6) + 1, ((-1)<<7) + 1, ((-1)<<8) + 1, ((-1)<<9) + 1, ((-1)<<10) + 1, ((-1)<<11) + 1, ((-1)<<12) + 1, ((-1)<<13) + 1, ((-1)<<14) + 1, ((-1)<<15) + 1 };
static const int s_extend_mask[] = { 0, (1<<0), (1<<1), (1<<2), (1<<3), (1<<4), (1<<5), (1<<6), (1<<7), (1<<8), (1<<9), (1<<10), (1<<11), (1<<12), (1<<13), (1<<14), (1<<15), (1<<16) };
// The logical AND's in this macro are to shut up static code analysis (aren't really necessary - couldn't find another way to do this)
#define JPGD_HUFF_EXTEND(x, s) (((x) < s_extend_test[s & 15]) ? ((x) + s_extend_offset[s & 15]) : (x))

// Clamps a value between 0-255.
_FORCEINLINE unsigned char jpeg_decoder::clamp(int i)
{
  if (static_cast<unsigned int>(i) > 255)
    i = (((~i) >> 31) & 0xFF);

  return static_cast<unsigned char>(i);
}

namespace DCT_Upsample
{
	struct Matrix44
	{
		typedef int Element_Type;
		enum { NUM_ROWS = 4, NUM_COLS = 4 };

		Element_Type v[NUM_ROWS][NUM_COLS];

		_FORCEINLINE int rows() const { return NUM_ROWS; }
		_FORCEINLINE int cols() const { return NUM_COLS; }

//		_FORCEINLINE const Element_Type & at(int r, int c) const { return v[r][c]; }
//		_FORCEINLINE       Element_Type & at(int r, int c)       { return v[r][c]; }
		_FORCEINLINE const Element_Type & at(int r, int c) const { return ((Element_Type*)v)[c+(r<<2)]; }
		_FORCEINLINE       Element_Type & at(int r, int c)       { return ((Element_Type*)v)[c+(r<<2)]; }
		_FORCEINLINE const Element_Type & at(int p) const { return ((Element_Type*)v)[p]; }
		_FORCEINLINE       Element_Type & at(int p)       { return ((Element_Type*)v)[p]; }

		_FORCEINLINE Matrix44() { }

	_FORCEINLINE Matrix44& operator += (const Matrix44& a)
	{
		arvFunctions.A4IAdd((void*)&a.at(0),(void*)&at(0),(void*)&at(0),4*4,4*4,4*4,NUM_ROWS);
		return *this;
	}

    _FORCEINLINE Matrix44& operator -= (const Matrix44& a)
    {
		arvFunctions.A4ISub((void*)&at(0),(void*)&a.at(0),(void*)&at(0),4*4,4*4,4*4,NUM_ROWS);
		return *this;
    }

    friend _FORCEINLINE Matrix44 operator + (const Matrix44& a, const Matrix44& b)
    {
		Matrix44 ret;
		arvFunctions.A4IAdd((void*)&a.at(0),(void*)&b.at(0),(void*)&ret.at(0),4*4,4*4,4*4,NUM_ROWS);
		return ret;
    }

	friend _FORCEINLINE Matrix44 operator - (const Matrix44& a, const Matrix44& b)
    {
		Matrix44 ret;
		arvFunctions.A4ISub((void*)&a.at(0),(void*)&b.at(0),(void*)&ret.at(0),4*4,4*4,4*4,NUM_ROWS);
		return ret;
    }

    static inline void add_and_store(jpgd_block_t* pDst, const Matrix44& a, const Matrix44& b)
	{
		Matrix44 ret;
		arvFunctions.A4IAdd((void*)&a.at(0),(void*)&b.at(0),(void*)&ret.at(0),4*4,4*4,4*4,NUM_ROWS);
		vecFunctions.M4FTranspose((void*)&ret.at(0),(void*)&ret.at(0));
		arvFunctions.A4ITo4W((void*)&ret.at(0),(void*)pDst,4*4,4*4,NUM_ROWS);
	}

    static _FORCEINLINE void sub_and_store(jpgd_block_t* pDst, const Matrix44& a, const Matrix44& b)
    {
		Matrix44 ret;
		arvFunctions.A4ISub((void*)&a.at(0),(void*)&b.at(0),(void*)&ret.at(0),4*4,4*4,4*4,NUM_ROWS);
		vecFunctions.M4FTranspose((void*)&ret.at(0),(void*)&ret.at(0));
		arvFunctions.A4ITo4W((void*)&ret.at(0),(void*)pDst,4*4,4*4,NUM_ROWS);
	}
};

const int FRACT_BITS = 10;
const int SCALE = 1 << FRACT_BITS;

typedef int Temp_Type;
#define D(i) (((i) + (SCALE >> 1)) >> FRACT_BITS)
#define F(i) ((int)((i) * SCALE + .5f))

// Any decent C++ compiler will optimize this at compile time to a 0, or an array access.
#define AT(c, r) ((((c)>=NUM_COLS)||((r)>=NUM_ROWS)) ? 0 : pSrc[(c)+(r)*8])
#define ATi(c, r) ((((c)>=NUM_COLS)||((r)>=NUM_ROWS)) ? 0 : pSrci[(c)+(r)*8])
#define ATai(c, r) pSrci[(c)+(r)*8]

bt::matrix4f fixP_Q(0.415735f,0.791065f,-0.352443f,0.277785f,0.022887f,-0.097545f,0.490393f,0.865723f,0.906127f,-0.318190f,0.212608f,-0.180240f,-0.074658f,0.513280f,0.768178f,-0.375330f);
//bt::vector4f fixP_Q1(0.415735f,0.791065f,-0.352443f,0.277785f);
//bt::vector4f fixP_Q2(0.022887f,-0.097545f,0.490393f,0.865723f);
//bt::vector4f fixP_Q3(0.906127f,-0.318190f,0.212608f,-0.180240f);
//bt::vector4f fixP_Q4(-0.074658f,0.513280f,0.768178f,-0.375330f);

void _FASTCALL P_Q_load_1(float *m,const jpgd_block_t* pSrc,int NUM_ROWS,int NUM_COLS)
{
	const jpgd_block_t* pSrci=pSrc;
	m[0]=(float)ATi(1, 1);
	m[1]=(float)ATi(1, 3);
	m[2]=(float)ATi(1, 5);
	m[3]=(float)ATi(1, 7);
	m[4]=(float)ATi(3, 1);
	m[5]=(float)ATi(3, 3);
	m[6]=(float)ATi(3, 5);
	m[7]=(float)ATi(3, 6);
	m[8]=(float)ATi(5, 1);
	m[9]=(float)ATi(5, 3);
	m[10]=(float)ATi(5, 5);
	m[11]=(float)ATi(5, 7);
	m[12]=(float)ATi(7, 1);
	m[13]=(float)ATi(7, 3);
	m[14]=(float)ATi(7, 5);
	m[15]=(float)ATi(7, 7);
}

void _FASTCALL P_Q_load_2(float *m,const jpgd_block_t* pSrc,int NUM_ROWS,int NUM_COLS)
{
	const jpgd_block_t* pSrci=pSrc;
	m[0]=(float)ATi(1, 0);
	m[1]=(float)ATi(1, 2);
	m[2]=(float)ATi(1, 4);
	m[3]=(float)ATi(1, 6);
	m[4]=(float)ATi(3, 0);
	m[5]=(float)ATi(3, 2);
	m[6]=(float)ATi(3, 4);
	m[7]=(float)ATi(3, 6);
	m[8]=(float)ATi(5, 0);
	m[9]=(float)ATi(5, 2);
	m[10]=(float)ATi(5, 4);
	m[11]=(float)ATi(5, 6);
	m[12]=(float)ATi(7, 0);
	m[13]=(float)ATi(7, 2);
	m[14]=(float)ATi(7, 4);
	m[15]=(float)ATi(7, 6);
}

void _FASTCALL P_Q_save_1(Matrix44& P, Matrix44& Q,float *m)
{
	bt::vector4i ri;
	vecFunctions.V4FTo4I(m,&ri);
	P.at(1, 0) = ri.x;
	Q.at(1, 1) = ri.y;
	P.at(1, 2) = ri.z;
	Q.at(1, 3) = ri.w;
	m+=4;
	vecFunctions.V4FTo4I(m,&ri);
	P.at(3, 0) = ri.x;
	Q.at(3, 1) = ri.y;
	P.at(3, 2) = ri.z;
	Q.at(3, 3) = ri.w;
}
	
void _FASTCALL P_Q_save_2(Matrix44& P, Matrix44& Q,float *m)
{
	bt::vector4i ri;
	vecFunctions.V4FTo4I(m,&ri);
	P.at(0, 1) = ri.x;
	P.at(1, 1) = ri.y;
	P.at(2, 1) = ri.z;
	P.at(3, 1) = ri.w;
	m+=4;
	vecFunctions.V4FTo4I(m,&ri);
	P.at(0, 3) = ri.x;
	P.at(1, 3) = ri.y;
	P.at(2, 3) = ri.z;
	P.at(3, 3) = ri.w;
	m+=4;
	vecFunctions.V4FTo4I(m,&ri);
	Q.at(0, 0) = ri.x;
	Q.at(1, 0) = ri.y;
	Q.at(2, 0) = ri.z;
	Q.at(3, 0) = ri.w;
	m+=4;
	vecFunctions.V4FTo4I(m,&ri);
	Q.at(0, 2) = ri.x;
	Q.at(1, 2) = ri.y;
	Q.at(2, 2) = ri.z;
	Q.at(3, 2) = ri.w;
}

// NUM_ROWS/NUM_COLS = # of non-zero rows/cols in input matrix
template<int NUM_ROWS, int NUM_COLS>
struct P_Q
{
	static void calc(Matrix44& P, Matrix44& Q, const jpgd_block_t* pSrc)
	{
		bt::matrix4f tempy;
		const jpgd_block_t* pSrci=pSrc;
		P_Q_load_1(tempy.m,pSrc,NUM_ROWS,NUM_COLS);
		
		bt::matrix4f tempx;
		vecFunctions.V4FTransform(&fixP_Q.m[0],&tempy,&tempx.m[0]);
		vecFunctions.V4FTransform(&fixP_Q.m[4],&tempy,&tempx.m[4]);

		tempx.m[15]=tempx.m[7];
		tempx.m[13]=tempx.m[3];
		tempx.m[11]=tempx.m[6];
		tempx.m[9]=tempx.m[2];
		tempx.m[7]=tempx.m[5];
		tempx.m[5]=tempx.m[1];
		tempx.m[3]=tempx.m[4];
		tempx.m[1]=tempx.m[0];

		tempx.m[0]=(float)ATi(0, 1);
		tempx.m[2]=(float)ATi(4, 1);
		tempx.m[4]=(float)ATi(0, 3);
		tempx.m[6]=(float)ATi(4, 3);
		tempx.m[8]=(float)ATi(0, 5);
		tempx.m[10]=(float)ATi(4, 5);
		tempx.m[12]=(float)ATi(0, 7);
		tempx.m[14]=(float)ATi(4, 7);

		bt::matrix4f r;
		bt::vector4i ri;
		vecFunctions.M4FMul(&tempx,&fixP_Q,&r);

		P_Q_load_2(tempy.m,pSrc,NUM_ROWS,NUM_COLS);

		vecFunctions.V4FTransform(&fixP_Q.m[0],&tempy,&tempx.m[0]);
		vecFunctions.V4FTransform(&fixP_Q.m[4],&tempy,&tempx.m[4]);

		P_Q_save_1(P,Q,tempx.m);

		// 4x4 = 4x8 times 8x4, matrix 1 is constant
		P.at(0, 0) = ATi(0, 0);
		P.at(2, 0) = ATi(4, 0);
		P.at(0, 2) = ATi(0, 4);      
		P.at(2, 2) = ATi(4, 4);

		// 40 muls 24 adds

		// 4x4 = 4x8 times 8x4, matrix 1 is constant
		Q.at(0, 1) = ATi(0, 2);
		Q.at(2, 1) = ATi(4, 2);
		Q.at(0, 3) = ATi(0, 6);
		Q.at(2, 3) = ATi(4, 6);

		P_Q_save_2(P,Q,r.m);

	}
};

template<>
struct P_Q<1,1>
{
	static void calc(Matrix44& P, Matrix44& Q, const jpgd_block_t* pSrc)
	{
      // 4x4 = 4x8 times 8x4, matrix 1 is constant
		extFunctions.CleanMem(&P,sizeof(Matrix44));
		extFunctions.CleanMem(&Q,sizeof(Matrix44));
		P.at(0, 0) = pSrc[0];

      // 40 muls 24 adds

      // 4x4 = 4x8 times 8x4, matrix 1 is constant
	}
};

template<>
struct P_Q<1,2>
{
	static void calc(Matrix44& P, Matrix44& Q, const jpgd_block_t* pSrc)
	{
      // 4x4 = 4x8 times 8x4, matrix 1 is constant
		extFunctions.CleanMem(&P,sizeof(Matrix44));
		extFunctions.CleanMem(&Q,sizeof(Matrix44));
		P.at(0, 0) = pSrc[0];
		P.at(1, 0) = matFunctions.FRound(fixP_Q.m[0]*(float)pSrc[1]);
		P.at(3, 0) = matFunctions.FRound(fixP_Q.m[4]*(float)pSrc[1]);
	}
};

template<>
struct P_Q<2,2>
{
	static void calc(Matrix44& P, Matrix44& Q, const jpgd_block_t* pSrc)
	{
      // 4x4 = 4x8 times 8x4, matrix 1 is constant
		extFunctions.CleanMem(&P,sizeof(Matrix44));
		extFunctions.CleanMem(&Q,sizeof(Matrix44));
		P.at(0, 0) = pSrc[0];
		
		bt::matrix4f tempx;
		extFunctions.CleanMem(&tempx,sizeof(bt::matrix4f));

		tempx.m[0]=(float)pSrc[8];
		tempx.m[1]=fixP_Q.m[0]*(float)pSrc[9];
		tempx.m[3]=fixP_Q.m[4]*(float)pSrc[9];

		bt::matrix4f r;
		bt::vector4i ri;
		vecFunctions.M4FMul(&tempx,&fixP_Q,&r);

		P.at(1, 0) = matFunctions.FRound(fixP_Q.m[0]*(float)pSrc[1]);
		P.at(3, 0) = matFunctions.FRound(fixP_Q.m[4]*(float)pSrc[1]);
		P_Q_save_2(P,Q,r.m);
	}
};

void _FASTCALL R_S_save_1(Matrix44& R, Matrix44& S,float *m)
{
	bt::vector4i ri;
	vecFunctions.V4FTo4I(m,&ri);
	R.at(0, 0) = ri.x;
	S.at(0, 1) = ri.y;
	R.at(0, 2) = ri.z;
	S.at(0, 3) = ri.w;
	m+=4;
	vecFunctions.V4FTo4I(m,&ri);
	R.at(2, 0) = ri.x;
	S.at(2, 1) = ri.y;
	R.at(2, 2) = ri.z;
	S.at(2, 3) = ri.w;
}

//bt::matrix4f fixR_S(0.415735f,0.791065f,-0.352443f,0.277785f,0.022887f,-0.097545f,0.490393f,0.865723f,0.906127f,-0.318190f,0.212608f,-0.180240f,-0.074658f,0.513280f,0.768178f,-0.375330f);

template<int NUM_ROWS, int NUM_COLS>
struct R_S
{
	static void calc(Matrix44& R, Matrix44& S, const jpgd_block_t* pSrc)
	{
		bt::matrix4f tempy;
		P_Q_load_1(tempy.m,pSrc,NUM_ROWS,NUM_COLS);

		bt::matrix4f tempx;

		vecFunctions.V4FTransform(&fixP_Q.m[8],&tempy,&tempx.m[0]);
		vecFunctions.V4FTransform(&fixP_Q.m[12],&tempy,&tempx.m[4]);

		tempx.m[14]=tempx.m[7];
		tempx.m[12]=tempx.m[3];
		tempx.m[10]=tempx.m[6];
		tempx.m[8]=tempx.m[2];
		tempx.m[6]=tempx.m[5];
		tempx.m[4]=tempx.m[1];
		tempx.m[2]=tempx.m[4];
		tempx.m[0]=tempx.m[0];

		tempx.m[1]=(float)AT(2, 1);
		tempx.m[3]=(float)AT(6, 1);
		tempx.m[5]=(float)AT(2, 3);
		tempx.m[7]=(float)AT(6, 3);
		tempx.m[9]=(float)AT(2, 5);
		tempx.m[11]=(float)AT(6, 5);
		tempx.m[13]=(float)AT(2, 7);
		tempx.m[15]=(float)AT(6, 7);

      // 80 muls 48 adds

		bt::matrix4f r;
		bt::vector4i ri;
		vecFunctions.M4FMul(&tempx,&fixP_Q,&r);

		P_Q_load_2(tempy.m,pSrc,NUM_ROWS,NUM_COLS);

		vecFunctions.V4FTransform(&fixP_Q.m[8],&tempy,&tempx.m[0]);
		vecFunctions.V4FTransform(&fixP_Q.m[12],&tempy,&tempx.m[4]);

		R_S_save_1(R,S,tempx.m);

      // 4x4 = 4x8 times 8x4, matrix 1 is constant
		R.at(1, 0) = AT(2, 0);
		R.at(3, 0) = AT(6, 0);
		R.at(1, 2) = AT(2, 4);
		R.at(3, 2) = AT(6, 4);
		
		S.at(1, 1) = AT(2, 2);
		S.at(3, 1) = AT(6, 2);
		S.at(1, 3) = AT(2, 6);
		S.at(3, 3) = AT(6, 6);

		P_Q_save_2(R,S,r.m);

    }
  };

template<>
struct R_S<1,1>
{
	static void calc(Matrix44& R, Matrix44& S, const jpgd_block_t* )
	{
      // 4x4 = 4x8 times 8x4, matrix 1 is constant
		extFunctions.CleanMem(&R,sizeof(Matrix44));
		extFunctions.CleanMem(&S,sizeof(Matrix44));

      // 40 muls 24 adds

      // 4x4 = 4x8 times 8x4, matrix 1 is constant
	}
};

template<>
struct R_S<1,2>
{
	static void calc(Matrix44& R, Matrix44& S, const jpgd_block_t* )
	{
      // 4x4 = 4x8 times 8x4, matrix 1 is constant
		extFunctions.CleanMem(&R,sizeof(Matrix44));
		extFunctions.CleanMem(&S,sizeof(Matrix44));

      // 40 muls 24 adds

      // 4x4 = 4x8 times 8x4, matrix 1 is constant
	}
};
} // end namespace DCT_Upsample

// Unconditionally frees all allocated m_blocks.
void jpeg_decoder::free_all_blocks()
{
	m_pStream = NULL;
	for (mem_block *b = m_pMem_blocks; b; )
	{
		mem_block *n = b->m_pNext;
		jpgd_free(b);
		b = n;
	}
	m_pMem_blocks = NULL;
}

// This method handles all errors. It will never return.
// It could easily be changed to use C++ exceptions.
JPGD_NORETURN void jpeg_decoder::stop_decoding(jpgd_status status)
{
	m_error_code = status;
	free_all_blocks();
	longjmp(m_jmp_state, status);
}

void *jpeg_decoder::alloc(unsigned int nSize, bool zero)
{
	nSize = (JPGD_MAX(nSize, 1) + 3) & ~3;
	char *rv = NULL;
	for (mem_block *b = m_pMem_blocks; b; b = b->m_pNext)
	{
		if ((b->m_used_count + nSize) <= b->m_size)
		{
			rv = b->m_data + b->m_used_count;
			b->m_used_count += nSize;
			break;
		}
	}
	if (!rv)
	{
		int capacity = JPGD_MAX(32768 - 256, (nSize + 2047) & ~2047);
		mem_block *b = (mem_block*)jpgd_malloc(sizeof(mem_block) + capacity);
		if (!b) { stop_decoding(JPGD_NOTENOUGHMEM); }
		b->m_pNext = m_pMem_blocks; m_pMem_blocks = b;
		b->m_used_count = nSize;
		b->m_size = capacity;
		rv = b->m_data;
	}
	if (zero) extFunctions.CleanMem(rv, nSize);
	return rv;
}

void jpeg_decoder::word_clear(void *p, unsigned short c, unsigned int n)
{
	unsigned char *pD = (unsigned char*)p;
	const unsigned char l = c & 0xFF, h = (c >> 8) & 0xFF;
	while (n)
	{
		pD[0] = l; pD[1] = h; pD += 2;
		n--;
	}
}

// Refill the input buffer.
// This method will sit in a loop until (A) the buffer is full or (B)
// the stream's read() method reports and end of file condition.
void jpeg_decoder::prep_in_buffer()
{
	m_in_buf_left = 0;
	m_pIn_buf_ofs = m_in_buf;

	if (m_eof_flag)
		return;

	do
	{
		int bytes_read = m_pStream->read(m_in_buf + m_in_buf_left, JPGD_IN_BUF_SIZE - m_in_buf_left, &m_eof_flag);
		if (bytes_read == -1)
		stop_decoding(JPGD_STREAM_READ);

		m_in_buf_left += bytes_read;
	} while ((m_in_buf_left < JPGD_IN_BUF_SIZE) && (!m_eof_flag));

	m_total_bytes_read += m_in_buf_left;

  // Pad the end of the block with M_EOI (prevents the decompressor from going off the rails if the stream is invalid).
  // (This dates way back to when this decompressor was written in C/asm, and the all-asm Huffman decoder did some fancy things to increase perf.)
	word_clear(m_pIn_buf_ofs + m_in_buf_left, 0xD9FF, 64);
}

// Read a Huffman code table.
void jpeg_decoder::read_dht_marker()
{
  int i, index, count;
  unsigned char huff_num[17];
  unsigned char huff_val[256];

  unsigned int num_left = get_bits(16);

  if (num_left < 2)
    stop_decoding(JPGD_BAD_DHT_MARKER);

  num_left -= 2;

  while (num_left)
  {
    index = get_bits(8);

    huff_num[0] = 0;

    count = 0;

    for (i = 1; i <= 16; i++)
    {
      huff_num[i] = static_cast<unsigned char>(get_bits(8));
      count += huff_num[i];
    }

    if (count > 255)
      stop_decoding(JPGD_BAD_DHT_COUNTS);

    for (i = 0; i < count; i++)
      huff_val[i] = static_cast<unsigned char>(get_bits(8));

    i = 1 + 16 + count;

    if (num_left < (unsigned int)i)
      stop_decoding(JPGD_BAD_DHT_MARKER);

    num_left -= i;

    if ((index & 0x10) > 0x10)
      stop_decoding(JPGD_BAD_DHT_INDEX);

    index = (index & 0x0F) + ((index & 0x10) >> 4) * (JPGD_MAX_HUFF_TABLES >> 1);

    if (index >= JPGD_MAX_HUFF_TABLES)
      stop_decoding(JPGD_BAD_DHT_INDEX);

    if (!m_huff_num[index])
      m_huff_num[index] = (unsigned char *)alloc(17);

    if (!m_huff_val[index])
      m_huff_val[index] = (unsigned char *)alloc(256);

    m_huff_ac[index] = (index & 0x10) != 0;
	extFunctions.MoveMem(huff_num,m_huff_num[index], 17);
    extFunctions.MoveMem(huff_val,m_huff_val[index], 256);
  }
}

// Read a quantization table.
void jpeg_decoder::read_dqt_marker()
{
  int n, i, prec;
  unsigned int num_left;
  unsigned int temp;

  num_left = get_bits(16);

  if (num_left < 2)
    stop_decoding(JPGD_BAD_DQT_MARKER);

  num_left -= 2;

  while (num_left)
  {
    n = get_bits(8);
    prec = n >> 4;
    n &= 0x0F;

    if (n >= JPGD_MAX_QUANT_TABLES)
      stop_decoding(JPGD_BAD_DQT_TABLE);

    if (!m_quant[n])
      m_quant[n] = (jpgd_quant_t *)alloc(64 * sizeof(jpgd_quant_t));

    // read quantization entries, in zag order
    for (i = 0; i < 64; i++)
    {
      temp = get_bits(8);

      if (prec)
        temp = (temp << 8) + get_bits(8);

			m_quant[n][i] = static_cast<jpgd_quant_t>(temp);
    }

    i = 64 + 1;

    if (prec)
      i += 64;

    if (num_left < (unsigned int)i)
      stop_decoding(JPGD_BAD_DQT_LENGTH);

    num_left -= i;
  }
}

// Read the start of frame (SOF) marker.
void jpeg_decoder::read_sof_marker()
{
  int i;
  unsigned int num_left;

  num_left = get_bits(16);

  if (get_bits(8) != 8)   /* precision: sorry, only 8-bit precision is supported right now */
    stop_decoding(JPGD_BAD_PRECISION);

  m_image_y_size = get_bits(16);

  if ((m_image_y_size < 1) || (m_image_y_size > JPGD_MAX_HEIGHT))
    stop_decoding(JPGD_BAD_HEIGHT);

  m_image_x_size = get_bits(16);

  if ((m_image_x_size < 1) || (m_image_x_size > JPGD_MAX_WIDTH))
    stop_decoding(JPGD_BAD_WIDTH);

  m_comps_in_frame = get_bits(8);

  if (m_comps_in_frame > JPGD_MAX_COMPONENTS)
    stop_decoding(JPGD_TOO_MANY_COMPONENTS);

  if (num_left != (unsigned int)(m_comps_in_frame * 3 + 8))
    stop_decoding(JPGD_BAD_SOF_LENGTH);

  for (i = 0; i < m_comps_in_frame; i++)
  {
    m_comp_ident[i]  = get_bits(8);
    m_comp_h_samp[i] = get_bits(4);
    m_comp_v_samp[i] = get_bits(4);
    m_comp_quant[i]  = get_bits(8);
  }
}

// Used to skip unrecognized markers.
void jpeg_decoder::skip_variable_marker()
{
  unsigned int num_left;

  num_left = get_bits(16);

  if (num_left < 2)
    stop_decoding(JPGD_BAD_VARIABLE_MARKER);

  num_left -= 2;

  while (num_left)
  {
    get_bits(8);
    num_left--;
  }
}

// Read a define restart interval (DRI) marker.
void jpeg_decoder::read_dri_marker()
{
  if (get_bits(16) != 4)
    stop_decoding(JPGD_BAD_DRI_LENGTH);

  m_restart_interval = get_bits(16);
}

// Read a start of scan (SOS) marker.
void jpeg_decoder::read_sos_marker()
{
  unsigned int num_left;
  int i, ci, n, c, cc;

  num_left = get_bits(16);

  n = get_bits(8);

  m_comps_in_scan = n;

  num_left -= 3;

  if ( (num_left != (unsigned int)(n * 2 + 3)) || (n < 1) || (n > JPGD_MAX_COMPS_IN_SCAN) )
    stop_decoding(JPGD_BAD_SOS_LENGTH);

  for (i = 0; i < n; i++)
  {
    cc = get_bits(8);
    c = get_bits(8);
    num_left -= 2;

    for (ci = 0; ci < m_comps_in_frame; ci++)
      if (cc == m_comp_ident[ci])
        break;

    if (ci >= m_comps_in_frame)
      stop_decoding(JPGD_BAD_SOS_COMP_ID);

    m_comp_list[i]    = ci;
    m_comp_dc_tab[ci] = (c >> 4) & 15;
    m_comp_ac_tab[ci] = (c & 15) + (JPGD_MAX_HUFF_TABLES >> 1);
  }

  m_spectral_start  = get_bits(8);
  m_spectral_end    = get_bits(8);
  m_successive_high = get_bits(4);
  m_successive_low  = get_bits(4);

  if (!m_progressive_flag)
  {
    m_spectral_start = 0;
    m_spectral_end = 63;
  }

  num_left -= 3;

  while (num_left)                  /* read past whatever is num_left */
  {
    get_bits(8);
    num_left--;
  }
}

// Finds the next marker.
int jpeg_decoder::next_marker()
{
  unsigned int c, bytes;

  bytes = 0;

  do
  {
    do
    {
      bytes++;
      c = get_bits(8);
    } while (c != 0xFF);

    do
    {
      c = get_bits(8);
    } while (c == 0xFF);

  } while (c == 0);

  // If bytes > 0 here, there where extra bytes before the marker (not good).

  return c;
}

// Process markers. Returns when an SOFx, SOI, EOI, or SOS marker is
// encountered.
int jpeg_decoder::process_markers()
{
  int c;

  for ( ; ; )
  {
    c = next_marker();

    switch (c)
    {
      case M_SOF0:
      case M_SOF1:
      case M_SOF2:
      case M_SOF3:
      case M_SOF5:
      case M_SOF6:
      case M_SOF7:
//      case M_JPG:
      case M_SOF9:
      case M_SOF10:
      case M_SOF11:
      case M_SOF13:
      case M_SOF14:
      case M_SOF15:
      case M_SOI:
      case M_EOI:
      case M_SOS:
      {
        return c;
      }
      case M_DHT:
      {
        read_dht_marker();
        break;
      }
      // No arithmitic support - dumb patents!
      case M_DAC:
      {
        stop_decoding(JPGD_NO_ARITHMITIC_SUPPORT);
        break;
      }
      case M_DQT:
      {
        read_dqt_marker();
        break;
      }
      case M_DRI:
      {
        read_dri_marker();
        break;
      }
      //case M_APP0:  /* no need to read the JFIF marker */

      case M_JPG:
      case M_RST0:    /* no parameters */
      case M_RST1:
      case M_RST2:
      case M_RST3:
      case M_RST4:
      case M_RST5:
      case M_RST6:
      case M_RST7:
      case M_TEM:
      {
        stop_decoding(JPGD_UNEXPECTED_MARKER);
        break;
      }
      default:    /* must be DNL, DHP, EXP, APPn, JPGn, COM, or RESn or APP0 */
      {
        skip_variable_marker();
        break;
      }
    }
  }
}

// Finds the start of image (SOI) marker.
// This code is rather defensive: it only checks the first 512 bytes to avoid
// false positives.
void jpeg_decoder::locate_soi_marker()
{
  unsigned int lastchar, thischar;
  unsigned int bytesleft;

  lastchar = get_bits(8);

  thischar = get_bits(8);

  /* ok if it's a normal JPEG file without a special header */

  if ((lastchar == 0xFF) && (thischar == M_SOI))
    return;

  bytesleft = 4096; //512;

  for ( ; ; )
  {
    if (--bytesleft == 0)
      stop_decoding(JPGD_NOT_JPEG);

    lastchar = thischar;

    thischar = get_bits(8);

    if (lastchar == 0xFF)
    {
      if (thischar == M_SOI)
        break;
      else if (thischar == M_EOI) // get_bits will keep returning M_EOI if we read past the end
        stop_decoding(JPGD_NOT_JPEG);
    }
  }

  // Check the next character after marker: if it's not 0xFF, it can't be the start of the next marker, so the file is bad.
  thischar = (m_bit_buf >> 24) & 0xFF;

  if (thischar != 0xFF)
    stop_decoding(JPGD_NOT_JPEG);
}

// Find a start of frame (SOF) marker.
void jpeg_decoder::locate_sof_marker()
{
  locate_soi_marker();

  int c = process_markers();

  switch (c)
  {
    case M_SOF2:
      m_progressive_flag = JPGD_TRUE;
    case M_SOF0:  /* baseline DCT */
    case M_SOF1:  /* extended sequential DCT */
    {
      read_sof_marker();
      break;
    }
    case M_SOF9:  /* Arithmitic coding */
    {
      stop_decoding(JPGD_NO_ARITHMITIC_SUPPORT);
      break;
    }
    default:
    {
      stop_decoding(JPGD_UNSUPPORTED_MARKER);
      break;
    }
  }
}

// Find a start of scan (SOS) marker.
int jpeg_decoder::locate_sos_marker()
{
  int c;

  c = process_markers();

  if (c == M_EOI)
    return JPGD_FALSE;
  else if (c != M_SOS)
    stop_decoding(JPGD_UNEXPECTED_MARKER);

  read_sos_marker();

  return JPGD_TRUE;
}

// Reset everything to default/uninitialized state.
void jpeg_decoder::init(jpeg_decoder_stream *pStream)
{
	m_pMem_blocks = NULL;
	m_error_code = JPGD_SUCCESS;
	m_ready_flag = false;
	m_image_x_size = m_image_y_size = 0;
	m_pStream = pStream;
	m_progressive_flag = JPGD_FALSE;

	extFunctions.CleanMem(m_huff_ac, sizeof(m_huff_ac));
	extFunctions.CleanMem(m_huff_num, sizeof(m_huff_num));
	extFunctions.CleanMem(m_huff_val, sizeof(m_huff_val));
	extFunctions.CleanMem(m_quant, sizeof(m_quant));

  m_scan_type = 0;
  m_comps_in_frame = 0;

	extFunctions.CleanMem(m_comp_h_samp, sizeof(m_comp_h_samp));
	extFunctions.CleanMem(m_comp_v_samp, sizeof(m_comp_v_samp));
	extFunctions.CleanMem(m_comp_quant, sizeof(m_comp_quant));
	extFunctions.CleanMem(m_comp_ident, sizeof(m_comp_ident));
	extFunctions.CleanMem(m_comp_h_blocks, sizeof(m_comp_h_blocks));
	extFunctions.CleanMem(m_comp_v_blocks, sizeof(m_comp_v_blocks));

  m_comps_in_scan = 0;
  extFunctions.CleanMem(m_comp_list, sizeof(m_comp_list));
  extFunctions.CleanMem(m_comp_dc_tab, sizeof(m_comp_dc_tab));
  extFunctions.CleanMem(m_comp_ac_tab, sizeof(m_comp_ac_tab));

  m_spectral_start = 0;
  m_spectral_end = 0;
  m_successive_low = 0;
  m_successive_high = 0;
  m_max_mcu_x_size = 0;
  m_max_mcu_y_size = 0;
  m_blocks_per_mcu = 0;
  m_max_blocks_per_row = 0;
  m_mcus_per_row = 0;
  m_mcus_per_col = 0;
  m_expanded_blocks_per_component = 0;
  m_expanded_blocks_per_mcu = 0;
  m_expanded_blocks_per_row = 0;
  m_freq_domain_chroma_upsample = false;

  extFunctions.CleanMem(m_mcu_org, sizeof(m_mcu_org));

  m_total_lines_left = 0;
  m_mcu_lines_left = 0;
  m_real_dest_bytes_per_scan_line = 0;
  m_dest_bytes_per_scan_line = 0;
  m_dest_bytes_per_pixel = 0;

  extFunctions.CleanMem(m_pHuff_tabs, sizeof(m_pHuff_tabs));

  extFunctions.CleanMem(m_dc_coeffs, sizeof(m_dc_coeffs));
  extFunctions.CleanMem(m_ac_coeffs, sizeof(m_ac_coeffs));
  extFunctions.CleanMem(m_block_y_mcu, sizeof(m_block_y_mcu));

  m_eob_run = 0;

  extFunctions.CleanMem(m_block_y_mcu, sizeof(m_block_y_mcu));

  m_pIn_buf_ofs = m_in_buf;
  m_in_buf_left = 0;
  m_eof_flag = false;
  m_tem_flag = 0;

  extFunctions.CleanMem(m_in_buf_pad_start, sizeof(m_in_buf_pad_start));
  extFunctions.CleanMem(m_in_buf, sizeof(m_in_buf));
  extFunctions.CleanMem(m_in_buf_pad_end, sizeof(m_in_buf_pad_end));

  m_restart_interval = 0;
  m_restarts_left    = 0;
  m_next_restart_num = 0;

  m_max_mcus_per_row = 0;
  m_max_blocks_per_mcu = 0;
  m_max_mcus_per_col = 0;

  extFunctions.CleanMem(m_last_dc_val, sizeof(m_last_dc_val));
  m_pMCU_coefficients = NULL;
  m_pSample_buf = NULL;

  m_total_bytes_read = 0;

  m_pScan_line_0 = NULL;
  m_pScan_line_1 = NULL;

  // Ready the input buffer.
  prep_in_buffer();

  // Prime the bit buffer.
  m_bits_left = 16;
  m_bit_buf = 0;

  get_bits(16);
  get_bits(16);

	for (int i = 0; i < JPGD_MAX_BLOCKS_PER_MCU; i++)
		m_mcu_block_max_zag[i] = 64;
}

#define SCALEBITS 16
#define ONE_HALF  ((int) 1 << (SCALEBITS-1))
#define FIX(x)    ((int) ((x) * (1L<<SCALEBITS) + 0.5f))

// Create a few tables that allow us to quickly convert YCbCr to RGB.
void jpeg_decoder::create_look_ups()
{
  for (int i = 0; i <= 255; i++)
  {
    int k = i - 128;
    m_crr[i] = ( FIX(1.40200f)  * k + ONE_HALF) >> SCALEBITS;
    m_cbb[i] = ( FIX(1.77200f)  * k + ONE_HALF) >> SCALEBITS;
    m_crg[i] = (-FIX(0.71414f)) * k;
    m_cbg[i] = (-FIX(0.34414f)) * k + ONE_HALF;
  }
}

// This method throws back into the stream any bytes that where read
// into the bit buffer during initial marker scanning.
void jpeg_decoder::fix_in_buffer()
{
  // In case any 0xFF's where pulled into the buffer during marker scanning.
  JPGD_ASSERT((m_bits_left & 7) == 0);

  if (m_bits_left == 16)
    stuff_char( (unsigned char)(m_bit_buf & 0xFF));

  if (m_bits_left >= 8)
    stuff_char( (unsigned char)((m_bit_buf >> 8) & 0xFF));

  stuff_char((unsigned char)((m_bit_buf >> 16) & 0xFF));
  stuff_char((unsigned char)((m_bit_buf >> 24) & 0xFF));

  m_bits_left = 16;
  get_bits_no_markers(16);
  get_bits_no_markers(16);
}

void jpeg_decoder::transform_mcu(int mcu_row)
{
  jpgd_block_t* pSrc_ptr = m_pMCU_coefficients;
  unsigned char* pDst_ptr = m_pSample_buf + mcu_row * m_blocks_per_mcu * 64;

  for (int mcu_block = 0; mcu_block < m_blocks_per_mcu; mcu_block++)
  {
    idct(pSrc_ptr, pDst_ptr, m_mcu_block_max_zag[mcu_block]);
    pSrc_ptr += 64;
    pDst_ptr += 64;
  }
}

static const unsigned char s_max_rc[64] =
{
  17, 18, 34, 50, 50, 51, 52, 52, 52, 68, 84, 84, 84, 84, 85, 86, 86, 86, 86, 86,
  102, 118, 118, 118, 118, 118, 118, 119, 120, 120, 120, 120, 120, 120, 120, 136,
  136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
  136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136
};

void jpeg_decoder::transform_mcu_expand(int mcu_row)
{
  jpgd_block_t* pSrc_ptr = m_pMCU_coefficients;
  unsigned char* pDst_ptr = m_pSample_buf + mcu_row * m_expanded_blocks_per_mcu * 64;

  // Y IDCT
	int mcu_block;
  for (mcu_block = 0; mcu_block < m_expanded_blocks_per_component; mcu_block++)
  {
    idct(pSrc_ptr, pDst_ptr, m_mcu_block_max_zag[mcu_block]);
    pSrc_ptr += 64;
    pDst_ptr += 64;
  }

  // Chroma IDCT, with upsampling
	jpgd_block_t temp_block[64];

	//long long s=extFunctions.TSC();

	for (int i = 0; i < 2; i++)
	{
		DCT_Upsample::Matrix44 P, Q, R, S;

		JPGD_ASSERT(m_mcu_block_max_zag[mcu_block] >= 1);
		JPGD_ASSERT(m_mcu_block_max_zag[mcu_block] <= 64);

		int max_zag = m_mcu_block_max_zag[mcu_block++] - 1; 
		if (max_zag <= 0) max_zag = 0; // should never happen, only here to shut up static analysis
		switch (s_max_rc[max_zag])
		{
		case 1*16+1:
		  DCT_Upsample::P_Q<1, 1>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<1, 1>::calc(R, S, pSrc_ptr);
		  break;
		case 1*16+2:
		  DCT_Upsample::P_Q<1, 2>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<1, 2>::calc(R, S, pSrc_ptr);
		  break;
		case 2*16+2:
		  DCT_Upsample::P_Q<2, 2>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<2, 2>::calc(R, S, pSrc_ptr);
		  break;
		case 3*16+2:
		  DCT_Upsample::P_Q<3, 2>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<3, 2>::calc(R, S, pSrc_ptr);
		  break;
		case 3*16+3:
		  DCT_Upsample::P_Q<3, 3>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<3, 3>::calc(R, S, pSrc_ptr);
		  break;
		case 3*16+4:
		  DCT_Upsample::P_Q<3, 4>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<3, 4>::calc(R, S, pSrc_ptr);
		  break;
		case 4*16+4:
		  DCT_Upsample::P_Q<4, 4>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<4, 4>::calc(R, S, pSrc_ptr);
		  break;
		case 5*16+4:
		  DCT_Upsample::P_Q<5, 4>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<5, 4>::calc(R, S, pSrc_ptr);
		  break;
		case 5*16+5:
		  DCT_Upsample::P_Q<5, 5>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<5, 5>::calc(R, S, pSrc_ptr);
		  break;
		case 5*16+6:
		  DCT_Upsample::P_Q<5, 6>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<5, 6>::calc(R, S, pSrc_ptr);
		  break;
		case 6*16+6:
		  DCT_Upsample::P_Q<6, 6>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<6, 6>::calc(R, S, pSrc_ptr);
		  break;
		case 7*16+6:
		  DCT_Upsample::P_Q<7, 6>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<7, 6>::calc(R, S, pSrc_ptr);
		  break;
		case 7*16+7:
		  DCT_Upsample::P_Q<7, 7>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<7, 7>::calc(R, S, pSrc_ptr);
		  break;
		case 7*16+8:
		  DCT_Upsample::P_Q<7, 8>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<7, 8>::calc(R, S, pSrc_ptr);
		  break;
		case 8*16+8:
		  DCT_Upsample::P_Q<8, 8>::calc(P, Q, pSrc_ptr);
		  DCT_Upsample::R_S<8, 8>::calc(R, S, pSrc_ptr);
		  break;
		default:
		  JPGD_ASSERT(false);
		}

		DCT_Upsample::Matrix44 a(P + Q); P -= Q;
		DCT_Upsample::Matrix44& b = P;
		DCT_Upsample::Matrix44 c(R + S); R -= S;
		DCT_Upsample::Matrix44& d = R;

		DCT_Upsample::Matrix44::add_and_store(temp_block, a, c);
		idct_4x4(temp_block, pDst_ptr);
		pDst_ptr += 64;

		DCT_Upsample::Matrix44::sub_and_store(temp_block, a, c);
		idct_4x4(temp_block, pDst_ptr);
		pDst_ptr += 64;

		DCT_Upsample::Matrix44::add_and_store(temp_block, b, d);
		idct_4x4(temp_block, pDst_ptr);
		pDst_ptr += 64;

		DCT_Upsample::Matrix44::sub_and_store(temp_block, b, d);
		idct_4x4(temp_block, pDst_ptr);
		pDst_ptr += 64;

		pSrc_ptr += 64;
	}

  	/*s=extFunctions.TSC()-s;
	double ds=s;
	csad::Log::console("-- %f",ds);*/
}

// Loads and dequantizes the next row of (already decoded) coefficients.
// Progressive images only.
void jpeg_decoder::load_next_row()
{
  int i;
  jpgd_block_t *p;
  jpgd_quant_t *q;
  int mcu_row, mcu_block, row_block = 0;
  int component_num, component_id;
  int block_x_mcu[JPGD_MAX_COMPONENTS];

  extFunctions.CleanMem(block_x_mcu, JPGD_MAX_COMPONENTS * sizeof(int));

  for (mcu_row = 0; mcu_row < m_mcus_per_row; mcu_row++)
  {
    int block_x_mcu_ofs = 0, block_y_mcu_ofs = 0;

    for (mcu_block = 0; mcu_block < m_blocks_per_mcu; mcu_block++)
    {
      component_id = m_mcu_org[mcu_block];
      q = m_quant[m_comp_quant[component_id]];

      p = m_pMCU_coefficients + 64 * mcu_block;

      jpgd_block_t* pAC = coeff_buf_getp(m_ac_coeffs[component_id], block_x_mcu[component_id] + block_x_mcu_ofs, m_block_y_mcu[component_id] + block_y_mcu_ofs);
      jpgd_block_t* pDC = coeff_buf_getp(m_dc_coeffs[component_id], block_x_mcu[component_id] + block_x_mcu_ofs, m_block_y_mcu[component_id] + block_y_mcu_ofs);
      p[0] = pDC[0];
	  extFunctions.MoveMem(&pAC[1],&p[1], 63 * sizeof(jpgd_block_t));

      for (i = 63; i > 0; i--)
        if (p[g_ZAG[i]])
          break;

      m_mcu_block_max_zag[mcu_block] = i + 1;

      for ( ; i >= 0; i--)
				if (p[g_ZAG[i]])
					p[g_ZAG[i]] = static_cast<jpgd_block_t>(p[g_ZAG[i]] * q[i]);

      row_block++;

      if (m_comps_in_scan == 1)
        block_x_mcu[component_id]++;
      else
      {
        if (++block_x_mcu_ofs == m_comp_h_samp[component_id])
        {
          block_x_mcu_ofs = 0;

          if (++block_y_mcu_ofs == m_comp_v_samp[component_id])
          {
            block_y_mcu_ofs = 0;

            block_x_mcu[component_id] += m_comp_h_samp[component_id];
          }
        }
      }
    }

    if (m_freq_domain_chroma_upsample)
      transform_mcu_expand(mcu_row);
    else
      transform_mcu(mcu_row);
  }

  if (m_comps_in_scan == 1)
    m_block_y_mcu[m_comp_list[0]]++;
  else
  {
    for (component_num = 0; component_num < m_comps_in_scan; component_num++)
    {
      component_id = m_comp_list[component_num];

      m_block_y_mcu[component_id] += m_comp_v_samp[component_id];
    }
  }
}

// Restart interval processing.
void jpeg_decoder::process_restart()
{
  int i;
  int c = 0;

  // Align to a byte boundry
  // FIXME: Is this really necessary? get_bits_no_markers() never reads in markers!
  //get_bits_no_markers(m_bits_left & 7);

  // Let's scan a little bit to find the marker, but not _too_ far.
  // 1536 is a "fudge factor" that determines how much to scan.
  for (i = 1536; i > 0; i--)
    if (get_char() == 0xFF)
      break;

  if (i == 0)
    stop_decoding(JPGD_BAD_RESTART_MARKER);

  for ( ; i > 0; i--)
    if ((c = get_char()) != 0xFF)
      break;

  if (i == 0)
    stop_decoding(JPGD_BAD_RESTART_MARKER);

  // Is it the expected marker? If not, something bad happened.
  if (c != (m_next_restart_num + M_RST0))
    stop_decoding(JPGD_BAD_RESTART_MARKER);

  // Reset each component's DC prediction values.
  extFunctions.CleanMem(&m_last_dc_val, m_comps_in_frame * sizeof(unsigned int));

  m_eob_run = 0;

  m_restarts_left = m_restart_interval;

  m_next_restart_num = (m_next_restart_num + 1) & 7;

  // Get the bit buffer going again...

  m_bits_left = 16;
  get_bits_no_markers(16);
  get_bits_no_markers(16);
}

static _FORCEINLINE int dequantize_ac(int c, int q) {	c *= q;	return c; }

// Decodes and dequantizes the next row of coefficients.
void jpeg_decoder::decode_next_row()
{
  int row_block = 0;

  for (int mcu_row = 0; mcu_row < m_mcus_per_row; mcu_row++)
  {
    if ((m_restart_interval) && (m_restarts_left == 0))
      process_restart();

    jpgd_block_t* p = m_pMCU_coefficients;
    for (int mcu_block = 0; mcu_block < m_blocks_per_mcu; mcu_block++, p += 64)
    {
      int component_id = m_mcu_org[mcu_block];
      jpgd_quant_t* q = m_quant[m_comp_quant[component_id]];

      int r, s;
      s = huff_decode(m_pHuff_tabs[m_comp_dc_tab[component_id]], r);
      s = JPGD_HUFF_EXTEND(r, s);

      m_last_dc_val[component_id] = (s += m_last_dc_val[component_id]);

      p[0] = static_cast<jpgd_block_t>(s * q[0]);

      int prev_num_set = m_mcu_block_max_zag[mcu_block];

      huff_tables *pH = m_pHuff_tabs[m_comp_ac_tab[component_id]];

      int k;
      for (k = 1; k < 64; k++)
      {
        int extra_bits;
        s = huff_decode(pH, extra_bits);

        r = s >> 4;
        s &= 15;

        if (s)
        {
          if (r)
          {
            if ((k + r) > 63)
              stop_decoding(JPGD_DECODE_ERROR);

            if (k < prev_num_set)
            {
              int n = JPGD_MIN(r, prev_num_set - k);
              int kt = k;
              while (n--)
                p[g_ZAG[kt++]] = 0;
            }

            k += r;
          }
          
          s = JPGD_HUFF_EXTEND(extra_bits, s);

          JPGD_ASSERT(k < 64);

          p[g_ZAG[k]] = static_cast<jpgd_block_t>(dequantize_ac(s, q[k])); //s * q[k];
        }
        else
        {
          if (r == 15)
          {
            if ((k + 16) > 64)
              stop_decoding(JPGD_DECODE_ERROR);

            if (k < prev_num_set)
            {
              int n = JPGD_MIN(16, prev_num_set - k);
              int kt = k;
              while (n--)
              {
                JPGD_ASSERT(kt <= 63);
                p[g_ZAG[kt++]] = 0;
              }
            }

            k += 16 - 1; // - 1 because the loop counter is k
            JPGD_ASSERT(p[g_ZAG[k]] == 0);
          }
          else
            break;
        }
      }

      if (k < prev_num_set)
      {
        int kt = k;
        while (kt < prev_num_set)
          p[g_ZAG[kt++]] = 0;
      }

      m_mcu_block_max_zag[mcu_block] = k;

      row_block++;
    }

    if (m_freq_domain_chroma_upsample)
      transform_mcu_expand(mcu_row);
    else
      transform_mcu(mcu_row);

    m_restarts_left--;
  }
}

// YCbCr H1V1 (1x1:1:1, 3 m_blocks per MCU) to RGB
void jpeg_decoder::H1V1Convert()
{
  int row = m_max_mcu_y_size - m_mcu_lines_left;
  unsigned char *d = m_pScan_line_0;
  unsigned char *s = m_pSample_buf + row * 8;

  for (int i = m_max_mcus_per_row; i > 0; i--)
  {
    for (int j = 0; j < 8; j++)
    {
      int y = s[j];
      int cb = s[64+j];
      int cr = s[128+j];

      d[0] = clamp(y + m_crr[cr]);
      d[1] = clamp(y + ((m_crg[cr] + m_cbg[cb]) >> 16));
      d[2] = clamp(y + m_cbb[cb]);
      d[3] = 255;

      d += 4;
    }

    s += 64*3;
  }
}

// YCbCr H2V1 (2x1:1:1, 4 m_blocks per MCU) to RGB
void jpeg_decoder::H2V1Convert()
{
  int row = m_max_mcu_y_size - m_mcu_lines_left;
  unsigned char *d0 = m_pScan_line_0;
  unsigned char *y = m_pSample_buf + row * 8;
  unsigned char *c = m_pSample_buf + 2*64 + row * 8;

  for (int i = m_max_mcus_per_row; i > 0; i--)
  {
    for (int l = 0; l < 2; l++)
    {
      for (int j = 0; j < 4; j++)
      {
        int cb = c[0];
        int cr = c[64];

        int rc = m_crr[cr];
        int gc = ((m_crg[cr] + m_cbg[cb]) >> 16);
        int bc = m_cbb[cb];

        int yy = y[j<<1];
        d0[0] = clamp(yy+rc);
        d0[1] = clamp(yy+gc);
        d0[2] = clamp(yy+bc);
        d0[3] = 255;

        yy = y[(j<<1)+1];
        d0[4] = clamp(yy+rc);
        d0[5] = clamp(yy+gc);
        d0[6] = clamp(yy+bc);
        d0[7] = 255;

        d0 += 8;

        c++;
      }
      y += 64;
    }

    y += 64*4 - 64*2;
    c += 64*4 - 8;
  }
}

// YCbCr H2V1 (1x2:1:1, 4 m_blocks per MCU) to RGB
void jpeg_decoder::H1V2Convert()
{
  int row = m_max_mcu_y_size - m_mcu_lines_left;
  unsigned char *d0 = m_pScan_line_0;
  unsigned char *d1 = m_pScan_line_1;
  unsigned char *y;
  unsigned char *c;

  if (row < 8)
    y = m_pSample_buf + row * 8;
  else
    y = m_pSample_buf + 64*1 + (row & 7) * 8;

  c = m_pSample_buf + 64*2 + (row >> 1) * 8;

  for (int i = m_max_mcus_per_row; i > 0; i--)
  {
    for (int j = 0; j < 8; j++)
    {
      int cb = c[0+j];
      int cr = c[64+j];

      int rc = m_crr[cr];
      int gc = ((m_crg[cr] + m_cbg[cb]) >> 16);
      int bc = m_cbb[cb];

      int yy = y[j];
      d0[0] = clamp(yy+rc);
      d0[1] = clamp(yy+gc);
      d0[2] = clamp(yy+bc);
      d0[3] = 255;

      yy = y[8+j];
      d1[0] = clamp(yy+rc);
      d1[1] = clamp(yy+gc);
      d1[2] = clamp(yy+bc);
      d1[3] = 255;

      d0 += 4;
      d1 += 4;
    }

    y += 64*4;
    c += 64*4;
  }
}

// YCbCr H2V2 (2x2:1:1, 6 m_blocks per MCU) to RGB
void jpeg_decoder::H2V2Convert()
{
	int row = m_max_mcu_y_size - m_mcu_lines_left;
	unsigned char *d0 = m_pScan_line_0;
	unsigned char *d1 = m_pScan_line_1;
	unsigned char *y;
	unsigned char *c;

	if (row < 8)
		y = m_pSample_buf + row * 8;
	else
		y = m_pSample_buf + 64*2 + (row & 7) * 8;

	c = m_pSample_buf + 64*4 + (row >> 1) * 8;

	for (int i = m_max_mcus_per_row; i > 0; i--)
	{
		for (int l = 0; l < 2; l++)
		{
			for (int j = 0; j < 8; j += 2)
			{
				int cb = c[0];
				int cr = c[64];

				int rc = m_crr[cr];
				int gc = ((m_crg[cr] + m_cbg[cb]) >> 16);
				int bc = m_cbb[cb];

				int yy = y[j];
				d0[0] = clamp(yy+rc);
				d0[1] = clamp(yy+gc);
				d0[2] = clamp(yy+bc);
				d0[3] = 255;

				yy = y[j+1];
				d0[4] = clamp(yy+rc);
				d0[5] = clamp(yy+gc);
				d0[6] = clamp(yy+bc);
				d0[7] = 255;

				yy = y[j+8];
				d1[0] = clamp(yy+rc);
				d1[1] = clamp(yy+gc);
				d1[2] = clamp(yy+bc);
				d1[3] = 255;

				yy = y[j+8+1];
				d1[4] = clamp(yy+rc);
				d1[5] = clamp(yy+gc);
				d1[6] = clamp(yy+bc);
				d1[7] = 255;

				d0 += 8;
				d1 += 8;

				c++;
			}
			y += 64;
		}

		y += 64*6 - 64*2;
		c += 64*6 - 8;
	}
}

// Y (1 block per MCU) to 8-bit grayscale
void jpeg_decoder::gray_convert()
{
  int row = m_max_mcu_y_size - m_mcu_lines_left;
  unsigned char *d = m_pScan_line_0;
  unsigned char *s = m_pSample_buf + row * 8;

  for (int i = m_max_mcus_per_row; i > 0; i--)
  {
    *(unsigned int *)d = *(unsigned int *)s;
    *(unsigned int *)(&d[4]) = *(unsigned int *)(&s[4]);

    s += 64;
    d += 8;
  }
}

void jpeg_decoder::expanded_convert()
{
  int row = m_max_mcu_y_size - m_mcu_lines_left;

  unsigned char* Py = m_pSample_buf + (row / 8) * 64 * m_comp_h_samp[0] + (row & 7) * 8;

  unsigned char* d = m_pScan_line_0;

  for (int i = m_max_mcus_per_row; i > 0; i--)
  {
    for (int k = 0; k < m_max_mcu_x_size; k += 8)
    {
      const int Y_ofs = k * 8;
      const int Cb_ofs = Y_ofs + 64 * m_expanded_blocks_per_component;
      const int Cr_ofs = Y_ofs + 64 * m_expanded_blocks_per_component * 2;
      for (int j = 0; j < 8; j++)
      {
        int y = Py[Y_ofs + j];
        int cb = Py[Cb_ofs + j];
        int cr = Py[Cr_ofs + j];

        d[0] = clamp(y + m_crr[cr]);
        d[1] = clamp(y + ((m_crg[cr] + m_cbg[cb]) >> 16));
        d[2] = clamp(y + m_cbb[cb]);
        d[3] = 255;

        d += 4;
      }
    }

    Py += 64 * m_expanded_blocks_per_mcu;
  }
}

// Find end of image (EOI) marker, so we can return to the user the exact size of the input stream.
void jpeg_decoder::find_eoi()
{
  if (!m_progressive_flag)
  {
    // Attempt to read the EOI marker.
    //get_bits_no_markers(m_bits_left & 7);

    // Prime the bit buffer
    m_bits_left = 16;
    get_bits(16);
    get_bits(16);

    // The next marker _should_ be EOI
    process_markers();
  }

  m_total_bytes_read -= m_in_buf_left;
}

int jpeg_decoder::decode(const void** pScan_line, unsigned int* pScan_line_len)
{
  if ((m_error_code) || (!m_ready_flag))
    return JPGD_FAILED;

  if (m_total_lines_left == 0)
    return JPGD_DONE;

  if (m_mcu_lines_left == 0)
  {
    if (setjmp(m_jmp_state))
      return JPGD_FAILED;

    if (m_progressive_flag)
      load_next_row();
    else
      decode_next_row();

    // Find the EOI marker if that was the last row.
    if (m_total_lines_left <= m_max_mcu_y_size)
      find_eoi();

    m_mcu_lines_left = m_max_mcu_y_size;
  }

  if (m_freq_domain_chroma_upsample)
  {
    expanded_convert();
    *pScan_line = m_pScan_line_0;
  }
  else
  {
    switch (m_scan_type)
    {
      case JPGD_YH2V2:
      {
        if ((m_mcu_lines_left & 1) == 0)
        {
          H2V2Convert();
          *pScan_line = m_pScan_line_0;
        }
        else
          *pScan_line = m_pScan_line_1;

        break;
      }
      case JPGD_YH2V1:
      {
        H2V1Convert();
        *pScan_line = m_pScan_line_0;
        break;
      }
      case JPGD_YH1V2:
      {
        if ((m_mcu_lines_left & 1) == 0)
        {
          H1V2Convert();
          *pScan_line = m_pScan_line_0;
        }
        else
          *pScan_line = m_pScan_line_1;

        break;
      }
      case JPGD_YH1V1:
      {
        H1V1Convert();
        *pScan_line = m_pScan_line_0;
        break;
      }
      case JPGD_GRAYSCALE:
      {
        gray_convert();
        *pScan_line = m_pScan_line_0;

        break;
      }
    }
  }

  *pScan_line_len = m_real_dest_bytes_per_scan_line;

  m_mcu_lines_left--;
  m_total_lines_left--;

  return JPGD_SUCCESS;
}

// Creates the tables needed for efficient Huffman decoding.
void jpeg_decoder::make_huff_table(int index, huff_tables *pH)
{
	int p, i, l, si;
	unsigned char huffsize[257];
	unsigned int huffcode[257];
	unsigned int code;
	unsigned int subtree;
	int code_size;
	int lastp;
	int nextfreeentry;
	int currententry;

  pH->ac_table = m_huff_ac[index] != 0;

  p = 0;

	for (l = 1; l <= 16; l++)
	{
		extFunctions.StocBMem(&huffsize[p],m_huff_num[index][l],l);
		p+=m_huff_num[index][l];
		//for (i = 1; i <= m_huff_num[index][l]; i++)
			//huffsize[p++] = static_cast<unsigned char>(l);
	}

  huffsize[p] = 0;

  lastp = p;

  code = 0;
  si = huffsize[0];
  p = 0;

  while (huffsize[p])
  {
    while (huffsize[p] == si)
    {
      huffcode[p++] = code;
      code++;
    }

    code <<= 1;
    si++;
  }

	extFunctions.CleanMem(pH->look_up, sizeof(pH->look_up));
	extFunctions.CleanMem(pH->look_up2, sizeof(pH->look_up2));
	extFunctions.CleanMem(pH->tree, sizeof(pH->tree));
	extFunctions.CleanMem(pH->code_size, sizeof(pH->code_size));

  nextfreeentry = -1;

  p = 0;

  while (p < lastp)
  {
    i = m_huff_val[index][p];
    code = huffcode[p];
    code_size = huffsize[p];

    pH->code_size[i] = static_cast<unsigned char>(code_size);

    if (code_size <= 8)
    {
      code <<= (8 - code_size);

      for (l = 1 << (8 - code_size); l > 0; l--)
      {
        JPGD_ASSERT(i < 256);

        pH->look_up[code] = i;

        bool has_extrabits = false;
				int extra_bits = 0;
        int num_extra_bits = i & 15;

        int bits_to_fetch = code_size;
        if (num_extra_bits)
        {
          int total_codesize = code_size + num_extra_bits;
          if (total_codesize <= 8)
          {
            has_extrabits = true;
            extra_bits = ((1 << num_extra_bits) - 1) & (code >> (8 - total_codesize));
            JPGD_ASSERT(extra_bits <= 0x7FFF);
            bits_to_fetch += num_extra_bits;
          }
        }

        if (!has_extrabits)
          pH->look_up2[code] = i | (bits_to_fetch << 8);
        else
          pH->look_up2[code] = i | 0x8000 | (extra_bits << 16) | (bits_to_fetch << 8);

        code++;
      }
    }
    else
    {
      subtree = (code >> (code_size - 8)) & 0xFF;

      currententry = pH->look_up[subtree];

      if (currententry == 0)
      {
        pH->look_up[subtree] = currententry = nextfreeentry;
        pH->look_up2[subtree] = currententry = nextfreeentry;

        nextfreeentry -= 2;
      }

      code <<= (16 - (code_size - 8));

      for (l = code_size; l > 9; l--)
      {
        if ((code & 0x8000) == 0)
          currententry--;

        if (pH->tree[-currententry - 1] == 0)
        {
          pH->tree[-currententry - 1] = nextfreeentry;

          currententry = nextfreeentry;

          nextfreeentry -= 2;
        }
        else
          currententry = pH->tree[-currententry - 1];

        code <<= 1;
      }

      if ((code & 0x8000) == 0)
        currententry--;

      pH->tree[-currententry - 1] = i;
    }

    p++;
  }
}

// Verifies the quantization tables needed for this scan are available.
void jpeg_decoder::check_quant_tables()
{
  for (int i = 0; i < m_comps_in_scan; i++)
    if (m_quant[m_comp_quant[m_comp_list[i]]] == NULL)
      stop_decoding(JPGD_UNDEFINED_QUANT_TABLE);
}

// Verifies that all the Huffman tables needed for this scan are available.
void jpeg_decoder::check_huff_tables()
{
  for (int i = 0; i < m_comps_in_scan; i++)
  {
    if ((m_spectral_start == 0) && (m_huff_num[m_comp_dc_tab[m_comp_list[i]]] == NULL))
      stop_decoding(JPGD_UNDEFINED_HUFF_TABLE);

    if ((m_spectral_end > 0) && (m_huff_num[m_comp_ac_tab[m_comp_list[i]]] == NULL))
      stop_decoding(JPGD_UNDEFINED_HUFF_TABLE);
  }

  for (int i = 0; i < JPGD_MAX_HUFF_TABLES; i++)
    if (m_huff_num[i])
    {
      if (!m_pHuff_tabs[i])
        m_pHuff_tabs[i] = (huff_tables *)alloc(sizeof(huff_tables));

      make_huff_table(i, m_pHuff_tabs[i]);
    }
}

// Determines the component order inside each MCU.
// Also calcs how many MCU's are on each row, etc.
void jpeg_decoder::calc_mcu_block_order()
{
  int component_num, component_id;
  int max_h_samp = 0, max_v_samp = 0;

  for (component_id = 0; component_id < m_comps_in_frame; component_id++)
  {
    if (m_comp_h_samp[component_id] > max_h_samp)
      max_h_samp = m_comp_h_samp[component_id];

    if (m_comp_v_samp[component_id] > max_v_samp)
      max_v_samp = m_comp_v_samp[component_id];
  }

  for (component_id = 0; component_id < m_comps_in_frame; component_id++)
  {
    m_comp_h_blocks[component_id] = ((((m_image_x_size * m_comp_h_samp[component_id]) + (max_h_samp - 1)) / max_h_samp) + 7) / 8;
    m_comp_v_blocks[component_id] = ((((m_image_y_size * m_comp_v_samp[component_id]) + (max_v_samp - 1)) / max_v_samp) + 7) / 8;
  }

  if (m_comps_in_scan == 1)
  {
    m_mcus_per_row = m_comp_h_blocks[m_comp_list[0]];
    m_mcus_per_col = m_comp_v_blocks[m_comp_list[0]];
  }
  else
  {
    m_mcus_per_row = (((m_image_x_size + 7) / 8) + (max_h_samp - 1)) / max_h_samp;
    m_mcus_per_col = (((m_image_y_size + 7) / 8) + (max_v_samp - 1)) / max_v_samp;
  }

  if (m_comps_in_scan == 1)
  {
    m_mcu_org[0] = m_comp_list[0];

    m_blocks_per_mcu = 1;
  }
  else
  {
    m_blocks_per_mcu = 0;

    for (component_num = 0; component_num < m_comps_in_scan; component_num++)
    {
      int num_blocks;

      component_id = m_comp_list[component_num];

      num_blocks = m_comp_h_samp[component_id] * m_comp_v_samp[component_id];

      while (num_blocks--)
        m_mcu_org[m_blocks_per_mcu++] = component_id;
    }
  }
}

// Starts a new scan.
int jpeg_decoder::init_scan()
{
  if (!locate_sos_marker())
    return JPGD_FALSE;

  calc_mcu_block_order();

  check_huff_tables();

  check_quant_tables();

  extFunctions.CleanMem(m_last_dc_val, m_comps_in_frame * sizeof(unsigned int));

  m_eob_run = 0;

  if (m_restart_interval)
  {
    m_restarts_left = m_restart_interval;
    m_next_restart_num = 0;
  }

  fix_in_buffer();

  return JPGD_TRUE;
}

// Starts a frame. Determines if the number of components or sampling factors
// are supported.
void jpeg_decoder::init_frame()
{
  int i;

  if (m_comps_in_frame == 1)
  {
    if ((m_comp_h_samp[0] != 1) || (m_comp_v_samp[0] != 1))
      stop_decoding(JPGD_UNSUPPORTED_SAMP_FACTORS);

    m_scan_type = JPGD_GRAYSCALE;
    m_max_blocks_per_mcu = 1;
    m_max_mcu_x_size = 8;
    m_max_mcu_y_size = 8;
  }
  else if (m_comps_in_frame == 3)
  {
    if ( ((m_comp_h_samp[1] != 1) || (m_comp_v_samp[1] != 1)) ||
         ((m_comp_h_samp[2] != 1) || (m_comp_v_samp[2] != 1)) )
      stop_decoding(JPGD_UNSUPPORTED_SAMP_FACTORS);

    if ((m_comp_h_samp[0] == 1) && (m_comp_v_samp[0] == 1))
    {
      m_scan_type = JPGD_YH1V1;

      m_max_blocks_per_mcu = 3;
      m_max_mcu_x_size = 8;
      m_max_mcu_y_size = 8;
    }
    else if ((m_comp_h_samp[0] == 2) && (m_comp_v_samp[0] == 1))
    {
      m_scan_type = JPGD_YH2V1;
      m_max_blocks_per_mcu = 4;
      m_max_mcu_x_size = 16;
      m_max_mcu_y_size = 8;
    }
    else if ((m_comp_h_samp[0] == 1) && (m_comp_v_samp[0] == 2))
    {
      m_scan_type = JPGD_YH1V2;
      m_max_blocks_per_mcu = 4;
      m_max_mcu_x_size = 8;
      m_max_mcu_y_size = 16;
    }
    else if ((m_comp_h_samp[0] == 2) && (m_comp_v_samp[0] == 2))
    {
      m_scan_type = JPGD_YH2V2;
      m_max_blocks_per_mcu = 6;
      m_max_mcu_x_size = 16;
      m_max_mcu_y_size = 16;
    }
    else
      stop_decoding(JPGD_UNSUPPORTED_SAMP_FACTORS);
  }
  else
    stop_decoding(JPGD_UNSUPPORTED_COLORSPACE);

  m_max_mcus_per_row = (m_image_x_size + (m_max_mcu_x_size - 1)) / m_max_mcu_x_size;
  m_max_mcus_per_col = (m_image_y_size + (m_max_mcu_y_size - 1)) / m_max_mcu_y_size;

  // These values are for the *destination* pixels: after conversion.
  if (m_scan_type == JPGD_GRAYSCALE)
    m_dest_bytes_per_pixel = 1;
  else
    m_dest_bytes_per_pixel = 4;

  m_dest_bytes_per_scan_line = ((m_image_x_size + 15) & 0xFFF0) * m_dest_bytes_per_pixel;

  m_real_dest_bytes_per_scan_line = (m_image_x_size * m_dest_bytes_per_pixel);

  // Initialize two scan line buffers.
  m_pScan_line_0 = (unsigned char *)alloc(m_dest_bytes_per_scan_line, true);
  if ((m_scan_type == JPGD_YH1V2) || (m_scan_type == JPGD_YH2V2))
    m_pScan_line_1 = (unsigned char *)alloc(m_dest_bytes_per_scan_line, true);

  m_max_blocks_per_row = m_max_mcus_per_row * m_max_blocks_per_mcu;

  // Should never happen
  if (m_max_blocks_per_row > JPGD_MAX_BLOCKS_PER_ROW)
    stop_decoding(JPGD_ASSERTION_ERROR);

  // Allocate the coefficient buffer, enough for one MCU
  m_pMCU_coefficients = (jpgd_block_t*)alloc(m_max_blocks_per_mcu * 64 * sizeof(jpgd_block_t));

  for (i = 0; i < m_max_blocks_per_mcu; i++)
    m_mcu_block_max_zag[i] = 64;

  m_expanded_blocks_per_component = m_comp_h_samp[0] * m_comp_v_samp[0];
  m_expanded_blocks_per_mcu = m_expanded_blocks_per_component * m_comps_in_frame;
  m_expanded_blocks_per_row = m_max_mcus_per_row * m_expanded_blocks_per_mcu;
	// Freq. domain chroma upsampling is only supported for H2V2 subsampling factor (the most common one I've seen).
  m_freq_domain_chroma_upsample = false;
#if JPGD_SUPPORT_FREQ_DOMAIN_UPSAMPLING
  m_freq_domain_chroma_upsample = (m_expanded_blocks_per_mcu == 4*3);
#endif

  if (m_freq_domain_chroma_upsample)
    m_pSample_buf = (unsigned char *)alloc(m_expanded_blocks_per_row * 64);
  else
    m_pSample_buf = (unsigned char *)alloc(m_max_blocks_per_row * 64);

  m_total_lines_left = m_image_y_size;

  m_mcu_lines_left = 0;

  create_look_ups();
}

// The coeff_buf series of methods originally stored the coefficients
// into a "virtual" file which was located in EMS, XMS, or a disk file. A cache
// was used to make this process more efficient. Now, we can store the entire
// thing in RAM.
jpeg_decoder::coeff_buf* jpeg_decoder::coeff_buf_open(int block_num_x, int block_num_y, int block_len_x, int block_len_y)
{
  coeff_buf* cb = (coeff_buf*)alloc(sizeof(coeff_buf));

  cb->block_num_x = block_num_x;
  cb->block_num_y = block_num_y;
  cb->block_len_x = block_len_x;
  cb->block_len_y = block_len_y;
  cb->block_size = (block_len_x * block_len_y) * sizeof(jpgd_block_t);
  cb->pData = (unsigned char *)alloc(cb->block_size * block_num_x * block_num_y, true);
  return cb;
}

inline jpgd_block_t *jpeg_decoder::coeff_buf_getp(coeff_buf *cb, int block_x, int block_y)
{
  JPGD_ASSERT((block_x < cb->block_num_x) && (block_y < cb->block_num_y));
  return (jpgd_block_t *)(cb->pData + block_x * cb->block_size + block_y * (cb->block_size * cb->block_num_x));
}

// The following methods decode the various types of m_blocks encountered
// in progressively encoded images.
void jpeg_decoder::decode_block_dc_first(jpeg_decoder *pD, int component_id, int block_x, int block_y)
{
  int s, r;
  jpgd_block_t *p = pD->coeff_buf_getp(pD->m_dc_coeffs[component_id], block_x, block_y);

  if ((s = pD->huff_decode(pD->m_pHuff_tabs[pD->m_comp_dc_tab[component_id]])) != 0)
  {
    r = pD->get_bits_no_markers(s);
    s = JPGD_HUFF_EXTEND(r, s);
  }

  pD->m_last_dc_val[component_id] = (s += pD->m_last_dc_val[component_id]);

  p[0] = static_cast<jpgd_block_t>(s << pD->m_successive_low);
}

void jpeg_decoder::decode_block_dc_refine(jpeg_decoder *pD, int component_id, int block_x, int block_y)
{
  if (pD->get_bits_no_markers(1))
  {
    jpgd_block_t *p = pD->coeff_buf_getp(pD->m_dc_coeffs[component_id], block_x, block_y);

    p[0] |= (1 << pD->m_successive_low);
  }
}

void jpeg_decoder::decode_block_ac_first(jpeg_decoder *pD, int component_id, int block_x, int block_y)
{
  int k, s, r;

  if (pD->m_eob_run)
  {
    pD->m_eob_run--;
    return;
  }

  jpgd_block_t *p = pD->coeff_buf_getp(pD->m_ac_coeffs[component_id], block_x, block_y);

  for (k = pD->m_spectral_start; k <= pD->m_spectral_end; k++)
  {
    s = pD->huff_decode(pD->m_pHuff_tabs[pD->m_comp_ac_tab[component_id]]);

    r = s >> 4;
    s &= 15;

    if (s)
    {
      if ((k += r) > 63)
        pD->stop_decoding(JPGD_DECODE_ERROR);

      r = pD->get_bits_no_markers(s);
      s = JPGD_HUFF_EXTEND(r, s);

      p[g_ZAG[k]] = static_cast<jpgd_block_t>(s << pD->m_successive_low);
    }
    else
    {
      if (r == 15)
      {
        if ((k += 15) > 63)
          pD->stop_decoding(JPGD_DECODE_ERROR);
      }
      else
      {
        pD->m_eob_run = 1 << r;

        if (r)
          pD->m_eob_run += pD->get_bits_no_markers(r);

        pD->m_eob_run--;

        break;
      }
    }
  }
}

void jpeg_decoder::decode_block_ac_refine(jpeg_decoder *pD, int component_id, int block_x, int block_y)
{
  int s, k, r;
  int p1 = 1 << pD->m_successive_low;
  int m1 = (-1) << pD->m_successive_low;
  jpgd_block_t *p = pD->coeff_buf_getp(pD->m_ac_coeffs[component_id], block_x, block_y);
  
  JPGD_ASSERT(pD->m_spectral_end <= 63);
  
  k = pD->m_spectral_start;
  
  if (pD->m_eob_run == 0)
  {
    for ( ; k <= pD->m_spectral_end; k++)
    {
      s = pD->huff_decode(pD->m_pHuff_tabs[pD->m_comp_ac_tab[component_id]]);

      r = s >> 4;
      s &= 15;

      if (s)
      {
        if (s != 1)
          pD->stop_decoding(JPGD_DECODE_ERROR);

        if (pD->get_bits_no_markers(1))
          s = p1;
        else
          s = m1;
      }
      else
      {
        if (r != 15)
        {
          pD->m_eob_run = 1 << r;

          if (r)
            pD->m_eob_run += pD->get_bits_no_markers(r);

          break;
        }
      }

      do
      {
        jpgd_block_t *this_coef = p + g_ZAG[k & 63];

        if (*this_coef != 0)
        {
          if (pD->get_bits_no_markers(1))
          {
            if ((*this_coef & p1) == 0)
            {
              if (*this_coef >= 0)
                *this_coef = static_cast<jpgd_block_t>(*this_coef + p1);
              else
                *this_coef = static_cast<jpgd_block_t>(*this_coef + m1);
            }
          }
        }
        else
        {
          if (--r < 0)
            break;
        }

        k++;

      } while (k <= pD->m_spectral_end);

      if ((s) && (k < 64))
      {
        p[g_ZAG[k]] = static_cast<jpgd_block_t>(s);
      }
    }
  }

  if (pD->m_eob_run > 0)
  {
    for ( ; k <= pD->m_spectral_end; k++)
    {
      jpgd_block_t *this_coef = p + g_ZAG[k & 63]; // logical AND to shut up static code analysis

      if (*this_coef != 0)
      {
        if (pD->get_bits_no_markers(1))
        {
          if ((*this_coef & p1) == 0)
          {
            if (*this_coef >= 0)
              *this_coef = static_cast<jpgd_block_t>(*this_coef + p1);
            else
              *this_coef = static_cast<jpgd_block_t>(*this_coef + m1);
          }
        }
      }
    }

    pD->m_eob_run--;
  }
}

// Decode a scan in a progressively encoded image.
void jpeg_decoder::decode_scan(pDecode_block_func decode_block_func)
{
  int mcu_row, mcu_col, mcu_block;
  int block_x_mcu[JPGD_MAX_COMPONENTS], m_block_y_mcu[JPGD_MAX_COMPONENTS];

  extFunctions.CleanMem(m_block_y_mcu, sizeof(m_block_y_mcu));

  for (mcu_col = 0; mcu_col < m_mcus_per_col; mcu_col++)
  {
    int component_num, component_id;

    extFunctions.CleanMem(block_x_mcu, sizeof(block_x_mcu));

    for (mcu_row = 0; mcu_row < m_mcus_per_row; mcu_row++)
    {
      int block_x_mcu_ofs = 0, block_y_mcu_ofs = 0;

      if ((m_restart_interval) && (m_restarts_left == 0))
        process_restart();

      for (mcu_block = 0; mcu_block < m_blocks_per_mcu; mcu_block++)
      {
        component_id = m_mcu_org[mcu_block];

        decode_block_func(this, component_id, block_x_mcu[component_id] + block_x_mcu_ofs, m_block_y_mcu[component_id] + block_y_mcu_ofs);

        if (m_comps_in_scan == 1)
          block_x_mcu[component_id]++;
        else
        {
          if (++block_x_mcu_ofs == m_comp_h_samp[component_id])
          {
            block_x_mcu_ofs = 0;

            if (++block_y_mcu_ofs == m_comp_v_samp[component_id])
            {
              block_y_mcu_ofs = 0;
              block_x_mcu[component_id] += m_comp_h_samp[component_id];
            }
          }
        }
      }

      m_restarts_left--;
    }

    if (m_comps_in_scan == 1)
      m_block_y_mcu[m_comp_list[0]]++;
    else
    {
      for (component_num = 0; component_num < m_comps_in_scan; component_num++)
      {
        component_id = m_comp_list[component_num];
        m_block_y_mcu[component_id] += m_comp_v_samp[component_id];
      }
    }
  }
}

// Decode a progressively encoded image.
void jpeg_decoder::init_progressive()
{
	int i;

	if (m_comps_in_frame == 4)
		stop_decoding(JPGD_UNSUPPORTED_COLORSPACE);

  // Allocate the coefficient buffers.
	for (i = 0; i < m_comps_in_frame; i++)
	{
		m_dc_coeffs[i] = coeff_buf_open(m_max_mcus_per_row * m_comp_h_samp[i], m_max_mcus_per_col * m_comp_v_samp[i], 1, 1);
		m_ac_coeffs[i] = coeff_buf_open(m_max_mcus_per_row * m_comp_h_samp[i], m_max_mcus_per_col * m_comp_v_samp[i], 8, 8);
	}

	for ( ; ; )
	{
		int dc_only_scan, refinement_scan;
		pDecode_block_func decode_block_func;

    if (!init_scan())
		break;

	dc_only_scan = (m_spectral_start == 0);
	refinement_scan = (m_successive_high != 0);

    if ((m_spectral_start > m_spectral_end) || (m_spectral_end > 63))
		stop_decoding(JPGD_BAD_SOS_SPECTRAL);

	if (dc_only_scan)
	{
		if (m_spectral_end)
			stop_decoding(JPGD_BAD_SOS_SPECTRAL);
    }
	else if (m_comps_in_scan != 1)  /* AC scans can only contain one component */
		stop_decoding(JPGD_BAD_SOS_SPECTRAL);

    if ((refinement_scan) && (m_successive_low != m_successive_high - 1))
      stop_decoding(JPGD_BAD_SOS_SUCCESSIVE);

    if (dc_only_scan)
    {
      if (refinement_scan)
        decode_block_func = decode_block_dc_refine;
      else
        decode_block_func = decode_block_dc_first;
    }
    else
    {
      if (refinement_scan)
        decode_block_func = decode_block_ac_refine;
      else
        decode_block_func = decode_block_ac_first;
    }

    decode_scan(decode_block_func);

    m_bits_left = 16;
    get_bits(16);
    get_bits(16);
  }

  m_comps_in_scan = m_comps_in_frame;

  for (i = 0; i < m_comps_in_frame; i++)
    m_comp_list[i] = i;

  calc_mcu_block_order();
}

void jpeg_decoder::init_sequential()
{
  if (!init_scan())
    stop_decoding(JPGD_UNEXPECTED_MARKER);
}

void jpeg_decoder::decode_start()
{
  init_frame();

  if (m_progressive_flag)
    init_progressive();
  else
    init_sequential();
}

void jpeg_decoder::decode_init(jpeg_decoder_stream *pStream)
{
  init(pStream);
  locate_sof_marker();
}

jpeg_decoder::jpeg_decoder(jpeg_decoder_stream *pStream)
{
  if (setjmp(m_jmp_state))
    return;
  decode_init(pStream);
}

int jpeg_decoder::begin_decoding()
{
  if (m_ready_flag)
    return JPGD_SUCCESS;

  if (m_error_code)
    return JPGD_FAILED;

  if (setjmp(m_jmp_state))
    return JPGD_FAILED;

  decode_start();

  m_ready_flag = true;

  return JPGD_SUCCESS;
}

jpeg_decoder::~jpeg_decoder()
{
  free_all_blocks();
}

unsigned char *decompress_jpeg_image_from_stream(jpeg_decoder_stream *pStream, int *width, int *height, int *actual_comps, int req_comps)
{
	if (!actual_comps)
		return NULL;
	*actual_comps = 0;

	if ((!pStream) || (!width) || (!height) || (!actual_comps))
		return NULL;

	jpeg_decoder decoder(pStream);
	if (decoder.get_error_code() != JPGD_SUCCESS)
		return NULL;

	const int image_width = decoder.get_width(), image_height = decoder.get_height();
	*width = image_width;
	*height = image_height;
	*actual_comps = decoder.get_num_components();

	if ((req_comps != 1) && (req_comps != 3) && (req_comps != 4))
		req_comps=*actual_comps;

	if (decoder.begin_decoding() != JPGD_SUCCESS)
		return NULL;

	const int dst_bpl = image_width * req_comps;

	unsigned char *pImage_data = (unsigned char*)jpgd_malloc(dst_bpl * image_height);
	if (!pImage_data)
		return NULL;

	for (int y = 0; y < image_height; y++)
	{
		const unsigned char* pScan_line;
		unsigned int scan_line_len;
		if (decoder.decode((const void**)&pScan_line, &scan_line_len) != JPGD_SUCCESS)
		{
			jpgd_free(pImage_data);
			return NULL;
		}

		unsigned char *pDst = pImage_data + y * dst_bpl;

		if (((req_comps == 1) && (decoder.get_num_components() == 1)) || ((req_comps == 4) && (decoder.get_num_components() == 3)))
			extFunctions.MoveMem((void*)pScan_line,pDst, dst_bpl);
		else if (decoder.get_num_components() == 1)
		{
			if (req_comps == 3)
			{
				for (int x = 0; x < image_width; x++)
				{
					unsigned char luma = pScan_line[x];
					pDst[0] = luma;
					pDst[1] = luma;
					pDst[2] = luma;
					pDst += 3;
				}
			} else {
				for (int x = 0; x < image_width; x++)
				{
					unsigned char luma = pScan_line[x];
					pDst[0] = luma;
					pDst[1] = luma;
					pDst[2] = luma;
					pDst[3] = 255;
					pDst += 4;
				}
			}
		}
		else if (decoder.get_num_components() == 3)
		{
			if (req_comps == 1)
			{
				const int YR = 19595, YG = 38470, YB = 7471;
				for (int x = 0; x < image_width; x++)
				{
					int r = pScan_line[x*4+0];
					int g = pScan_line[x*4+1];
					int b = pScan_line[x*4+2];
					*pDst++ = static_cast<unsigned char>((r * YR + g * YG + b * YB + 32768) >> 16);
				}
			} else {
				arvFunctions.A3BMove((void*)pScan_line,(void*)pDst,4,3,image_width);
			}
		}
	}

	return pImage_data;
}

} // namespace jpgd

OPTIMIZE_OFF;

#endif