/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id: TunedFunc.cpp 950 2012-10-14 09:56:14Z umezawa $ */

#include "stdafx.h"
#include "utvideo.h"
#include "TunedFunc.h"
#include "Predict.h"
#include "HuffmanCode.h"
#include "Convert.h"

const TUNEDFUNC tfnCPP = {
	cpp_PredictMedianAndCount,
	cpp_PredictMedianAndCount,
	cpp_PredictLeftAndCount,
	cpp_RestoreMedian,
	cpp_HuffmanEncode,
	cpp_HuffmanDecode,
	cpp_HuffmanDecodeAndAccum,
	cpp_HuffmanDecodeAndAccumStep2,
	cpp_HuffmanDecodeAndAccumStep4,
	cpp_HuffmanDecodeAndAccumStep4ForBottomupBGRXGreen,
	cpp_HuffmanDecodeAndAccumStep4ForBottomupBGRXBlue,
	cpp_HuffmanDecodeAndAccumStep4ForBottomupBGRXRed,
	cpp_HuffmanDecodeAndAccumStep4ForBottomupBGRXRedAndDummyAlpha,
	cpp_HuffmanDecodeAndAccumStep3ForBottomupBGRGreen,
	cpp_HuffmanDecodeAndAccumStep3ForBottomupBGRBlue,
	cpp_HuffmanDecodeAndAccumStep3ForBottomupBGRRed,
	cpp_HuffmanDecodeAndAccumStep4ForTopdownXRGBGreen,
	cpp_HuffmanDecodeAndAccumStep4ForTopdownXRGBBlue,
	cpp_HuffmanDecodeAndAccumStep4ForTopdownXRGBRed,
	cpp_HuffmanDecodeAndAccumStep4ForTopdownXRGBRedAndDummyAlpha,
	cpp_HuffmanDecodeAndAccumStep3ForTopdownRGBGreen,
	cpp_HuffmanDecodeAndAccumStep3ForTopdownRGBBlue,
	cpp_HuffmanDecodeAndAccumStep3ForTopdownRGBRed,
	cpp_HuffmanDecodeAndAccumStep4ForTopdownBGRXRedAndDummyAlpha,
	cpp_ConvertULY2ToBottomupBGR,
	cpp_ConvertULY2ToBottomupBGRX,
	cpp_ConvertULY2ToTopdownBGR,
	cpp_ConvertULY2ToTopdownBGRX,
	cpp_ConvertULY2ToTopdownRGB,
	cpp_ConvertULY2ToTopdownXRGB,
	cpp_ConvertBottomupBGRToULY2,
	cpp_ConvertBottomupBGRXToULY2,
	cpp_ConvertTopdownBGRToULY2,
	cpp_ConvertTopdownBGRXToULY2,
	cpp_ConvertTopdownRGBToULY2,
	cpp_ConvertTopdownXRGBToULY2,
	DummyTunedFunc
};

TUNEDFUNC tfn = tfnCPP;

#ifdef STATIC_LIB_WITH_ASM
# ifdef __x86_64__
#  include "TunedFunc_x64.cpp"
# elif __i386__
#  include "TunedFunc_x86.cpp"
# endif
#endif
