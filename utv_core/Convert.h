/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id: Convert.h 889 2012-05-10 10:15:34Z umezawa $ */

#pragma once

#include "TunedFunc.h"

#define ConvertULY2ToBottomupRGB24 tfn.pfnConvertULY2ToBottomupRGB24
#define ConvertULY2ToBottomupRGB32 tfn.pfnConvertULY2ToBottomupRGB32
#define ConvertULY2ToTopdownRGB24 tfn.pfnConvertULY2ToTopdownRGB24
#define ConvertULY2ToTopdownRGB32 tfn.pfnConvertULY2ToTopdownRGB32
#define ConvertBottomupRGB24ToULY2 tfn.pfnConvertBottomupRGB24ToULY2
#define ConvertBottomupRGB32ToULY2 tfn.pfnConvertBottomupRGB32ToULY2
#define ConvertTopdownRGB24ToULY2 tfn.pfnConvertTopdownRGB24ToULY2
#define ConvertTopdownRGB32ToULY2 tfn.pfnConvertTopdownRGB32ToULY2

void cpp_ConvertULY2ToBottomupRGB24(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
void cpp_ConvertULY2ToBottomupRGB32(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
void cpp_ConvertULY2ToTopdownRGB24(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
void cpp_ConvertULY2ToTopdownRGB32(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
void cpp_ConvertBottomupRGB24ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);
void cpp_ConvertBottomupRGB32ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);
void cpp_ConvertTopdownRGB24ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);
void cpp_ConvertTopdownRGB32ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);

#ifdef __i386__
extern "C" void x86_sse2_ConvertULY2ToBottomupRGB24(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x86_sse2_ConvertULY2ToBottomupRGB32(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x86_sse2_ConvertULY2ToTopdownRGB24(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x86_sse2_ConvertULY2ToTopdownRGB32(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x86_sse2_ConvertBottomupRGB24ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x86_sse2_ConvertBottomupRGB32ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x86_sse2_ConvertTopdownRGB24ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x86_sse2_ConvertTopdownRGB32ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);
#endif

#ifdef __x86_64__
extern "C" void x64_sse2_ConvertULY2ToBottomupRGB24(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x64_sse2_ConvertULY2ToBottomupRGB32(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x64_sse2_ConvertULY2ToTopdownRGB24(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x64_sse2_ConvertULY2ToTopdownRGB32(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x64_sse2_ConvertBottomupRGB24ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x64_sse2_ConvertBottomupRGB32ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x64_sse2_ConvertTopdownRGB24ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);
extern "C" void x64_sse2_ConvertTopdownRGB32ToULY2(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbGrossWidth, size_t cbNetWidth);
#endif
