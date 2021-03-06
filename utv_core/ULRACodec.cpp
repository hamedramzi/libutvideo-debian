/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id: ULRACodec.cpp 955 2012-10-18 13:53:44Z umezawa $ */

#include "stdafx.h"
#include "utvideo.h"
#include "ULRACodec.h"
#include "Predict.h"

const utvf_t CULRACodec::m_utvfEncoderInput[] = {
	UTVF_NFCC_BGRA_BU,
	UTVF_NFCC_BGRX_BU,
	UTVF_NFCC_BGRA_TD,
	UTVF_NFCC_ARGB_TD,
	UTVF_INVALID,
};

const utvf_t CULRACodec::m_utvfDecoderOutput[] = {
	UTVF_NFCC_BGRA_BU,
	UTVF_NFCC_BGRX_BU,
	UTVF_NFCC_BGRA_TD,
	UTVF_NFCC_ARGB_TD,
	UTVF_INVALID,
};

const utvf_t CULRACodec::m_utvfCompressed[] = {
	UTVF_ULRA,
	UTVF_INVALID,
};

CULRACodec::CULRACodec(const char *pszInterfaceName) : CUL00Codec("ULRA", pszInterfaceName)
{
}

CULRACodec::~CULRACodec(void)
{
}

CCodec *CULRACodec::CreateInstance(const char *pszInterfaceName)
{
	return new CULRACodec(pszInterfaceName);
}

void CULRACodec::CalcPlaneSizes(unsigned int width, unsigned int height)
{
	m_dwPlaneSize[0]          = width * height;
	m_dwPlaneSize[1]          = width * height;
	m_dwPlaneSize[2]          = width * height;
	m_dwPlaneSize[3]          = width * height;

	m_dwPlaneWidth[0]         = width;
	m_dwPlaneWidth[1]         = width;
	m_dwPlaneWidth[2]         = width;
	m_dwPlaneWidth[3]         = width;

	m_dwPlaneStripeSize[0]    = width;
	m_dwPlaneStripeSize[1]    = width;
	m_dwPlaneStripeSize[2]    = width;
	m_dwPlaneStripeSize[3]    = width;

	m_dwPlanePredictStride[0] = width;
	m_dwPlanePredictStride[1] = width;
	m_dwPlanePredictStride[2] = width;
	m_dwPlanePredictStride[3] = width;
}

void CULRACodec::ConvertToPlanar(uint32_t nBandIndex)
{
	uint8_t *g, *b, *r, *a;
	const uint8_t *pSrcBegin, *pSrcEnd, *pStrideBegin, *p;

	pSrcBegin = ((uint8_t *)m_pInput) + m_dwRawStripeBegin[nBandIndex] * m_dwRawStripeSize;
	pSrcEnd   = ((uint8_t *)m_pInput) + m_dwRawStripeEnd[nBandIndex]   * m_dwRawStripeSize;
	g = m_pCurFrame->GetPlane(0) + m_dwPlaneStripeBegin[nBandIndex] * m_dwPlaneStripeSize[0];
	b = m_pCurFrame->GetPlane(1) + m_dwPlaneStripeBegin[nBandIndex] * m_dwPlaneStripeSize[1];
	r = m_pCurFrame->GetPlane(2) + m_dwPlaneStripeBegin[nBandIndex] * m_dwPlaneStripeSize[2];
	a = m_pCurFrame->GetPlane(3) + m_dwPlaneStripeBegin[nBandIndex] * m_dwPlaneStripeSize[3];

	switch (m_utvfRaw)
	{
	case UTVF_NFCC_BGRA_BU:
	case UTVF_NFCC_BGRX_BU:
		for (pStrideBegin = pSrcEnd - m_dwRawGrossWidth; pStrideBegin >= pSrcBegin; pStrideBegin -= m_dwRawGrossWidth)
		{
			const uint8_t *pStrideEnd = pStrideBegin + m_nWidth * 4;
			for (p = pStrideBegin; p < pStrideEnd; p += 4)
			{
				*g++ = *(p+1);
				*b++ = *(p+0) - *(p+1) + 0x80;
				*r++ = *(p+2) - *(p+1) + 0x80;
				*a++ = *(p+3);
			}
		}
		break;
	case UTVF_NFCC_BGRA_TD:
		for (pStrideBegin = pSrcBegin; pStrideBegin < pSrcEnd; pStrideBegin += m_dwRawGrossWidth)
		{
			const uint8_t *pStrideEnd = pStrideBegin + m_nWidth * 4;
			for (p = pStrideBegin; p < pStrideEnd; p += 4)
			{
				*g++ = *(p+1);
				*b++ = *(p+0) - *(p+1) + 0x80;
				*r++ = *(p+2) - *(p+1) + 0x80;
				*a++ = *(p+3);
			}
		}
		break;
	case UTVF_NFCC_ARGB_TD:
		for (pStrideBegin = pSrcBegin; pStrideBegin < pSrcEnd; pStrideBegin += m_dwRawGrossWidth)
		{
			const uint8_t *pStrideEnd = pStrideBegin + m_nWidth * 4;
			for (p = pStrideBegin; p < pStrideEnd; p += 4)
			{
				*g++ = *(p+2);
				*b++ = *(p+3) - *(p+2) + 0x80;
				*r++ = *(p+1) - *(p+2) + 0x80;
				*a++ = *(p+0);
			}
		}
		break;
	}
}

