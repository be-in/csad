//=============================================================================
///**
// *  @file x86array_transform.h
// *
// *  $Id: x86array_transform.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float transform, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef X86ARRAY_TRANSFORM_H_
#define X86ARRAY_TRANSFORM_H_

//**************************** TRANSFORM ARRAY STDCALL *********************************
// array vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *  edx=[esp+12]-c void *  [esp+16]-stepa unsigned int  [esp+20]-stepc unsigned int ecx=[esp+24]-count unsigned int

/// трансформирование массива двухмерных векторов, команды SSE
#define ARRAYP2DTRANSFORMSSE_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( xorps xmm4,xmm4 ) \
ASM( xorps xmm5,xmm5 ) \
ASM( xorps xmm7,xmm7 ) \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
_LINE4( 0x0F,0x12,0x68,0x10 )                               /* movlps      xmm5,qword ptr [eax+10h]  */ \
_LINE4( 0x0F,0x12,0x78,0x30 )                               /* movlps      xmm7,qword ptr [eax+30h]  */ \
ASM( movlhps xmm4,xmm4 ) \
ASM( movlhps xmm5,xmm5 ) \
ASM( movlhps xmm7,xmm7 ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP2DTransformSSEend_loop ) \
ASM( _ArrayP2DTransformSSEmloop: ) \
ASM( movss xmm2,dword ptr [eax] ) \
ASM( movss xmm3,dword ptr [eax+4] ) \
ASM( movhps xmm2,qword ptr [eax+edi] ) \
ASM( shufps xmm3,xmm2,0xF0 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( shufps xmm2,xmm2,0xA0 ) \
ASM( movss xmm0,dword ptr [eax] ) \
ASM( movss xmm1,dword ptr [eax+4] ) \
ASM( movhps xmm0,qword ptr [eax+edi] ) \
ASM( shufps xmm1,xmm1,0xF0 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( shufps xmm0,xmm0,0xA0 ) \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE3( 0x0F,0x59,0xDD )                                    /* mulps       xmm3,xmm5  */ \
_LINE3( 0x0F,0x59,0xC4 )                                    /* mulps       xmm0,xmm4  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x58,0xC7 )                                    /* addps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x58,0xC3 )                                    /* addps       xmm0,xmm3  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
ASM( movhps qword ptr [edx+esi],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
ASM( movhps qword ptr [edx+esi],xmm0 ) \
ASM( loop _ArrayP2DTransformSSEmloop ) \
ASM( _ArrayP2DTransformSSEend_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DTransformSSEend_loop2 ) \
ASM( _ArrayP2DTransformSSEmloop2: ) \
ASM( movss xmm2,dword ptr [eax] ) \
ASM( movss xmm3,dword ptr [eax+4] ) \
_LINE4( 0x0F,0xC6,0xD2,0x50 )                               /* shufps      xmm2,xmm2,0x50  */ \
_LINE4( 0x0F,0xC6,0xDB,0x50 )                               /* shufps      xmm3,xmm3,0x50  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
ASM( add eax,edi ) \
_LINE3( 0x0F,0x59,0xDD )                                    /* mulps       xmm3,xmm5  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DTransformSSEmloop2 ) \
ASM( _ArrayP2DTransformSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// трансформирование массива двухмерных векторов, команды SSE3
#define ARRAYP2DTRANSFORMSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movsd xmm4,qword ptr [eax] ) \
ASM( movsd xmm5,qword ptr [eax+0x10] ) \
ASM( movsd xmm7,qword ptr [eax+0x30] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,1) \
ASM( jecxz _ArrayP2DTransformSSE3end_loop ) \
ASM( _ArrayP2DTransformSSE3mloop: ) \
ASM( movss xmm2,dword ptr [eax] ) \
ASM( movss xmm3,dword ptr [eax+4] ) \
_LINE4( 0x0F,0xC6,0xD2,0x50 )                               /* shufps      xmm2,xmm2,0x50  */ \
_LINE4( 0x0F,0xC6,0xDB,0x50 )                               /* shufps      xmm3,xmm3,0x50  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
ASM( add eax,edi ) \
_LINE3( 0x0F,0x59,0xDD )                                    /* mulps       xmm3,xmm5  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
ASM( movss xmm0,dword ptr [eax] ) \
ASM( movss xmm1,dword ptr [eax+4] ) \
ASM( add edx,esi ) \
_LINE4( 0x0F,0xC6,0xC0,0x50 )                               /* shufps      xmm0,xmm0,0x50  */ \
_LINE4( 0x0F,0xC6,0xC9,0x50 )                               /* shufps      xmm1,xmm1,0x50  */ \
_LINE3( 0x0F,0x59,0xC4 )                                    /* mulps       xmm0,xmm4  */ \
ASM( add eax,edi ) \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xC7 )                                    /* addps       xmm0,xmm7  */ \
_LINE3( 0x0F,0x58,0xC1 )                                    /* addps       xmm0,xmm1  */ \
_LINE3( 0x0F,0x13,0x02 )                                    /* movlps      qword ptr [edx],xmm0  */ \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DTransformSSE3mloop ) \
ASM( _ArrayP2DTransformSSE3end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,1 ) \
ASM( jecxz _ArrayP2DTransformSSE3end_loop2 ) \
ASM( _ArrayP2DTransformSSE3mloop2: ) \
ASM( movss xmm2,dword ptr [eax] ) \
ASM( movss xmm3,dword ptr [eax+4] ) \
_LINE4( 0x0F,0xC6,0xD2,0x50 )                               /* shufps      xmm2,xmm2,0x50  */ \
_LINE4( 0x0F,0xC6,0xDB,0x50 )                               /* shufps      xmm3,xmm3,0x50  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
ASM( add eax,edi ) \
_LINE3( 0x0F,0x59,0xDD )                                    /* mulps       xmm3,xmm5  */ \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DTransformSSE3mloop2 ) \
ASM( _ArrayP2DTransformSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// трансформирование массива трехмерных векторов, команды SSE
#define ARRAYP3DTRANSFORMSSE_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x60,0x08 )                               /* movhps      xmm4,qword ptr [eax+8]  */ \
_LINE4( 0x0F,0x12,0x68,0x10 )                               /* movlps      xmm5,qword ptr [eax+10h]  */ \
_LINE4( 0x0F,0x16,0x68,0x18 )                               /* movhps      xmm5,qword ptr [eax+18h]  */ \
_LINE4( 0x0F,0x12,0x70,0x20 )                               /* movlps      xmm6,qword ptr [eax+20h]  */ \
_LINE4( 0x0F,0x16,0x70,0x28 )                               /* movhps      xmm6,qword ptr [eax+28h]  */ \
_LINE4( 0x0F,0x12,0x78,0x30 )                               /* movlps      xmm7,qword ptr [eax+30h]  */ \
_LINE4( 0x0F,0x16,0x78,0x38 )                               /* movhps      xmm7,qword ptr [eax+38h]  */ \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP3DTransformSSEend_loop ) \
ASM( _ArrayP3DTransformSSEmloop: ) \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
ASM( add eax,edi ) \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
_LINE3( 0x0F,0x15,0xD2 )                                    /* unpckhps    xmm2,xmm2  */ \
_LINE5( 0xF3,0x0F,0x11,0x52,0x08 )                          /* movss       dword ptr [edx+8],xmm2 */ \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DTransformSSEmloop ) \
ASM( _ArrayP3DTransformSSEend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// трансформирование массива трехмерных векторов, команды SSE3
#define ARRAYP3DTRANSFORMSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( lddqu xmm4,xmmword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( lddqu xmm5,xmmword ptr [eax+0x10] ) \
ASM( mov edx,[esp+12] ) \
ASM( lddqu xmm6,xmmword ptr [eax+0x20] ) \
ASM( mov edi,[esp+16] ) \
ASM( lddqu xmm7,xmmword ptr [eax+0x30] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP3DTransformSSE3end_loop ) \
ASM( _ArrayP3DTransformSSE3mloop: ) \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
ASM( add eax,edi ) \
_LINE3( 0x0F,0x58,0xD7 )                                    /* addps       xmm2,xmm7  */ \
ASM( movhlps xmm0,xmm2 ) \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
ASM( movss [edx+8],xmm0 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DTransformSSE3mloop ) \
ASM( _ArrayP3DTransformSSE3end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// трансформирование массива четырехмерных векторов, команды SSE
#define ARRAYP4DTRANSFORMSSE_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
_LINE3( 0x0F,0x12,0x20 )                                    /* movlps      xmm4,qword ptr [eax]  */ \
_LINE4( 0x0F,0x16,0x60,0x08 )                               /* movhps      xmm4,qword ptr [eax+8]  */ \
_LINE4( 0x0F,0x12,0x68,0x10 )                               /* movlps      xmm5,qword ptr [eax+10h]  */ \
_LINE4( 0x0F,0x16,0x68,0x18 )                               /* movhps      xmm5,qword ptr [eax+18h]  */ \
_LINE4( 0x0F,0x12,0x70,0x20 )                               /* movlps      xmm6,qword ptr [eax+20h]  */ \
_LINE4( 0x0F,0x16,0x70,0x28 )                               /* movhps      xmm6,qword ptr [eax+28h]  */ \
_LINE4( 0x0F,0x12,0x78,0x30 )                               /* movlps      xmm7,qword ptr [eax+30h]  */ \
_LINE4( 0x0F,0x16,0x78,0x38 )                               /* movhps      xmm7,qword ptr [eax+38h]  */ \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DTransformSSEend_loop ) \
ASM( _ArrayP4DTransformSSEmloop: ) \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x0C )                          /* movss       xmm0,dword ptr [eax+12]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
ASM( add eax,edi ) \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x08 )                               /* movhps      qword ptr [edx+8],xmm2 */ \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DTransformSSEmloop ) \
ASM( _ArrayP4DTransformSSEend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// трансформирование массива четырехмерных векторов, команды SSE3
#define ARRAYP4DTRANSFORMSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( lddqu xmm4,xmmword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( lddqu xmm5,xmmword ptr [eax+0x10] ) \
ASM( mov edx,[esp+12] ) \
ASM( lddqu xmm6,xmmword ptr [eax+0x20] ) \
ASM( mov edi,[esp+16] ) \
ASM( lddqu xmm7,xmmword ptr [eax+0x30] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DTransformSSE3end_loop ) \
ASM( _ArrayP4DTransformSSE3mloop: ) \
_LINE4( 0xF3,0x0F,0x10,0x10 )                               /* movss       xmm2,dword ptr [eax]  */ \
_LINE4( 0x0F,0xC6,0xD2,0x00 )                               /* shufps      xmm2,xmm2,0  */ \
_LINE3( 0x0F,0x59,0xD4 )                                    /* mulps       xmm2,xmm4  */ \
_LINE5( 0xF3,0x0F,0x10,0x48,0x04 )                          /* movss       xmm1,dword ptr [eax+4]  */ \
_LINE4( 0x0F,0xC6,0xC9,0x00 )                               /* shufps      xmm1,xmm1,0  */ \
_LINE3( 0x0F,0x59,0xCD )                                    /* mulps       xmm1,xmm5  */ \
_LINE3( 0x0F,0x58,0xD1 )                                    /* addps       xmm2,xmm1  */ \
_LINE5( 0xF3,0x0F,0x10,0x58,0x08 )                          /* movss       xmm3,dword ptr [eax+8]  */ \
_LINE4( 0x0F,0xC6,0xDB,0x00 )                               /* shufps      xmm3,xmm3,0  */ \
_LINE3( 0x0F,0x59,0xDE )                                    /* mulps       xmm3,xmm6  */ \
_LINE5( 0xF3,0x0F,0x10,0x40,0x0C )                          /* movss       xmm0,dword ptr [eax+12]  */ \
_LINE4( 0x0F,0xC6,0xC0,0x00 )                               /* shufps      xmm0,xmm0,0  */ \
_LINE3( 0x0F,0x58,0xD3 )                                    /* addps       xmm2,xmm3  */ \
_LINE3( 0x0F,0x59,0xC7 )                                    /* mulps       xmm0,xmm7  */ \
ASM( add eax,edi ) \
_LINE3( 0x0F,0x58,0xD0 )                                    /* addps       xmm2,xmm0  */ \
_LINE3( 0x0F,0x13,0x12 )                                    /* movlps      qword ptr [edx],xmm2  */ \
_LINE4( 0x0F,0x17,0x52,0x08 )                               /* movhps      qword ptr [edx+8],xmm2 */ \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DTransformSSE3mloop ) \
ASM( _ArrayP4DTransformSSE3end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// трансформирование массива двухмерных векторов двойной точности, команды SSE2
#define ARRAYP2DDTRANSFORMSSE2_STD \
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
ASM( jecxz _ArrayP2DDTransformSSE2end_loop ) \
ASM( _ArrayP2DDTransformSSE2mloop: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movsd xmm3,qword ptr [eax+8] ) \
ASM( addsd xmm2,xmm0 ) \
ASM( addsd xmm3,xmm1 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( movsd qword ptr [edx+8],xmm3 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DDTransformSSE2mloop ) \
ASM( _ArrayP2DDTransformSSE2end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// трансформирование массива двухмерных векторов двойной точности, команды SSE3
#define ARRAYP2DDTRANSFORMSSE3_STD \
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
ASM( jecxz _ArrayP2DDTransformSSE3end_loop ) \
ASM( _ArrayP2DDTransformSSE3mloop: ) \
ASM( lddqu xmm2,xmmword ptr [eax] ) \
ASM( addpd xmm2,xmm0 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
ASM( movsd qword ptr [edx+8],xmm2 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DDTransformSSE3mloop ) \
ASM( _ArrayP2DDTransformSSE3end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// трансформирование массива трехмерных векторов двойной точности, команды SSE2
#define ARRAYP3DDTRANSFORMSSE2_STD \
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
ASM( jecxz _ArrayP3DDTransformSSE2end_loop ) \
ASM( _ArrayP3DDTransformSSE2mloop: ) \
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
ASM( loop _ArrayP3DDTransformSSE2mloop ) \
ASM( _ArrayP3DDTransformSSE2end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// трансформирование массива трехмерных векторов двойной точности, команды AVX
#define ARRAYP3DDTRANSFORMAVX_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( vmovupd ymm4,xmmword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( vmovupd ymm5,xmmword ptr [eax+0x20] ) \
ASM( mov edx,[esp+12] ) \
ASM( vmovupd ymm6,xmmword ptr [eax+0x40] ) \
ASM( mov edi,[esp+16] ) \
ASM( vmovupd ymm7,xmmword ptr [eax+0x60] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP3DDTransformAVXend_loop ) \
ASM( _ArrayP3DDTransformAVXmloop: ) \
ASM( vbroadcastsd ymm0,qword ptr [eax] ) \
ASM( vbroadcastsd ymm1,qword ptr [eax+8] ) \
ASM( vbroadcastsd ymm2,qword ptr [eax+16] ) \
ASM( vmulpd ymm0,ymm0,ymm4 ) \
ASM( vmulpd ymm1,ymm1,ymm5 ) \
ASM( vmulpd ymm2,ymm2,ymm6 ) \
ASM( add eax,edi ) \
ASM( vaddpd ymm0,ymm0,ymm7 ) \
ASM( vaddpd ymm1,ymm1,ymm2 ) \
ASM( vaddpd ymm0,ymm0,ymm1 ) \
ASM( VEXTRACTF128 xmm2,ymm0,1 ) \
ASM( vmovupd [edx],xmm0 ) \
ASM( vmovsd qword ptr [edx+16],xmm2 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DDTransformAVXmloop ) \
ASM( _ArrayP3DDTransformAVXend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
ASM( vzeroupper ) \
_END_ASM

/// трансформирование массива четырехмерных векторов двойной точности, команды SSE2
#define ARRAYP4DDTRANSFORMSSE2_STD \
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
ASM( jecxz _ArrayP4DDTransformSSE2end_loop ) \
ASM( _ArrayP4DDTransformSSE2mloop: ) \
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
ASM( loop _ArrayP4DDTransformSSE2mloop ) \
ASM( _ArrayP4DDTransformSSE2end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// трансформирование массива четырехмерных векторов двойной точности, команды SSE3
#define ARRAYP4DDTRANSFORMSSE3_STD \
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
ASM( jecxz _ArrayP4DDTransformSSE3end_loop ) \
ASM( _ArrayP4DDTransformSSE3mloop: ) \
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
ASM( loop _ArrayP4DDTransformSSE3mloop ) \
ASM( _ArrayP4DDTransformSSE3end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// трансформирование массива четырехмерных векторов двойной точности, команды AVX
#define ARRAYP4DDTRANSFORMAVX_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( vmovupd ymm4,xmmword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( vmovupd ymm5,xmmword ptr [eax+0x20] ) \
ASM( mov edx,[esp+12] ) \
ASM( vmovupd ymm6,xmmword ptr [eax+0x40] ) \
ASM( mov edi,[esp+16] ) \
ASM( vmovupd ymm7,xmmword ptr [eax+0x60] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DDTransformAVXend_loop ) \
ASM( _ArrayP4DDTransformAVXmloop: ) \
ASM( vbroadcastsd ymm0,qword ptr [eax] ) \
ASM( vbroadcastsd ymm1,qword ptr [eax+8] ) \
ASM( vbroadcastsd ymm2,qword ptr [eax+16] ) \
ASM( vbroadcastsd ymm3,qword ptr [eax+24] ) \
ASM( vmulpd ymm0,ymm0,ymm4 ) \
ASM( vmulpd ymm1,ymm1,ymm5 ) \
ASM( vmulpd ymm2,ymm2,ymm6 ) \
ASM( vmulpd ymm3,ymm3,ymm7 ) \
ASM( add eax,edi ) \
ASM( vaddpd ymm0,ymm0,ymm3 ) \
ASM( vaddpd ymm1,ymm1,ymm2 ) \
ASM( vaddpd ymm0,ymm0,ymm1 ) \
ASM( vmovupd [edx],ymm0 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DDTransformAVXmloop ) \
ASM( _ArrayP4DDTransformAVXend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
ASM( vzeroupper ) \
_END_ASM

#endif /* X86ARRAY_TRANSFORM_H_ */

