//=============================================================================
///**
// *  @file x86array_mul.h
// *
// *  $Id: x86array_mul.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float mul, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef X86ARRAY_MUL_H_
#define X86ARRAY_MUL_H_

//**************************** MULVECTOR STDCALL *********************************
// array vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *  edx=[esp+12]-c void *  [esp+16]-stepa unsigned int  [esp+20]-stepc unsigned int ecx=[esp+24]-count unsigned int

/// умножение массива двухмерных векторов и двухмерного вектора, команды SSE
#define ARRAYP2DMULVECTORSSE_STD \
_BEGIN_ASM \
ASM( xorps xmm4,xmm4 ) \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movlps xmm0,qword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( movlhps xmm0,xmm0 ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP2DMulVectorSSEend_loop ) \
ASM( _ArrayP2DMulVectorSSEmloop: ) \
ASM( movlps xmm1,qword ptr [eax] ) \
ASM( movlps xmm2,qword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movhps xmm1,qword ptr [eax] ) \
ASM( movhps xmm2,qword ptr [eax+edi] ) \
ASM( mulps xmm1,xmm0 ) \
ASM( mulps xmm2,xmm0 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movlps qword ptr [edx],xmm1 ) \
ASM( movlps qword ptr [edx+esi],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movhps qword ptr [edx],xmm1 ) \
ASM( movhps qword ptr [edx+esi],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP2DMulVectorSSEmloop ) \
ASM( _ArrayP2DMulVectorSSEend_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DMulVectorSSEend_loop2 ) \
ASM( _ArrayP2DMulVectorSSEmloop2: ) \
ASM( movlps xmm4,qword ptr [eax] ) \
ASM( add eax,edi ) \
ASM( mulps xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DMulVectorSSEmloop2 ) \
ASM( _ArrayP2DMulVectorSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// умножение массива двухмерных векторов и двухмерного вектора, команды SSE3
#define ARRAYP2DMULVECTORSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movsd xmm0,qword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( movlhps xmm0,xmm0 ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP2DMulVectorSSE3end_loop ) \
ASM( _ArrayP2DMulVectorSSE3mloop: ) \
ASM( movsd xmm1,qword ptr [eax] ) \
ASM( movsd xmm2,qword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movhps xmm1,qword ptr [eax] ) \
ASM( movhps xmm2,qword ptr [eax+edi] ) \
ASM( mulps xmm1,xmm0 ) \
ASM( mulps xmm2,xmm0 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movlps qword ptr [edx],xmm1 ) \
ASM( movlps qword ptr [edx+esi],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movhps qword ptr [edx],xmm1 ) \
ASM( movhps qword ptr [edx+esi],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP2DMulVectorSSE3mloop ) \
ASM( _ArrayP2DMulVectorSSE3end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DMulVectorSSE3end_loop2 ) \
ASM( _ArrayP2DMulVectorSSE3mloop2: ) \
ASM( movsd xmm4,qword ptr [eax] ) \
ASM( add eax,edi ) \
ASM( mulps xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DMulVectorSSE3mloop2 ) \
ASM( _ArrayP2DMulVectorSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// умножение массива трехмерных векторов и трехмерных вектора, команды SSE
#define ARRAYP3DMULVECTORSSE_STD \
_BEGIN_ASM \
ASM( xorps xmm1,xmm1 ) \
ASM( xorps xmm2,xmm2 ) \
ASM( xorps xmm3,xmm3 ) \
ASM( xorps xmm4,xmm4 ) \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movss xmm0,dword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( movhps xmm0,qword ptr [eax+4] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( movaps xmm5,xmm0 ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP3DMulVectorSSEend_loop ) \
ASM( _ArrayP3DMulVectorSSEmloop: ) \
ASM( movss xmm1,dword ptr [eax] ) \
ASM( movss xmm2,dword ptr [eax+edi] ) \
ASM( movhps xmm1,qword ptr [eax+4] ) \
ASM( movhps xmm2,qword ptr [eax+edi+4] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movss xmm3,dword ptr [eax] ) \
ASM( movss xmm4,dword ptr [eax+edi] ) \
ASM( movhps xmm3,qword ptr [eax+4] ) \
ASM( movhps xmm4,qword ptr [eax+edi+4] ) \
ASM( mulps xmm1,xmm0 ) \
ASM( mulps xmm2,xmm5 ) \
ASM( mulps xmm3,xmm0 ) \
ASM( mulps xmm4,xmm5 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movss dword ptr [edx],xmm1 ) \
ASM( movss dword ptr [edx+esi],xmm2 ) \
ASM( movhps qword ptr [edx+4],xmm1 ) \
ASM( movhps qword ptr [edx+esi+4],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movss dword ptr [edx],xmm3 ) \
ASM( movss dword ptr [edx+esi],xmm4 ) \
ASM( movhps qword ptr [edx+4],xmm3 ) \
ASM( movhps qword ptr [edx+esi+4],xmm4 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP3DMulVectorSSEmloop ) \
ASM( _ArrayP3DMulVectorSSEend_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP3DMulVectorSSEend_loop2 ) \
ASM( _ArrayP3DMulVectorSSEmloop2: ) \
ASM( movss xmm4,dword ptr [eax] ) \
ASM( movhps xmm4,qword ptr [eax+4] ) \
ASM( add eax,edi ) \
ASM( mulps xmm4,xmm0 ) \
ASM( movss dword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+4],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DMulVectorSSEmloop2 ) \
ASM( _ArrayP3DMulVectorSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// умножение массива четырехмерных векторов и четырехмерного вектора, команды SSE
#define ARRAYP4DMULVECTORSSE_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movlps xmm0,qword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( movhps xmm0,qword ptr [eax+8] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( movaps xmm5,xmm0 ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP4DMulVectorSSEend_loop ) \
ASM( _ArrayP4DMulVectorSSEmloop: ) \
ASM( movlps xmm1,qword ptr [eax] ) \
ASM( movlps xmm2,qword ptr [eax+edi] ) \
ASM( movhps xmm1,qword ptr [eax+8] ) \
ASM( movhps xmm2,qword ptr [eax+edi+8] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movlps xmm3,qword ptr [eax] ) \
ASM( movlps xmm4,qword ptr [eax+edi] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movhps xmm4,qword ptr [eax+edi+8] ) \
ASM( mulps xmm1,xmm0 ) \
ASM( mulps xmm2,xmm5 ) \
ASM( mulps xmm3,xmm0 ) \
ASM( mulps xmm4,xmm5 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movlps qword ptr [edx],xmm1 ) \
ASM( movlps qword ptr [edx+esi],xmm2 ) \
ASM( movhps qword ptr [edx+8],xmm1 ) \
ASM( movhps qword ptr [edx+esi+8],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movlps qword ptr [edx],xmm3 ) \
ASM( movlps qword ptr [edx+esi],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movhps qword ptr [edx+esi+8],xmm4 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP4DMulVectorSSEmloop ) \
ASM( _ArrayP4DMulVectorSSEend_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4DMulVectorSSEend_loop2 ) \
ASM( _ArrayP4DMulVectorSSEmloop2: ) \
ASM( movlps xmm4,qword ptr [eax] ) \
ASM( movhps xmm4,qword ptr [eax+8] ) \
ASM( add eax,edi ) \
ASM( mulps xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DMulVectorSSEmloop2 ) \
ASM( _ArrayP4DMulVectorSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// умножение массива четырехмерных векторов и четырехмерного вектора, команды SSE3
#define ARRAYP4DMULVECTORSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( lddqu xmm0,xmmword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( movaps xmm5,xmm0 ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP4DMulVectorSSE3end_loop ) \
ASM( _ArrayP4DMulVectorSSE3mloop: ) \
ASM( lddqu xmm1,xmmword ptr [eax] ) \
ASM( lddqu xmm2,xmmword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( lddqu xmm3,xmmword ptr [eax] ) \
ASM( lddqu xmm4,xmmword ptr [eax+edi] ) \
ASM( mulps xmm1,xmm0 ) \
ASM( mulps xmm2,xmm5 ) \
ASM( mulps xmm3,xmm0 ) \
ASM( mulps xmm4,xmm5 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movlps qword ptr [edx],xmm1 ) \
ASM( movlps qword ptr [edx+esi],xmm2 ) \
ASM( movhps qword ptr [edx+8],xmm1 ) \
ASM( movhps qword ptr [edx+esi+8],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movlps qword ptr [edx],xmm3 ) \
ASM( movlps qword ptr [edx+esi],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movhps qword ptr [edx+esi+8],xmm4 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP4DMulVectorSSE3mloop ) \
ASM( _ArrayP4DMulVectorSSE3end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4DMulVectorSSE3end_loop2 ) \
ASM( _ArrayP4DMulVectorSSE3mloop2: ) \
ASM( lddqu xmm4,xmmword ptr [eax] ) \
ASM( add eax,edi ) \
ASM( mulps xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DMulVectorSSE3mloop2 ) \
ASM( _ArrayP4DMulVectorSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// умножение массива двухмерных векторов двойной точности и двухмерного вектора, команды SSE2
#define ARRAYP2DDMULVECTORSSE2_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movsd xmm0,qword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( movhps xmm0,qword ptr [eax+8] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( movaps xmm5,xmm0 ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP2DDMulVectorSSE2end_loop ) \
ASM( _ArrayP2DDMulVectorSSE2mloop: ) \
ASM( movsd xmm1,qword ptr [eax] ) \
ASM( movsd xmm2,qword ptr [eax+edi] ) \
ASM( movhps xmm1,qword ptr [eax+8] ) \
ASM( movhps xmm2,qword ptr [eax+edi+8] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movsd xmm3,qword ptr [eax] ) \
ASM( movsd xmm4,qword ptr [eax+edi] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movhps xmm4,qword ptr [eax+edi+8] ) \
ASM( mulpd xmm1,xmm0 ) \
ASM( mulpd xmm2,xmm5 ) \
ASM( mulpd xmm3,xmm0 ) \
ASM( mulpd xmm4,xmm5 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movsd qword ptr [edx],xmm1 ) \
ASM( movsd qword ptr [edx+esi],xmm2 ) \
ASM( movhps qword ptr [edx+8],xmm1 ) \
ASM( movhps qword ptr [edx+esi+8],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movsd qword ptr [edx],xmm3 ) \
ASM( movsd qword ptr [edx+esi],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movhps qword ptr [edx+esi+8],xmm4 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP2DDMulVectorSSE2mloop ) \
ASM( _ArrayP2DDMulVectorSSE2end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DDMulVectorSSE2end_loop2 ) \
ASM( _ArrayP2DDMulVectorSSE2mloop2: ) \
ASM( movsd xmm4,qword ptr [eax] ) \
ASM( movhps xmm4,qword ptr [eax+8] ) \
ASM( add eax,edi ) \
ASM( mulpd xmm4,xmm0 ) \
ASM( movsd qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DDMulVectorSSE2mloop2 ) \
ASM( _ArrayP2DDMulVectorSSE2end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// умножение массива двухмерных векторов двойной точности и двухмерного вектора, команды SSE3
#define ARRAYP2DDMULVECTORSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( lddqu xmm0,xmmword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( movaps xmm5,xmm0 ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP2DDMulVectorSSE3end_loop ) \
ASM( _ArrayP2DDMulVectorSSE3mloop: ) \
ASM( lddqu xmm1,xmmword ptr [eax] ) \
ASM( lddqu xmm2,xmmword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( lddqu xmm3,xmmword ptr [eax] ) \
ASM( lddqu xmm4,xmmword ptr [eax+edi] ) \
ASM( mulpd xmm1,xmm0 ) \
ASM( mulpd xmm2,xmm5 ) \
ASM( mulpd xmm3,xmm0 ) \
ASM( mulpd xmm4,xmm5 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movsd qword ptr [edx],xmm1 ) \
ASM( movsd qword ptr [edx+esi],xmm2 ) \
ASM( movhps qword ptr [edx+8],xmm1 ) \
ASM( movhps qword ptr [edx+esi+8],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movsd qword ptr [edx],xmm3 ) \
ASM( movsd qword ptr [edx+esi],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movhps qword ptr [edx+esi+8],xmm4 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP2DDMulVectorSSE3mloop ) \
ASM( _ArrayP2DDMulVectorSSE3end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DDMulVectorSSE3end_loop2 ) \
ASM( _ArrayP2DDMulVectorSSE3mloop2: ) \
ASM( lddqu xmm4,xmmword ptr [eax] ) \
ASM( add eax,edi ) \
ASM( mulpd xmm4,xmm0 ) \
ASM( movsd qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DDMulVectorSSE3mloop2 ) \
ASM( _ArrayP2DDMulVectorSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// умножение массива трехмерных векторов двойной точности и трехмерных вектора, команды SSE2
#define ARRAYP3DDMULVECTORSSE2_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movsd xmm0,qword ptr [eax] ) \
ASM( movsd xmm1,qword ptr [eax+16] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( movhps xmm0,qword ptr [eax+8] ) \
ASM( movhps xmm1,qword ptr [eax+16] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( movaps xmm2,xmm0 ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jnz _ArrayP3DDMulVectorSSE2mloop ) \
ASM( jmp _ArrayP3DDMulVectorSSE2end_loop ) \
ASM( _ArrayP3DDMulVectorSSE2mloop: ) \
ASM( movsd xmm3,qword ptr [eax] ) \
ASM( movsd xmm4,qword ptr [eax+16] ) \
ASM( movsd xmm5,qword ptr [eax+edi] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movhps xmm4,qword ptr [eax+edi+16] ) \
ASM( movhps xmm5,qword ptr [eax+edi+8] ) \
ASM( mulpd xmm3,xmm0 ) \
ASM( mulpd xmm4,xmm1 ) \
ASM( mulpd xmm5,xmm2 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movsd qword ptr [edx],xmm3 ) \
ASM( movsd qword ptr [edx+16],xmm4 ) \
ASM( movsd qword ptr [edx+esi],xmm5 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movhps qword ptr [edx+esi+16],xmm4 ) \
ASM( movhps qword ptr [edx+esi+8],xmm5 ) \
ASM( movsd xmm3,qword ptr [eax] ) \
ASM( movsd xmm4,qword ptr [eax+16] ) \
ASM( movsd xmm5,qword ptr [eax+edi] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movhps xmm4,qword ptr [eax+edi+16] ) \
ASM( movhps xmm5,qword ptr [eax+edi+8] ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( mulpd xmm3,xmm0 ) \
ASM( mulpd xmm4,xmm1 ) \
ASM( mulpd xmm5,xmm2 ) \
ASM( movsd qword ptr [edx],xmm3 ) \
ASM( movsd qword ptr [edx+16],xmm4 ) \
ASM( movsd qword ptr [edx+esi],xmm5 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movhps qword ptr [edx+esi+16],xmm4 ) \
ASM( movhps qword ptr [edx+esi+8],xmm5 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( dec ecx ) \
ASM( jecxz _ArrayP3DDMulVectorSSE2end_loop ) \
ASM( jmp _ArrayP3DDMulVectorSSE2mloop ) \
ASM( _ArrayP3DDMulVectorSSE2end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP3DDMulVectorSSE2end_loop2 ) \
ASM( _ArrayP3DDMulVectorSSE2mloop2: ) \
ASM( movsd xmm3,qword ptr [eax] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movsd xmm4,qword ptr [eax+16] ) \
ASM( mulpd xmm3,xmm0 ) \
ASM( mulsd xmm4,xmm1 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm3 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movsd qword ptr [edx+16],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DDMulVectorSSE2mloop2 ) \
ASM( _ArrayP3DDMulVectorSSE2end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// умножение массива четырехмерных векторов двойной точности и четырехмерного вектора, команды SSE2
#define ARRAYP4DDMULVECTORSSE2_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movsd xmm0,qword ptr [eax] ) \
ASM( movsd xmm1,qword ptr [eax+16] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov edi,[esp+16] ) \
ASM( movhps xmm0,qword ptr [eax+8] ) \
ASM( movhps xmm1,qword ptr [eax+24] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jnz _ArrayP4DDMulVectorSSE2mloop ) \
ASM( jmp _ArrayP4DDMulVectorSSE2end_loop ) \
ASM( _ArrayP4DDMulVectorSSE2mloop: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movsd xmm3,qword ptr [eax+16] ) \
ASM( movhps xmm2,qword ptr [eax+8] ) \
ASM( movhps xmm3,qword ptr [eax+24] ) \
ASM( movsd xmm4,qword ptr [eax+edi] ) \
ASM( movsd xmm5,qword ptr [eax+edi+16] ) \
ASM( movhps xmm4,qword ptr [eax+edi+8] ) \
ASM( movhps xmm5,qword ptr [eax+edi+24] ) \
ASM( mulpd xmm2,xmm0 ) \
ASM( mulpd xmm3,xmm1 ) \
ASM( mulpd xmm4,xmm0 ) \
ASM( mulpd xmm5,xmm1 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( movsd qword ptr [edx+16],xmm3 ) \
ASM( movhps qword ptr [edx+8],xmm2 ) \
ASM( movhps qword ptr [edx+24],xmm3 ) \
ASM( movsd qword ptr [edx+esi],xmm4 ) \
ASM( movsd qword ptr [edx+esi+16],xmm5 ) \
ASM( movhps qword ptr [edx+esi+8],xmm4 ) \
ASM( movhps qword ptr [edx+esi+24],xmm5 ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movsd xmm3,qword ptr [eax+16] ) \
ASM( movhps xmm2,qword ptr [eax+8] ) \
ASM( movhps xmm3,qword ptr [eax+24] ) \
ASM( movsd xmm4,qword ptr [eax+edi] ) \
ASM( movsd xmm5,qword ptr [eax+edi+16] ) \
ASM( movhps xmm4,qword ptr [eax+edi+8] ) \
ASM( movhps xmm5,qword ptr [eax+edi+24] ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( mulpd xmm2,xmm0 ) \
ASM( mulpd xmm3,xmm1 ) \
ASM( mulpd xmm4,xmm0 ) \
ASM( mulpd xmm5,xmm1 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( movsd qword ptr [edx+16],xmm3 ) \
ASM( movhps qword ptr [edx+8],xmm2 ) \
ASM( movhps qword ptr [edx+24],xmm3 ) \
ASM( movsd qword ptr [edx+esi],xmm4 ) \
ASM( movsd qword ptr [edx+esi+16],xmm5 ) \
ASM( movhps qword ptr [edx+esi+8],xmm4 ) \
ASM( movhps qword ptr [edx+esi+24],xmm5 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( dec ecx ) \
ASM( jecxz _ArrayP4DDMulVectorSSE2end_loop ) \
ASM( jmp _ArrayP4DDMulVectorSSE2mloop ) \
ASM( _ArrayP4DDMulVectorSSE2end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4DDMulVectorSSE2end_loop2 ) \
ASM( _ArrayP4DDMulVectorSSE2mloop2: ) \
ASM( movsd xmm3,qword ptr [eax] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movsd xmm4,qword ptr [eax+16] ) \
ASM( movhps xmm3,qword ptr [eax+24] ) \
ASM( mulpd xmm3,xmm0 ) \
ASM( mulpd xmm4,xmm1 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm3 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movsd qword ptr [edx+16],xmm4 ) \
ASM( movhps qword ptr [edx+24],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DDMulVectorSSE2mloop2 ) \
ASM( _ArrayP4DDMulVectorSSE2end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// умножение массива четырехмерных векторов двойной точности и четырехмерного вектора, команды SSE3
#define ARRAYP4DDMULVECTORSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( lddqu xmm0,xmmword ptr [eax] ) \
ASM( mov ecx,[esp+24] ) \
ASM( mov edx,[esp+12] ) \
ASM( lddqu xmm1,xmmword ptr [eax+16] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+20] ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jnz _ArrayP4DDMulVectorSSE3mloop ) \
ASM( jmp _ArrayP4DDMulVectorSSE3end_loop ) \
ASM( _ArrayP4DDMulVectorSSE3mloop: ) \
ASM( lddqu xmm2,xmmword ptr [eax] ) \
ASM( lddqu xmm3,xmmword ptr [eax+16] ) \
ASM( lddqu xmm4,xmmword ptr [eax+edi] ) \
ASM( lddqu xmm5,xmmword ptr [eax+edi+16] ) \
ASM( mulpd xmm2,xmm0 ) \
ASM( mulpd xmm3,xmm1 ) \
ASM( mulpd xmm4,xmm0 ) \
ASM( mulpd xmm5,xmm1 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( movsd qword ptr [edx+16],xmm3 ) \
ASM( movhps qword ptr [edx+8],xmm2 ) \
ASM( movhps qword ptr [edx+24],xmm3 ) \
ASM( movsd qword ptr [edx+esi],xmm4 ) \
ASM( movsd qword ptr [edx+esi+16],xmm5 ) \
ASM( movhps qword ptr [edx+esi+8],xmm4 ) \
ASM( movhps qword ptr [edx+esi+24],xmm5 ) \
ASM( lddqu xmm2,xmmword ptr [eax] ) \
ASM( lddqu xmm3,xmmword ptr [eax+16] ) \
ASM( lddqu xmm4,xmmword ptr [eax+edi] ) \
ASM( lddqu xmm5,xmmword ptr [eax+edi+16] ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( mulpd xmm2,xmm0 ) \
ASM( mulpd xmm3,xmm1 ) \
ASM( mulpd xmm4,xmm0 ) \
ASM( mulpd xmm5,xmm1 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movsd qword ptr [edx],xmm2 ) \
ASM( movsd qword ptr [edx+16],xmm3 ) \
ASM( movhps qword ptr [edx+8],xmm2 ) \
ASM( movhps qword ptr [edx+24],xmm3 ) \
ASM( movsd qword ptr [edx+esi],xmm4 ) \
ASM( movsd qword ptr [edx+esi+16],xmm5 ) \
ASM( movhps qword ptr [edx+esi+8],xmm4 ) \
ASM( movhps qword ptr [edx+esi+24],xmm5 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( dec ecx ) \
ASM( jecxz _ArrayP4DDMulVectorSSE3end_loop ) \
ASM( jmp _ArrayP4DDMulVectorSSE3mloop ) \
ASM( _ArrayP4DDMulVectorSSE3end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4DDMulVectorSSE3end_loop2 ) \
ASM( _ArrayP4DDMulVectorSSE3mloop2: ) \
ASM( lddqu xmm3,xmmword ptr [eax] ) \
ASM( lddqu xmm4,xmmword ptr [eax+16] ) \
ASM( mulpd xmm3,xmm0 ) \
ASM( mulpd xmm4,xmm1 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm3 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movsd qword ptr [edx+16],xmm4 ) \
ASM( movhps qword ptr [edx+24],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DDMulVectorSSE3mloop2 ) \
ASM( _ArrayP4DDMulVectorSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

#endif /* X86ARRAY_MUL_H_ */