void CULRACodec::ConvertFromPlanar(uint32_t nBandIndex)
{
	const uint8_t *g, *b, *r, *a;
	uint8_t *pDstBegin, *pDstEnd, *pStrideBegin, *p;

	pDstBegin = ((uint8_t *)m_pOutput) + m_dwRawStripeBegin[nBandIndex] * m_dwRawStripeSize;
	pDstEnd   = ((uint8_t *)m_pOutput) + m_dwRawStripeEnd[nBandIndex]   * m_dwRawStripeSize;
	g = m_pCurFrame->GetPlane(0) + m_dwPlaneStripeBegin[nBandIndex] * m_dwPlaneStripeSize[0];
	b = m_pCurFrame->GetPlane(1) + m_dwPlaneStripeBegin[nBandIndex] * m_dwPlaneStripeSize[1];
	r = m_pCurFrame->GetPlane(2) + m_dwPlaneStripeBegin[nBandIndex] * m_dwPlaneStripeSize[2];
	a = m_pCurFrame->GetPlane(3) + m_dwPlaneStripeBegin[nBandIndex] * m_dwPlaneStripeSize[3];

	switch (m_utvfRaw)
	{
	case UTVF_NFCC_BGRA_BU:
	case UTVF_NFCC_BGRX_BU:
		for (pStrideBegin = pDstEnd - m_dwRawGrossWidth; pStrideBegin >= pDstBegin; pStrideBegin -= m_dwRawGrossWidth)
		{
			uint8_t *pStrideEnd = pStrideBegin + m_nWidth * 4;
			for (p = pStrideBegin; p < pStrideEnd; p += 4)
			{
				*(p+1) = *g;
				*(p+0) = *b + *g - 0x80;
				*(p+2) = *r + *g - 0x80;
				*(p+3) = *a;
				g++; b++; r++; a++;
			}
		}
		break;
	case UTVF_NFCC_BGRA_TD:
		for (pStrideBegin = pDstBegin; pStrideBegin < pDstEnd; pStrideBegin += m_dwRawGrossWidth)
		{
			uint8_t *pStrideEnd = pStrideBegin + m_nWidth * 4;
			for (p = pStrideBegin; p < pStrideEnd; p += 4)
			{
				*(p+1) = *g;
				*(p+0) = *b + *g - 0x80;
				*(p+2) = *r + *g - 0x80;
				*(p+3) = *a;
				g++; b++; r++; a++;
			}
		}
		break;
	case UTVF_NFCC_ARGB_TD:
		for (pStrideBegin = pDstBegin; pStrideBegin < pDstEnd; pStrideBegin += m_dwRawGrossWidth)
		{
			uint8_t *pStrideEnd = pStrideBegin + m_nWidth * 4;
			for (p = pStrideBegin; p < pStrideEnd; p += 4)
			{
				*(p+2) = *g;
				*(p+3) = *b + *g - 0x80;
				*(p+1) = *r + *g - 0x80;
				*(p+0) = *a;
				g++; b++; r++; a++;
			}
		}
		break;
	}
}

