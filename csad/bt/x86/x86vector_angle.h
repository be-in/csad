//=============================================================================
///**
// *  @file vector_angle.h
// *
// *  $Id: vector_angle.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float angle, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_ANGLE_H
#define GEN3_VECTOR_ANGLE_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** ANGLE STDCALL *********************************
// ANGLE vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *

/// ”гол между двухмерными векторами одинарной точности, команды FPU.
#define VECTORP2DANGLEFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xD9,0x00 )                /* fld         dword ptr [eax]  */ \
_LINE3( 0xD8,0x4A,0x04 )           /* fmul        dword ptr [edx+4]  */ \
_LINE2( 0xD9,0x02 )                /* fld         dword ptr [edx]  */ \
_LINE3( 0xD8,0x48,0x04 )           /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xE9 )                /* fsubp       st(1),st  */ \
_LINE2( 0xD9,0x00 )                /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x0A )                /* fmul        dword ptr [edx]  */ \
_LINE3( 0xD9,0x40,0x04 )           /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x4A,0x04 )           /* fmul        dword ptr [edx+4]  */ \
_LINE2( 0xDE,0xC1 )                /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xF3 )                /* farctg */ \
_END_ASM

/// ”гол между трехмерными векторами одинарной точности, команды FPU.
#define VECTORP3DANGLEFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xD9,0x42,0x08 )           /* fld         dword ptr [edx+8h]  */ \
_LINE3( 0xD8,0x48,0x04 )           /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x40,0x08 )           /* fld         dword ptr [eax+8h]  */ \
_LINE3( 0xD8,0x4A,0x04 )           /* fmul        dword ptr [edx+4]  */ \
_LINE2( 0xDE,0xE9 )                /* fsubp       st(1),st  */ \
_LINE2( 0xD8,0xC8 )                /* fmul        st,st(0)  */ \
_LINE3( 0xD9,0x40,0x08 )           /* fld         dword ptr [eax+8h]  */ \
_LINE2( 0xD8,0x0A )                /* fmul        dword ptr [edx]  */ \
_LINE3( 0xD9,0x42,0x08 )           /* fld         dword ptr [edx+8h]  */ \
_LINE2( 0xD8,0x08 )                /* fmul        dword ptr [eax]  */ \
_LINE2( 0xDE,0xE9 )                /* fsubp       st(1),st  */ \
_LINE2( 0xD8,0xC8 )                /* fmul        st,st(0)  */ \
_LINE2( 0xD9,0x00 )                /* fld         dword ptr [eax]  */ \
_LINE3( 0xD8,0x4A,0x04 )           /* fmul        dword ptr [edx+4]  */ \
_LINE2( 0xD9,0x02 )                /* fld         dword ptr [edx]  */ \
_LINE3( 0xD8,0x48,0x04 )           /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xE9 )                /* fsubp       st(1),st  */ \
_LINE2( 0xD8,0xC8 )                /* fmul        st,st(0)  */ \
_LINE2( 0xDE,0xC2 )                /* faddp       st(2),st  */ \
_LINE2( 0xDE,0xC1 )                /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                /* fsqrt */ \
_LINE2( 0xD9,0x00 )                /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x0A )                /* fmul        dword ptr [edx]  */ \
_LINE3( 0xD9,0x40,0x04 )           /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x4A,0x04 )           /* fmul        dword ptr [edx+4]  */ \
_LINE2( 0xDE,0xC1 )                /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )           /* fld         dword ptr [eax+8h]  */ \
_LINE3( 0xD8,0x4A,0x08 )           /* fmul        dword ptr [edx+8h]  */ \
_LINE2( 0xDE,0xC1 )                /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xF3 )                /* farctg */ \
_END_ASM

/// ”гол между двухмерными векторами двойной точности, команды FPU.
#define VECTORP2DDANGLEFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE2( 0xDD,0x00 )                /* fld         qword ptr [eax]  */ \
_LINE3( 0xDC,0x4A,0x08 )           /* fmul        qword ptr [edx+8]  */ \
_LINE2( 0xDD,0x02 )                /* fld         qword ptr [edx]  */ \
_LINE3( 0xDC,0x48,0x08 )           /* fmul        qword ptr [eax+8]  */ \
_LINE2( 0xDE,0xE9 )                /* fsubp       st(1),st  */ \
_LINE2( 0xDD,0x00 )                /* fld         qword ptr [eax]  */ \
_LINE2( 0xDC,0x0A )                /* fmul        qword ptr [edx]  */ \
_LINE3( 0xDD,0x40,0x08 )           /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x4A,0x08 )           /* fmul        qword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xF3 )                /* farctg */ \
_END_ASM

/// ”гол между трехмерными векторами двойной точности, команды FPU.
#define VECTORP3DDANGLEFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )      /* mov         eax,dword ptr [esp+4]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )      /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xDD,0x42,0x10 )           /* fld         qword ptr [edx+10h]  */ \
_LINE3( 0xDC,0x48,0x08 )           /* fmul        qword ptr [eax+8]  */ \
_LINE3( 0xDD,0x40,0x10 )           /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDC,0x4A,0x08 )           /* fmul        qword ptr [edx+8]  */ \
_LINE2( 0xDE,0xE9 )                /* fsubp       st(1),st  */ \
_LINE2( 0xD8,0xC8 )                /* fmul        st,st(0)  */ \
_LINE3( 0xDD,0x40,0x10 )           /* fld         qword ptr [eax+10h]  */ \
_LINE2( 0xDC,0x0A )                /* fmul        qword ptr [edx]  */ \
_LINE3( 0xDD,0x42,0x10 )           /* fld         qword ptr [edx+10h]  */ \
_LINE2( 0xDC,0x08 )                /* fmul        qword ptr [eax]  */ \
_LINE2( 0xDE,0xE9 )                /* fsubp       st(1),st  */ \
_LINE2( 0xD8,0xC8 )                /* fmul        st,st(0)  */ \
_LINE2( 0xDD,0x00 )                /* fld         qword ptr [eax]  */ \
_LINE3( 0xDC,0x4A,0x08 )           /* fmul        qword ptr [edx+8]  */ \
_LINE2( 0xDD,0x02 )                /* fld         qword ptr [edx]  */ \
_LINE3( 0xDC,0x48,0x08 )           /* fmul        qword ptr [eax+8]  */ \
_LINE2( 0xDE,0xE9 )                /* fsubp       st(1),st  */ \
_LINE2( 0xD8,0xC8 )                /* fmul        st,st(0)  */ \
_LINE2( 0xDE,0xC2 )                /* faddp       st(2),st  */ \
_LINE2( 0xDE,0xC1 )                /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                /* fsqrt */ \
_LINE2( 0xDD,0x00 )                /* fld         qword ptr [eax]  */ \
_LINE2( 0xDC,0x0A )                /* fmul        qword ptr [edx]  */ \
_LINE3( 0xDD,0x40,0x08 )           /* fld         qword ptr [eax+8]  */ \
_LINE3( 0xDC,0x4A,0x08 )           /* fmul        qword ptr [edx+8]  */ \
_LINE2( 0xDE,0xC1 )                /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x40,0x10 )           /* fld         qword ptr [eax+10h]  */ \
_LINE3( 0xDC,0x4A,0x10 )           /* fmul        qword ptr [edx+10h]  */ \
_LINE2( 0xDE,0xC1 )                /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xF3 )                /* farctg */ \
_END_ASM

#endif
