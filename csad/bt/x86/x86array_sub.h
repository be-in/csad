//=============================================================================
///**
// *  @file x86array_sub.h
// *
// *  $Id: x86array_sub.h 16.10.2011  $
// *
// *  @brief generator 3, assembler vector double/float sub, MS Visual C++ 2003-2008
// *
// *  @author Pant_eleymonov Alek_sandr Kons_tantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef X86ARRAY_SUB_H_
#define X86ARRAY_SUB_H_

//**************************** SUBVECTOR STDCALL *********************************
// array vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *  edx=[esp+12]-c void *  [esp+16]-stepa unsigned int  [esp+20]-stepc unsigned int ecx=[esp+24]-count unsigned int

/// вычетание массива двухмерных векторов и двухмерного вектора, команды SSE
#define ARRAYP2DSUBVECTORSSE_STD \
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
ASM( jecxz _ArrayP2DSubVectorSSEend_loop ) \
ASM( _ArrayP2DSubVectorSSEmloop: ) \
ASM( movlps xmm1,qword ptr [eax] ) \
ASM( movlps xmm2,qword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movhps xmm1,qword ptr [eax] ) \
ASM( movhps xmm2,qword ptr [eax+edi] ) \
ASM( subps xmm1,xmm0 ) \
ASM( subps xmm2,xmm0 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movlps qword ptr [edx],xmm1 ) \
ASM( movlps qword ptr [edx+esi],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movhps qword ptr [edx],xmm1 ) \
ASM( movhps qword ptr [edx+esi],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP2DSubVectorSSEmloop ) \
ASM( _ArrayP2DSubVectorSSEend_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DSubVectorSSEend_loop2 ) \
ASM( _ArrayP2DSubVectorSSEmloop2: ) \
ASM( movlps xmm4,qword ptr [eax] ) \
ASM( add eax,edi ) \
ASM( subps xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DSubVectorSSEmloop2 ) \
ASM( _ArrayP2DSubVectorSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// вычетание массива двухмерных векторов и двухмерного вектора, команды SSE3
#define ARRAYP2DSUBVECTORSSE3_STD \
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
ASM( jecxz _ArrayP2DSubVectorSSE3end_loop ) \
ASM( _ArrayP2DSubVectorSSE3mloop: ) \
ASM( movsd xmm1,qword ptr [eax] ) \
ASM( movsd xmm2,qword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movhps xmm1,qword ptr [eax] ) \
ASM( movhps xmm2,qword ptr [eax+edi] ) \
ASM( subps xmm1,xmm0 ) \
ASM( subps xmm2,xmm0 ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movlps qword ptr [edx],xmm1 ) \
ASM( movlps qword ptr [edx+esi],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( movhps qword ptr [edx],xmm1 ) \
ASM( movhps qword ptr [edx+esi],xmm2 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( loop _ArrayP2DSubVectorSSE3mloop ) \
ASM( _ArrayP2DSubVectorSSE3end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DSubVectorSSE3end_loop2 ) \
ASM( _ArrayP2DSubVectorSSE3mloop2: ) \
ASM( movsd xmm4,qword ptr [eax] ) \
ASM( add eax,edi ) \
ASM( subps xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DSubVectorSSE3mloop2 ) \
ASM( _ArrayP2DSubVectorSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// вычетание массива трехмерных векторов и трехмерных вектора, команды SSE
#define ARRAYP3DSUBVECTORSSE_STD \
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
ASM( jecxz _ArrayP3DSubVectorSSEend_loop ) \
ASM( _ArrayP3DSubVectorSSEmloop: ) \
ASM( movss xmm1,dword ptr [eax] ) \
ASM( movss xmm2,dword ptr [eax+edi] ) \
ASM( movhps xmm1,qword ptr [eax+4] ) \
ASM( movhps xmm2,qword ptr [eax+edi+4] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movss xmm3,dword ptr [eax] ) \
ASM( movss xmm4,dword ptr [eax+edi] ) \
ASM( movhps xmm3,qword ptr [eax+4] ) \
ASM( movhps xmm4,qword ptr [eax+edi+4] ) \
ASM( subps xmm1,xmm0 ) \
ASM( subps xmm2,xmm5 ) \
ASM( subps xmm3,xmm0 ) \
ASM( subps xmm4,xmm5 ) \
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
ASM( loop _ArrayP3DSubVectorSSEmloop ) \
ASM( _ArrayP3DSubVectorSSEend_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP3DSubVectorSSEend_loop2 ) \
ASM( _ArrayP3DSubVectorSSEmloop2: ) \
ASM( movss xmm4,dword ptr [eax] ) \
ASM( movhps xmm4,qword ptr [eax+4] ) \
ASM( add eax,edi ) \
ASM( subps xmm4,xmm0 ) \
ASM( movss dword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+4],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DSubVectorSSEmloop2 ) \
ASM( _ArrayP3DSubVectorSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// вычетание массива четырехмерных векторов и четырехмерного вектора, команды SSE
#define ARRAYP4DSUBVECTORSSE_STD \
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
ASM( jecxz _ArrayP4DSubVectorSSEend_loop ) \
ASM( _ArrayP4DSubVectorSSEmloop: ) \
ASM( movlps xmm1,qword ptr [eax] ) \
ASM( movlps xmm2,qword ptr [eax+edi] ) \
ASM( movhps xmm1,qword ptr [eax+8] ) \
ASM( movhps xmm2,qword ptr [eax+edi+8] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movlps xmm3,qword ptr [eax] ) \
ASM( movlps xmm4,qword ptr [eax+edi] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movhps xmm4,qword ptr [eax+edi+8] ) \
ASM( subps xmm1,xmm0 ) \
ASM( subps xmm2,xmm5 ) \
ASM( subps xmm3,xmm0 ) \
ASM( subps xmm4,xmm5 ) \
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
ASM( loop _ArrayP4DSubVectorSSEmloop ) \
ASM( _ArrayP4DSubVectorSSEend_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4DSubVectorSSEend_loop2 ) \
ASM( _ArrayP4DSubVectorSSEmloop2: ) \
ASM( movlps xmm4,qword ptr [eax] ) \
ASM( movhps xmm4,qword ptr [eax+8] ) \
ASM( add eax,edi ) \
ASM( subps xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DSubVectorSSEmloop2 ) \
ASM( _ArrayP4DSubVectorSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// вычетание массива четырехмерных векторов и четырехмерного вектора, команды SSE3
#define ARRAYP4DSUBVECTORSSE3_STD \
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
ASM( jecxz _ArrayP4DSubVectorSSE3end_loop ) \
ASM( _ArrayP4DSubVectorSSE3mloop: ) \
ASM( lddqu xmm1,xmmword ptr [eax] ) \
ASM( lddqu xmm2,xmmword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( lddqu xmm3,xmmword ptr [eax] ) \
ASM( lddqu xmm4,xmmword ptr [eax+edi] ) \
ASM( subps xmm1,xmm0 ) \
ASM( subps xmm2,xmm5 ) \
ASM( subps xmm3,xmm0 ) \
ASM( subps xmm4,xmm5 ) \
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
ASM( loop _ArrayP4DSubVectorSSE3mloop ) \
ASM( _ArrayP4DSubVectorSSE3end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4DSubVectorSSE3end_loop2 ) \
ASM( _ArrayP4DSubVectorSSE3mloop2: ) \
ASM( lddqu xmm4,xmmword ptr [eax] ) \
ASM( add eax,edi ) \
ASM( subps xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DSubVectorSSE3mloop2 ) \
ASM( _ArrayP4DSubVectorSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// вычетание массива двухмерных векторов двойной точности и двухмерного вектора, команды SSE2
#define ARRAYP2DDSUBVECTORSSE2_STD \
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
ASM( jecxz _ArrayP2DDSubVectorSSE2end_loop ) \
ASM( _ArrayP2DDSubVectorSSE2mloop: ) \
ASM( movsd xmm1,qword ptr [eax] ) \
ASM( movsd xmm2,qword ptr [eax+edi] ) \
ASM( movhps xmm1,qword ptr [eax+8] ) \
ASM( movhps xmm2,qword ptr [eax+edi+8] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movsd xmm3,qword ptr [eax] ) \
ASM( movsd xmm4,qword ptr [eax+edi] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movhps xmm4,qword ptr [eax+edi+8] ) \
ASM( subpd xmm1,xmm0 ) \
ASM( subpd xmm2,xmm5 ) \
ASM( subpd xmm3,xmm0 ) \
ASM( subpd xmm4,xmm5 ) \
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
ASM( loop _ArrayP2DDSubVectorSSE2mloop ) \
ASM( _ArrayP2DDSubVectorSSE2end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DDSubVectorSSE2end_loop2 ) \
ASM( _ArrayP2DDSubVectorSSE2mloop2: ) \
ASM( movsd xmm4,qword ptr [eax] ) \
ASM( movhps xmm4,qword ptr [eax+8] ) \
ASM( add eax,edi ) \
ASM( subpd xmm4,xmm0 ) \
ASM( movsd qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DDSubVectorSSE2mloop2 ) \
ASM( _ArrayP2DDSubVectorSSE2end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// вычетание массива двухмерных векторов двойной точности и двухмерного вектора, команды SSE3
#define ARRAYP2DDSUBVECTORSSE3_STD \
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
ASM( jecxz _ArrayP2DDSubVectorSSE3end_loop ) \
ASM( _ArrayP2DDSubVectorSSE3mloop: ) \
ASM( lddqu xmm1,xmmword ptr [eax] ) \
ASM( lddqu xmm2,xmmword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( lddqu xmm3,xmmword ptr [eax] ) \
ASM( lddqu xmm4,xmmword ptr [eax+edi] ) \
ASM( subpd xmm1,xmm0 ) \
ASM( subpd xmm2,xmm5 ) \
ASM( subpd xmm3,xmm0 ) \
ASM( subpd xmm4,xmm5 ) \
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
ASM( loop _ArrayP2DDSubVectorSSE3mloop ) \
ASM( _ArrayP2DDSubVectorSSE3end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP2DDSubVectorSSE3end_loop2 ) \
ASM( _ArrayP2DDSubVectorSSE3mloop2: ) \
ASM( lddqu xmm4,xmmword ptr [eax] ) \
ASM( add eax,edi ) \
ASM( subpd xmm4,xmm0 ) \
ASM( movsd qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP2DDSubVectorSSE3mloop2 ) \
ASM( _ArrayP2DDSubVectorSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// вычетание массива трехмерных векторов двойной точности и трехмерных вектора, команды SSE2
#define ARRAYP3DDSUBVECTORSSE2_STD \
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
ASM( jnz _ArrayP3DDSubVectorSSE2mloop ) \
ASM( jmp _ArrayP3DDSubVectorSSE2end_loop ) \
ASM( _ArrayP3DDSubVectorSSE2mloop: ) \
ASM( movsd xmm3,qword ptr [eax] ) \
ASM( movsd xmm4,qword ptr [eax+16] ) \
ASM( movsd xmm5,qword ptr [eax+edi] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movhps xmm4,qword ptr [eax+edi+16] ) \
ASM( movhps xmm5,qword ptr [eax+edi+8] ) \
ASM( subpd xmm3,xmm0 ) \
ASM( subpd xmm4,xmm1 ) \
ASM( subpd xmm5,xmm2 ) \
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
ASM( subpd xmm3,xmm0 ) \
ASM( subpd xmm4,xmm1 ) \
ASM( subpd xmm5,xmm2 ) \
ASM( movsd qword ptr [edx],xmm3 ) \
ASM( movsd qword ptr [edx+16],xmm4 ) \
ASM( movsd qword ptr [edx+esi],xmm5 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movhps qword ptr [edx+esi+16],xmm4 ) \
ASM( movhps qword ptr [edx+esi+8],xmm5 ) \
ASM( lea edx,[edx+esi*2] ) \
ASM( dec ecx ) \
ASM( jecxz _ArrayP3DDSubVectorSSE2end_loop ) \
ASM( jmp _ArrayP3DDSubVectorSSE2mloop ) \
ASM( _ArrayP3DDSubVectorSSE2end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP3DDSubVectorSSE2end_loop2 ) \
ASM( _ArrayP3DDSubVectorSSE2mloop2: ) \
ASM( movsd xmm3,qword ptr [eax] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movsd xmm4,qword ptr [eax+16] ) \
ASM( subpd xmm3,xmm0 ) \
ASM( subsd xmm4,xmm1 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm3 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movsd qword ptr [edx+16],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP3DDSubVectorSSE2mloop2 ) \
ASM( _ArrayP3DDSubVectorSSE2end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// вычетание массива четырехмерных векторов двойной точности и четырехмерного вектора, команды SSE2
#define ARRAYP4DDSUBVECTORSSE2_STD \
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
ASM( jnz _ArrayP4DDSubVectorSSE2mloop ) \
ASM( jmp _ArrayP4DDSubVectorSSE2end_loop ) \
ASM( _ArrayP4DDSubVectorSSE2mloop: ) \
ASM( movsd xmm2,qword ptr [eax] ) \
ASM( movsd xmm3,qword ptr [eax+16] ) \
ASM( movhps xmm2,qword ptr [eax+8] ) \
ASM( movhps xmm3,qword ptr [eax+24] ) \
ASM( movsd xmm4,qword ptr [eax+edi] ) \
ASM( movsd xmm5,qword ptr [eax+edi+16] ) \
ASM( movhps xmm4,qword ptr [eax+edi+8] ) \
ASM( movhps xmm5,qword ptr [eax+edi+24] ) \
ASM( subpd xmm2,xmm0 ) \
ASM( subpd xmm3,xmm1 ) \
ASM( subpd xmm4,xmm0 ) \
ASM( subpd xmm5,xmm1 ) \
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
ASM( subpd xmm2,xmm0 ) \
ASM( subpd xmm3,xmm1 ) \
ASM( subpd xmm4,xmm0 ) \
ASM( subpd xmm5,xmm1 ) \
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
ASM( jecxz _ArrayP4DDSubVectorSSE2end_loop ) \
ASM( jmp _ArrayP4DDSubVectorSSE2mloop ) \
ASM( _ArrayP4DDSubVectorSSE2end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4DDSubVectorSSE2end_loop2 ) \
ASM( _ArrayP4DDSubVectorSSE2mloop2: ) \
ASM( movsd xmm3,qword ptr [eax] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movsd xmm4,qword ptr [eax+16] ) \
ASM( movhps xmm3,qword ptr [eax+24] ) \
ASM( subpd xmm3,xmm0 ) \
ASM( subpd xmm4,xmm1 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm3 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movsd qword ptr [edx+16],xmm4 ) \
ASM( movhps qword ptr [edx+24],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DDSubVectorSSE2mloop2 ) \
ASM( _ArrayP4DDSubVectorSSE2end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// вычетание массива четырехмерных векторов двойной точности и четырехмерного вектора, команды SSE3
#define ARRAYP4DDSUBVECTORSSE3_STD \
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
ASM( jnz _ArrayP4DDSubVectorSSE3mloop ) \
ASM( jmp _ArrayP4DDSubVectorSSE3end_loop ) \
ASM( _ArrayP4DDSubVectorSSE3mloop: ) \
ASM( lddqu xmm2,xmmword ptr [eax] ) \
ASM( lddqu xmm3,xmmword ptr [eax+16] ) \
ASM( lddqu xmm4,xmmword ptr [eax+edi] ) \
ASM( lddqu xmm5,xmmword ptr [eax+edi+16] ) \
ASM( subpd xmm2,xmm0 ) \
ASM( subpd xmm3,xmm1 ) \
ASM( subpd xmm4,xmm0 ) \
ASM( subpd xmm5,xmm1 ) \
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
ASM( subpd xmm2,xmm0 ) \
ASM( subpd xmm3,xmm1 ) \
ASM( subpd xmm4,xmm0 ) \
ASM( subpd xmm5,xmm1 ) \
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
ASM( jecxz _ArrayP4DDSubVectorSSE3end_loop ) \
ASM( jmp _ArrayP4DDSubVectorSSE3mloop ) \
ASM( _ArrayP4DDSubVectorSSE3end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4DDSubVectorSSE3end_loop2 ) \
ASM( _ArrayP4DDSubVectorSSE3mloop2: ) \
ASM( lddqu xmm3,xmmword ptr [eax] ) \
ASM( lddqu xmm4,xmmword ptr [eax+16] ) \
ASM( subpd xmm3,xmm0 ) \
ASM( subpd xmm4,xmm1 ) \
ASM( add eax,edi ) \
ASM( movsd qword ptr [edx],xmm3 ) \
ASM( movhps qword ptr [edx+8],xmm3 ) \
ASM( movsd qword ptr [edx+16],xmm4 ) \
ASM( movhps qword ptr [edx+24],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DDSubVectorSSE3mloop2 ) \
ASM( _ArrayP4DDSubVectorSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

//**************************** SUB STDCALL *********************************
// array vectors eax=[esp+4]-a void *, edx=[esp+8]-b void *  edx=[esp+12]-c void *  [esp+16]-stepa unsigned int  [esp+20]-stepb unsigned int  [esp+24]-stepc unsigned int ecx=[esp+28]-count unsigned int

/// вычетание массивов четырехмерных векторов, команды SSE
#define ARRAYP4ISUBSSE_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movlps xmm0,qword ptr [eax] ) \
ASM( mov ecx,[esp+28] ) \
ASM( mov edx,[esp+12] ) \
ASM( movhps xmm0,qword ptr [eax+8] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+24] ) \
ASM( movaps xmm5,xmm0 ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP4ISubSSEend_loop ) \
ASM( _ArrayP4ISubSSEmloop: ) \
ASM( movlps xmm1,qword ptr [eax] ) \
ASM( movlps xmm2,qword ptr [eax+edi] ) \
ASM( movhps xmm1,qword ptr [eax+8] ) \
ASM( movhps xmm2,qword ptr [eax+edi+8] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movlps xmm3,qword ptr [eax] ) \
ASM( movlps xmm4,qword ptr [eax+edi] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movhps xmm4,qword ptr [eax+edi+8] ) \
ASM( psubd xmm1,xmm0 ) \
ASM( psubd xmm2,xmm5 ) \
ASM( psubd xmm3,xmm0 ) \
ASM( psubd xmm4,xmm5 ) \
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
ASM( loop _ArrayP4ISubSSEmloop ) \
ASM( _ArrayP4ISubSSEend_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4ISubSSEend_loop2 ) \
ASM( _ArrayP4ISubSSEmloop2: ) \
ASM( movlps xmm4,qword ptr [eax] ) \
ASM( movhps xmm4,qword ptr [eax+8] ) \
ASM( add eax,edi ) \
ASM( psubd xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4ISubSSEmloop2 ) \
ASM( _ArrayP4ISubSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// вычетание массивов четырехмерных векторов, команды SSE3
#define ARRAYP4ISUBSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov [esp-16],ebx ) \
ASM( mov ebx,[esp+8] ) \
ASM( mov ecx,[esp+28] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov esi,[esp+24] ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP4ISubSSE3end_loop ) \
ASM( _ArrayP4ISubSSE3mloop: ) \
ASM( mov edi,[esp+20] ) \
ASM( lddqu xmm0,xmmword ptr [ebx] ) \
ASM( lddqu xmm5,xmmword ptr [ebx+edi] ) \
ASM( lea ebx,[ebx+edi*2] ) \
ASM( lddqu xmm6,xmmword ptr [ebx] ) \
ASM( lddqu xmm7,xmmword ptr [ebx+edi] ) \
ASM( mov edi,[esp+16] ) \
ASM( lddqu xmm1,xmmword ptr [eax] ) \
ASM( lddqu xmm2,xmmword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( lddqu xmm3,xmmword ptr [eax] ) \
ASM( lddqu xmm4,xmmword ptr [eax+edi] ) \
ASM( psubd xmm1,xmm0 ) \
ASM( psubd xmm2,xmm5 ) \
ASM( psubd xmm3,xmm6 ) \
ASM( psubd xmm4,xmm7 ) \
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
ASM( loop _ArrayP4ISubSSE3mloop ) \
ASM( _ArrayP4ISubSSE3end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4ISubSSE3end_loop2 ) \
ASM( _ArrayP4ISubSSE3mloop2: ) \
ASM( lddqu xmm0,xmmword ptr [ebx] ) \
ASM( lddqu xmm4,xmmword ptr [eax] ) \
ASM( add ebx,[esp+20] ) \
ASM( add eax,[esp+16] ) \
ASM( psubd xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4ISubSSE3mloop2 ) \
ASM( _ArrayP4ISubSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
ASM( mov ebx,[esp-16]) \
_END_ASM

/// вычетание массивов четырехмерных векторов, команды SSE
#define ARRAYP4DSUBSSE_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov eax,[esp+8] ) \
ASM( movlps xmm0,qword ptr [eax] ) \
ASM( mov ecx,[esp+28] ) \
ASM( mov edx,[esp+12] ) \
ASM( movhps xmm0,qword ptr [eax+8] ) \
ASM( mov edi,[esp+16] ) \
ASM( mov esi,[esp+24] ) \
ASM( movaps xmm5,xmm0 ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP4DSubSSEend_loop ) \
ASM( _ArrayP4DSubSSEmloop: ) \
ASM( movlps xmm1,qword ptr [eax] ) \
ASM( movlps xmm2,qword ptr [eax+edi] ) \
ASM( movhps xmm1,qword ptr [eax+8] ) \
ASM( movhps xmm2,qword ptr [eax+edi+8] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( movlps xmm3,qword ptr [eax] ) \
ASM( movlps xmm4,qword ptr [eax+edi] ) \
ASM( movhps xmm3,qword ptr [eax+8] ) \
ASM( movhps xmm4,qword ptr [eax+edi+8] ) \
ASM( subps xmm1,xmm0 ) \
ASM( subps xmm2,xmm5 ) \
ASM( subps xmm3,xmm0 ) \
ASM( subps xmm4,xmm5 ) \
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
ASM( loop _ArrayP4DSubSSEmloop ) \
ASM( _ArrayP4DSubSSEend_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4DSubSSEend_loop2 ) \
ASM( _ArrayP4DSubSSEmloop2: ) \
ASM( movlps xmm4,qword ptr [eax] ) \
ASM( movhps xmm4,qword ptr [eax+8] ) \
ASM( add eax,edi ) \
ASM( subps xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DSubSSEmloop2 ) \
ASM( _ArrayP4DSubSSEend_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
_END_ASM

/// вычетание массивов четырехмерных векторов, команды SSE3
#define ARRAYP4DSUBSSE3_STD \
_BEGIN_ASM \
ASM( mov [esp-8],edi ) \
ASM( mov [esp-12],esi ) \
ASM( mov [esp-16],ebx ) \
ASM( mov ebx,[esp+8] ) \
ASM( mov ecx,[esp+28] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov esi,[esp+24] ) \
ASM( mov eax,[esp+4] ) \
ASM( shr ecx,2 ) \
ASM( jecxz _ArrayP4DSubSSE3end_loop ) \
ASM( _ArrayP4DSubSSE3mloop: ) \
ASM( mov edi,[esp+20] ) \
ASM( lddqu xmm0,xmmword ptr [ebx] ) \
ASM( lddqu xmm5,xmmword ptr [ebx+edi] ) \
ASM( lea ebx,[ebx+edi*2] ) \
ASM( lddqu xmm6,xmmword ptr [ebx] ) \
ASM( lddqu xmm7,xmmword ptr [ebx+edi] ) \
ASM( mov edi,[esp+16] ) \
ASM( lddqu xmm1,xmmword ptr [eax] ) \
ASM( lddqu xmm2,xmmword ptr [eax+edi] ) \
ASM( lea eax,[eax+edi*2] ) \
ASM( lddqu xmm3,xmmword ptr [eax] ) \
ASM( lddqu xmm4,xmmword ptr [eax+edi] ) \
ASM( subps xmm1,xmm0 ) \
ASM( subps xmm2,xmm5 ) \
ASM( subps xmm3,xmm6 ) \
ASM( subps xmm4,xmm7 ) \
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
ASM( loop _ArrayP4DSubSSE3mloop ) \
ASM( _ArrayP4DSubSSE3end_loop: ) \
ASM( mov ecx,[esp+24] ) \
ASM( and ecx,3 ) \
ASM( jecxz _ArrayP4DSubSSE3end_loop2 ) \
ASM( _ArrayP4DSubSSE3mloop2: ) \
ASM( lddqu xmm0,xmmword ptr [ebx] ) \
ASM( lddqu xmm4,xmmword ptr [eax] ) \
ASM( add ebx,[esp+20] ) \
ASM( add eax,[esp+16] ) \
ASM( subps xmm4,xmm0 ) \
ASM( movlps qword ptr [edx],xmm4 ) \
ASM( movhps qword ptr [edx+8],xmm4 ) \
ASM( add edx,esi ) \
ASM( loop _ArrayP4DSubSSE3mloop2 ) \
ASM( _ArrayP4DSubSSE3end_loop2: ) \
ASM( mov edi,[esp-8]) \
ASM( mov esi,[esp-12]) \
ASM( mov ebx,[esp-16]) \
_END_ASM


#endif /* X86ARRAY_SUB_H_ */

