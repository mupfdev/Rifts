// T32WLD.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// Written by BLB, June 1995
//
#if !defined(__T32WLD_H__)
#define __T32WLD_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
//
const TInt KWorldServerMajorVN=1;
const TInt KWorldServerMinorVN=0;
const TInt KWorldServerBuildVN=103;
//
const TInt KMaxZoneName=3;
const TInt KMaxCityName=25;  
const TInt KMaxCountryName=25;
const TInt KMaxAreaCode=10;
const TInt KMaxDialString=50;
const TInt KMaxNatCode=10;
const TInt KMaxNatPrefCode=10;
const TInt KMaxIntlPrefCode=10;
const TInt KMaxWorldRomTitle=32;
const TInt KMaxWorldLatitudeMinutes=90*60;
const TInt KMaxWorldLongitudeMinutes=180*60;
const TInt KMaxWorldUniversalTimeOffsetMinutes=13*60;
const TInt KISOCountryCodeLength=2;
//
typedef TBuf<KMaxCityName> TCityName;
typedef TBuf<KMaxCountryName> TCountryName;
typedef TBuf<KMaxDialString> TDialString;
typedef TBuf<KMaxAreaCode> TAreaCode;
typedef TBuf<KMaxNatCode> TNatCode;
typedef TBuf<KMaxNatPrefCode> TNatPrefCode;
typedef TBuf<KMaxIntlPrefCode> TIntlPrefCode;
typedef TBuf<KISOCountryCodeLength> TISOCountryCode;
//
enum TWldDistanceUnits 
	{
	EWldMiles,
	EWldKilometers,
	EWldNauticalMiles
	};
enum TWldSelect 
	{
	EWithinWorld,
	EWithinCountry
	};
enum TWldDeleteDeniedFlags
	{
	EWldDelNotFound=0x01,
	EWldDelDerivedFromRom=0x02,
	EWldDelHomeCityCountry=0x04,
	EWldDelCapitalCity=0x08,
	EWldDelDefaultCountry=0x10,
	EWldDelAll=0xff
	};
//
class TLatLong
    {
public:
	inline TInt MinutesLat() const; // North is +ve, South is -ve
	inline TInt MinutesLong() const; // West is +ve, East is -ve
	IMPORT_C void SetMinutesL(TInt aLat,TInt aLong); // North and West are +ve, South and East are -ve
	IMPORT_C void SetMinutesCorrectingErrors(TInt aLat,TInt aLong); // North and West are +ve, South and East are -ve
private:
    TInt16 iLat;
    TInt16 iLong;
    };
//
class TCityData
    {
public:
    TCityName iCity;
    TCountryName iCountry;
    TPoint iMapPos;
    TLatLong iLatLong;
    TAreaCode iAreaCode;
    TInt iUniversalTimeOffset; // in minutes
    TDaylightSavingZone iDaylightSavingZone;
    };
//
class TCountryData  
    {
public:
    TCountryName iCountry;
    TNatCode iNatCode;
    TCityName iCapital;
    TNatPrefCode iNatPref;
    TIntlPrefCode iIntlPref;
    };
//
class TWorldId
    {
public:
    IMPORT_C TWorldId();
    inline const TCityName& City() const;
    inline const TCountryName& Country() const;
    inline TWldSelect Select() const;
	inline void SetSelect(TWldSelect aSelector);
private:
    TCityName iCity;
    TWldSelect iSelect;
    TCountryName iCountry;
	friend class RWorldServer;
    };
