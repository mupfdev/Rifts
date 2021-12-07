// WLDTOOLS.H
// Written by BLB, July 1995
// Copyright (C) Psion PLC 1995
//
//	Define constants relevant to the compressed world database
//
#if !defined(__WLDTOOLS_H__)
#define __WLDTOOLS_H__
#include <e32std.h>

const TInt KWldToolsMajorVersionNumber=1;
const TInt KWldToolsMinorVersionNumber=1;
const TInt KWldToolsBuildVersionNumber=26;
//
const TInt KUidDataFile=268435920; // 0x100001D0
const TInt KUidWorldRomData=268435884; // 0x100001AC
const TInt KUidWorldRomDataCompression1=268435885; // 0x100001AD
const TInt KUidWorldRomDataFormat2=0x1000AF57;
//
const TInt KWldToolsSizeID=1;
const TInt KWldToolsSizeOffset=2;
const TInt KWldToolsSizeUids=16;
const TInt KWldToolsSizeHeader=20;
const TInt KWldToolsSizeNameLen=1;
const TInt KWldToolsSizeIndexChar=2;
const TInt KWldToolsSizeNibDialLen=1;
const TInt KWldToolsSizeDescription=32;
const TInt KWldToolsSizeBitCity=8; // sizeof(TBitPackableCityData)
//
const TInt KWldToolsSizeOfFixedWidthCityEntry_Format2=(2*KWldToolsSizeOffset)+KWldToolsSizeBitCity; // data structure is: offset-to-variable-width-city-entry, offset-to-fixed-width-country-entry, TBitPackableCityData-data-structure
const TInt KWldToolsSizeOfFixedWidthCountryEntry_Format2=3*KWldToolsSizeOffset; // data structure is: offset-to-variable-width-country-entry, offset-to-fixed-width-city-entry-of-capital, ISO-code
const TInt KWldToolsOffsetToCities_Format2=8; // this replaces KWldToolsOffCityIndex - the data structure is: number-of-cities (2-bytes), all-the-fixed-width-city-entries-in-order
const TInt KWldToolsOffsetToCountries_Format2=10; // this replaces KWldToolsOffCountryIndex - the data structure is: number-of-countries (2-bytes), all-the-fixed-width-country-entries-in-order
//
const TInt KWldToolsOffHeader=KWldToolsSizeUids;
const TInt KWldToolsOffDescrip=KWldToolsOffHeader+KWldToolsSizeHeader;
//
const TInt KWldToolsOffReleaseId=0;
const TInt KWldToolsOffDaysOffset=2;
const TInt KWldToolsOffSpare1=4; // set to 1
const TInt KWldToolsOffReleaseVersion=5;
const TInt KWldToolsOffDescription=6;
const TInt KWldToolsOffCityIndex=8; // superseded in format 2 by KWldToolsOffsetToCities_Format2
const TInt KWldToolsOffCountryIndex=10; // superseded in format 2 by KWldToolsOffsetToCountries_Format2
const TInt KWldToolsOffSpare2=12; // set to 0
const TInt KWldToolsOffLanguageId=13;
const TInt KWldToolsOffDefaultCity=14;
const TInt KWldToolsOffDefaultCountry=16;
const TInt KWldToolsOffDefaultAltCity=18;
//
const TInt KWldToolsDialSpacer=10;
const TInt KWldToolsDialPause=11;
const TInt KWldToolsDialSeparator=12;
const TInt KWldToolsDialUnknown=13;
const TInt KWldToolsCharLastIndex=0xffff;
//
const TInt KWldToolsMaxLat=90*60;
const TInt KWldToolsMaxLong=180*60;
const TInt KWldToolsMaxGmt=780;
const TInt KWldToolsMaxMapX=640;
const TInt KWldToolsMaxMapY=240;
//
enum TWldToolsDstZoneIndex
	{
	EWldToolsDstIndexNone,
	EWldToolsDstIndexEurope,
	EWldToolsDstIndexNorth,
	EWldToolsDstIndexSouth,
	EWldToolsDstIndexLast
	};
//
enum TCityDataBitsSize 
	{
	ECityDataBitsLat=14,		// signed
	ECityDataBitsX=10,			// unsigned
	ECityDataBitsY=8,			// unsigned
	ECityDataBitsLong=15,		// signed
	ECityDataBitsGmt=11,		// signed
	ECityDataBitsDst=3,			// unsigned
	ECityDataBitsSpare=3,		
	ECityDataBitsTotal=64 // Must be a multiple of 8
	};

#endif

