/*
 * windisplay.cpp
 *
 *  Created on: 14.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include <platform/platformapi.h>

#if defined (OS_WIN)

#include "csad/platform/localdisplay.h"
#include "csad/platform/base/basesoftrender.h"
#include <platform.h>
#include <bt.h>
#include <core/graph.h>

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

unsigned _int32 LocalDisplay::flag()
{
	return ffunctions.mode>>8;
}

void LocalDisplay::setFlag(unsigned _int32 mask,unsigned _int32 val)
{
	unsigned _int32 flag=ffunctions.mode>>8;
	if ((mask&FM_VSYNC)!=0) if (0!=(val^flag&FM_VSYNC)) {
		flag^=FM_VSYNC;
	}
	if ((mask&FM_WINDOWED)!=0) if (0!=(val^flag&FM_WINDOWED)) {
		flag^=FM_WINDOWED;
	}
	if ((mask&FM_TRANSPARENT)!=0) if (0!=(val^flag&FM_TRANSPARENT)) {
		flag^=FM_TRANSPARENT;
	}
	if ((mask&FM_HARDWAREMOUSE)!=0) if (0!=(val^flag&FM_HARDWAREMOUSE)) {
		flag^=FM_HARDWAREMOUSE;
		SetFocus(p_display.surface);
		ShowCursor(val);
	}
	ffunctions.mode=(ffunctions.mode & 0xFF) | (flag<<8);
	initDisplayRender(&ffunctions,ffunctions.mode);
}

void LocalDisplay::SetTitle(char *)
{
	//SetWindowTitle();
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

_int32 LocalDisplay::width()
{
	if ((ffunctions.mode&(FM_WINDOWED<<8))!=0) return p_display.xres;
	return p_display.xres;
}

_int32 LocalDisplay::height()
{
	return p_display.yres;
}

_int32 LocalDisplay::left()
{
	return p_display.posx;
}

_int32 LocalDisplay::top() 
{
	if ((ffunctions.mode&(FM_WINDOWED<<8))!=0) return p_display.posy;
	return p_display.posy;
}

void LocalDisplay::setSize(bt::vector4i &)
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
	ffunctions.Buffers(this);
}*/

struct displayBITMAPINFO {
    BITMAPINFOHEADER    bmiHeader;
    RGBQUAD             bmiColors[4];
};

void LocalDisplay::softDraw()
{
#if defined(CSAD_SOFT_RENDER) || defined(SOFT_RENDER_CSAD)
	Display_P * mdisplay=&p_display;
	softDisplay *sd=(softDisplay*)ffunctions.soft;
	if (!sd) return;
	if (!sd->colorOffset) return;
	
	displayBITMAPINFO binfo;
	extFunctions.CleanMem(&binfo,sizeof(binfo));
	binfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	binfo.bmiHeader.biWidth=sd->maxx;
	binfo.bmiHeader.biHeight=sd->maxy;
	binfo.bmiHeader.biPlanes=1;
	binfo.bmiHeader.biBitCount=32;
	binfo.bmiHeader.biClrImportant=0;
	binfo.bmiHeader.biClrUsed=0;
	binfo.bmiHeader.biSizeImage=sd->maxx*sd->maxy*4;
	binfo.bmiHeader.biCompression=BI_RGB;
	SetDIBitsToDevice(mdisplay->display,0,0,sd->maxx,sd->maxy,0,0,0,sd->maxy,sd->colorOffset,(BITMAPINFO*)&binfo,DIB_RGB_COLORS);
#endif
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	csad::Display*display = csad::Graph::graph().getDisplayByHandle((void*)hWnd);
	Display_P * mdisplay=((LocalDisplay*)display)->localDisplay();
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOVE: {
		POINTS *p=(POINTS *)&lParam;
		mdisplay->posx=p->x;
		mdisplay->posy=p->y;
		return DefWindowProc(hWnd,message,wParam,lParam);
				  }
	case WM_SIZE: {
		POINTS *p=(POINTS *)&lParam;
		mdisplay->xres=p->x;
		mdisplay->yres=p->y;
		/*if ((((LocalDisplay*)display)->mode()&0xFF)==0) {
#if defined(CSAD_SOFT_RENDER) || defined(SOFT_RENDER_CSAD)
			softDisplay *sd=(softDisplay*)((LocalDisplay*)display)->functions().soft;
			if (sd->buffer) delete (char*)sd->buffer;
			sd->bufferStride=mdisplay->xres<<2;
			//sd->obj=0;
			int size=mdisplay->yres*sd->bufferStride;
			sd->buffer=(void*)new char[size*2+16];
			sd->colorOffset=(void*)(((_voidint)sd->buffer)&(_voidintmax-15));
			sd->depthOffset=((char*)sd->colorOffset)+size;
			sd->maxx=mdisplay->xres;
			sd->maxy=mdisplay->yres;
#endif
		}*/
		return DefWindowProc(hWnd,message,wParam,lParam);
				  }
	case WM_PAINT:
	case WM_ERASEBKGND:
	case WM_SETREDRAW:
	case WM_PAINTICON:
	case WM_SYSCOLORCHANGE:
	case WM_ICONERASEBKGND:
		ValidateRect(hWnd,0);
		break;
	case WM_CLOSE: {
		delete display;
		return DefWindowProc(hWnd,message,wParam,lParam);
				   }
	case WM_NCPAINT: {
		if (!display->isWindowed()) ValidateRect(hWnd,0);
		return DefWindowProc(hWnd,message,wParam,lParam);
					 }
	default:
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}