bool CULRACodec::DecodeDirect(uint32_t nBandIndex)
{
	if ((m_fi.dwFlags0 & FI_FLAGS0_INTRAFRAME_PREDICT_MASK) != FI_FLAGS0_INTRAFRAME_PREDICT_LEFT)
		return false;

	uint8_t *pDstBegin = ((uint8_t *)m_pOutput) + m_dwRawStripeBegin[nBandIndex] * m_dwRawStripeSize;
	uint8_t *pDstEnd   = ((uint8_t *)m_pOutput) + m_dwRawStripeEnd[nBandIndex]   * m_dwRawStripeSize;

	switch (m_utvfRaw)
	{
	case UTVF_NFCC_BGRA_BU:
	case UTVF_NFCC_BGRX_BU:
		HuffmanDecodeAndAccumStep4ForBottomupBGRXGreen(pDstBegin+1, pDstEnd+1, m_pDecodeCode[0][nBandIndex], &m_hdt[0], m_dwRawNetWidth, m_dwRawGrossWidth);
		HuffmanDecodeAndAccumStep4ForBottomupBGRXBlue (pDstBegin+0, pDstEnd+0, m_pDecodeCode[1][nBandIndex], &m_hdt[1], m_dwRawNetWidth, m_dwRawGrossWidth);
		HuffmanDecodeAndAccumStep4ForBottomupBGRXRed  (pDstBegin+2, pDstEnd+2, m_pDecodeCode[2][nBandIndex], &m_hdt[2], m_dwRawNetWidth, m_dwRawGrossWidth);
		HuffmanDecodeAndAccumStep4ForBottomupBGRXGreen(pDstBegin+3, pDstEnd+3, m_pDecodeCode[3][nBandIndex], &m_hdt[3], m_dwRawNetWidth, m_dwRawGrossWidth);
		return true;
	case UTVF_NFCC_BGRA_TD:
		HuffmanDecodeAndAccumStep4ForTopdownXRGBGreen(pDstBegin+1, pDstEnd+1, m_pDecodeCode[0][nBandIndex], &m_hdt[0], m_dwRawNetWidth, m_dwRawGrossWidth);
		HuffmanDecodeAndAccumStep4ForTopdownXRGBRed  (pDstBegin+0, pDstEnd+0, m_pDecodeCode[1][nBandIndex], &m_hdt[1], m_dwRawNetWidth, m_dwRawGrossWidth);
		HuffmanDecodeAndAccumStep4ForTopdownXRGBBlue (pDstBegin+2, pDstEnd+2, m_pDecodeCode[2][nBandIndex], &m_hdt[2], m_dwRawNetWidth, m_dwRawGrossWidth);
		HuffmanDecodeAndAccumStep4ForTopdownXRGBGreen(pDstBegin+3, pDstEnd+3, m_pDecodeCode[3][nBandIndex], &m_hdt[3], m_dwRawNetWidth, m_dwRawGrossWidth);
		return true;
	case UTVF_NFCC_ARGB_TD:
		HuffmanDecodeAndAccumStep4ForTopdownXRGBGreen(pDstBegin+2, pDstEnd+2, m_pDecodeCode[0][nBandIndex], &m_hdt[0], m_dwRawNetWidth, m_dwRawGrossWidth);
		HuffmanDecodeAndAccumStep4ForTopdownXRGBBlue (pDstBegin+3, pDstEnd+3, m_pDecodeCode[1][nBandIndex], &m_hdt[1], m_dwRawNetWidth, m_dwRawGrossWidth);
		HuffmanDecodeAndAccumStep4ForTopdownXRGBRed  (pDstBegin+1, pDstEnd+1, m_pDecodeCode[2][nBandIndex], &m_hdt[2], m_dwRawNetWidth, m_dwRawGrossWidth);
		HuffmanDecodeAndAccumStep4ForTopdownXRGBGreen(pDstBegin+0, pDstEnd+0, m_pDecodeCode[3][nBandIndex], &m_hdt[3], m_dwRawNetWidth, m_dwRawGrossWidth);
		return true;
	}

	return false;
}