//
class RWorldServer : public RSessionBase
    {
public:
    IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;
	IMPORT_C void RomTitle(TDes& aText) const;
	IMPORT_C TInt NumberCities() const;
	IMPORT_C TInt NumberCountries() const;
	//
    IMPORT_C void NotifyOnChange(TRequestStatus& aStatus);
    IMPORT_C void NotifyOnChangeCancel();
	//
	IMPORT_C TInt ResetAllData();
	IMPORT_C TInt DataFileSave();
	IMPORT_C TInt DataFileRevertToSaved();
	IMPORT_C TInt DataFileOpen(const TDesC& aDataFile);
    IMPORT_C TInt DataFileLocation(TFileName& aDataFile) const;
	IMPORT_C TInt DataFileSaveAs(const TDesC& aDataFile,TBool aReplace=EFalse);
	//
    IMPORT_C TInt DefaultCountry(TWorldId& aCountry) const;
    IMPORT_C TInt SetDefaultCountry(const TWorldId& aId);
    IMPORT_C TInt Home(TWorldId& aHome) const;
    IMPORT_C TInt SetHome(const TWorldId& aId);
	//
    IMPORT_C TInt AddCity(const TCityData& aCity);
    IMPORT_C TInt AddCountry(const TCountryData& aCountry,const TCityData& aCapital);
    IMPORT_C TInt CityData(TCityData& aCity,const TWorldId& aId) const;
    IMPORT_C TInt CountryData(TCountryData& aCountry,const TWorldId& aId) const;
	IMPORT_C TInt CalculateDistance(TInt& aDistance,const TWorldId& aLeft,const TWorldId& aRight) const;
	IMPORT_C TInt CalculateSunlight(TTime& aSunrise,TTime& aSunset,const TWorldId& aId,const TTime& aDate=Time::NullTTime()) const;
    IMPORT_C TInt DeleteCity(TWorldId& aId);
    IMPORT_C TInt DeleteCountry(TWorldId& aId);
    IMPORT_C TInt DistanceUnits(TWldDistanceUnits& aDistanceUnit) const;
    IMPORT_C TInt SetDistanceUnits(TWldDistanceUnits aUnit);
    IMPORT_C TInt Find(TWorldId& aId,const TDesC& aCity,const TDesC& aCountry) const;
    IMPORT_C TInt FindCity(TWorldId& aCity,const TDesC& aPartialCity) const;
    IMPORT_C TInt FindCountry(TWorldId& aCountry,const TDesC& aPartialCountry) const;
	IMPORT_C TInt FirstCity(TWorldId& aId) const;
	IMPORT_C TInt FirstCountry(TWorldId& aId) const;
	IMPORT_C TInt IsCityDeletable(TInt& aDeleteDeniedFlags,const TWorldId& aId) const;
	IMPORT_C TInt IsCountryDeletable(TInt& aDeleteDeniedFlags,const TWorldId& aId) const;
	IMPORT_C TInt LastCity(TWorldId& aId) const;
	IMPORT_C TInt LastCountry(TWorldId& aId) const;
    IMPORT_C TInt NearestCity(const TPoint& aMapCoord,const TWorldId* aCityToBeat=NULL);
    IMPORT_C TInt NextNearestCity(TWorldId& aId,TInt aMaxNumberToCompare=KMaxTInt);
    IMPORT_C TInt NextCity(TWorldId& aId) const;
    IMPORT_C TInt NextCountry(TWorldId& aId) const;
    IMPORT_C TInt PrevCity(TWorldId& aId) const;
    IMPORT_C TInt PrevCountry(TWorldId& aId) const;
    IMPORT_C TInt UpdateCity(TWorldId& aId,const TCityData& aCity);
    IMPORT_C TInt UpdateCountry(TWorldId& aId,const TCountryData& aCountry);
	IMPORT_C TInt GetCountryNameByISOCode(const TDesC& aCode, TDes& aCountry) const;
	IMPORT_C TInt SetCollationLevelForFind(TInt aCollationLevel); // this is a per-client setting
public: // *** Do not use! API liable to change ***
	IMPORT_C void __DbgFailAlloc(TInt aCount); // for test code only
	IMPORT_C void __DbgMarkEnd(); // for test code only
	IMPORT_C void __DbgMarkHeap(); // for test code only
	IMPORT_C TInt SetRomDatabaseToUse(const TDesC& aRomDatabaseToUse); // for test code only
	IMPORT_C TBool ReadOnlyDataIsInRAM() const; // for test code only
private:
	TInt SendReceiveID(TWorldId& aId,TInt aFunc,TInt aOption,TAny* aMessage[]);
	TInt SendReceiveID(const TWorldId& aId,TInt aFunc,TInt aOption,TAny* aMessage[]) const;
    };
//
#include <t32wld.inl>
#endif