bool LocalDisplay::_choosePixelFormat(Display * display,bool ,bool gl,int r,int g,int b,int a,int depth,int stencil,int sample)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	sFunctionsDisplayRender * mfunctions=&((LocalDisplay*)display)->ffunctions;

	bool retry=true;
	while (retry) {
		PIXELFORMATDESCRIPTOR pfd;
		extFunctions.CleanMem(&pfd,sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion=1;
		if ((mfunctions->mode&(FM_TRANSPARENT<<8))!=0) {
			pfd.dwFlags=PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
		} else {
			pfd.dwFlags=PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
		}
		if (gl) pfd.dwFlags |= PFD_SUPPORT_OPENGL;
		pfd.iPixelType=PFD_TYPE_RGBA;
		pfd.cColorBits=r+g+b+a;
		pfd.cRedBits=r;
		pfd.cGreenBits=g;
		pfd.cBlueBits=b;
		pfd.cAlphaBits=a;
		pfd.cDepthBits=depth;
		pfd.cStencilBits=stencil;
		pfd.cAccumBits=0;
		pfd.cAuxBuffers=0;
		pfd.iLayerType=PFD_MAIN_PLANE;

		mdisplay->config=ChoosePixelFormat(mdisplay->display,&pfd);

		if (mdisplay->config==0) return false;
		if (!SetPixelFormat(mdisplay->display,mdisplay->config,&pfd)) return false;
		if (!DescribePixelFormat(mdisplay->display,mdisplay->config,sizeof(pfd),&pfd)) return false;

		//if (gl && ((pfd.dwFlags & PFD_SUPPORT_OPENGL)==0)) return false;
		//if (gl && ((pfd.dwFlags & PFD_SWAP_EXCHANGE)==0)) return false;
		//if (gl && ((pfd.dwFlags & PFD_DOUBLEBUFFER)==0)) return false;

		Context_P mcontext;
		mcontext.initialize=false;
		glBasefunctions(&mcontext);
		HGLRC context=(HGLRC)mcontext.CreateContext(mdisplay->display);
		if (context==0) continue;
		mcontext.DeleteContext(context);
		retry=false;
	}

	return true;
}

