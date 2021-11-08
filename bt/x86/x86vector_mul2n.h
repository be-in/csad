//=============================================================================
///**
// *  @file vector_mul2n.h
// *
// *  $Id: vector_mul2n.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float mul2n, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_VECTOR_MUL2N_H
#define GEN3_VECTOR_MUL2N_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium M, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** MUL2N STDCALL *********************************
// mul2n vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *, ecx=[esp+12]-int

/// умножение двухмерного вектора одинарной точности на 2 в степени N, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP2DMUL2NFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld dword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fstp dword ptr [edx]  ) \
ASM( fmul dword ptr [eax+4] ) \
ASM( fstp dword ptr [edx+4]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение двухмерного вектора одинарной точности на 2 в степени N, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DMUL2NSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x7F ) \
ASM( and eax,0xFF ) \
ASM( shl eax,23 ) \
ASM( movd xmm0,eax ) \
ASM( mov eax,[esp+4] ) \
ASM( movss xmm1,[eax] ) \
ASM( movss xmm2,[eax+4] ) \
ASM( mulss xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulss xmm2,xmm0 ) \
ASM( movss [eax],xmm1 ) \
ASM( movss [eax+4],xmm2 ) \
_END_ASM

/// умножение трехмерного вектора одинарной точности на 2 в степени N, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DMUL2NFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld dword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fstp dword ptr [edx]  ) \
ASM( fld dword ptr [eax+4] ) \
ASM( fmul st,st(1) ) \
ASM( fstp dword ptr [edx+4]  ) \
ASM( fmul dword ptr [eax+8] ) \
ASM( fstp dword ptr [edx+8]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение трехмерного вектора одинарной точности на 2 в степени N, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DMUL2NSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x7F ) \
ASM( and eax,0xFF ) \
ASM( shl eax,23 ) \
ASM( movd xmm0,eax ) \
ASM( mov eax,[esp+4] ) \
ASM( movss xmm1,[eax] ) \
ASM( movss xmm2,[eax+4] ) \
ASM( movss xmm3,[eax+8] ) \
ASM( mulss xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulss xmm2,xmm0 ) \
ASM( mulss xmm3,xmm0 ) \
ASM( movss [eax],xmm1 ) \
ASM( movss [eax+4],xmm2 ) \
ASM( movss [eax+8],xmm3 ) \
_END_ASM

/// умножение четырехмерного вектора одинарной точности на 2 в степени N, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DMUL2NFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld dword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fstp dword ptr [edx]  ) \
ASM( fld dword ptr [eax+4] ) \
ASM( fmul st,st(1) ) \
ASM( fstp dword ptr [edx+4]  ) \
ASM( fld dword ptr [eax+8] ) \
ASM( fmul st,st(1) ) \
ASM( fstp dword ptr [edx+8]  ) \
ASM( fmul dword ptr [eax+12] ) \
ASM( fstp dword ptr [edx+12]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение четырехмерного вектора одинарной точности на 2 в степени N, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DMUL2NSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x7F ) \
ASM( and eax,0xFF ) \
ASM( shl eax,23 ) \
ASM( movd xmm0,eax ) \
ASM( mov eax,[esp+4] ) \
ASM( movss xmm1,[eax] ) \
ASM( movss xmm2,[eax+4] ) \
ASM( movss xmm3,[eax+8] ) \
ASM( movss xmm4,[eax+12] ) \
ASM( mulss xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulss xmm2,xmm0 ) \
ASM( mulss xmm3,xmm0 ) \
ASM( mulss xmm4,xmm0 ) \
ASM( movss [eax],xmm1 ) \
ASM( movss [eax+4],xmm2 ) \
ASM( movss [eax+8],xmm3 ) \
ASM( movss [eax+12],xmm4 ) \
_END_ASM

