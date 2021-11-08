/*
 * linuxdisplay.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr
 */

#include <platform/platformapi.h>

#if defined (OS_LINUX)

#include "csad/platform/localdisplay.h"
#include "csad/platform/base/basesoftrender.h"
#include <platform.h>
#include <bt.h>
#include <core/graph.h>
#include <core/module.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/extensions/XShm.h>
#include <sys/shm.h>

OPTIMIZE_ON;

namespace csad {

using namespace bt;

GlContext * LocalDisplay::getContext(char *name)
{
	return (GlContext*)p_context.getObject(name);
}

void LocalDisplay::addContext(GlContext * context,char * name)
{
	p_context.addObject(context,name);
}

void *LocalDisplay::getHandle()
{
	return (void *)p_display.surface;
}

void *LocalDisplay::getBase()
{
	return (void *)p_display.display;
}

void LocalDisplay::SetVSync(bool val)
{
	if (val!=(p_display.flag&VSYNC)) {
		p_display.flag^=VSYNC;
	}
}

void LocalDisplay::SetHM(bool val)
{
	if (val!=(p_display.flag&HARDWAREMOUSE)) {
		p_display.flag^=HARDWAREMOUSE;
		//SetFocus(p_display.surface);
		//ShowCursor(val);
	}
}

void LocalDisplay::SetWindowed(bool val)
{
	if (val!=(p_display.flag&WINDOWED)) {
		p_display.flag^=WINDOWED;
	}
}

void LocalDisplay::SetTitle(char *title)
{
	//SetWindowTitle();
}

bool LocalDisplay::isVSync()
{
	return ((p_display.flag&VSYNC)!=0);
}

/*void Display::offGlContexts()
{
	Render::MakeCurrent(this,0);
	GlContext::p_current=0;
}*/

bool LocalDisplay::isGlobalPoint(vector2i*pos)
{
	if (p_display.posx>pos->x) return false;
	if (p_display.posx+p_display.xres<=pos->x) return false;
	if (p_display.posy>pos->y) return false;
	if (p_display.posy+p_display.yres<=pos->y) return false;
	return true;
}

int LocalDisplay::width()
{
	return p_display.xres;
}

int LocalDisplay::height()
{
	return p_display.yres;
}

int LocalDisplay::left()
{
	return p_display.posx;
}

int LocalDisplay::top() 
{
	return p_display.posy;
}

void LocalDisplay::setSize(bt::vector4i &size)
{
}

void LocalDisplay::toLocal(vector2f*global,vector2f*local)
{
	local->x=global->x-p_display.posx;//-p_display->xres*0.5f;
	local->y=global->y-p_display.posy;//p_display->yres*0.5f-global->y+p_display->posy;
}

void LocalDisplay::toLocal(vector2i*global,vector2i*local)
{
	local->x=global->x-p_display.posx;//-p_display->xres*0.5f;
	local->y=global->y-p_display.posy;//p_display->yres*0.5f-global->y+p_display->posy;
}

/*void LocalDisplay::swapBuffers()
{
	Render::Buffers(this);
}*/

void LocalDisplay::softDraw()
{
	softDisplay *sd=(softDisplay *)ffunctions.soft;
	if (!sd) return;
	if (!sd->colorOffset) return;
	GC gc = XCreateGC( p_display.display, p_display.surface, 0, NULL );
	if (gc!=NULL) {
		XShmPutImage(p_display.display,p_display.surface,gc,(XImage*)(sd->obj),0,0,0,0,p_display.xres,p_display.yres,false);
		XFreeGC( p_display.display, gc );
	}
}

bool LocalDisplay::_choosePixelFormat(Display * display,bool format,bool gl,int r,int g,int b,int a,int depth,int stencil,int sample)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;

	int size=3;
	if (gl) size+=2;
	if (r>0) size+=2;
	if (g>0) size+=2;
	if (b>0) size+=2;
	if (a>0) size+=2;
	if (depth>0) size+=2;
	if (stencil>0) size+=2;