bool LocalDisplay::_createDisplay(Display * display,_int32 ,_int32 dispid)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	sFunctionsDisplayRender * mfunctions=&((LocalDisplay*)display)->ffunctions;

	DISPLAY_DEVICEA dispdev;
	dispdev.cb=sizeof(dispdev);

	EnumDisplayDevicesA(0,dispid,(DISPLAY_DEVICEA*)&dispdev,0);
	DEVMODEA mode;
	mode.dmSize=sizeof(mode);
	EnumDisplaySettingsA(dispdev.DeviceName,ENUM_CURRENT_SETTINGS,&mode);

	mdisplay->xres=mode.dmPelsWidth;
	mdisplay->yres=mode.dmPelsHeight;
	mdisplay->posx=mode.dmPosition.x;
	mdisplay->posy=mode.dmPosition.y;
	mdisplay->colorres=GetDeviceCaps(0,COLORRES);

	// create full screen window
	WNDCLASSA wndclass;
	extFunctions.CleanMem(&wndclass,sizeof(WNDCLASS));
	wndclass.lpfnWndProc=(WNDPROC)WndProc;
	wndclass.lpszClassName="CSADWNDCLASS";
	wndclass.hInstance=(HINSTANCE)Render::hInst;
	wndclass.style=CS_VREDRAW | CS_HREDRAW;
	wndclass.hbrBackground=0;
	wndclass.hCursor = LoadCursor((HINSTANCE)Render::hInst,0);

	if (!GetClassInfoA((HINSTANCE)Render::hInst,wndclass.lpszClassName,&wndclass)) {
	
		if (RegisterClassA(&wndclass)==0) {
#ifdef LOG_CSAD
			Log::console("RegisterClass() failed");
#endif
			return false;
		}
	}
	DWORD style=WS_POPUP | WS_VISIBLE;
	DWORD drawstyle=0;
	if ((mfunctions->mode & (FM_WINDOWED<<8))!=0 && (mfunctions->mode & (FM_TRANSPARENT<<8))==0) {
		style=WS_POPUPWINDOW | WS_OVERLAPPEDWINDOW | WS_VISIBLE;
		drawstyle=WS_EX_OVERLAPPEDWINDOW;
	}
	if ((mfunctions->mode & (FM_TRANSPARENT<<8))!=0) {
		drawstyle|=WS_EX_LAYERED;
	}
	mdisplay->surface=CreateWindowExA(drawstyle,wndclass.lpszClassName,"",style,mdisplay->posx,mdisplay->posy,mdisplay->xres,mdisplay->yres,0,0,(HINSTANCE)Render::hInst,0);
	//lastSurface=mdisplay->surface;
	if (!mdisplay->surface) {
#ifdef LOG_CSAD
		Log::console("CreateWindowExA() failed");
#endif
		return false;
	}

	if (!ShowWindow(mdisplay->surface,SW_MAXIMIZE)) {
#ifdef LOG_CSAD
		Log::console("ShowWindow() failed");
#endif
	}
	
	// create dc
	mdisplay->display=GetDC(mdisplay->surface);
	if (mdisplay->display==0)
	{
#ifdef LOG_CSAD
		Log::console("GetDC() failed");
#endif
		return false;
	}

	if ((mfunctions->mode & (FM_WINDOWED<<8))==0) {
		mdisplay->xres=GetDeviceCaps(mdisplay->display,HORZRES);
		mdisplay->yres=GetDeviceCaps(mdisplay->display,VERTRES);
	}
	mdisplay->colorres=GetDeviceCaps(mdisplay->display,COLORRES);

	if ((((LocalDisplay*)display)->ffunctions.mode&0xFF)==0) {
	// software
#if defined(CSAD_SOFT_RENDER) || defined(SOFT_RENDER_CSAD)
		if (((LocalDisplay*)display)->ffunctions.soft==0) {
			((LocalDisplay*)display)->ffunctions.soft=new softDisplay();
		}
		softDisplay *sd=(softDisplay*)((LocalDisplay*)display)->ffunctions.soft;
		sd->bufferStride=mdisplay->xres<<2;
		sd->obj=0;
		int size=mdisplay->yres*sd->bufferStride;
		sd->buffer=(void*)new char[size*2+16];
		sd->colorOffset=(void*)(((_voidint)sd->buffer)&(_voidintmax-15));
		sd->depthOffset=((char*)sd->colorOffset)+size;
		sd->maxx=mdisplay->xres;
		sd->maxy=mdisplay->yres;
#endif
	} else {
	// hardware
		if (_choosePixelFormat(display,true,true,8,8,8,8,32,0,1)) {
#ifdef LOG_CSAD
			Log::console("PixelFormat: 32 bit Depth 32 bit GL enable");
#endif
		} else if (_choosePixelFormat(display,true,true,8,8,8,8,16,0,1)) {
#ifdef LOG_CSAD
			Log::console("PixelFormat: 32 bit Depth 16 bit GL enable");
#endif
		} else if (_choosePixelFormat(display,true,true,8,8,8,0,16,0,0)) {
#ifdef LOG_CSAD
			Log::console("PixelFormat: 24 bit Depth 16 bit GL enable");
#endif
		} else if (_choosePixelFormat(display,true,true,4,4,4,0,16,0,0)) {
#ifdef LOG_CSAD
			Log::console("PixelFormat: 16 bit Depth 16 bit GL enable");
#endif
		} else if (_choosePixelFormat(display,true,true,4,4,4,0,0,0,0)) {
#ifdef LOG_CSAD
			Log::console("PixelFormat: 16 bit GL enable");
#endif
		} else if (_choosePixelFormat(display,true,true,0,0,0,0,0,0,0)) {
#ifdef LOG_CSAD
			Log::console("PixelFormat: Low GL enable");
#endif
		} else {
#ifdef LOG_CSAD
			Log::console("Unable to choose pixel format");
#endif
			return false;
		}
	}
	
	ShowCursor(((mfunctions->mode & (FM_HARDWAREMOUSE<<8))!=0));

	return true;
}

bool LocalDisplay::_destroyDisplay(Display * display)
{
	Display_P * mdisplay=&((LocalDisplay*)display)->p_display;
	sFunctionsDisplayRender * mfunctions=&((LocalDisplay*)display)->ffunctions;
#if defined(CSAD_SOFT_RENDER) || defined(SOFT_RENDER_CSAD)
	softDisplay *sd=(softDisplay*)((LocalDisplay*)display)->ffunctions.soft;
	if (sd) {
		if (sd->buffer) delete (char*)sd->buffer;
		sd->buffer=0;
		delete sd;
		sd=0;
	}
#endif
	if (ReleaseDC((HWND)mdisplay->surface,(HDC)mdisplay->display)==0) {
		int err=GetLastError();
#ifdef LOG_CSAD
		Log::console("LocalDisplay::ReleaseDC() err: %s",strerror(err));
#endif
	}
	mdisplay->display=0;
	if (DestroyWindow((HWND)mdisplay->surface)==0) {
		int err=GetLastError();
#ifdef LOG_CSAD
		Log::console("LocalDisplay::DestroyWindow() err: %s",strerror(err));
#endif
	}
	mdisplay->surface=0;
	return true;
}

}

OPTIMIZE_OFF;

#endif
