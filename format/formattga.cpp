/*
 * formattga.cpp
 *
 *  Created on: 10.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#if defined(TGA_JPEG) || defined(TGA_CSAD)
#include <format.h>
#include <bt.h>
#include <platform.h>
#include <gen3.h>

OPTIMIZE_ON;

namespace csad {

void MoveRLE(void *Surse, void *Dest, int size, int BPP);
void SwapBGR(void *Surse, int size, int BPP);

FormatTGA::FormatTGA()
{
	p_TGAImg=0;
	p_BytePP=0;
}

FormatTGA::~FormatTGA()
{
	if (p_TGAImg) delete (char*)p_TGAImg;
}

bool FormatTGA::readFromFile(char *name)
{
	File file(name,File::READ);
	if (!file.open()) return false;
	readFromFile(&file);
	file.close();

	return true;
}

bool FormatTGA::readFromFile(File *file)
{
	int size=file->size();
	if (size<(int)sizeof(p_TGA)) return false;
	file->read(&p_TGA,sizeof(p_TGA));
	size-=sizeof(p_TGA)-p_TGA.dLeight;
	if (size<0) return false;
	if (!_create()) return false;
	char *dataL=new char[p_TGA.dLeight];
	file->read(dataL,p_TGA.dLeight);
	char *data=new char[size];
	if (size!=file->read(data,size)) {
		delete data;
		delete dataL;
		return false;
	}

	bool ret=true;
	if (p_TGA.DataType==0x2) {
		extFunctions.MoveMem(data,p_TGAImg,p_ImgSize);
	} else if (p_TGA.DataType==0xA) {
		MoveRLE(data,p_TGAImg,p_ImgSize,p_BytePP);
	} else ret=false;

	if (ret) SwapBGR(p_TGAImg,p_ImgSize,p_BytePP);
	
	if ((p_TGA.Description & 0x20)!=0) {
		gen::ModellerRaster::revers(p_TGAImg,p_TGA.Width*p_BytePP,p_TGA.Height);
	}

	delete data;
	delete dataL;

	return ret;
}

void FormatTGA::clear()
{
	if (p_TGAImg) delete (char*)p_TGAImg;
	p_TGAImg=0;
	p_BytePP=0;
}

bool FormatTGA::_create()
{
	if ((p_TGA.BPP==16) || (p_TGA.BPP==15)) {
		p_ImgPixels=p_TGA.Height*p_TGA.Width;
		p_BytePP=2;
	} else if (p_TGA.BPP==24) {
		p_ImgPixels=p_TGA.Height*p_TGA.Width;
		p_BytePP=3;
	} else if (p_TGA.BPP==32) {
		p_ImgPixels=p_TGA.Height*p_TGA.Width;
		p_BytePP=4;
	} else {
		p_BytePP=0;
		p_ImgPixels=0;
	}
	p_ImgSize=p_ImgPixels*p_BytePP;
	if (p_ImgSize<=0) return false;
	if (p_TGAImg) delete (char*)p_TGAImg;
	p_TGAImg=new char[p_ImgSize];
	return true;
}

//*************************************************************************

//*************************************************************************

void RLEcopy16(void **Surse,void **Dest,int *all,int copy)
{
	copy&=0x7F;
	copy++;
	copy=copy<<1;
	*all-=copy;
	extFunctions.StocSMem(*Dest,copy>>1,*(unsigned short *)*Surse);
	char **c=(char **)Surse;
	*c+=2;
	c=(char **)Dest;
	*c+=copy;
}

void RLEcopy24(void **Surse,void **Dest,int *all,int copy)
{
	copy&=0x7F;
	copy++;
	copy=(copy<<1)+copy;
	*all-=copy;
	char *cc=(char *)*Surse;
	char **c=(char **)Dest;
	while (copy>0) {
		**c=cc[0];
		*c+=1;
		**c=cc[1];
		*c+=1;
		**c=cc[2];
		*c+=1;
		copy-=3;
	}
	c=(char **)Surse;
	*c+=3;
}

void RLEcopy32(void **Surse,void **Dest,int *all,int copy)
{
	copy&=0x7F;
	copy++;
	copy=copy<<2;
	*all-=copy;
	extFunctions.StocIMem(*Dest,copy>>2,*(unsigned int *)*Surse);
	char **c=(char **)Surse;
	*c+=4;
	c=(char **)Dest;
	*c+=copy;
}

void RLEmove16(void **Surse,void **Dest,int *all,int copy)
{
	copy&=0x7F;
	copy++;
	copy=copy<<1;
	*all-=copy;
	extFunctions.MoveMem(*Surse,*Dest,copy);
	char **c=(char **)Surse;
	*c+=copy;
	c=(char **)Dest;
	*c+=copy;
}

void RLEmove24(void **Surse,void **Dest,int *all,int copy)
{
	copy&=0x7F;
	copy++;
	copy=(copy<<1)+copy;
	*all-=copy;
	extFunctions.MoveMem(*Surse,*Dest,copy);
	char **c=(char **)Surse;
	*c+=copy;
	c=(char **)Dest;
	*c+=copy;
}

void RLEmove32(void **Surse,void **Dest,int *all,int copy)
{
	copy&=0x7F;
	copy++;
	copy=copy<<2;
	*all-=copy;
	extFunctions.MoveMem(*Surse,*Dest,copy);
	char **c=(char **)Surse;
	*c+=copy;
	c=(char **)Dest;
	*c+=copy;
}

void MoveRLE(void *Surse, void *Dest, int size, int BPP)
{
	if ((BPP<=0) || (BPP>4)) return;
	void (*RLEcopy)(void **Surse,void **Dest,int *all,int copy)=0;
	void (*RLEmove)(void **Surse,void **Dest,int *all,int copy)=0;
	if (BPP==2) {
		RLEcopy=RLEcopy16;
		RLEmove=RLEmove16;
	} else if (BPP==3) {
		RLEcopy=RLEcopy24;
		RLEmove=RLEmove24;
	} else if (BPP==4) {
		RLEcopy=RLEcopy32;
		RLEmove=RLEmove32;
	}

	unsigned char *sr=(unsigned char *)Surse;
	if ((RLEcopy) && (RLEmove))
	while (size) {
		unsigned int c=*sr;
		sr++;
		if ((c & 0x80)!=0) {
			RLEcopy((void**)&sr,&Dest,&size,c);
		} else {
			RLEmove((void**)&sr,&Dest,&size,c);
		}
	}
}

void Swap16BGR(void *Surse,int all)
{
	unsigned short *d=(unsigned short *)Surse;
	unsigned short *cd=d;
	cd+=(all>>1);
	while (d<cd) {
		*d=(*d &0x07E0) | (*d>>11) | (*d<<11);
		d++;
	}
}

void Swap24BGR(void *Surse,int all)
{
	char *d=(char *)Surse;
	char *cd=d;
	cd+=all;
	char c;
	while (d<cd) {
		c=d[0];
		d[0]=d[2];
		d[2]=c;
		d+=3;
	}
}

void Swap32BGR(void *Surse,int all)
{
	char *d=(char *)Surse;
	char *cd=d;
	cd+=all;
	char c;
	while (d<cd) {
		c=d[0];
		d[0]=d[2];
		d[2]=c;
		d+=4;
	}
}

void SwapBGR(void *Surse, int size, int BPP)
{
	if ((BPP<2) || (BPP>4)) return;
	void (*SwapBPPBGR)(void *Surse,int all)=0;
	if (BPP==2) {
		SwapBPPBGR=Swap16BGR;
	} else if (BPP==3) {
		SwapBPPBGR=Swap24BGR;
	} else if (BPP==4) {
		SwapBPPBGR=Swap32BGR;
	}

	SwapBPPBGR(Surse,size);
}

}

OPTIMIZE_OFF;

#endif