	int *attribute_list = new int[size];
	int index=0;
	attribute_list[index]=GLX_RGBA;
	index++;
	attribute_list[index]=GLX_DOUBLEBUFFER;
	index++;
	if (gl) {
		attribute_list[index]=GLX_USE_GL;
		attribute_list[index+1]=1;
		index+=2;
	}
	if (r>0) {
		attribute_list[index]=GLX_RED_SIZE;
		attribute_list[index+1]=r;
		index+=2;
	}
	if (g>0) {
		attribute_list[index]=GLX_GREEN_SIZE;
		attribute_list[index+1]=g;
		index+=2;
	}
	if (b>0) {
		attribute_list[index]=GLX_BLUE_SIZE;
		attribute_list[index+1]=b;
		index+=2;
	}
	if (a>0) {
		attribute_list[index]=GLX_ALPHA_SIZE;
		attribute_list[index+1]=a;
		index+=2;
	}
	if (depth>0) {
		attribute_list[index]=GLX_DEPTH_SIZE;
		attribute_list[index+1]=depth;
		index+=2;
	}
	if (stencil>0) {
		attribute_list[index]=GLX_STENCIL_SIZE;
		attribute_list[index+1]=stencil;
		index+=2;
	}
	attribute_list[index]=None;

	Module *module=glLib();
	bt::tfSTDCALL_p_FUNC_p_int_p ChooseVisual=(bt::tfSTDCALL_p_FUNC_p_int_p)module->getProc("glXChooseVisual");
	mdisplay->vi = (XVisualInfo*)ChooseVisual( mdisplay->display, mdisplay->scrnum, attribute_list );

	delete[] attribute_list;

	if (!mdisplay->vi) return false;

	return true;
}

