/*  */
/* $Id: QTDecoder.cpp 863 2012-01-23 14:50:08Z umezawa $ */


#include "stdafx.h"
#include "utvideo.h"
#include "QTDecoder.h"
#include "Codec.h"
#include "Format.h"

extern "C" pascal ComponentResult QTDecoderComponentDispatch(ComponentParameters *params, CQTDecoder *glob);

#define IMAGECODEC_BASENAME()		QTDecoder
#define IMAGECODEC_GLOBALS()		CQTDecoder *storage
#define CALLCOMPONENT_BASENAME()	IMAGECODEC_BASENAME()
#define CALLCOMPONENT_GLOBALS()		IMAGECODEC_GLOBALS()

#define COMPONENT_DISPATCH_FILE		"QTDecoderDispatch.h"
#define COMPONENT_SELECT_PREFIX()	kImageCodec
#define COMPONENT_UPP_PREFIX()		uppImageCodec

#define GET_DELEGATE_COMPONENT()	(storage->delegateComponent)

#include <CoreServices/Components.k.h>
#include <QuickTime/ImageCodec.k.h>
#include <QuickTime/ComponentDispatchHelper.c>

pascal ComponentResult QTDecoderOpen(CQTDecoder *glob, ComponentInstance self)
{
	OSErr err;

	glob = (CQTDecoder *)NewPtrClear(sizeof(CQTDecoder));
	if (glob == NULL)
		return memFullErr;

	err = QTCodecOpen(glob, self);
	if (err != noErr)
	{
		DisposePtr((Ptr)glob);
		return err;
	}

	glob->beginBandDone = false;

	{
		const utvf_t *p;
		OSType *post;
		int n;

		p = glob->codec->GetDecoderOutputFormat();
		n = 0;
		while (*p)
		{
			n++;
			p++;
		}

		glob->wantedDestinationPixelTypes = (OSType **)NewHandleClear(sizeof(OSType) * (n + 1));
		post = *glob->wantedDestinationPixelTypes;
		for (p = glob->codec->GetDecoderOutputFormat(); *p; p++)
		{
			if (UtVideoFormatToQuickTimeFormat(post, *p) == 0)
				post++;
		}
		*post = 0;
	}

	return noErr;
}

pascal ComponentResult QTDecoderClose(CQTDecoder *glob, ComponentInstance self)
{
	if (glob != NULL)
	{
		if (glob->wantedDestinationPixelTypes != NULL)
			DisposeHandle((Handle)glob->wantedDestinationPixelTypes);

		QTCodecClose(glob, self);

		DisposePtr((Ptr)glob);
	}

	return noErr;
}

pascal ComponentResult QTDecoderVersion(CQTDecoder *glob)
{
	return QTCodecVersion(glob);
}

pascal ComponentResult QTDecoderTarget(CQTDecoder *glob, ComponentInstance target)
{
	return QTCodecTarget(glob, target);
}

pascal ComponentResult QTDecoderGetCodecInfo(CQTDecoder *glob, CodecInfo *info)
{
	return QTCodecGetCodecInfo(glob, info);
}

pascal ComponentResult QTDecoderPreflight(CQTDecoder *glob, CodecDecompressParams *param)
{
	CMutexLock lock(glob->mutex);

	param->wantedDestinationPixelTypes = glob->wantedDestinationPixelTypes;

	return noErr;
}

pascal ComponentResult QTDecoderInitialize(CQTDecoder *glob, ImageSubCodecDecompressCapabilities *cap)
{
	CMutexLock lock(glob->mutex);

	cap->decompressRecordSize = sizeof(bool);

	return noErr;
}

pascal ComponentResult QTDecoderBeginBand(CQTDecoder *glob, CodecDecompressParams *param, ImageSubCodecDecompressRecord *drp, long flags)
{
	CMutexLock lock(glob->mutex);

	int i;
	long c;
	Handle imgDescExt;
	size_t imgDescExtSize;
	size_t extDataOffset;
	utvf_t outfmt;

	if (glob->beginBandDone)
	{
		*(bool *)drp->userDecompressRecord = true;
		return paramErr;
	}
	glob->beginBandDone = true;
	*(bool *)drp->userDecompressRecord = false;

	if (QuickTimeFormatToUtVideoFormat(&outfmt, param->dstPixMap.pixelFormat) != 0)
		return paramErr;

	imgDescExt = NULL;
	if (GetImageDescriptionExtension(param->imageDescription, &imgDescExt, 'strf', 1) == noErr) // AVI file
		extDataOffset = 40; // sizeof(BITMAPINFOHEADER)
	else if (GetImageDescriptionExtension(param->imageDescription, &imgDescExt, 'glbl', 1) == noErr) // MOV file (converted by ffmpeg/avconv)
		extDataOffset = 0;
	else
		return paramErr;
	imgDescExtSize = GetHandleSize(imgDescExt);
	if (imgDescExtSize < extDataOffset)
	{
		DisposeHandle(imgDescExt);
		return paramErr;
	}
	glob->codec->DecodeBegin(outfmt, (*param->imageDescription)->width, (*param->imageDescription)->height, drp->rowBytes,
							 ((char *)(*imgDescExt)) + extDataOffset, imgDescExtSize - extDataOffset);
	DisposeHandle(imgDescExt);

	return noErr;
}

pascal ComponentResult QTDecoderDrawBand(CQTDecoder *glob, ImageSubCodecDecompressRecord *drp)
{
	CMutexLock lock(glob->mutex);

	glob->codec->DecodeFrame(drp->baseAddr, drp->codecData, true /* XXX */);

	return noErr;
}

pascal ComponentResult QTDecoderEndBand(CQTDecoder *glob, ImageSubCodecDecompressRecord *drp, OSErr result, long flags)
{
	CMutexLock lock(glob->mutex);

	if (*(bool *)drp->userDecompressRecord)
		return noErr;

	glob->codec->DecodeEnd();
	glob->beginBandDone = false;

	return noErr;
}

pascal ComponentResult QTDecoderDecodeBand(CQTDecoder *glob, ImageSubCodecDecompressRecord *drp, unsigned long flags)
{
	return noErr;
}
