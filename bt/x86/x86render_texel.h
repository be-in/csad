//=============================================================================
///**
// *  @file render_texel.h
// *
// *  $Id: render_texel.h 16.10.2011  $
// *
// *  @brief generator 3, assembler render texel, MS Visual C++ 2003-2008
// *
// *  @author Panteleymono_v Aleksand_r Konstantinovic_h  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef GEN3_RENDER_TEXEL_H
#define GEN3_RENDER_TEXEL_H

// CPUTYPE1 - cpu 486, Intel Pentium, AMD
// CPUTYPE2 - AMD 3dnow
// CPUTYPE3 - Core2 Duo, Pentium 4
// CPUTYPE4 - core i3, i5, i7

//**************************** TEXEL STDCALL *********************************
// texel eax=[esp+4]-void *ret edx=[esp+8]-void *data edx=[esp+12]-int wboff

#define RENDERPV3BHALFTEXELSSE3_STD \
_BEGIN_ASM \
ASM( xorps xmm7,xmm7 ) \
ASM( xorps xmm6,xmm6 ) \
ASM( mov edx,[esp+12] ) \
ASM( mov ecx,[esp+8] ) \
ASM( mov eax,[ecx] ) \
ASM( movd xmm0,eax ) \
ASM( mov ax,[ecx+4] ) \
ASM( rol eax,8 ) \
ASM( movd xmm1,eax ) \
ASM( mov eax,[ecx+edx] ) \
ASM( movd xmm2,eax ) \
ASM( mov ax,[ecx+edx+4] ) \
ASM( rol eax,8 ) \
ASM( movd xmm3,eax ) \
ASM( mov edx,[esp+4] ) \
ASM( punpcklbw xmm0,xmm7 ) \
ASM( punpcklbw xmm1,xmm6 ) \
ASM( punpcklbw xmm2,xmm7 ) \
ASM( punpcklbw xmm3,xmm6 ) \
ASM( paddw xmm0,xmm1 ) \
ASM( paddw xmm2,xmm3 ) \
ASM( paddw xmm0,xmm2 ) \
ASM( psrlw xmm0,2 ) \
ASM( packuswb xmm0,xmm0 ) \
ASM( movd eax,xmm0 ) \
ASM( mov [edx],ax ) \
ASM( shr eax,16 ) \
ASM( mov [edx+2],al ) \
_END_ASM

#define RENDERPV4BHALFTEXELSSE3_STD \
_BEGIN_ASM \
ASM( xorps xmm7,xmm7 ) \
ASM( xorps xmm6,xmm6 ) \
ASM( mov edx,[esp+12] ) \
ASM( mov eax,[esp+8] ) \
ASM( movsd xmm0,[eax]) \
ASM( movsd xmm2,[eax+edx]) \
ASM( punpcklbw xmm0,xmm7 ) \
ASM( punpcklbw xmm2,xmm6 ) \
ASM( mov edx,[esp+4] ) \
ASM( paddw xmm0,xmm2 ) \
ASM( movhlps xmm2,xmm0 ) \
ASM( paddw xmm0,xmm2 ) \
ASM( psrlw xmm0,2 ) \
ASM( packuswb xmm0,xmm0 ) \
ASM( movss [edx],xmm0) \
_END_ASM

