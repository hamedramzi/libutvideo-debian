/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id: TunedFunc.h 814 2011-11-30 12:50:19Z umezawa $ */

#pragma once

struct HUFFMAN_ENCODE_TABLE;
struct HUFFMAN_DECODE_TABLE;

struct TUNEDFUNC
{
	void (*pfnPredictMedianAndCount_align16)(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t dwStride, uint32_t *pCountTable);
	void (*pfnPredictMedianAndCount_align1)(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t dwStride, uint32_t *pCountTable);
	void (*pfnPredictLeftAndCount_align1)(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, uint32_t *pCountTable);
	void (*pfnRestoreMedian_align1)(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t dwStride);
	size_t (*pfnHuffmanEncode)(uint8_t *pDstBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, const HUFFMAN_ENCODE_TABLE *pEncodeTable);
	void (*pfnHuffmanDecode)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable);
	void (*pfnHuffmanDecodeAndAccum)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable);
	void (*pfnHuffmanDecodeAndAccumStep2)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable);
	void (*pfnHuffmanDecodeAndAccumStep4)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable);
	void (*pfnHuffmanDecodeAndAccumStep4ForBottomupRGB32Green)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep4ForBottomupRGB32Blue)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep4ForBottomupRGB32Red)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep4ForBottomupRGB32RedAndDummyAlpha)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep3ForBottomupRGB24Green)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep3ForBottomupRGB24Blue)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep3ForBottomupRGB24Red)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep4ForTopdownRGB32Green)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep4ForTopdownRGB32Blue)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep4ForTopdownRGB32Red)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep4ForTopdownRGB32RedAndDummyAlpha)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep3ForTopdownRGB24Green)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep3ForTopdownRGB24Blue)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnHuffmanDecodeAndAccumStep3ForTopdownRGB24Red)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE *pDecodeTable, size_t dwNetWidth, size_t dwGrossWidth);
	void (*pfnConvertULY2ToBottomupRGB24)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t dwStride, size_t dwDataStride);
	void (*pfnConvertULY2ToBottomupRGB32)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t dwStride, size_t dwDataStride);
	void (*pfnConvertULY2ToTopdownRGB24)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t dwStride, size_t dwDataStride);
	void (*pfnConvertULY2ToTopdownRGB32)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t dwStride, size_t dwDataStride);
	void (*pfnConvertBottomupRGB24ToULY2)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t dwStride, size_t dwDataStride);
	void (*pfnConvertBottomupRGB32ToULY2)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t dwStride, size_t dwDataStride);
};

extern TUNEDFUNC tfn;
