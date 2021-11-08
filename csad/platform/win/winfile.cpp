/*
 * winfile.cpp
 *
 *  Created on: 20.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include <platform.h>
#include <bt.h>
#include <WinBase.h>

OPTIMIZE_ON;

namespace csad {

File::File(IOType io)
{
	p_io=io;
	p_header=0;
	p_buff = (char*)extFunctions.CreateMem(FILE_SIZE_BUFF,0);
	p_size_use=0;
	p_pos=0;
	p_clear=true;
}

File::File(char *name, IOType io)
{
	p_filename=name;
	p_io=io;
	p_header=0;
	p_buff = (char*)extFunctions.CreateMem(FILE_SIZE_BUFF, 0);
	p_size_use=0;
	p_pos=0;
	p_clear=true;
}

File::File(const char *name, IOType io)
{
	p_filename=name;
	p_io=io;
	p_header=0;
	p_buff = (char*)extFunctions.CreateMem(FILE_SIZE_BUFF, 0);
	p_size_use=0;
	p_pos=0;
	p_clear=true;
}

File::~File()
{
	extFunctions.DeleteMem(p_buff,0);
}

bool File::open()
{
	unsigned int flag=0;
	if (p_io==READ) flag|=GENERIC_READ;
	if (p_io==WRITE) flag|=GENERIC_WRITE;
	if (p_io==READWRITE) flag|=GENERIC_READ | GENERIC_WRITE;
	if (p_io==CREATE) flag|=GENERIC_WRITE;
	if (p_io==CREATERW) flag|=GENERIC_READ | GENERIC_WRITE;
	
//	_OFSTRUCT stre;
	if (p_io==READ || p_io==WRITE || p_io==READWRITE) {
		p_header=(void*)CreateFileA(p_filename.str(),flag,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	} else {
		p_header=(void*)CreateFileA(p_filename.str(),flag,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
	}
	if ((HFILE)p_header == HFILE_ERROR) {
		int err=GetLastError();
#ifdef LOG_CSAD
		Log::console("File::open() error open file: %s err: %s",p_filename.str(),strerror(err));
#endif
		return false;
	}
	return true;
}

bool File::close()
{
	CloseHandle((HANDLE)p_header);
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
	if (!count) return 0;
	char *d=(char*)p_buff;
	if (p_clear) {
		if (FILE_SIZE_BUFF>count) {
			bool rt=ReadFile((HANDLE)p_header,d,FILE_SIZE_BUFF,(LPDWORD)&p_size_use,0)!=0;
			if (!rt) {
#ifdef LOG_CSAD
				Log::console("File::read() error read file: %s err: %i",p_filename.str(),GetLastError());
#endif
			}
			if (p_size_use<count) count=p_size_use;
			extFunctions.MoveMem(d,data,count);
			p_pos=count;
			p_clear=false;
			return count;
		} else {
			int rc=0;
			char *r=(char*)data;
			while (count>=FILE_SIZE_BUFF) {
				int ra;
				bool rt=ReadFile((HANDLE)p_header,r,FILE_SIZE_BUFF,(LPDWORD)&ra,0)!=0;
				if (!rt) {
#ifdef LOG_CSAD
					Log::console("File::read() error read file: %s err: %i",p_filename.str(),GetLastError());
#endif
				}
				r+=ra;
				rc+=ra;
				count-=FILE_SIZE_BUFF;
				/*if (rc!=count) {
					int err=ferror((::FILE*)p_header);
					if (err) {
						Log::console("File::read() error read file: %s err: %s",p_filename.str(),strerror(err));
						return rc;
					} else if (feof((::FILE*)p_header)) {
						Log::console("File::read() error read file: end of file");
						return rc;
					}
				}*/
			}
			return read(r,count)+rc;
		}
	} else {
		d+=p_pos;
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
				c+=nr;
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
	char *ret=(char*)extFunctions.CreateMem(msize,0);
	int rs;
	ReadFile((HANDLE)p_header,ret,msize,(LPDWORD)&rs,0);
	if ((msize<=0) || (msize!=rs)) {
		extFunctions.DeleteMem(ret,0);
		return 0;
	}
	return ret;
}

int File::write(void*data,int count)
{
	int rs;
	WriteFile((HANDLE)p_header,data,count,(LPDWORD)&rs,0);
	return rs;
}

void File::setPos(long long pos,int from)
{
	p_clear=true;
	int lform=FILE_BEGIN;
	if (from==BEGIN) lform=FILE_BEGIN;
	if (from==CURRENT) lform=FILE_CURRENT;
	if (from==END) lform=FILE_END;
	int *hipos=(int *)&pos;
	if (SetFilePointer((HANDLE)p_header,pos & 0xFFFFFFFF, (PLONG)(hipos+1), lform)==INVALID_SET_FILE_POINTER) 
    { 
#ifdef LOG_CSAD
        Log::console("File::setPos() error read file: %s err: %i",p_filename.str(),GetLastError());
#endif
    }
}

long long File::getPos()
{
	return 0;
}

int File::size()
{
	if (!p_header) return 0;
	int size = GetFileSize((HANDLE)p_header,0);
	return size;
}

bool File::check(const char *name)
{
	void *header=(void*)CreateFileA(name,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if ((HFILE)header != HFILE_ERROR) {
		CloseHandle((HANDLE)header);
		return true;
	}
	return false;
}

bt::ShortStringList File::getFileList(char *path,char *name,_int32 mode)
{
	bt::ShortStringList *list=new bt::ShortStringList();
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char buff[128];
	GetCurrentDirectory(127,buff);
	SetCurrentDirectory(path);
	hFind = FindFirstFile(name, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		bool find=true;
		while (find)
		{
			list->assign(FindFileData.cFileName);
			find=FindNextFile(hFind, &FindFileData);
		}
		FindClose(hFind);
	}
	SetCurrentDirectory(buff);
	return *list;
}

TYPEINFO(File)

}

OPTIMIZE_OFF;

#endif