/// Нахождение цвета линейной интерполяцией, команды SSE3
/// @brief for CPUTYPE4
#define RENDERPV3BTEXELSSE3_STD \
_BEGIN_ASM \
ASM( xorps xmm7,xmm7 ) \
ASM( xorps xmm6,xmm6 ) \
ASM( mov eax,[esp+8] ) \
ASM( mov edx,[esp+12] ) \
ASM( mov ecx,[eax] ) \
ASM( movd xmm0,ecx ) \
ASM( mov cx,[eax+4] ) \
ASM( rol ecx,8 ) \
ASM( movd xmm1,ecx ) \
ASM( mov ecx,[eax+edx] ) \
ASM( movd xmm2,ecx ) \
ASM( mov cx,[eax+edx+4] ) \
ASM( rol ecx,8 ) \
ASM( movd xmm3,ecx ) \
ASM( mov edx,[esp+4] ) \
ASM( punpcklbw xmm0,xmm7 ) \
ASM( punpcklbw xmm1,xmm6 ) \
ASM( punpcklbw xmm2,xmm7 ) \
ASM( punpcklbw xmm3,xmm6 ) \
ASM( movss xmm4,[esp+16]) \
ASM( movss xmm5,[esp+20]) \
ASM( punpcklwd xmm0,xmm7 ) \
ASM( punpcklwd xmm1,xmm6 ) \
ASM( punpcklwd xmm2,xmm7 ) \
ASM( punpcklwd xmm3,xmm6 ) \
ASM( shufps xmm4,xmm4,00 ) \
ASM( shufps xmm5,xmm5,00 ) \
ASM( cvtdq2ps xmm0,xmm0 ) \
ASM( cvtdq2ps xmm1,xmm1 ) \
ASM( cvtdq2ps xmm2,xmm2 ) \
ASM( cvtdq2ps xmm3,xmm3 ) \
ASM( subps xmm1,xmm0 ) \
ASM( subps xmm3,xmm2 ) \
ASM( mulps xmm1,xmm4 ) \
ASM( mulps xmm3,xmm4 ) \
ASM( addps xmm1,xmm0 ) \
ASM( addps xmm3,xmm2 ) \
ASM( subps xmm3,xmm1 ) \
ASM( mulps xmm3,xmm5 ) \
ASM( addps xmm3,xmm1 ) \
ASM( cvttps2dq xmm1,xmm3 ) \
ASM( packssdw xmm1,xmm1 ) \
ASM( packuswb xmm1,xmm1 ) \
ASM( movd eax,xmm1 ) \
ASM( mov [edx],ax ) \
ASM( shr eax,16 ) \
ASM( mov [edx+2],al ) \
_END_ASM

/// Нахождение цвета линейной интерполяцией, команды SSE3
/// @brief for CPUTYPE4
#define RENDERPV4BTEXELSSE3_STD \
_BEGIN_ASM \
ASM( xorps xmm7,xmm7 ) \
ASM( xorps xmm6,xmm6 ) \
ASM( mov eax,[esp+8]) \
ASM( mov edx,[esp+12]) \
ASM( movss xmm0,[eax]) \
ASM( movss xmm1,[eax+4]) \
ASM( movss xmm2,[eax+edx]) \
ASM( movss xmm3,[eax+edx+4]) \
ASM( mov edx,[esp+4]) \
ASM( punpcklbw xmm0,xmm7 ) \
ASM( punpcklbw xmm1,xmm6 ) \
ASM( punpcklbw xmm2,xmm7 ) \
ASM( punpcklbw xmm3,xmm6 ) \
ASM( movss xmm4,[esp+16]) \
ASM( movss xmm5,[esp+20]) \
ASM( punpcklwd xmm0,xmm7 ) \
ASM( punpcklwd xmm1,xmm6 ) \
ASM( punpcklwd xmm2,xmm7 ) \
ASM( punpcklwd xmm3,xmm6 ) \
ASM( shufps xmm4,xmm4,00 ) \
ASM( shufps xmm5,xmm5,00 ) \
ASM( cvtdq2ps xmm0,xmm0 ) \
ASM( cvtdq2ps xmm1,xmm1 ) \
ASM( cvtdq2ps xmm2,xmm2 ) \
ASM( cvtdq2ps xmm3,xmm3 ) \
ASM( subps xmm1,xmm0 ) \
ASM( subps xmm3,xmm2 ) \
ASM( mulps xmm1,xmm4 ) \
ASM( mulps xmm3,xmm4 ) \
ASM( addps xmm1,xmm0 ) \
ASM( addps xmm3,xmm2 ) \
ASM( subps xmm3,xmm1 ) \
ASM( mulps xmm3,xmm5 ) \
ASM( addps xmm3,xmm1 ) \
ASM( cvttps2dq xmm1,xmm3 ) \
ASM( packssdw xmm1,xmm1 ) \
ASM( packuswb xmm1,xmm1 ) \
ASM( movss [edx],xmm1) \
_END_ASM

#endif /* GEN3_RENDER_TEXEL_H */
