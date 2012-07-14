/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id: TunedFunc_x64.cpp 825 2011-12-11 15:27:46Z umezawa $ */

#include "stdafx.h"
#include "utvideo.h"
#include "TunedFunc.h"
#include "Predict.h"
#include "HuffmanCode.h"
#include "Convert.h"

// intrin.h ���C���N���[�h�����
// error C2733: �I�[�o�[���[�h���ꂽ�֐� '_interlockedbittestandset' �� C �����P�[�W�� 2 ��ȏ�̐錾�͋�����܂���B
// �ȂǂƃG���[���o��B
extern "C" void __cpuid(int *, int);

const TUNEDFUNC tfnSSE2 = {
	x64_sse2_PredictMedianAndCount_align16,
	x64_sse2_PredictMedianAndCount_align1,
	x64_sse2_PredictLeftAndCount_align1,
	x64_sse1mmx_RestoreMedian_align1,
	x64_i686_HuffmanEncode,
	x64_i686_HuffmanDecode,
	x64_i686_HuffmanDecodeAndAccum,
	x64_i686_HuffmanDecodeAndAccumStep2,
	x64_i686_HuffmanDecodeAndAccumStep4,
	x64_i686_HuffmanDecodeAndAccumStep4ForBottomupRGB32Green,
	x64_i686_HuffmanDecodeAndAccumStep4ForBottomupRGB32Blue,
	x64_i686_HuffmanDecodeAndAccumStep4ForBottomupRGB32Red,
	x64_i686_HuffmanDecodeAndAccumStep4ForBottomupRGB32RedAndDummyAlpha,
	x64_i686_HuffmanDecodeAndAccumStep3ForBottomupRGB24Green,
	x64_i686_HuffmanDecodeAndAccumStep3ForBottomupRGB24Blue,
	x64_i686_HuffmanDecodeAndAccumStep3ForBottomupRGB24Red,
	x64_i686_HuffmanDecodeAndAccumStep4ForTopdownRGB32Green,
	x64_i686_HuffmanDecodeAndAccumStep4ForTopdownRGB32Blue,
	x64_i686_HuffmanDecodeAndAccumStep4ForTopdownRGB32Red,
	x64_i686_HuffmanDecodeAndAccumStep4ForTopdownRGB32RedAndDummyAlpha,
	x64_i686_HuffmanDecodeAndAccumStep3ForTopdownRGB24Green,
	x64_i686_HuffmanDecodeAndAccumStep3ForTopdownRGB24Blue,
	x64_i686_HuffmanDecodeAndAccumStep3ForTopdownRGB24Red,
	x64_sse2_ConvertULY2ToBottomupRGB24,
	x64_sse2_ConvertULY2ToBottomupRGB32,
	x64_sse2_ConvertULY2ToTopdownRGB24,
	x64_sse2_ConvertULY2ToTopdownRGB32,
	x64_sse2_ConvertBottomupRGB24ToULY2,
	x64_sse2_ConvertBottomupRGB32ToULY2,
};

const TUNEDFUNC &tfnSSE3 = tfnSSE2;

const TUNEDFUNC &tfnSSSE3 = tfnSSE2;

const TUNEDFUNC &tfnSSE41 = tfnSSE2;

const TUNEDFUNC &tfnSSE42 = tfnSSE2;

class CTunedFuncInitializer
{
public:
	CTunedFuncInitializer()
	{
		uint32_t cpuid_1_ecx = 0;
		uint32_t cpuid_1_edx = 0;

#if defined(_MSC_VER)
		int info[4];
		__cpuid(info, 0);
		if (info[0] >= 1)
		{
			__cpuid(info, 1);
			cpuid_1_ecx = info[2];
			cpuid_1_edx = info[3];
		}
#elif defined(__GNUC__)
		int tmp0, tmp1;
		asm volatile (
			"cpuid"
			: "=a"(tmp0), "=b"(tmp1), "=c"(cpuid_1_ecx), "=d"(cpuid_1_edx)
			: "a"(1)
		);
#else
#error
#endif

		_RPT2(_CRT_WARN, "CPUID.1 ECX=%08X EDX=%08X\n", cpuid_1_ecx, cpuid_1_edx);

		if (cpuid_1_ecx & (1 << 20))
		{
			_RPT0(_CRT_WARN, "supports SSE4.2\n");
			tfn = tfnSSE42;
		}
		else if (cpuid_1_ecx & (1 << 19))
		{
			_RPT0(_CRT_WARN, "supports SSE4.1\n");
			tfn = tfnSSE41;
		}
		else if (cpuid_1_ecx & (1 << 9))
		{
			_RPT0(_CRT_WARN, "supports SSSE3\n");
			tfn = tfnSSSE3;
		}
		else if (cpuid_1_ecx & (1 << 0))
		{
			_RPT0(_CRT_WARN, "supports SSE3\n");
			tfn = tfnSSE3;
		}
		else
		{
			// AMD64 / Intel 64 �� SSE2 ���K�{�B
			_RPT0(_CRT_WARN, "supports SSE2\n");
			tfn = tfnSSE2;
		}
	}
} tfi;