/// умножение двухмерного вектора двойной точности на 2 в степени N, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP2DDMUL2NFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld qword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fstp qword ptr [edx]  ) \
ASM( fmul qword ptr [eax+8] ) \
ASM( fstp qword ptr [edx+8]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение двухмерного вектора двойной точности на 2 в степени N, команды SSE2.
/// @brief for CPUTYPE1
#define VECTORP2DDMUL2NSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x3FF ) \
ASM( and eax,0x7FF ) \
ASM( shl eax,20 ) \
ASM( movd xmm0,eax ) \
ASM( shufps xmm0,xmm0,1 ) \
ASM( mov eax,[esp+4] ) \
ASM( movsd xmm1,[eax] ) \
ASM( movsd xmm2,[eax+8] ) \
ASM( mulsd xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulsd xmm2,xmm0 ) \
ASM( movsd [eax],xmm1 ) \
ASM( movsd [eax+8],xmm2 ) \
_END_ASM

/// умножение трехмерного вектора двойной точности на 2 в степени N, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DDMUL2NFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld qword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fstp qword ptr [edx]  ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fmul st,st(1) ) \
ASM( fstp qword ptr [edx+8]  ) \
ASM( fmul qword ptr [eax+16] ) \
ASM( fstp qword ptr [edx+16]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение трехмерного вектора двойной точности на 2 в степени N, команды SSE2.
/// @brief for CPUTYPE1
#define VECTORP3DDMUL2NSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x3FF ) \
ASM( and eax,0x7FF ) \
ASM( shl eax,20 ) \
ASM( movd xmm0,eax ) \
ASM( shufps xmm0,xmm0,1 ) \
ASM( mov eax,[esp+4] ) \
ASM( movsd xmm1,[eax] ) \
ASM( movsd xmm2,[eax+8] ) \
ASM( movsd xmm3,[eax+16] ) \
ASM( mulsd xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulsd xmm2,xmm0 ) \
ASM( mulsd xmm3,xmm0 ) \
ASM( movsd [eax],xmm1 ) \
ASM( movsd [eax+8],xmm2 ) \
ASM( movsd [eax+16],xmm3 ) \
_END_ASM

/// умножение четырехмерного вектора двойной точности на 2 в степени N, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DDMUL2NFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld qword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fstp qword ptr [edx]  ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fmul st,st(1) ) \
ASM( fstp qword ptr [edx+8]  ) \
ASM( fld qword ptr [eax+16] ) \
ASM( fmul st,st(1) ) \
ASM( fstp qword ptr [edx+16]  ) \
ASM( fmul qword ptr [eax+24] ) \
ASM( fstp qword ptr [edx+24]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение четырехмерного вектора двойной точности на 2 в степени N, команды SSE2.
/// @brief for CPUTYPE1
#define VECTORP4DDMUL2NSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x3FF ) \
ASM( and eax,0x7FF ) \
ASM( shl eax,20 ) \
ASM( movd xmm0,eax ) \
ASM( shufps xmm0,xmm0,1 ) \
ASM( mov eax,[esp+4] ) \
ASM( movsd xmm1,[eax] ) \
ASM( movsd xmm2,[eax+8] ) \
ASM( movsd xmm3,[eax+16] ) \
ASM( movsd xmm4,[eax+24] ) \
ASM( mulsd xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulsd xmm2,xmm0 ) \
ASM( mulsd xmm3,xmm0 ) \
ASM( mulsd xmm4,xmm0 ) \
ASM( movsd [eax],xmm1 ) \
ASM( movsd [eax+8],xmm2 ) \
ASM( movsd [eax+16],xmm3 ) \
ASM( movsd [eax+24],xmm4 ) \
_END_ASM

//**************************** MUL2N TRUNC STDCALL *********************************
// mul2n trunc vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *, st(0)=[esp+12]-int

/// умножение двухмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP2DMUL2NTRUNCFPU_STD \
_BEGIN_ASM \
ASM( fild dword ptr [esp+12] ) \
_LINE4( 0xD9,0x7C,0x24,0x0C )        /* fnstcw      word ptr [esp+12]  */ \
_LINE5( 0x66,0x8B,0x44,0x24,0x0C )   /* mov         ax,word ptr [esp+12]  */ \
_LINE3( 0x66,0x8B,0xC8 )             /* mov         cx,ax  */ \
_LINE4( 0x66,0x25,0xFF,0xF3 )        /* and         ax,0F3FFh  */ \
_LINE4( 0x66,0x0D,0x00,0x0C )        /* or          ax,C00h  */ \
_LINE5( 0x66,0x89,0x44,0x24,0x0C )   /* mov         word ptr [esp+12],ax  */ \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fld1 ) \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld dword ptr [eax] ) \
ASM( fmul st,st(1) ) \
_LINE5( 0x66,0x89,0x4C,0x24,0x0C )   /* mov         word ptr [esp+12],cx  */ \
ASM( fistp dword ptr [edx]  ) \
ASM( fmul dword ptr [eax+4] ) \
ASM( fistp dword ptr [edx+4]  ) \
_LINE2( 0xDD,0xD8 )                  /* fstp        st(0)  */ \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_END_ASM

/// умножение двухмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DMUL2NTRUNCSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x7F ) \
ASM( and eax,0xFF ) \
ASM( shl eax,23 ) \
ASM( movd xmm0,eax ) \
ASM( mov eax,[esp+4] ) \
ASM( movss xmm1,[eax] ) \
ASM( movss xmm2,[eax+4] ) \
ASM( mulss xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulss xmm2,xmm0 ) \
ASM( cvttss2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvttss2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
_END_ASM

/// умножение трехмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DMUL2NTRUNCFPU_STD \
_BEGIN_ASM \
ASM( fild dword ptr [esp+12] ) \
_LINE4( 0xD9,0x7C,0x24,0x0C )        /* fnstcw      word ptr [esp+12]  */ \
_LINE5( 0x66,0x8B,0x44,0x24,0x0C )   /* mov         ax,word ptr [esp+12]  */ \
_LINE3( 0x66,0x8B,0xC8 )             /* mov         cx,ax  */ \
_LINE4( 0x66,0x25,0xFF,0xF3 )        /* and         ax,0F3FFh  */ \
_LINE4( 0x66,0x0D,0x00,0x0C )        /* or          ax,C00h  */ \
_LINE5( 0x66,0x89,0x44,0x24,0x0C )   /* mov         word ptr [esp+12],ax  */ \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fld1 ) \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld dword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld dword ptr [eax+4] ) \
_LINE5( 0x66,0x89,0x4C,0x24,0x0C )   /* mov         word ptr [esp+12],cx  */ \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fmul dword ptr [eax+0x8] ) \
ASM( fistp dword ptr [edx+8]  ) \
_LINE2( 0xDD,0xD8 )                  /* fstp        st(0)  */ \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_END_ASM

