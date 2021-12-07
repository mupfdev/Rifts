// FAXTIFF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __FAXTIFF_H__
#define __FAXTIFF_H__
#include <faxstore.h>

/********************************************************************/

/* TIFF IFD tags - not all the tags defined are actually used. */

const TUint16 KNewSubfileType_tag (254);
const TUint16 KImageWidth_tag (256);
const TUint16 KImageLength_tag (257);
const TUint16 KBitsPerSample_tag (258);
const TUint16 KCompression_tag (259);
const TUint16 KPhotometricInterpretation_tag (262);
const TUint16 KFillOrder_tag (266);
const TUint16 KDocumentName_tag (269);
const TUint16 KStripOffsets_tag (273);
const TUint16 KOrientation_tag (274);
const TUint16 KSamplesPerPixel_tag (277);
const TUint16 KRowsPerStrip_tag (278);
const TUint16 KStripByteCounts_tag (279);
const TUint16 KXResolution_tag (282);
const TUint16 KYResolution_tag (283);
const TUint16 KT4Options_tag (292);
const TUint16 KT6Options_tag (293);
const TUint16 KResolutionUnit_tag (296);
const TUint16 KPageNumber_tag (297);
const TUint16 KSoftware_tag (305);
const TUint16 KDateTime_tag (306);
const TUint16 KBadFaxLines_tag (326);				
const TUint16 KCleanFaxData_tag (327);				
const TUint16 KConsecutiveBadFaxLines_tag (328);	


//******************************************************
/* TIFF IFD Entry #defines and structure */

const TUint8 KIfdBYTE (1);
const TUint8 KIfdASCII (2);
const TUint8 KIfdSHORT (3);
const TUint8 KIfdLONG (4);
const TUint8 KIfdRATIONAL (5);

//***********************************************************


const TUint16 KIfdEntries (16);
const TUint16 KIfdESize (12);
const TInt KNextIfd ((KIfdEntries * KIfdESize) + 2 + 2);

struct TIfdEntry
   {
   TUint16 iTag;
   TUint16 iType;
   TInt32 iCount;
   TInt32 iValue;
   };

struct TIfd
   {
   TUint16 iAlignmentBytes;
   TUint16 iIfd_count;
   TIfdEntry iNewSubfileType;    // 1
   TIfdEntry iImageWidth;        // 2
   TIfdEntry iImageLength;       // 3
   TIfdEntry iBitsPerSample;     // 4
   TIfdEntry iCompression;       // 5
   TIfdEntry iPhotometricInterpretation; // 6
   TIfdEntry iFillOrder;         // 7
   TIfdEntry iStripOffsets;      // 8
   TIfdEntry iSamplesPerPixel;   // 9
   TIfdEntry iRowsPerStrip;      // 10
   TIfdEntry iStripByteCounts;   // 11
   TIfdEntry iXresolution;       // 12
   TIfdEntry iYresolution;       // 13
   TIfdEntry iT4Options;         // 14
   TIfdEntry iResolutionUnit;    // 15
   TIfdEntry iPageNumber;        // 16
   TInt32 iNextIfd;
   TInt32 iXres[2];
   TInt32 iYres[2];
   };

typedef TPckgBuf <TIfd> TIfdPkg;
typedef TPckgBuf <TIfdEntry> TIfdEntryPkg;
typedef TPckgBuf <TInt32> TInt32Pkg;
typedef TPckgBuf <TInt16> TInt16Pkg;

#endif
