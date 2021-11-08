//=============================================================================
///**
// *  @file x86_64intrinsse.h
// *
// *  $Id: x86_64intrinsse.h 23.05.2014  $
// *
// *  @brief macro commands, only for x64 GNU C/C++;
// *
// *  @author Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
// */
//=============================================================================

#ifndef X86_64_INTRINSSE_H_
#define X86_64_INTRINSSE_H_

static _FORCEINLINE __m128 _mm_setzero_ps()
{
	__m128 value;
	__asm__("xorps %a[value], %a[value]" : [value] "=q" (value) : );
	return value;
}

static _FORCEINLINE __m128 _mm_load_ss(float *Offset)
{
	__m128 value;
	__asm__("movss %a[value], %[a]" : [value] "=q" (value) :  [a] "mr" (*a));
	return value;
}

#endif