/// умножение трехмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DMUL2NTRUNCSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x7F ) \
ASM( and eax,0xFF ) \
ASM( shl eax,23 ) \
ASM( movd xmm0,eax ) \
ASM( mov eax,[esp+4] ) \
ASM( movss xmm1,[eax] ) \
ASM( movss xmm2,[eax+4] ) \
ASM( movss xmm3,[eax+8] ) \
ASM( mulss xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulss xmm2,xmm0 ) \
ASM( mulss xmm3,xmm0 ) \
ASM( cvttss2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvttss2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
ASM( cvttss2si    edx,xmm3 ) \
ASM( mov [eax+8],edx ) \
_END_ASM

/// умножение четырехмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DMUL2NTRUNCFPU_STD \
_BEGIN_ASM \
ASM( fild dword ptr [esp+12] ) \
_LINE4( 0xD9,0x7C,0x24,0x0C )        /* fnstcw      word ptr [esp+12]  */ \
_LINE5( 0x66,0x8B,0x44,0x24,0x0C )   /* mov         ax,word ptr [esp+12]  */ \
_LINE3( 0x66,0x8B,0xC8 )             /* mov         cx,ax  */ \
_LINE4( 0x66,0x25,0xFF,0xF3 )        /* and         ax,0F3FFh  */ \
_LINE4( 0x66,0x0D,0x00,0x0C )        /* or          ax,C00h  */ \
_LINE5( 0x66,0x89,0x44,0x24,0x0C )   /* mov         word ptr [esp+12],ax  */ \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fld1 ) \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld dword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld dword ptr [eax+4] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fld dword ptr [eax+8] ) \
_LINE5( 0x66,0x89,0x4C,0x24,0x0C )   /* mov         word ptr [esp+12],cx  */ \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+8]  ) \
ASM( fmul dword ptr [eax+12] ) \
ASM( fistp dword ptr [edx+12]  ) \
_LINE2( 0xDD,0xD8 )                  /* fstp        st(0)  */ \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_END_ASM

