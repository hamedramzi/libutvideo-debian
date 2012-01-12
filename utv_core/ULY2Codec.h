/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id: ULY2Codec.h 757 2011-09-12 12:00:17Z umezawa $ */

#pragma once
#include "Codec.h"
#include "UL00Codec.h"
#include "FrameBuffer.h"
#include "Thread.h"
#include "HuffmanCode.h"

class CULY2Codec :
	public CUL00Codec
{
private:
	static const utvf_t m_utvfEncoderInput[];
	static const utvf_t m_utvfDecoderOutput[];
	static const utvf_t m_utvfCompressed[];

public:
	CULY2Codec(const char *pszInterfaceName);
	virtual ~CULY2Codec(void);
	static CCodec *CreateInstance(const char *pszInterfaceName);

public:
	virtual const utvf_t *GetEncoderInputFormat(void) { return m_utvfEncoderInput; }
	virtual const utvf_t *GetDecoderOutputFormat(void) { return m_utvfDecoderOutput; }
	virtual const utvf_t *GetCompressedFormat(void) { return m_utvfCompressed; }

protected:
	virtual const char *GetColorFormatName(void) { return "YUV422"; }
	virtual int GetRealBitCount(void) { return 16; }
	virtual int GetNumPlanes(void) { return 3; }
	virtual void CalcPlaneSizes(unsigned int width, unsigned int height);
	virtual void ConvertToPlanar(uint32_t nBandIndex);
	virtual int GetMacroPixelWidth(void) { return 2; }
	virtual int GetMacroPixelHeight(void) { return 1; }

	virtual void ConvertFromPlanar(uint32_t nBandIndex);
	virtual bool DecodeDirect(uint32_t nBandIndex);
};