bool LocalDisplay::_createDisplay(Display * display,int devid,int dispid)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;

	Atom wmDelete;
	bt::BaseShortString str=":";
	char buff[16];
	csad::Log::tocahr(buff,15,"%i",devid);
	str+=buff;
	str+='.';
	csad::Log::tocahr(buff,15,"%i",dispid);
	str+=buff;

	mdisplay->display = XOpenDisplay(str.str());

	if (!mdisplay->display) {
		Log::console("Error: couldn't open display %s\n", str.str());
		return false;
	}

	mdisplay->vi=0;
	mdisplay->scrnum = DefaultScreen( mdisplay->display );
	unsigned _int32 mode=((LocalDisplay*)display)->ffunctions.mode;

	if ((mode&0xFF)!=0) {
		if (_choosePixelFormat(display,true,true,8,8,8,8,32,0,1)) {
			Log::console("PixelFormat: 32 bit Depth 32 bit Antialiasing GL enable");
		} else if (_choosePixelFormat(display,true,true,8,8,8,8,24,0,1)) {
			Log::console("PixelFormat: 32 bit Depth 24 bit Antialiasing GL enable");
		} else if (_choosePixelFormat(display,true,true,8,8,8,8,16,0,1)) {
			Log::console("PixelFormat: 32 bit Depth 16 bit Antialiasing GL enable");
		} else if (_choosePixelFormat(display,true,true,8,8,8,8,16,0,0)) {
			Log::console("PixelFormat: 32 bit Depth 16 bit GL enable");
		} else if (_choosePixelFormat(display,true,true,8,8,8,0,16,0,0)) {
			Log::console("PixelFormat: 24 bit Depth 16 bit GL enable");
		} else if (_choosePixelFormat(display,true,true,4,4,4,4,16,0,0)) {
			Log::console("PixelFormat: 16 bit Depth 16 bit GL enable");
		} else if (_choosePixelFormat(display,true,true,4,4,4,0,16,0,0)) {
			Log::console("PixelFormat: 16 bit Depth 16 bit GL enable");
		} else if (_choosePixelFormat(display,true,true,5,5,5,1,0,0,0)) {
			Log::console("PixelFormat: 16 bit GL enable");
		} else if (_choosePixelFormat(display,true,true,4,4,4,4,0,0,0)) {
			Log::console("PixelFormat: 16 bit GL enable");
		} else if (_choosePixelFormat(display,true,true,4,4,4,0,0,0,0)) {
			Log::console("PixelFormat: 16 bit GL enable");
		} else if (_choosePixelFormat(display,true,false,8,8,8,8,0,0,0)) {
			Log::console("PixelFormat: 32 bit Depth 16 bit");
		} else if (_choosePixelFormat(display,true,false,5,5,5,1,0,0,0)) {
			Log::console("PixelFormat: 16 bit");
		} else if (_choosePixelFormat(display,true,false,4,4,4,4,0,0,0)) {
			Log::console("PixelFormat: 16 bit");
		} else if (_choosePixelFormat(display,true,true,0,0,0,0,0,0,0)) {
			Log::console("PixelFormat: Low GL enable");
		} else if (_choosePixelFormat(display,true,false,0,0,0,0,0,0,0)) {
			Log::console("PixelFormat: Low");
		} else if (_choosePixelFormat(display,false,false,0,0,0,0,0,0,0)) {
			Log::console("PixelFormat: Low");
		} else {
			Log::console("Unable to choose pixel format");
			return false;
		}
	} else {
		int vcount=0;
		XVisualInfo* visuals;
		mdisplay->vi = new XVisualInfo();
		int mask = VisualClassMask | VisualDepthMask | VisualRedMaskMask | VisualGreenMaskMask | VisualBlueMaskMask;
		mdisplay->vi->c_class=TrueColor;
		mdisplay->vi->depth=32;
		mdisplay->vi->red_mask=0xFF0000;
		mdisplay->vi->green_mask=0xFF00;
		mdisplay->vi->blue_mask=0xFF;
		visuals = (XVisualInfo*)XGetVisualInfo(mdisplay->display,mask,mdisplay->vi,&vcount);
		if (visuals==0 || vcount==0) {
			delete mdisplay->vi;
			mdisplay->vi=0;
			Log::console("Unable to choose pixel format");
			return false;
		}
		extFunctions.MoveMem(visuals,mdisplay->vi,sizeof(XVisualInfo));
		XFree(visuals);
	}

	XSetWindowAttributes attr;
	Window root = RootWindow( mdisplay->display, mdisplay->vi->screen );
	XWindowAttributes getWinAttr;
	XGetWindowAttributes(mdisplay->display, root, &getWinAttr);
	mdisplay->posx=getWinAttr.x;
	mdisplay->posy=getWinAttr.y;
	mdisplay->xres=getWinAttr.width;
	mdisplay->yres=getWinAttr.height;
	mdisplay->colorres=4;
		
	if ((mode&0xFF)==0) {
		if (((LocalDisplay*)display)->ffunctions.soft==0) {
			((LocalDisplay*)display)->ffunctions.soft=new softDisplay();
		}
		softDisplay *sd=(softDisplay*)((LocalDisplay*)display)->ffunctions.soft;
		XShmSegmentInfo *info=new XShmSegmentInfo();
		
		XImage *image=XShmCreateImage( mdisplay->display, mdisplay->vi->visual, mdisplay->vi->depth, XShmPixmapFormat(mdisplay->display),NULL, info, mdisplay->xres, mdisplay->yres);
		sd->obj=(void*)image;
		sd->bufferStride=mdisplay->xres<<2;
		int size=mdisplay->yres*sd->bufferStride;
		info->shmid=shmget(IPC_PRIVATE, size*2+16,IPC_CREAT | 0777 );
		sd->buffer=(void*)info;
		info->shmaddr = (char *)shmat(info->shmid, 0, 0);
		info->readOnly = false;
		sd->colorOffset=(void*)(((_voidint)info->shmaddr)&(_voidintmax-15));
		image->data=(char *)sd->colorOffset;
		sd->depthOffset=((char*)sd->colorOffset)+size;
		XShmAttach(mdisplay->display, info);
		sd->maxx=mdisplay->xres;
		sd->maxy=mdisplay->yres;
	}

	attr.background_pixel = 0;
	attr.border_pixel = 0;
	attr.override_redirect = true;
	attr.colormap = XCreateColormap( mdisplay->display, root, mdisplay->vi->visual, AllocNone);
	attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask;
	int mask=0;
	if ((mdisplay->flag & LocalDisplay::WINDOWED)!=0) {
		mask = CWBorderPixel | CWColormap | CWEventMask;
	} else {
		mask = CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect; // fullscreen
		XF86VidModeSetViewPort(mdisplay->display,mdisplay->scrnum,0,0);
	}

	mdisplay->surface=XCreateWindow(mdisplay->display,root,0, 0,mdisplay->xres,mdisplay->yres,0,mdisplay->vi->depth,InputOutput,mdisplay->vi->visual,mask,&attr);
	if ((mdisplay->flag & LocalDisplay::WINDOWED)==0) {
		XWarpPointer(mdisplay->display,None,mdisplay->surface,0,0,0,0,0,0); // fullscreen
	}

	if (!mdisplay->surface) {
		Log::console("XCreateWindow: couldn't create window \n");
		return false;
	}