/// умножение четырехмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DMUL2NTRUNCSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x7F ) \
ASM( and eax,0xFF ) \
ASM( shl eax,23 ) \
ASM( movd xmm0,eax ) \
ASM( mov eax,[esp+4] ) \
ASM( movss xmm1,[eax] ) \
ASM( movss xmm2,[eax+4] ) \
ASM( movss xmm3,[eax+8] ) \
ASM( movss xmm4,[eax+12] ) \
ASM( mulss xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulss xmm2,xmm0 ) \
ASM( mulss xmm3,xmm0 ) \
ASM( mulss xmm4,xmm0 ) \
ASM( cvttss2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvttss2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
ASM( cvttss2si    edx,xmm3 ) \
ASM( mov [eax+8],edx ) \
ASM( cvttss2si    edx,xmm4 ) \
ASM( mov [eax+12],edx ) \
_END_ASM

/// умножение двухмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP2DDMUL2NTRUNCFPU_STD \
_BEGIN_ASM \
ASM( fild dword ptr [esp+12] ) \
_LINE4( 0xD9,0x7C,0x24,0x0C )        /* fnstcw      word ptr [esp+12]  */ \
_LINE5( 0x66,0x8B,0x44,0x24,0x0C )   /* mov         ax,word ptr [esp+12]  */ \
_LINE3( 0x66,0x8B,0xC8 )             /* mov         cx,ax  */ \
_LINE4( 0x66,0x25,0xFF,0xF3 )        /* and         ax,0F3FFh  */ \
_LINE4( 0x66,0x0D,0x00,0x0C )        /* or          ax,C00h  */ \
_LINE5( 0x66,0x89,0x44,0x24,0x0C )   /* mov         word ptr [esp+12],ax  */ \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fld1 ) \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld qword ptr [eax] ) \
ASM( fmul st,st(1) ) \
_LINE5( 0x66,0x89,0x4C,0x24,0x0C )   /* mov         word ptr [esp+12],cx  */ \
ASM( fistp dword ptr [edx]  ) \
ASM( fmul qword ptr [eax+8] ) \
ASM( fistp dword ptr [edx+4]  ) \
_LINE2( 0xDD,0xD8 )                  /* fstp        st(0)  */ \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_END_ASM

