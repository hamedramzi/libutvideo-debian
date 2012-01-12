/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id: TunedFunc.cpp 814 2011-11-30 12:50:19Z umezawa $ */

#include "stdafx.h"
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
	cpp_HuffmanDecodeAndAccumStep4ForBottomupRGB32Green,
	cpp_HuffmanDecodeAndAccumStep4ForBottomupRGB32Blue,
	cpp_HuffmanDecodeAndAccumStep4ForBottomupRGB32Red,
	cpp_HuffmanDecodeAndAccumStep4ForBottomupRGB32RedAndDummyAlpha,
	cpp_HuffmanDecodeAndAccumStep3ForBottomupRGB24Green,
	cpp_HuffmanDecodeAndAccumStep3ForBottomupRGB24Blue,
	cpp_HuffmanDecodeAndAccumStep3ForBottomupRGB24Red,
	cpp_HuffmanDecodeAndAccumStep4ForTopdownRGB32Green,
	cpp_HuffmanDecodeAndAccumStep4ForTopdownRGB32Blue,
	cpp_HuffmanDecodeAndAccumStep4ForTopdownRGB32Red,
	cpp_HuffmanDecodeAndAccumStep4ForTopdownRGB32RedAndDummyAlpha,
	cpp_HuffmanDecodeAndAccumStep3ForTopdownRGB24Green,
	cpp_HuffmanDecodeAndAccumStep3ForTopdownRGB24Blue,
	cpp_HuffmanDecodeAndAccumStep3ForTopdownRGB24Red,
	cpp_ConvertULY2ToBottomupRGB24,
	cpp_ConvertULY2ToBottomupRGB32,
	cpp_ConvertULY2ToTopdownRGB24,
	cpp_ConvertULY2ToTopdownRGB32,
	cpp_ConvertBottomupRGB24ToULY2,
	cpp_ConvertBottomupRGB32ToULY2,
};

TUNEDFUNC tfn = tfnCPP;
