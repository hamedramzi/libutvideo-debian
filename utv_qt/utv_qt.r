/*  */
/* $Id: utv_qt.r 797 2011-11-05 18:55:01Z umezawa $ */

#define TARGET_REZ_CARBON_MACHO 1
#define thng_RezTemplateVersion 1
#define cfrg_RezTemplateVersion 1

#include <Carbon/Carbon.r>
#include <QuickTime/QuickTime.r>

resource 'cdci' (256) {
	"Ut Video Codec Suite",				// Name
	1,									// Version
	1,									// Revision level
	'Umzw',								// Manufacturer
	codecInfoDoes32,					// Decompression Flags
	0,									// Compression Flags
	codecInfoDepth32,					// Format Flags
	128,								// Compression Accuracy
	128,								// Decomression Accuracy
	200,								// Compression Speed
	200,								// Decompression Speed
	128,								// Compression Level
	0,									// Reserved
	1,									// Minimum Height
	1,									// Minimum Width
	0,									// Decompression Pipeline Latency
	0,									// Compression Pipeline Latency
	0									// Private Data
};

resource 'dlle' (256) {
	"QTDecoderComponentDispatch"
};

#define SUBTYPE      ULRA
#define SUBTYPE_VAL  'ULRA'
#define SUBTYPE_STR  "ULRA"
#define SUBTYPE_RID  256
#define SUBTYPE_STRI "RGBA"
#include "utv_qt.in.r"

#define SUBTYPE      ULRG
#define SUBTYPE_VAL  'ULRG'
#define SUBTYPE_STR  "ULRG"
#define SUBTYPE_RID  257
#define SUBTYPE_STRI "RGB"
#include "utv_qt.in.r"

#define SUBTYPE      ULY0
#define SUBTYPE_VAL  'ULY0'
#define SUBTYPE_STR  "ULY0"
#define SUBTYPE_RID  258
#define SUBTYPE_STRI "YUV420"
#include "utv_qt.in.r"

#define SUBTYPE      ULY2
#define SUBTYPE_VAL  'ULY2'
#define SUBTYPE_STR  "ULY2"
#define SUBTYPE_RID  259
#define SUBTYPE_STRI "YUV422"
#include "utv_qt.in.r"