/// умножение двухмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DDMUL2NTRUNCSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x3FF ) \
ASM( and eax,0x7FF ) \
ASM( shl eax,20 ) \
ASM( movd xmm0,eax ) \
ASM( shufps xmm0,xmm0,1 ) \
ASM( mov eax,[esp+4] ) \
ASM( movsd xmm1,[eax] ) \
ASM( movsd xmm2,[eax+8] ) \
ASM( mulsd xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulsd xmm2,xmm0 ) \
ASM( cvttsd2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvttsd2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
_END_ASM

/// умножение трехмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DDMUL2NTRUNCFPU_STD \
_BEGIN_ASM \
ASM( fild dword ptr [esp+12] ) \
_LINE4( 0xD9,0x7C,0x24,0x0C )        /* fnstcw      word ptr [esp+12]  */ \
_LINE5( 0x66,0x8B,0x44,0x24,0x0C )   /* mov         ax,word ptr [esp+12]  */ \
_LINE3( 0x66,0x8B,0xC8 )             /* mov         cx,ax  */ \
_LINE4( 0x66,0x25,0xFF,0xF3 )        /* and         ax,0F3FFh  */ \
_LINE4( 0x66,0x0D,0x00,0x0C )        /* or          ax,C00h  */ \
_LINE5( 0x66,0x89,0x44,0x24,0x0C )   /* mov         word ptr [esp+12],ax  */ \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fld1 ) \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld qword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld qword ptr [eax+8] ) \
_LINE5( 0x66,0x89,0x4C,0x24,0x0C )   /* mov         word ptr [esp+12],cx  */ \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fmul qword ptr [eax+0x10] ) \
ASM( fistp dword ptr [edx+8]  ) \
_LINE2( 0xDD,0xD8 )                  /* fstp        st(0)  */ \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_END_ASM

/// умножение трехмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DDMUL2NTRUNCSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x3FF ) \
ASM( and eax,0x7FF ) \
ASM( shl eax,20 ) \
ASM( movd xmm0,eax ) \
ASM( shufps xmm0,xmm0,1 ) \
ASM( mov eax,[esp+4] ) \
ASM( movsd xmm1,[eax] ) \
ASM( movsd xmm2,[eax+8] ) \
ASM( movsd xmm3,[eax+16] ) \
ASM( mulsd xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulsd xmm2,xmm0 ) \
ASM( mulsd xmm3,xmm0 ) \
ASM( cvttsd2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvttsd2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
ASM( cvttsd2si    edx,xmm3 ) \
ASM( mov [eax+8],edx ) \
_END_ASM

/// умножение четырехмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DDMUL2NTRUNCFPU_STD \
_BEGIN_ASM \
ASM( fild dword ptr [esp+12] ) \
_LINE4( 0xD9,0x7C,0x24,0x0C )        /* fnstcw      word ptr [esp+12]  */ \
_LINE5( 0x66,0x8B,0x44,0x24,0x0C )   /* mov         ax,word ptr [esp+12]  */ \
_LINE3( 0x66,0x8B,0xC8 )             /* mov         cx,ax  */ \
_LINE4( 0x66,0x25,0xFF,0xF3 )        /* and         ax,0F3FFh  */ \
_LINE4( 0x66,0x0D,0x00,0x0C )        /* or          ax,C00h  */ \
_LINE5( 0x66,0x89,0x44,0x24,0x0C )   /* mov         word ptr [esp+12],ax  */ \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fld1 ) \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld qword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fld qword ptr [eax+0x10] ) \
_LINE5( 0x66,0x89,0x4C,0x24,0x0C )   /* mov         word ptr [esp+12],cx  */ \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+8]  ) \
ASM( fmul qword ptr [eax+0x18] ) \
ASM( fistp dword ptr [edx+12]  ) \
_LINE2( 0xDD,0xD8 )                  /* fstp        st(0)  */ \
_LINE4( 0xD9,0x6C,0x24,0x0C )        /* fldcw       word ptr [esp+12]  */ \
_END_ASM

