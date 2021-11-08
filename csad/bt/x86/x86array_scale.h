//=============================================================================
///**
// *  @file x86array_scale.h
// *
// *  $Id: x86array_scale.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float scale, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef X86ARRAY_SCALE_H_
#define X86ARRAY_SCALE_H_

//**************************** SCALE ARRAY STDCALL *********************************
// array vectors eax=[esp+4]-a void *, edx=[esp+8]-b float  edx=[esp+12]-c void *  [esp+16]-stepa unsigned int  [esp+20]-stepc unsigned int ecx=[esp+24]-count unsigned int

/// маштобирование массива двухмерных векторов, команды SSE
#define ARRAYP2DSCALESSE_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( movss xmm0,dword ptr [esp+8] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( movaps xmm1,xmm0 ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP2DScaleSSEend_loop ) \
ASM( _ArrayP2DScaleSSEmloop: ) \
ASM( movss xmm2,dword ptr [eax] ) \
_LINE5( 0xF3,0x0F,0x10,0x58,0x04 )                          /* movss       xmm3,dword ptr [eax+4]  */ \
ASM( mulss xmm2,xmm0 ) \
ASM( mulss xmm3,xmm1 ) \
ASM( add eax,edi ) \
ASM( movss dword ptr [edx],xmm2 ) \
ASM( movss dword ptr [edx+4],xmm3 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DScaleSSEmloop ) \
ASM( _ArrayP2DScaleSSEend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// маштобирование массива двухмерных векторов, команды SSE3
#define ARRAYP2DSCALESSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( movss xmm0,dword ptr [esp+8] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( unpcklps xmm0,xmm0 ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP2DScaleSSE3end_loop ) \
ASM( _ArrayP2DScaleSSE3mloop: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( mulps xmm2,xmm0 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DScaleSSE3mloop ) \
ASM( _ArrayP2DScaleSSE3end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// маштобирование массива трехмерных векторов, команды SSE
#define ARRAYP3DSCALESSE_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov ecx,[esp+24] ) \
ASM( movss xmm0,dword ptr [esp+8] ) \
ASM( mov edx,[esp+12] ) \
ASM( movaps xmm1,xmm0 ) \
ASM( mov edi,[esp+16] ) \
ASM( movaps xmm4,xmm0 ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP3DScaleSSEend_loop ) \
ASM( _ArrayP3DScaleSSEmloop: ) \
ASM( movss xmm2,dword ptr [eax] ) \
_LINE5( 0xF3,0x0F,0x10,0x58,0x04 )                          /* movss       xmm3,dword ptr [eax+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x68,0x08 )                          /* movss       xmm5,dword ptr [eax+8]  */ \
ASM( mulss xmm2,xmm0 ) \
ASM( mulss xmm3,xmm1 ) \
ASM( mulss xmm5,xmm4 ) \
ASM( add eax,edi ) \
ASM( movss dword ptr [edx],xmm2 ) \
ASM( movss dword ptr [edx+4],xmm3 ) \
ASM( movss dword ptr [edx+8],xmm5 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DScaleSSEmloop ) \
ASM( _ArrayP3DScaleSSEend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// маштобирование массива трехмерных векторов, команды SSE3
#define ARRAYP3DSCALESSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov ecx,[esp+24] ) \
ASM( movss xmm0,dword ptr [esp+8] ) \
ASM( mov edx,[esp+12] ) \
ASM( unpcklps xmm0,xmm0 ) \
ASM( mov edi,[esp+16] ) \
ASM( movhps xmm0,dword ptr [esp+8] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP3DScaleSSEend_loop ) \
ASM( _ArrayP3DScaleSSEmloop: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movhps xmm2,dword ptr [eax+8] ) \
ASM( mulps xmm2,xmm0 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( movhps dword ptr [edx+8],xmm2 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DScaleSSEmloop ) \
ASM( _ArrayP3DScaleSSEend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// маштобирование массива четырехмерных векторов, команды SSE
#define ARRAYP4DSCALESSE_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( movss xmm0,dword ptr [esp+8] ) \
ASM( mov ecx,[esp+24] ) \
ASM( movaps xmm1,xmm0 ) \
ASM( mov edx,[esp+12] ) \
ASM( movaps xmm3,xmm0 ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( movaps xmm2,xmm1 ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DScaleSSEend_loop ) \
ASM( _ArrayP4DScaleSSEmloop: ) \
ASM( movss xmm4,dword ptr [eax] ) \
_LINE5( 0xF3,0x0F,0x10,0x68,0x04 )                          /* movss       xmm5,dword ptr [eax+4]  */ \
_LINE5( 0xF3,0x0F,0x10,0x70,0x08 )                          /* movss       xmm6,dword ptr [eax+8]  */ \
_LINE5( 0xF3,0x0F,0x10,0x78,0x0C )                          /* movss       xmm6,dword ptr [eax+12]  */ \
ASM( mulss xmm4,xmm0 ) \
ASM( mulss xmm5,xmm1 ) \
ASM( mulss xmm6,xmm2 ) \
ASM( mulss xmm7,xmm3 ) \
ASM( add eax,edi ) \
ASM( movss dword ptr [edx],xmm4 ) \
ASM( movss dword ptr [edx+4],xmm5 ) \
ASM( movss dword ptr [edx+8],xmm6 ) \
ASM( movss dword ptr [edx+12],xmm7 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DScaleSSEmloop ) \
ASM( _ArrayP4DScaleSSEend_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// маштобирование массива четырехмерных векторов, команды SSE3
#define ARRAYP4DSCALESSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( movss xmm0,dword ptr [esp+8] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( shafps xmm0,xmm0,0x00 ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DScaleSSE3end_loop ) \
ASM( _ArrayP4DScaleSSE3mloop: ) \
ASM( lddqu xmm2,xmmword ptr [eax] ) \
ASM( mulps xmm2,xmm0 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
ASM( movsd qword ptr [edx+8],xmm2 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DScaleSSE3mloop ) \
ASM( _ArrayP4DScaleSSE3end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// маштобирование массива двухмерных векторов двойной точности, команды SSE2
#define ARRAYP2DDSCALESSE2_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( movsd xmm0,qword ptr [esp+8] ) \
ASM( mov ecx,[esp+28] ) \
ASM( mov edx,[esp+16] ) \
ASM( movaps xmm1,xmm0 ) \
ASM( mov edi,[esp+20] ) \
ASM( mov esi,[esp+24] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP2DDScaleSSE2end_loop ) \
ASM( _ArrayP2DDScaleSSE2mloop: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movsd xmm3,qword ptr [eax+8] ) \
ASM( mulsd xmm2,xmm0 ) \
ASM( mulsd xmm3,xmm1 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( movsd qword ptr [edx+8],xmm3 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DDScaleSSE2mloop ) \
ASM( _ArrayP2DDScaleSSE2end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// маштобирование массива двухмерных векторов двойной точности, команды SSE3
#define ARRAYP2DDSCALESSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( movsd xmm0,qword ptr [esp+8] ) \
ASM( mov ecx,[esp+28] ) \
ASM( mov edx,[esp+16] ) \
ASM( unpcklpd xmm0,xmm0 ) \
ASM( mov edi,[esp+20] ) \
ASM( mov esi,[esp+24] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP2DDScaleSSE3end_loop ) \
ASM( _ArrayP2DDScaleSSE3mloop: ) \
ASM( lddqu xmm2,xmmword ptr [eax] ) \
ASM( mulpd xmm2,xmm0 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
ASM( movsd qword ptr [edx+8],xmm2 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DDScaleSSE3mloop ) \
ASM( _ArrayP2DDScaleSSE3end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// маштобирование массива трехмерных векторов двойной точности, команды SSE2
#define ARRAYP3DDSCALESSE2_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( movsd xmm0,qword ptr [esp+8] ) \
ASM( mov ecx,[esp+28] ) \
ASM( mov edx,[esp+16] ) \
ASM( movsd xmm1,xmm0 ) \
ASM( mov edi,[esp+20] ) \
ASM( mov esi,[esp+24] ) \
ASM( movsd xmm4,xmm0 ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP3DDScaleSSE2end_loop ) \
ASM( _ArrayP3DDScaleSSE2mloop: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movsd xmm3,qword ptr [eax+4] ) \
ASM( movsd xmm5,qword ptr [eax+8] ) \
ASM( mulsd xmm2,xmm0 ) \
ASM( mulsd xmm3,xmm1 ) \
ASM( mulsd xmm5,xmm4 ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( movsd qword ptr [edx+4],xmm3 ) \
ASM( movsd qword ptr [edx+8],xmm5 ) \
ASM( add eax,edi ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DDScaleSSE2mloop ) \
ASM( _ArrayP3DDScaleSSE2end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// маштобирование массива четырехмерных векторов двойной точности, команды SSE2
#define ARRAYP4DDSCALESSE2_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( movsd xmm0,qword ptr [esp+8] ) \
ASM( mov ecx,[esp+28] ) \
ASM( movsd xmm1,xmm0 ) \
ASM( mov edx,[esp+16] ) \
ASM( movsd xmm2,xmm0 ) \
ASM( mov edi,[esp+20] ) \
ASM( movsd xmm3,xmm1 ) \
ASM( mov esi,[esp+24] ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DDScaleSSE2end_loop ) \
ASM( _ArrayP4DDScaleSSE2mloop: ) \
ASM( movsd xmm4,qword ptr [eax] ) \
ASM( movsd xmm5,qword ptr [eax+8] ) \
ASM( movsd xmm6,qword ptr [eax+16] ) \
ASM( movsd xmm7,qword ptr [eax+24] ) \
ASM( mulsd xmm4,xmm0 ) \
ASM( mulsd xmm5,xmm1 ) \
ASM( mulsd xmm6,xmm2 ) \
ASM( mulsd xmm7,xmm3 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm4 ) \
ASM( movsd qword ptr [edx+8],xmm5 ) \
ASM( movsd qword ptr [edx+16],xmm6 ) \
ASM( movsd qword ptr [edx+24],xmm7 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DDScaleSSE2mloop ) \
ASM( _ArrayP4DDScaleSSE2end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// маштобирование массива четырехмерных векторов двойной точности, команды SSE3
#define ARRAYP4DDSCALESSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( movsd xmm0,xmmword ptr [esp+8] ) \
ASM( mov ecx,[esp+28] ) \
ASM( mov edx,[esp+16] ) \
ASM( unpcklpd xmm0,xmm0 ) \
ASM( mov edi,[esp+20] ) \
ASM( mov esi,[esp+24] ) \
ASM( movaps xmm1,xmm0 ) \
ASM( mov eax,[esp+4] ) \
ASM( jecxz _ArrayP4DDScaleSSE3end_loop ) \
ASM( _ArrayP4DDScaleSSE3mloop: ) \
ASM( lddqu xmm2,xmmword ptr [eax] ) \
ASM( lddqu xmm3,xmmword ptr [eax+16] ) \
ASM( mulpd xmm2,xmm0 ) \
ASM( mulpd xmm3,xmm1 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm2 ) \
_LINE4( 0x66,0x0F,0x15,0xD2 )                               /* unpckhpd    xmm2,xmm2  */ \
ASM( movsd qword ptr [edx+8],xmm2 ) \
ASM( movsd qword ptr [edx+16],xmm3 ) \
_LINE4( 0x66,0x0F,0x15,0xDB )                               /* unpckhpd    xmm3,xmm3  */ \
ASM( movsd qword ptr [edx+24],xmm3 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DDScaleSSE3mloop ) \
ASM( _ArrayP4DDScaleSSE3end_loop: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

#endif /* X86ARRAY_SCALE_H_ */

