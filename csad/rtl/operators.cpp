
#include "operators.h"
#include <bt.h>

//#undef RTL_LOCAL

#if (defined(LOCAL_RTL) || defined(RTL_LOCAL))// && !defined(_DLL)
#if defined(MSVC)
//#ifndef _INC_STDLIB

#include "csad/bt/x86/macrosasm.h"
#include "csad/bt/base/basemath.h"

OPTIMIZE_OFF

#ifdef __cplusplus
extern "C" {
#endif

typedef void* voidpointer;

/*void _NAKED memcpy(void *, void *, size_t)
{
}*/

voidpointer _NAKED memset(void * , int , size_t )
{
	BEGIN_ASM
		ASM(push edi)
		ASM(mov edi, [esp + 8])
		ASM(mov eax, [esp + 12])
		ASM(mov ecx, [esp + 16])
		ASM(rep stosb)
		ASM(pop edi)
		ASM(ret)
	END_ASM
}

double _hypot(double x, double y)
{
	return matFunctions.DSqrt(x*x + y*y);
}

void _NAKED _allshl()
{
	BEGIN_ASM
		ASM( cmp         cl,0x40  )
		ASM( jae _allshl2 )
		ASM( cmp         cl,0x20 )
		ASM( ja _allshl1 )
		ASM( shld        edx,eax,cl )
		ASM( shl         eax,cl )
		ASM( ret )
		ASM( _allshl1: )
		ASM( mov         edx,eax )
		ASM( xor         eax,eax )
		ASM( and         cl,0x1F )
		ASM( shl         edx,cl )
		ASM( ret )
		ASM( _allshl2: )
		ASM( xor         eax,eax )
		ASM( xor         edx,edx )
		ASM( ret )
	END_ASM
}

void _NAKED _allshr()
{
	BEGIN_ASM
		ASM(cmp         cl, 0x40)
		ASM(jae _allshl2)
		ASM(cmp         cl, 0x20)
		ASM(ja _allshl1)
		ASM(shrd        eax, edx, cl)
		ASM(shr         edx, cl)
		ASM(ret)
		ASM(_allshl1:)
		ASM(mov         eax, edx)
		ASM(xor         edx, edx)
		ASM(and         cl, 0x1F)
		ASM(shr         eax, cl)
		ASM(ret)
		ASM(_allshl2:)
		ASM(xor         eax, eax)
		ASM(xor         edx, edx)
		ASM(ret)
		END_ASM
}

void _NAKED _aullshr()
{
	BEGIN_ASM
		ASM( cmp         cl,0x40  )
		ASM( jae         _aullshr2  )
		ASM( cmp         cl,0x20  )
		ASM( jae         _aullshr1  )
		ASM( shrd        eax,edx,cl  )
		ASM( shr         edx,cl  )
		ASM( ret  )
		ASM( _aullshr1: )
		ASM( mov         eax,edx  )
		ASM( xor         edx,edx  )
		ASM( and         cl,0x1F  )
		ASM( shr         eax,cl  )
		ASM( ret  )
		ASM( _aullshr2: )
		ASM( xor         eax,eax  )
		ASM( xor         edx,edx  )
		ASM( ret )
	END_ASM
}

void _NAKED _allmul()
{
//	return 0;
}

/*void _NAKED _ltod3()
{
	BEGIN_ASM
		ASM(push edx)
		ASM(push ecx)
	END_ASM
	((bt::tfSTDCALL_PROC)matFunctions.LToD)();
	BEGIN_ASM
		ASM(ret)
	END_ASM
}

void _NAKED _ftol2() // fpu in
{
	//return matFunctions.FTrunc(a);
}

void _NAKED _dtol2() // fpu in
{
	//return matFunctions.DTrunc(a);
}

void _NAKED _ftol3() // sse in
{
	BEGIN_ASM
		ASM(push eax)
		ASM(movss dword ptr[esp], xmm0)
	END_ASM
	((bt::tfSTDCALL_PROC)matFunctions.FTrunc)();
	BEGIN_ASM
		ASM(ret)
	END_ASM
}

void _NAKED _ftoui3() // sse in
{
	BEGIN_ASM
		ASM(push eax)
		ASM(movss dword ptr[esp], xmm0)
	END_ASM
	((bt::tfSTDCALL_PROC)matFunctions.FTrunc)();
	BEGIN_ASM
		ASM(ret)
	END_ASM
}

void _NAKED _dtol3()
{
	BEGIN_ASM
		ASM(push eax)
		ASM(push eax)
		ASM(movsd qword ptr[esp], xmm0)
	END_ASM
	((bt::tfSTDCALL_PROC)matFunctions.DTrunc)();
	BEGIN_ASM
		ASM(ret)
	END_ASM
}

void _NAKED _dtoui3() // sse in
{
	BEGIN_ASM
		ASM(push eax)
		ASM(push eax)
		ASM(movsd qword ptr [esp],xmm0)
	END_ASM
	((bt::tfSTDCALL_PROC)matFunctions.DTrunc)();
	BEGIN_ASM
		ASM(ret)
	END_ASM
}*/

void _NAKED _ftol2_sse() // fpu in
{
	BEGIN_ASM
		ASM( push eax )
		ASM( fstp dword ptr [esp] )
	END_ASM
	((bt::tfSTDCALL_PROC)matFunctions.FTrunc)();
	BEGIN_ASM
		ASM(ret)
	END_ASM
}

/*void _NAKED _ftol2_sse_excpt() // fpu in
{
	BEGIN_ASM
		ASM(push eax)
		ASM(fstp dword ptr[esp])
	END_ASM
	((bt::tfSTDCALL_PROC)matFunctions.FTrunc)();
	BEGIN_ASM
		ASM(ret)
	END_ASM
}*/

#ifndef __ATEXIT__
int atexit( void (__cdecl * )( void ) )
{
	return 0;
}
#endif

int _purecall()
{
	return 0;
}

void _imp__free()
{
}

void _imp__malloc()
{
}

void _imp__realloc()
{
}

void __cdecl _wassert(_In_z_ const wchar_t * , _In_z_ const wchar_t *, _In_ unsigned )
{
}

void _imp__wassert()
{
}

#define _JBLEN  16
#define _JBTYPE int

#ifndef _JMP_BUF_DEFINED
typedef _JBTYPE jmp_buf[_JBLEN];
#define _JMP_BUF_DEFINED
#endif  /* _JMP_BUF_DEFINED */

/*int __cdecl setjmp(_Out_ jmp_buf _Buf)
{
	return 0;
}*/

/*int _NAKED __cdecl _setjmp(_Out_ jmp_buf)
{
	return 0;
}*/

int _NAKED __cdecl _setjmp3(_Out_ jmp_buf )
{
	BEGIN_ASM
		ASM(mov edx, dword ptr[esp + 4])
		ASM(mov dword ptr[edx], ebp)
		ASM(mov dword ptr[edx + 4], ebx)
		ASM(mov dword ptr[edx + 8], edi)
		ASM(mov dword ptr[edx + 0x0C], esi)
		ASM(mov dword ptr[edx + 0x10], esp)
		ASM(mov eax, dword ptr[esp])
		ASM(mov dword ptr[edx + 0x14], eax)
		ASM(mov dword ptr[edx + 0x20], 0x56433230)
		ASM(mov dword ptr[edx + 0x24], 0)
		ASM(mov eax, dword ptr fs : [0x00000000])
		ASM(mov dword ptr[edx + 0x18], eax)
		ASM(cmp eax, 0xFFFFFFFF)
		ASM(jne __setjmp31)
		ASM(mov dword ptr[edx + 0x1C], 0xFFFFFFFF)
		ASM(jmp __setjmp38)
		ASM(__setjmp31:)
		ASM(mov ecx, dword ptr[esp + 8])
		ASM(or ecx, ecx)
		ASM(je __setjmp35)
		ASM(mov eax, dword ptr[esp + 0x0C])
		ASM(mov dword ptr[edx + 24h], eax)
		ASM(dec ecx)
		ASM(jne __setjmp36)
		ASM(__setjmp35:)
		ASM(mov eax, dword ptr[eax + 0x0C])
		ASM(mov dword ptr[edx + 0x1C], eax)
		ASM(jmp __setjmp38)
		ASM(__setjmp36:)
		ASM(mov eax, dword ptr[esp + 0x10])
		ASM(mov dword ptr[edx + 0x1C], eax)
		ASM(dec ecx)
		ASM(je __setjmp38)
		ASM(push esi)
		ASM(push edi)
		ASM(lea esi, [esp + 0x1C])
		ASM(lea edi, [edx + 0x28])
		ASM(cmp ecx, 6)
		ASM(jbe __setjmp37)
		ASM(mov ecx, 6)
		ASM(__setjmp37:)
		ASM(rep movs    dword ptr es : [edi], dword ptr[esi])
		ASM(pop edi)
		ASM(pop esi)
		ASM(__setjmp38:)
		ASM(sub eax, eax)
		ASM(ret)
		/*0FE9B300  mov         edx,dword ptr [esp+4]
		0FE9B304  mov         dword ptr [edx],ebp
		0FE9B306  mov         dword ptr [edx+4],ebx
		0FE9B309  mov         dword ptr [edx+8],edi
		0FE9B30C  mov         dword ptr [edx+0Ch],esi
		0FE9B30F  mov         dword ptr [edx+10h],esp
		0FE9B312  mov         eax,dword ptr [esp]
		0FE9B315  mov         dword ptr [edx+14h],eax
		0FE9B318  mov         dword ptr [edx+20h],56433230h
		0FE9B31F  mov         dword ptr [edx+24h],0
		0FE9B326  mov         eax,dword ptr fs:[00000000h]
		0FE9B32C  mov         dword ptr [edx+18h],eax
		0FE9B32F  cmp         eax,0FFFFFFFFh
		0FE9B332  jne         __setjmp3+3Dh (0FE9B33Dh)
		0FE9B334  mov         dword ptr [edx+1Ch],0FFFFFFFFh
		0FE9B33B  jmp         __setjmp3+78h (0FE9B378h)
		0FE9B33D  mov         ecx,dword ptr [esp+8]
		0FE9B341  or          ecx,ecx
		0FE9B343  je          __setjmp3+4Fh (0FE9B34Fh)
		0FE9B345  mov         eax,dword ptr [esp+0Ch]
		0FE9B349  mov         dword ptr [edx+24h],eax
		0FE9B34C  dec         ecx
		0FE9B34D  jne         __setjmp3 + 57h (0FE9B357h)
		0FE9B34F  mov         eax, dword ptr[eax + 0Ch]
		0FE9B352  mov         dword ptr[edx + 1Ch], eax
		0FE9B355  jmp         __setjmp3 + 78h (0FE9B378h)
		0FE9B357  mov         eax, dword ptr[esp + 10h]
		0FE9B35B  mov         dword ptr[edx + 1Ch], eax
		0FE9B35E  dec         ecx
		0FE9B35F  je          __setjmp3 + 78h (0FE9B378h)
		0FE9B361  push        esi
		0FE9B362  push        edi
		0FE9B363  lea         esi, [esp + 1Ch]
		0FE9B367  lea         edi, [edx + 28h]
		0FE9B36A  cmp         ecx, 6
		0FE9B36D  jbe         __setjmp3 + 74h (0FE9B374h)
		0FE9B36F  mov         ecx, 6
		0FE9B374  rep movs    dword ptr es : [edi], dword ptr[esi]
		0FE9B376  pop         edi
		0FE9B377  pop         esi
		0FE9B378  sub         eax, eax
		0FE9B37A  ret*/
	END_ASM
}

void _NAKED __cdecl longjmp(_In_ jmp_buf , _In_ int )
{

}

void _NAKED __cdecl _imp__longjmp(_In_ jmp_buf , _In_ int )
{

}

void vsnprintf()
{

}

void sscanf()
{

}

void _imp__vsnprintf()
{

}

void _imp__sscanf()
{

}

/*void * __cdecl operator new(unsigned int)
{
	return 0;
}

void __cdecl operator delete(void *)
{
}*/

#ifdef __cplusplus
}
#endif

OPTIMIZE_OFF

#endif
#endif