/// умножение четырехмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DDMUL2NTRUNCSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x3FF ) \
ASM( and eax,0x7FF ) \
ASM( shl eax,20 ) \
ASM( movd xmm0,eax ) \
ASM( shufps xmm0,xmm0,1 ) \
ASM( mov eax,[esp+4] ) \
ASM( movsd xmm1,[eax] ) \
ASM( movsd xmm2,[eax+8] ) \
ASM( movsd xmm3,[eax+16] ) \
ASM( movsd xmm4,[eax+24] ) \
ASM( mulsd xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulsd xmm2,xmm0 ) \
ASM( mulsd xmm3,xmm0 ) \
ASM( mulsd xmm4,xmm0 ) \
ASM( cvttsd2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvttsd2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
ASM( cvttsd2si    edx,xmm3 ) \
ASM( mov [eax+8],edx ) \
ASM( cvttsd2si    edx,xmm4 ) \
ASM( mov [eax+12],edx ) \
_END_ASM

//**************************** MUL2N ROUND STDCALL *********************************
// mul2n round vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *, ecx=[esp+12]-int

/// умножение двухмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP2DMUL2NROUNDFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld dword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fmul dword ptr [eax+4] ) \
ASM( fistp dword ptr [edx+4]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение двухмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP2DMUL2NROUNDSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x7F ) \
ASM( and eax,0xFF ) \
ASM( shl eax,23 ) \
ASM( movd xmm0,eax ) \
ASM( mov eax,[esp+4] ) \
ASM( movss xmm1,[eax] ) \
ASM( movss xmm2,[eax+4] ) \
ASM( mulss xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulss xmm2,xmm0 ) \
ASM( cvtss2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvtss2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
_END_ASM

/// умножение трехмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DMUL2NROUNDFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld dword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld dword ptr [eax+4] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fmul dword ptr [eax+8] ) \
ASM( fistp dword ptr [edx+8]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение трехмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DMUL2NROUNDSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x7F ) \
ASM( and eax,0xFF ) \
ASM( shl eax,23 ) \
ASM( movd xmm0,eax ) \
ASM( mov eax,[esp+4] ) \
ASM( movss xmm1,[eax] ) \
ASM( movss xmm2,[eax+4] ) \
ASM( movss xmm3,[eax+8] ) \
ASM( mulss xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulss xmm2,xmm0 ) \
ASM( mulss xmm3,xmm0 ) \
ASM( cvtss2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvtss2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
ASM( cvtss2si    edx,xmm3 ) \
ASM( mov [eax+8],edx ) \
_END_ASM

/// умножение четырехмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DMUL2NROUNDFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld dword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld dword ptr [eax+4] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fld dword ptr [eax+8] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+8]  ) \
ASM( fmul dword ptr [eax+12] ) \
ASM( fistp dword ptr [edx+12]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение четырехмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DMUL2NROUNDSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x7F ) \
ASM( and eax,0xFF ) \
ASM( shl eax,23 ) \
ASM( movd xmm0,eax ) \
ASM( mov eax,[esp+4] ) \
ASM( movss xmm1,[eax] ) \
ASM( movss xmm2,[eax+4] ) \
ASM( movss xmm3,[eax+8] ) \
ASM( movss xmm4,[eax+12] ) \
ASM( mulss xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulss xmm2,xmm0 ) \
ASM( mulss xmm3,xmm0 ) \
ASM( mulss xmm4,xmm0 ) \
ASM( cvtss2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvtss2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
ASM( cvtss2si    edx,xmm3 ) \
ASM( mov [eax+8],edx ) \
ASM( cvtss2si    edx,xmm4 ) \
ASM( mov [eax+12],edx ) \
_END_ASM

/// умножение четырехмерного вектора одинарной точности на 2 в степени N и последующее округление в челочисленный, команды SSE4.
/// @brief for CPUTYPE3
#define VECTORP4DMUL2NROUNDSSE4_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x7F ) \
ASM( and eax,0xFF ) \
ASM( shl eax,23 ) \
ASM( movd xmm0,eax ) \
ASM( mov eax,[esp+4] ) \
ASM( shufps xmm0,xmm0,0x0 ) \
ASM( lddqu xmm1,[eax] ) \
ASM( mulps xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( cvtps2dq    xmm2,xmm1 ) \
ASM( movupd [eax],xmm2 ) \
_END_ASM

/// умножение двухмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP2DDMUL2NROUNDFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld qword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fmul qword ptr [eax+8] ) \
ASM( fistp dword ptr [edx+4]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение двухмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды SSE.
/// @brief for CPUTYPE3
#define VECTORP2DDMUL2NROUNDSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x3FF ) \
ASM( and eax,0x7FF ) \
ASM( shl eax,20 ) \
ASM( movd xmm0,eax ) \
ASM( shufps xmm0,xmm0,1 ) \
ASM( mov eax,[esp+4] ) \
ASM( movsd xmm1,[eax] ) \
ASM( movsd xmm2,[eax+8] ) \
ASM( mulsd xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulsd xmm2,xmm0 ) \
ASM( cvtsd2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvtsd2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
_END_ASM

/// умножение трехмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP3DDMUL2NROUNDFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld qword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fmul qword ptr [eax+0x10] ) \
ASM( fistp dword ptr [edx+8]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение трехмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP3DDMUL2NROUNDSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x3FF ) \
ASM( and eax,0x7FF ) \
ASM( shl eax,20 ) \
ASM( movd xmm0,eax ) \
ASM( shufps xmm0,xmm0,1 ) \
ASM( mov eax,[esp+4] ) \
ASM( movsd xmm1,[eax] ) \
ASM( movsd xmm2,[eax+8] ) \
ASM( movsd xmm3,[eax+16] ) \
ASM( mulsd xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulsd xmm2,xmm0 ) \
ASM( mulsd xmm3,xmm0 ) \
ASM( cvtsd2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvtsd2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
ASM( cvtsd2si    edx,xmm3 ) \
ASM( mov [eax+8],edx ) \
_END_ASM

/// умножение четырехмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды FPU.
/// @brief for CPUTYPE1
#define VECTORP4DDMUL2NROUNDFPU_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+4] ) \
ASM( mov edx,[esp+8] ) \
ASM( fild dword ptr [esp+12] ) \
ASM( fld1 ) \
_LINE2( 0xD9,0xFD )                                         /* fscale  */ \
ASM( fld qword ptr [eax] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx]  ) \
ASM( fld qword ptr [eax+8] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+4]  ) \
ASM( fld qword ptr [eax+0x10] ) \
ASM( fmul st,st(1) ) \
ASM( fistp dword ptr [edx+8]  ) \
ASM( fmul qword ptr [eax+0x18] ) \
ASM( fistp dword ptr [edx+12]  ) \
_LINE2( 0xDD,0xD8 )                                         /* fstp        st(0)  */ \
_END_ASM

/// умножение четырехмерного вектора двойной точности на 2 в степени N и последующее округление в челочисленный, команды SSE2.
/// @brief for CPUTYPE3
#define VECTORP4DDMUL2NROUNDSSE2_STD \
_BEGIN_ASM \
ASM( mov eax,[esp+12] ) \
ASM( add eax,0x3FF ) \
ASM( and eax,0x7FF ) \
ASM( shl eax,20 ) \
ASM( movd xmm0,eax ) \
ASM( shufps xmm0,xmm0,1 ) \
ASM( mov eax,[esp+4] ) \
ASM( movsd xmm1,[eax] ) \
ASM( movsd xmm2,[eax+8] ) \
ASM( movsd xmm3,[eax+16] ) \
ASM( movsd xmm4,[eax+24] ) \
ASM( mulsd xmm1,xmm0 ) \
ASM( mov eax,[esp+8] ) \
ASM( mulsd xmm2,xmm0 ) \
ASM( mulsd xmm3,xmm0 ) \
ASM( mulsd xmm4,xmm0 ) \
ASM( cvtsd2si    edx,xmm1 ) \
ASM( mov [eax],edx ) \
ASM( cvtsd2si    edx,xmm2 ) \
ASM( mov [eax+4],edx ) \
ASM( cvtsd2si    edx,xmm3 ) \
ASM( mov [eax+8],edx ) \
ASM( cvtsd2si    edx,xmm4 ) \
ASM( mov [eax+12],edx ) \
_END_ASM

#endif