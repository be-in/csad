//=============================================================================
///**
// *  @file   quaternion_vector.h
// *
// *  $Id: quaternion_inv.h 16.10.2011  $
// *
// *  @brief generator 3, assembler quaternion double/float vector, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_QUATERNION_VECTOR_H
#define GEN3_QUATERNION_VECTOR_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** VECTOR SDTCALL *********************************
// addition vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *

/// Разложение на элементы, команды FPU.
/// @brief for CPUTYPE1
#define QUATERNIONPDVECTORFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE2( 0xD9,0x1A )                                         /* fstp        dword ptr [edx]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x5A,0x04 )                                    /* fstp        dword ptr [edx+4]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x5A,0x08 )                                    /* fstp        dword ptr [edx+8]  */ \
_LINE3( 0xD9,0x40,0x0C )                                    /* fld         dword ptr [eax+0x0C]  */ \
_LINE2( 0xD9,0xF3 )                                         /* farctg */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
_LINE3( 0xD9,0x5A,0x0C )                                    /* fstp        dword ptr [edx+0x0C]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// Разложение на элементы, команды FPU.
/// @brief for CPUTYPE1
#define QUATERNIONPDDVECTORFPU_STD \
_BEGIN_ASM \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDD,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xDC,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xDD,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xDC,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xDD,0x40,0x10 )                                    /* fld         dword ptr [eax+0x10]  */ \
_LINE3( 0xDC,0x48,0x10 )                                    /* fmul        dword ptr [eax+0x10]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xDC,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE2( 0xDD,0x1A )                                         /* fstp        dword ptr [edx]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE3( 0xDC,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE3( 0xDD,0x5A,0x08 )                                    /* fstp        dword ptr [edx+8]  */ \
_LINE3( 0xDC,0x48,0x10 )                                    /* fmul        dword ptr [eax+0x10]  */ \
_LINE3( 0xDD,0x5A,0x10 )                                    /* fstp        dword ptr [edx+0x10]  */ \
_LINE3( 0xDD,0x40,0x18 )                                    /* fld         dword ptr [eax+0x18]  */ \
_LINE2( 0xD9,0xF3 )                                         /* farctg */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
_LINE3( 0xDD,0x5A,0x18 )                                    /* fstp        dword ptr [edx+0x18]  */ \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

#endif /* GEN3_QUATERNION_VECTOR_H */