/*
 X Error of failed request:  BadValue (integer parameter out of range for operation)
  Major opcode of failed request:  1 (X_CreateWindow)
  Value in failed request:  0xd8
  Serial number of failed request:  25
  Current serial number in output stream:  26
 */
	XSizeHints sizehints;
	sizehints.x = 0;
	sizehints.y = 0;
	sizehints.width  = mdisplay->xres;
	sizehints.height = mdisplay->yres;
	sizehints.flags = USSize | USPosition;
	wmDelete = XInternAtom((::Display *)mdisplay->display, "WM_DELETE_WINDOW", True);
	XSetWMProtocols((::Display *)mdisplay->display, mdisplay->surface, &wmDelete, 1);
	XSetNormalHints((::Display *)mdisplay->display, mdisplay->surface, &sizehints);
	XSetStandardProperties((::Display *)mdisplay->display, mdisplay->surface, "unname", "unname",None, (char **)NULL, 0, &sizehints);

	XMapRaised((::Display *)mdisplay->display, mdisplay->surface);

	if ((mdisplay->flag & LocalDisplay::WINDOWED)==0) {
		XGrabKeyboard((::Display *)mdisplay->display,mdisplay->surface,True,GrabModeAsync,GrabModeAsync,CurrentTime);
	}

	//XMapWindow(mdisplay->display,mdisplay->surface);

	//XAllowEvents((::Display *)mdisplay->display,SyncBoth,CurrentTime);
	//XGrabPointer((::Display *)mdisplay->display,mdisplay->surface,1,0,GrabModeAsync,GrabModeAsync,None,None,CurrentTime);
	//PointerMotionMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | KeymapStateMask

	return true;
}

bool LocalDisplay::_destroyDisplay(Display * display)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	softDisplay *sd=(softDisplay*)((LocalDisplay*)display)->ffunctions.soft;
	if (sd) {
		if (sd->buffer) {
			XShmSegmentInfo *info=(XShmSegmentInfo *)sd->buffer;
			XShmDetach(mdisplay->display, info);
			shmdt(info->shmaddr);
		}
		if (sd->obj) XDestroyImage((XImage*)sd->obj);
		sd->buffer=0;
		delete sd;
		sd=0;
		delete mdisplay->vi;
	} else {
		XFree(mdisplay->vi);
	}
	mdisplay->vi=0;
	XCloseDisplay(mdisplay->display);
	mdisplay->display=0;
	return true;
}

}

OPTIMIZE_OFF;

#endif
