/////////////////////////////////////////////////////////////////////////////
//
//	MsvOffPeakTime.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef MSV_OFF_PEAK_TIME_H_
#define MSV_OFF_PEAK_TIME_H_

/////////////////////////////////////////////////////////////////////////////
//
//	Constants
//
/////////////////////////////////////////////////////////////////////////////

const TUid		KUidMsvFileOffPeak			= {0x100056BC};	//Used by CMsvOffPeakTimes
const TInt16	KMsvOffPeakTimeVersion		= 1;
const TInt16	KMsvOffPeakTimesVersion		= 1;

/////////////////////////////////////////////////////////////////////////////
//
//	TMsvOffPeakTime Declaration
//
/////////////////////////////////////////////////////////////////////////////

class TMsvOffPeakTime
	{
public:
	IMPORT_C TMsvOffPeakTime();
	IMPORT_C TMsvOffPeakTime(const TDay aDay, const TInt aHour, const TInt aMinute, const TTimeIntervalMinutes aValidityPeriod);

	IMPORT_C void ExternalizeL (RWriteStream &) const;
    IMPORT_C void InternalizeL (RReadStream &);

	IMPORT_C void Reset();

	IMPORT_C const TDay Day() const;
	IMPORT_C void SetDay(const TDay aDay);

	IMPORT_C const TInt Hour() const;
	IMPORT_C void SetHour(const TInt aHour);

	IMPORT_C const TInt Minute() const;
	IMPORT_C void SetMinute(const TInt aMinute);

	IMPORT_C const TTimeIntervalMinutes ValidityPeriod() const;
	IMPORT_C void SetValidityPeriod(const TTimeIntervalMinutes aValidityPeriod);

	IMPORT_C const TTime NextTimeInclusive(const TTime& aFromTime) const;

private:
	TInt16 iVersion;
	TDay iDay;
	TInt8 iHour;							//Start hour
	TInt8 iMinute;							//Start minute
	TTimeIntervalMinutes iValidityPeriod;	//Validity period. Must be less than 24 hours
	};

/////////////////////////////////////////////////////////////////////////////
//
//	CMsvOffPeakTimes Declaration
//
/////////////////////////////////////////////////////////////////////////////

class CMsvOffPeakTimes : public CArrayFixFlat<TMsvOffPeakTime>
	{
public:
	IMPORT_C CMsvOffPeakTimes();

	IMPORT_C void StoreL(CMsvStore& aStore) const;
	IMPORT_C void RestoreL(CMsvStore& aStore);

	IMPORT_C const TInt GetNextOffPeakTime(const TTime& aFromTime, TMsvOffPeakTime& aNext, TTime& aNextTime) const;

protected:

	void ExternalizeL (RWriteStream &) const;
    void InternalizeL (RReadStream &);

private:

	TInt16 iVersion;
	};

#endif