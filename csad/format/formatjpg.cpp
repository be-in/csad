/*
 * formatjpg.cpp
 *
 *  Created on: 10.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(CSAD_JPEG) || defined(JPEG_CSAD)
#include <format.h>
#include <bt.h>
#include <platform.h>
#include <gen3.h>
#include "csad/btext/jpg/jpge.h"
#include "csad/btext/jpg/jpgd.h"

OPTIMIZE_ON;

namespace csad {

	class jpegDecodeFile:public jpgd::jpeg_decoder_stream {
	public:
		jpegDecodeFile() {}
		virtual ~jpegDecodeFile() {}

		int read(unsigned char *pBuf, int max_bytes_to_read, bool *pEOF_flag) {
			int ret=ffile->read(pBuf,max_bytes_to_read);
			if (max_bytes_to_read>ret) {
				*pEOF_flag=true;
			}
			return ret;
		}

		File *ffile;
	private:
	};

	class jpegEncodeFile : public jpge::output_stream
	{
	public:
		jpegEncodeFile() : ffile(NULL), m_bStatus(true) { }

		virtual ~jpegEncodeFile()
		{
			if (ffile) ffile->close();
		}

		virtual bool put_buf(const void* pBuf, int len)
		{
			if (ffile) {
				m_bStatus = m_bStatus && (ffile->write((void*)pBuf, len) == len);
				return m_bStatus;
			}
			return false;
		}

		File* ffile;
		bool m_bStatus;
	};

	FormatJPG::FormatJPG()
	{
		p_JPGImg=0;
		fBPP=0;
		fWidth=0;
		fHeight=0;
	}

	FormatJPG::~FormatJPG()
	{
		clear();
	}

	bool FormatJPG::readFromFile(char *name)
	{
		File file(name,File::READ);
		if (!file.open()) return false;
		readFromFile(&file);
		file.close();

		return true;
	}

	bool FormatJPG::readFromFile(File *file)
	{
		jpegDecodeFile jpgdf;
		jpgdf.ffile=file;

		p_JPGImg=jpgd::decompress_jpeg_image_from_stream(&jpgdf,&fWidth,&fHeight,&fBPP,0);
		if (!p_JPGImg) return false;
		//gen::ModellerRaster::revers(p_JPGImg,fWidth*fBPP,fHeight);
		return true;
	}

	bool FormatJPG::writeToFile(char *name,int qual)
	{
		File file(name,File::CREATE);
		if (!file.open()) return false;
		writeToFile(&file,qual);
		file.close();

		return true;
	}

	bool FormatJPG::writeToFile(File *file,int qual)
	{
		jpegEncodeFile jpgef;
		jpgef.ffile=file;

		jpge::params params;
		params.m_quality = qual;
		params.m_subsampling = jpge::H1V1;
		params.m_two_pass_flag = false;

		jpge::compress_image_to_jpeg_steam(&jpgef,fWidth, fHeight, fBPP, (const unsigned char*)p_JPGImg, params);
		
		if (!p_JPGImg) return false;
		//gen::ModellerRaster::revers(p_JPGImg,fWidth*fBPP,fHeight);
		return true;
	}

	void FormatJPG::setMatrix(int height,int width,int bpp,void *data)
	{
		fWidth=width;
		fHeight=height;
		fBPP=bpp;
		p_JPGImg=data;
	}

	void FormatJPG::clear()
	{
		if (p_JPGImg) free(p_JPGImg);
		p_JPGImg=0;
		fBPP=0;
		fWidth=0;
		fHeight=0;
	}

}

OPTIMIZE_OFF;

#endif