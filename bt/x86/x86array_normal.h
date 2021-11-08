//=============================================================================
///**
// *  @file x86array_normal.h
// *
// *  $Id: x86array_normal.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float normal, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef X86ARRAY_NORMAL_H_
#define X86ARRAY_NORMAL_H_

//**************************** NORMAL STDCALL *********************************
// array vectors eax=[esp+4]-a void *, edx=[esp+8]-b void * [esp+12]-stepa unsigned int  [esp+16]-stepb unsigned int ecx=[esp+20]-count unsigned int

/// нормализация массива двухмерных векторов, команды FPU
#define ARRAYP2DNORMALFPU_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov ecx,[esp+20] ) \
ASM( mov edx,[esp+8] ) \
ASM( mov edi,[esp+12] ) \
ASM( mov esi,[esp+16] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP2DNormalFPUend_loop ) \
ASM( _ArrayP2DNormalFPUmloop: ) \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE2( 0xD9,0x1A )                                         /* fstp        dword ptr [edx]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x5A,0x04 )                                    /* fstp        dword ptr [edx+4]  */ \
ASM( add eax,edi ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DNormalFPUmloop ) \
ASM( _ArrayP2DNormalFPUend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива двухмерных векторов, команды SSE
#define ARRAYP2DNORMALSSE_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov ecx,[esp+20] ) \
ASM( mov edx,[esp+8] ) \
ASM( mov edi,[esp+12] ) \
ASM( mov esi,[esp+16] ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP2DNormalSSEend_loop ) \
ASM( _ArrayP2DNormalSSEmloop: ) \
ASM( movlps xmm2,qword ptr [eax] ) \
ASM( movlps xmm3,qword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movhps xmm2,qword ptr [eax] ) \
ASM( movhps xmm3,qword ptr [eax+edi] ) \
ASM( movaps xmm0,xmm2 ) \
ASM( movaps xmm1,xmm3 ) \
ASM( mulps xmm0,xmm0 ) \
ASM( mulps xmm1,xmm1 ) \
ASM( movaps xmm4,xmm0 ) \
ASM( movaps xmm5,xmm1 ) \
ASM( shufps xmm0,xmm5,0x88 ) \
ASM( shufps xmm1,xmm4,0xDD ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( addps xmm0,xmm1 ) \
ASM( sqrtps xmm0,xmm0 ) \
ASM( movaps xmm4,xmm0 ) \
ASM( shufps xmm0,xmm0,0x50 ) \
ASM( shufps xmm4,xmm4,0xFA ) \
ASM( divps xmm2,xmm0 ) \
ASM( divps xmm3,xmm4 ) \
ASM( movlps qword ptr [edx],xmm2 ) \
ASM( movlps qword ptr [edx+esi],xmm3 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movhps qword ptr [edx],xmm2 ) \
ASM( movhps qword ptr [edx+esi],xmm3 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP2DNormalSSEmloop ) \
ASM( _ArrayP2DNormalSSEend_loop: ) \
ASM( mov ecx,[esp+20] ) \
ASM( xorps xmm2,xmm2 ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DNormalSSEend_loop2 ) \
ASM( _ArrayP2DNormalSSEmloop2: ) \
ASM( movlps xmm2,qword ptr [eax] ) \
ASM( movaps xmm0,xmm2 ) \
ASM( mulps xmm0,xmm0 ) \
ASM( movaps xmm4,xmm0 ) \
ASM( shufps xmm4,xmm4,0x01 ) \
ASM( addss xmm0,xmm4 ) \
ASM( add eax,edi ) \
ASM( sqrtss xmm0,xmm0 ) \
ASM( shufps xmm0,xmm0,0x50 ) \
ASM( divps xmm2,xmm0 ) \
ASM( movlps qword ptr [edx],xmm2 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DNormalSSEmloop2 ) \
ASM( _ArrayP2DNormalSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива двухмерных векторов, команды SSE3
#define ARRAYP2DNORMALSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov ecx,[esp+20] ) \
ASM( mov edx,[esp+8] ) \
ASM( mov edi,[esp+12] ) \
ASM( mov esi,[esp+16] ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP2DNormalSSE3end_loop ) \
ASM( _ArrayP2DNormalSSE3mloop: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movsd xmm3,qword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movhps xmm2,qword ptr [eax] ) \
ASM( movhps xmm3,qword ptr [eax+edi] ) \
ASM( movaps xmm0,xmm2 ) \
ASM( movaps xmm1,xmm3 ) \
ASM( mulps xmm0,xmm0 ) \
ASM( mulps xmm1,xmm1 ) \
ASM( movaps xmm4,xmm0 ) \
ASM( movaps xmm5,xmm1 ) \
ASM( shufps xmm0,xmm5,0x88 ) \
ASM( shufps xmm1,xmm4,0xDD ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( addps xmm0,xmm1 ) \
ASM( sqrtps xmm0,xmm0 ) \
ASM( movaps xmm4,xmm0 ) \
ASM( shufps xmm0,xmm0,0x50 ) \
ASM( shufps xmm4,xmm4,0xFA ) \
ASM( divps xmm2,xmm0 ) \
ASM( divps xmm3,xmm4 ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( movsd qword ptr [edx+esi],xmm3 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movhps qword ptr [edx],xmm2 ) \
ASM( movhps qword ptr [edx+esi],xmm3 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP2DNormalSSE3mloop ) \
ASM( _ArrayP2DNormalSSE3end_loop: ) \
ASM( mov ecx,[esp+20] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DNormalSSE3end_loop2 ) \
ASM( _ArrayP2DNormalSSE3mloop2: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movaps xmm0,xmm2 ) \
ASM( mulps xmm0,xmm0 ) \
ASM( movaps xmm4,xmm0 ) \
ASM( shufps xmm4,xmm4,0x01 ) \
ASM( addss xmm0,xmm4 ) \
ASM( add eax,edi ) \
ASM( sqrtss xmm0,xmm0 ) \
ASM( shufps xmm0,xmm0,0x50 ) \
ASM( divps xmm2,xmm0 ) \
ASM( movlps qword ptr [edx],xmm2 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DNormalSSE3mloop2 ) \
ASM( _ArrayP2DNormalSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива двухмерных векторов, команды SSE4
#define ARRAYP2DNORMALSSE4_STD \
_BEGIN_ASM \
_LINE4( 0x89,0x7C,0x24,0xF8 )        /* mov         dword ptr [esp-8],edi  */ \
_LINE4( 0x89,0x74,0x24,0xF4 )        /* mov         dword ptr [esp-0Ch],esi  */ \
_LINE4( 0x8B,0x4C,0x24,0x14 )        /* mov         ecx,dword ptr [esp+14h]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )        /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x7C,0x24,0x0C )        /* mov         edi,dword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x74,0x24,0x10 )        /* mov         esi,dword ptr [esp+10h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [esp+4]  */ \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP2DNormalSSE4end_loop ) \
ASM( _ArrayP2DNormalSSE4mloop: ) \
ASM( movsd xmm0,qword ptr [eax] ) \
ASM( movsd xmm1,qword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movsd xmm3,qword ptr [eax+edi] ) \
ASM( movsd xmm4,xmm0 ) \
ASM( movlhps xmm4,xmm2 ) \
ASM( movsd xmm5,xmm1 ) \
ASM( movlhps xmm5,xmm3 ) \
ASM( dpps xmm0,xmm0,0x31 ) \
ASM( dpps xmm1,xmm1,0x34 ) \
ASM( dpps xmm2,xmm2,0x32 ) \
ASM( dpps xmm3,xmm3,0x38 ) \
ASM( orps xmm0,xmm1 ) \
ASM( orps xmm2,xmm3 ) \
ASM( orps xmm0,xmm2 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( sqrtps xmm0,xmm0 ) \
ASM( movaps xmm1,xmm0 ) \
ASM( shufps xmm0,xmm0,0x50 ) \
ASM( shufps xmm1,xmm1,0xFA ) \
ASM( divps xmm4,xmm0 ) \
ASM( divps xmm5,xmm1 ) \
ASM( movsd qword ptr [edx],xmm4 ) \
ASM( movsd qword ptr [edx+esi],xmm5 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movhps qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+esi],xmm5 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP2DNormalSSE4mloop ) \
ASM( _ArrayP2DNormalSSE4end_loop: ) \
ASM( mov ecx,[esp+20] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DNormalSSE4end_loop2 ) \
ASM( _ArrayP2DNormalSSE4mloop2: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movaps xmm0,xmm2 ) \
ASM( dpps xmm0,xmm0,0x31 ) \
ASM( add eax,edi ) \
ASM( sqrtss xmm0,xmm0 ) \
ASM( shufps xmm0,xmm0,0x50 ) \
ASM( divps xmm2,xmm0 ) \
ASM( movlps qword ptr [edx],xmm2 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DNormalSSE4mloop2 ) \
ASM( _ArrayP2DNormalSSE4end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива трехмерных векторов, команды FPU
#define ARRAYP3DNORMALFPU_STD \
_BEGIN_ASM \
_LINE4( 0x89,0x7C,0x24,0xF8 )        /* mov         dword ptr [esp-8],edi  */ \
_LINE4( 0x89,0x74,0x24,0xF4 )        /* mov         dword ptr [esp-0Ch],esi  */ \
_LINE4( 0x8B,0x4C,0x24,0x14 )        /* mov         ecx,dword ptr [esp+14h]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )        /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x7C,0x24,0x0C )        /* mov         edi,dword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x74,0x24,0x10 )        /* mov         esi,dword ptr [esp+10h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [esp+4]  */ \
ASM( jecxz _ArrayP3DNormalFPUend_loop ) \
ASM( _ArrayP3DNormalFPUmloop: ) \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
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
ASM( add eax,edi ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DNormalFPUmloop ) \
ASM( _ArrayP3DNormalFPUend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива трехмерных векторов, команды SSE ???
#define ARRAYP3DNORMALSSE_STD \
_BEGIN_ASM \
_LINE4( 0x89,0x7C,0x24,0xF8 )        /* mov         dword ptr [esp-8],edi  */ \
_LINE4( 0x89,0x74,0x24,0xF4 )        /* mov         dword ptr [esp-0Ch],esi  */ \
_LINE4( 0x8B,0x4C,0x24,0x14 )        /* mov         ecx,dword ptr [esp+14h]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )        /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x7C,0x24,0x0C )        /* mov         edi,dword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x74,0x24,0x10 )        /* mov         esi,dword ptr [esp+10h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [esp+4]  */ \
_LINE3( 0xC1,0xE9,0x02 )             /* shr         ecx,2  */ \
ASM( jnz _ArrayP3DNormalSSEmloop ) \
ASM( jmp _ArrayP3DNormalSSEend_loop ) \
ASM( _ArrayP3DNormalSSEmloop: ) \
ASM( movss xmm0,dword ptr [eax] ) \
ASM( movss xmm1,dword ptr [eax+edi] ) \
ASM( movhps xmm0,qword ptr [eax+4] ) \
ASM( movhps xmm1,qword ptr [eax+edi+4] ) \
ASM( movaps xmm4,xmm0 ) \
ASM( movaps xmm5,xmm1 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( mulps xmm4,xmm4 ) \
ASM( mulps xmm5,xmm5 ) \
ASM( movss xmm2,dword ptr [eax] ) \
ASM( movss xmm3,dword ptr [eax+edi] ) \
ASM( movhps xmm2,qword ptr [eax+4] ) \
ASM( movhps xmm3,qword ptr [eax+edi+4] ) \
ASM( movaps xmm6,xmm4 ) \
ASM( movlhps xmm6,xmm5 ) \
ASM( shufps xmm4,xmm5,0xEE ) \
ASM( addps xmm4,xmm6 ) \
ASM( movaps xmm7,xmm3 ) \
ASM( movaps xmm6,xmm2 ) \
ASM( mulps xmm7,xmm7 ) \
ASM( mulps xmm6,xmm6 ) \
ASM( movaps xmm5,xmm6 ) \
ASM( movlhps xmm5,xmm7 ) \
ASM( shufps xmm6,xmm7,0xEE ) \
ASM( addps xmm6,xmm5 ) \
ASM( movaps xmm7,xmm4 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( shufps xmm7,xmm6,0x88 ) \
ASM( shufps xmm4,xmm6,0xDD ) \
ASM( addps xmm4,xmm7 ) \
ASM( sqrtps xmm4,xmm4 ) \
_LINE3( 0x0F,0x28,0xFC )           /* movaps      xmm7,xmm4  */ \
_LINE3( 0x0F,0x28,0xEC )           /* movaps      xmm5,xmm4  */ \
_LINE3( 0x0F,0x28,0xF7 )           /* movaps      xmm6,xmm7  */ \
_LINE4( 0x0F,0xC6,0xE4,0x00 )        /* shufps      xmm4,xmm4,0  */ \
_LINE4( 0x0F,0xC6,0xED,0x55 )        /* shufps      xmm5,xmm5,55h  */ \
_LINE4( 0x0F,0xC6,0xF6,0xAA )        /* shufps      xmm6,xmm6,0AAh  */ \
_LINE4( 0x0F,0xC6,0xFF,0xFF )        /* shufps      xmm7,xmm7,0FFh  */ \
_LINE3( 0x0F,0x5E,0xC4 )           /* divps       xmm0,xmm4  */ \
_LINE3( 0x0F,0x5E,0xCD )           /* divps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x5E,0xD6 )           /* divps       xmm2,xmm6  */ \
_LINE3( 0x0F,0x5E,0xDF )           /* divps       xmm3,xmm7  */ \
ASM( movss dword ptr [edx],xmm0 ) \
ASM( movss dword ptr [edx+esi],xmm1 ) \
ASM( movhps qword ptr [edx+4],xmm0 ) \
ASM( movhps qword ptr [edx+esi+4],xmm1 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movss dword ptr [edx],xmm2 ) \
ASM( movss dword ptr [edx+esi],xmm3 ) \
ASM( movhps qword ptr [edx+4],xmm2 ) \
ASM( movhps qword ptr [edx+esi+4],xmm3 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( dec ecx ) \
ASM( jecxz _ArrayP3DNormalSSEend_loop ) \
ASM( jmp _ArrayP3DNormalSSEmloop ) \
ASM( _ArrayP3DNormalSSEend_loop: ) \
ASM( mov ecx,[esp+20] ) \
ASM( xorps xmm2,xmm2 ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP3DNormalSSEend_loop2 ) \
ASM( _ArrayP3DNormalSSEmloop2: ) \
_LINE5( 0xF3,0x0F,0x10,0x40,0x08 )                          /* movss       xmm0,dword ptr [eax+8]  */ \
_LINE3( 0x0F,0x16,0x00 )                                    /* movhps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x28,0xD1 )                                    /* movaps      xmm2,xmm1  */ \
_LINE4( 0x0F,0xC6,0xC9,0x0E )                               /* shufps      xmm1,xmm1,0Eh  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
ASM( add eax,edi ) \
_LINE4( 0x0F,0xC6,0xC9,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
_LINE4( 0xF3,0x0F,0x51,0xD2 )                               /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x5E,0xC2 )                                    /* divps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x17,0x02 )                                    /* movhps      qword ptr [edx],xmm0  */ \
_LINE5( 0xF3,0x0F,0x11,0x42,0x08 )                          /* movss       dword ptr [edx+8],xmm0  */ \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DNormalSSEmloop2 ) \
ASM( _ArrayP3DNormalSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива четырехмерных векторов, команды FPU
#define ARRAYP4DNORMALFPU_STD \
_BEGIN_ASM \
_LINE4( 0x89,0x7C,0x24,0xF8 )        /* mov         dword ptr [esp-8],edi  */ \
_LINE4( 0x89,0x74,0x24,0xF4 )        /* mov         dword ptr [esp-0Ch],esi  */ \
_LINE4( 0x8B,0x4C,0x24,0x14 )        /* mov         ecx,dword ptr [esp+14h]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )        /* mov         edx,dword ptr [esp+8]  */ \
_LINE4( 0x8B,0x7C,0x24,0x0C )        /* mov         edi,dword ptr [esp+0Ch]  */ \
_LINE4( 0x8B,0x74,0x24,0x10 )        /* mov         esi,dword ptr [esp+10h]  */ \
_LINE4( 0x8B,0x44,0x24,0x04 )        /* mov         eax,dword ptr [esp+4]  */ \
ASM( jecxz _ArrayP4DNormalFPUend_loop ) \
ASM( _ArrayP4DNormalFPUmloop: ) \
_LINE4( 0x8B,0x44,0x24,0x04 )                               /* mov         eax,dword ptr [esp+4]  */ \
_LINE2( 0xD9,0x00 )                                         /* fld         dword ptr [eax]  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8]  */ \
_LINE3( 0xD9,0x40,0x04 )                                    /* fld         dword ptr [eax+4]  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x08 )                                    /* fld         dword ptr [eax+8]  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE3( 0xD9,0x40,0x0C )                                    /* fld         dword ptr [eax+12]  */ \
_LINE3( 0xD8,0x48,0x0C )                                    /* fmul        dword ptr [eax+12]  */ \
_LINE2( 0xDE,0xC1 )                                         /* faddp       st(1),st  */ \
_LINE2( 0xD9,0xFA )                                         /* fsqrt             */ \
_LINE2( 0xD9,0xE8 )                                         /* fld1              */ \
_LINE2( 0xDE,0xF1 )                                         /* fdivrp      st(1),st  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE2( 0xD8,0x08 )                                         /* fmul        dword ptr [eax]  */ \
_LINE2( 0xD9,0x1A )                                         /* fstp        dword ptr [edx]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE3( 0xD8,0x48,0x04 )                                    /* fmul        dword ptr [eax+4]  */ \
_LINE3( 0xD9,0x5A,0x04 )                                    /* fstp        dword ptr [edx+4]  */ \
_LINE2( 0xD9,0xC0 )                                         /* fld         st(0)  */ \
_LINE3( 0xD8,0x48,0x08 )                                    /* fmul        dword ptr [eax+8]  */ \
_LINE3( 0xD9,0x5A,0x08 )                                    /* fstp        dword ptr [edx+8]  */ \
_LINE3( 0xD8,0x48,0x0C )                                    /* fmul        dword ptr [eax+12]  */ \
_LINE3( 0xD9,0x5A,0x0C )                                    /* fstp        dword ptr [edx+12]  */ \
ASM( add eax,edi ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DNormalFPUmloop ) \
ASM( _ArrayP4DNormalFPUend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива четырехмерных векторов, команды SSE
#define ARRAYP4DNORMALSSE_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov ecx,[esp+20] ) \
ASM( mov edx,[esp+8] ) \
ASM( mov edi,[esp+12] ) \
ASM( mov esi,[esp+16] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DNormalSSEend_loop2 ) \
ASM( xorps xmm3,xmm3 ) \
ASM( _ArrayP4DNormalSSEmloop2: ) \
ASM( xorps xmm0,xmm0 ) \
_LINE4( 0x0F,0x12,0x58,0x08 )                               /* movlps      xmm3,qword ptr [eax+8]  */ \
_LINE3( 0x0F,0x12,0x00 )                                    /* movlps      xmm0,qword ptr [eax]  */ \
_LINE3( 0x0F,0x28,0xC8 )                                    /* movaps      xmm1,xmm0  */ \
_LINE3( 0x0F,0x28,0xD3 )                                    /* movaps      xmm2,xmm3  */ \
_LINE3( 0x0F,0x59,0xC9 )                                    /* mulps       xmm1,xmm1  */ \
_LINE3( 0x0F,0x59,0xD2 )                                    /* mulps       xmm2,xmm2  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE3( 0x0F,0x28,0xCA )                                    /* movaps      xmm1,xmm2  */ \
ASM( add eax,edi ) \
_LINE4( 0x0F,0xC6,0xD2,0x01 )                               /* shufps      xmm1,xmm1,1  */ \
_LINE4( 0xF3,0x0F,0x58,0xD1 )                               /* addss       xmm2,xmm1  */ \
ASM( movlhps xmm0,xmm3 ) \
_LINE4( 0xF3,0x0F,0x51,0xD2 )                               /* sqrtss      xmm2,xmm2  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE4( 0x8B,0x54,0x24,0x08 )                               /* mov         edx,dword ptr [esp+8] */ \
_LINE3( 0x0F,0x5E,0xC2 )                                    /* divps       xmm0,xmm2  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
_LINE4( 0x0F,0x17,0x42,0x08 )                               /* movhps      qword ptr [edx+8],xmm0 */ \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DNormalSSEmloop2 ) \
ASM( _ArrayP4DNormalSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива четырехмерных векторов, команды SSE3
#define ARRAYP4DNORMALSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( lddqu xmm0,xmmword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DNormalSSE3end_loop ) \
ASM( _ArrayP4DNormalSSE3mloop: ) \
ASM( lddqu xmm2,xmmword ptr [eax] ) \
ASM( addps xmm2,xmm0 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
ASM( movsd qword ptr [edx+8],xmm2 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DNormalSSE3mloop ) \
ASM( _ArrayP4DNormalSSE3end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива двухмерных векторов двойной точности, команды FPU
#define ARRAYP2DDNORMALFPU_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov ecx,[esp+20] ) \
ASM( mov edx,[esp+8] ) \
ASM( mov edi,[esp+12] ) \
ASM( mov esi,[esp+16] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP2DDNormalFPUend_loop ) \
ASM( _ArrayP2DDNormalFPUmloop: ) \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD9) _DB(0xFA)) \
 _STR(_DB(0xD9) _DB(0xE8)) \
 _STR(_DB(0xDE) _DB(0xF1)) \
 _STR(_DB(0xD9) _DB(0xC0)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x1A)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x08)) \
ASM( add eax,edi ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DDNormalFPUmloop ) \
ASM( _ArrayP2DDNormalFPUend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива двухмерных векторов двойной точности, команды SSE2
#define ARRAYP2DDNORMALSSE2_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movsd xmm0,qword ptr [eax] ) \
ASM( movsd xmm1,qword ptr [eax+8] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP2DDNormalSSE2end_loop ) \
ASM( _ArrayP2DDNormalSSE2mloop: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movsd xmm3,qword ptr [eax+8] ) \
ASM( addsd xmm2,xmm0 ) \
ASM( addsd xmm3,xmm1 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( movsd qword ptr [edx+8],xmm3 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DDNormalSSE2mloop ) \
ASM( _ArrayP2DDNormalSSE2end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива двухмерных векторов двойной точности, команды SSE3
#define ARRAYP2DDNORMALSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( lddqu xmm0,xmmword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP2DDNormalSSE3end_loop ) \
ASM( _ArrayP2DDNormalSSE3mloop: ) \
ASM( lddqu xmm2,xmmword ptr [eax] ) \
ASM( addpd xmm2,xmm0 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
ASM( movsd qword ptr [edx+8],xmm2 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DDNormalSSE3mloop ) \
ASM( _ArrayP2DDNormalSSE3end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива трехмерных векторов двойной точности, команды FPU
#define ARRAYP3DDNORMALFPU_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov ecx,[esp+20] ) \
ASM( mov edx,[esp+8] ) \
ASM( mov edi,[esp+12] ) \
ASM( mov esi,[esp+16] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP3DDNormalFPUend_loop ) \
ASM( _ArrayP3DDNormalFPUmloop: ) \
 _STR(_DB(0xDD) _DB(0x00)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x10)) \
 _STR(_DB(0xDE) _DB(0xC1)) \
 _STR(_DB(0xD9) _DB(0xFA)) \
 _STR(_DB(0xD9) _DB(0xE8)) \
 _STR(_DB(0xDE) _DB(0xF1)) \
 _STR(_DB(0xD9) _DB(0xC0)) \
 _STR(_DB(0xDC) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x1A)) \
 _STR(_DB(0xD9) _DB(0xC0)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x08)) \
 _STR(_DB(0xDC) _DB(0x48) _DB(0x10)) \
 _STR(_DB(0xDD) _DB(0x5A) _DB(0x10)) \
ASM( add eax,edi ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DDNormalFPUmloop ) \
ASM( _ArrayP3DDNormalFPUend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива трехмерных векторов двойной точности, команды SSE2
#define ARRAYP3DDNORMALSSE2_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movsd xmm0,qword ptr [eax] ) \
ASM( movsd xmm1,qword ptr [eax+8] ) \
ASM( movsd xmm4,qword ptr [eax+16] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP3DDNormalSSE2end_loop ) \
ASM( _ArrayP3DDNormalSSE2mloop: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movsd xmm3,qword ptr [eax+4] ) \
ASM( movsd xmm5,qword ptr [eax+8] ) \
ASM( addsd xmm2,xmm0 ) \
ASM( addsd xmm3,xmm1 ) \
ASM( addsd xmm5,xmm4 ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( movsd qword ptr [edx+4],xmm3 ) \
ASM( movsd qword ptr [edx+8],xmm5 ) \
ASM( add eax,edi ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DDNormalSSE2mloop ) \
ASM( _ArrayP3DDNormalSSE2end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива четырехмерных векторов двойной точности, команды FPU
#define ARRAYP4DDNORMALFPU_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov ecx,[esp+20] ) \
ASM( mov edx,[esp+8] ) \
ASM( mov edi,[esp+12] ) \
ASM( mov esi,[esp+16] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DDNormalFPUend_loop ) \
ASM( _ArrayP4DDNormalFPUmloop: ) \
_LINE2( 0xDD,0x00 ) \
_LINE2( 0xDC,0x08 ) \
_LINE3( 0xDD,0x40,0x08 ) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x10)) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x10)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xDD) _DB(0x40) _DB(0x18)) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x18)) \
_STR(_DB(0xDE) _DB(0xC1)) \
_STR(_DB(0xD9) _DB(0xFA)) \
_STR(_DB(0xD9) _DB(0xE8)) \
_STR(_DB(0xDE) _DB(0xF1)) \
_STR(_DB(0xD9) _DB(0xC0)) \
_STR(_DB(0xDC) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x1A)) \
_STR(_DB(0xD9) _DB(0xC0)) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x08)) \
_STR(_DB(0xDD) _DB(0x5A) _DB(0x08)) \
_STR(_DB(0xD9) _DB(0xC0)) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x10)) \
_STR(_DB(0xDD) _DB(0x5A) _DB(0x10)) \
_STR(_DB(0xDC) _DB(0x48) _DB(0x18)) \
_STR(_DB(0xDD) _DB(0x5A) _DB(0x18)) \
ASM( add eax,edi ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DDNormalFPUmloop ) \
ASM( _ArrayP4DDNormalFPUend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива четырехмерных векторов двойной точности, команды SSE2
#define ARRAYP4DDNORMALSSE2_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movsd xmm0,qword ptr [eax] ) \
ASM( movsd xmm1,qword ptr [eax+8] ) \
ASM( movsd xmm2,qword ptr [eax+16] ) \
ASM( movsd xmm3,qword ptr [eax+24] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DDNormalSSE2end_loop ) \
ASM( _ArrayP4DDNormalSSE2mloop: ) \
ASM( movsd xmm4,qword ptr [eax] ) \
ASM( movsd xmm5,qword ptr [eax+8] ) \
ASM( movsd xmm6,qword ptr [eax+16] ) \
ASM( movsd xmm7,qword ptr [eax+24] ) \
ASM( addsd xmm4,xmm0 ) \
ASM( addsd xmm5,xmm1 ) \
ASM( addsd xmm6,xmm2 ) \
ASM( addsd xmm7,xmm3 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm4 ) \
ASM( movsd qword ptr [edx+8],xmm5 ) \
ASM( movsd qword ptr [edx+16],xmm6 ) \
ASM( movsd qword ptr [edx+24],xmm7 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DDNormalSSE2mloop ) \
ASM( _ArrayP4DDNormalSSE2end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// нормализация массива четырехмерных векторов двойной точности, команды SSE3
#define ARRAYP4DDNORMALSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( lddqu xmm0,xmmword ptr [eax] ) \
ASM( lddqu xmm1,xmmword ptr [eax+16] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DDNormalSSE3end_loop ) \
ASM( _ArrayP4DDNormalSSE3mloop: ) \
ASM( lddqu xmm2,xmmword ptr [eax] ) \
ASM( lddqu xmm3,xmmword ptr [eax+16] ) \
ASM( addpd xmm2,xmm0 ) \
ASM( addpd xmm3,xmm1 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
ASM( movsd qword ptr [edx+8],xmm2 ) \
ASM( movsd qword ptr [edx+16],xmm3 ) \
_LINE4( 0x66,0x0F,0x15,0xDB )                               /* unpckhpd    xmm3,xmm3  */ \
ASM( movsd qword ptr [edx+24],xmm3 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DDNormalSSE3mloop ) \
ASM( _ArrayP4DDNormalSSE3end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

#endif /* X86ARRAY_NORMAL_H_ */

