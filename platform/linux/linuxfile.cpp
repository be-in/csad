/*
 * linuxfile.cpp
 *
 *  Created on: 20.08.2013
 *      Author: Panteleymonov Aleksandr
 */

#include <platform/platformapi.h>

#if defined (OS_LINUX)

#include <platform.h>
#include <bt.h>

OPTIMIZE_ON;

namespace csad {

File::File(IOType io)
{
	p_io=io;
	p_header=0;
	p_buff=new char[FILE_SIZE_BUFF];
	p_size_use=0;
	p_pos=0;
	p_clear=true;
}

File::File(char *name, IOType io)
{
	p_filename=name;
	p_io=io;
	p_header=0;
	p_buff=new char[FILE_SIZE_BUFF];
	p_size_use=0;
	p_pos=0;
	p_clear=true;
}

File::File(const char *name, IOType io)
{
	p_filename=name;
	p_io=io;
	p_header=0;
	p_buff=new char[FILE_SIZE_BUFF];
	p_size_use=0;
	p_pos=0;
	p_clear=true;
}

File::~File()
{
	delete p_buff;
}

bool File::open()
{
	int flag=0;
	if (p_io==READ) flag|=O_RDONLY;
	if (p_io==WRITE) flag|=O_WRONLY;
	if (p_io==READWRITE) flag|=O_RDWR;
	if (p_io==CREATE) flag|=O_CREAT;
	p_header=(void*)(_voidint)::open(p_filename.str(),flag);
	if ((_voidint)p_header == (_voidint)-1) {
		Log::console("File::open() error open file: %s",p_filename.str());
		return false;
	}
	return true;
}

bool File::close()
{
	::close((_voidint)p_header);
	p_header=0;
	p_size_use=0;
	p_pos=0;
	p_clear=true;
	return false;
}

void File::setFileName(char * name)
{
	p_filename=name;
}

const char *File::getFileName()
{
	return p_filename.str();
}

int File::read(void*data,int count)
{
	char *d=(char*)p_buff;
	d+=p_pos;
	if (p_clear) {
		if (FILE_SIZE_BUFF>count) {
			p_size_use=::read((_voidint)p_header,d,FILE_SIZE_BUFF);
			if (p_size_use<count) count=p_size_use;
			extFunctions.MoveMem(d,data,count);
			p_pos=count;
			p_clear=false;
			return count;
		} else {
			return ::read((_voidint)p_header,data,count);
		}
	} else {
		if (p_size_use-p_pos>count) {
			extFunctions.MoveMem(d,data,count);
			p_pos+=count;
			return count;
		} else {
			int nr=p_size_use-p_pos;
			char *r=(char*)data;
			int c=0;
			if (nr>0) {
				extFunctions.MoveMem(d,r,nr);
				r+=nr;
				count-=nr;
				c++;
			}
			p_clear=true;
			p_pos=0;
			p_size_use=0;
			return read(r,count)+c;
		}
	}
	return 0;
}

char* File::readAll()
{
	int msize=size();
	char *ret=new char[msize];
	if ((msize<=0) || (msize!=::read((_voidint)p_header,ret,msize))) {
		delete ret;
		return 0;
	}
	return ret;
}

int File::write(void*data,int count)
{
	::write((_voidint)p_header,data,count);
	return 0;
}

void File::setPos(_int64 pos,int from)
{
	int lform=SEEK_SET;
	if (from==BEGIN) lform=SEEK_SET;
	if (from==CURRENT) lform=SEEK_CUR;
	if (from==END) lform=SEEK_END;
	::lseek((_voidint)p_header,pos,lform);
}

_int64 File::getPos()
{
	return ::lseek((_voidint)p_header,0,SEEK_CUR);
}

int File::size()
{
	_int64 pos=::lseek((_voidint)p_header,0,SEEK_CUR);
	_int64 size=::lseek((_voidint)p_header,0,SEEK_END);
	::lseek((_voidint)p_header,pos,SEEK_SET);
	return size;
}

bool File::check(const char *name)
{
	void *header=(void*)(_voidint)::open(name,O_RDONLY);
	if ((_voidint)header == (_voidint)-1) {
		return false;
	}
	::close((_voidint)header);
	return true;
}

TYPEINFO(File)

}

OPTIMIZE_OFF;

#endif
