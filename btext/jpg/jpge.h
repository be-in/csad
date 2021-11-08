// jpge.h - C++ class for JPEG compression.
// Public domain, Rich Geldreich <richgel99@gmail.com>
// Alex Evans: Added RGBA support, linear memory allocator.
#if defined(CSAD_JPEG) || defined(JPEG_CSAD)
#ifndef JPEG_ENCODER_H
#define JPEG_ENCODER_H

#include <bt/macroscall.h>

OPTIMIZE_ON;

namespace jpge
{
  typedef unsigned char  uint8;
  typedef signed short   int16;
  typedef signed int     int32;
  typedef unsigned short uint16;
  typedef unsigned int   uint32;
  typedef unsigned int   uint;
  
  // JPEG chroma subsampling factors. Y_ONLY (grayscale images) and H2V2 (color images) are the most common.
  enum subsampling_t { Y_ONLY = 0, H1V1 = 1, H2V1 = 2, H2V2 = 3 };

  // JPEG compression parameters structure.
  struct params
  {
    _FORCEINLINE params() : m_quality(85), m_subsampling(H2V2), m_no_chroma_discrim_flag(false), m_two_pass_flag(false) { }

    _FORCEINLINE bool check() const
    {
      if ((m_quality < 1) || (m_quality > 100)) return false;
      if ((uint)m_subsampling > (uint)H2V2) return false;
      return true;
    }

    // Quality: 1-100, higher is better. Typical values are around 50-95.
    int m_quality;

    // m_subsampling:
    // 0 = Y (grayscale) only
    // 1 = YCbCr, no subsampling (H1V1, YCbCr 1x1x1, 3 blocks per MCU)
    // 2 = YCbCr, H2V1 subsampling (YCbCr 2x1x1, 4 blocks per MCU)
    // 3 = YCbCr, H2V2 subsampling (YCbCr 4x1x1, 6 blocks per MCU-- very common)
    subsampling_t m_subsampling;

    // Disables CbCr discrimination - only intended for testing.
    // If true, the Y quantization table is also used for the CbCr channels.
    bool m_no_chroma_discrim_flag;

    bool m_two_pass_flag;
  };
  
  // Output stream abstract class - used by the jpeg_encoder class to write to the output stream. 
  // put_buf() is generally called with len==JPGE_OUT_BUF_SIZE bytes, but for headers it'll be called with smaller amounts.
  class output_stream
  {
  public:
    virtual ~output_stream() { };
    virtual bool put_buf(const void* Pbuf, int len) = 0;
    template<class T> inline bool put_obj(const T& obj) { return put_buf(&obj, sizeof(T)); }
  };
    
	bool compress_image_to_jpeg_steam(output_stream *pStream, int width, int height, int num_channels, const unsigned char *pImage_data, const params &comp_params);

  // Lower level jpeg_encoder class - useful if more control is needed than the above helper functions.
  class jpeg_encoder
  {
  public:
    jpeg_encoder();
    ~jpeg_encoder();

    // Initializes the compressor.
    // pStream: The stream object to use for writing compressed data.
    // params - Compression parameters structure, defined above.
    // width, height  - Image dimensions.
    // channels - May be 1, or 3. 1 indicates grayscale, 3 indicates RGB source data.
    // Returns false on out of memory or if a stream write fails.
    bool init(output_stream *pStream, int width, int height, int src_channels, const params &comp_params = params());
    
    const params &get_params() const { return m_params; }
    
    // Deinitializes the compressor, freeing any allocated memory. May be called at any time.
    void deinit();

    uint get_total_passes() const { return m_params.m_two_pass_flag ? 2 : 1; }
    _FORCEINLINE uint get_cur_pass() { return m_pass_num; }

    // Call this method with each source scanline.
    // width * src_channels bytes per scanline is expected (RGB or Y format).
    // You must call with NULL after all scanlines are processed to finish compression.
    // Returns false on out of memory or if a stream write fails.
    bool process_scanline(const void* pScanline);
        
  private:
    jpeg_encoder(const jpeg_encoder &);
    jpeg_encoder &operator =(const jpeg_encoder &);

    typedef int32 sample_array_t;
        
    output_stream *m_pStream;
    params m_params;
    unsigned char m_num_components;
    unsigned char m_comp_h_samp[3], m_comp_v_samp[3];
    int m_image_x, m_image_y, m_image_bpp, m_image_bpl;
    int m_image_x_mcu, m_image_y_mcu;
    int m_image_bpl_xlt, m_image_bpl_mcu;
    int m_mcus_per_row;
    int m_mcu_x, m_mcu_y;
    unsigned char *m_mcu_lines[16];
    unsigned char m_mcu_y_ofs;
    sample_array_t m_sample_array[64];
    int16 m_coefficient_array[64];
    int32 m_quantization_tables[2][64];
    uint m_huff_codes[4][256];
    unsigned char m_huff_code_sizes[4][256];
    unsigned char m_huff_bits[4][17];
    unsigned char m_huff_val[4][256];
    uint32 m_huff_count[4][256];
    int m_last_dc_val[3];
    enum { JPGE_OUT_BUF_SIZE = 2048 };
    unsigned char m_out_buf[JPGE_OUT_BUF_SIZE];
    unsigned char *m_pOut_buf;
    uint m_out_buf_left;
    uint32 m_bit_buffer;
    uint m_bits_in;
    unsigned char m_pass_num;
    bool m_all_stream_writes_succeeded;
        
    void optimize_huffman_table(int table_num, int table_len);
    void emit_byte(unsigned char i);
    void emit_word(uint i);
    void emit_marker(int marker);
    void emit_jfif_app0();
    void emit_dqt();
    void emit_sof();
    void emit_dht(unsigned char *bits, unsigned char *val, int index, bool ac_flag);
    void emit_dhts();
    void emit_sos();
    void emit_markers();
    void compute_huffman_table(uint *codes, unsigned char *code_sizes, unsigned char *bits, unsigned char *val);
    void compute_quant_table(int32 *dst, int16 *src);
    void adjust_quant_table(int32 *dst, int32 *src);
    void first_pass_init();
    bool second_pass_init();
    bool jpg_open(int p_x_res, int p_y_res, int src_channels);
    void load_block_8_8_grey(int x);
    void load_block_8_8(int x, int y, int c);
    void load_block_16_8(int x, int c);
    void load_block_16_8_8(int x, int c);
    void load_quantized_coefficients(int component_num);
    void flush_output_buffer();
    void put_bits(uint bits, uint len);
    void code_coefficients_pass_one(int component_num);
    void code_coefficients_pass_two(int component_num);
    void code_block(int component_num);
    void process_mcu_row();
    bool terminate_pass_one();
    bool terminate_pass_two();
    bool process_end_of_image();
    void load_mcu(const void* src);
    void clear();
    void init();
  };

} // namespace jpge

OPTIMIZE_OFF;

#endif // JPEG_ENCODER
#endif