// AGMRPTD.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if defined(_DEBUG)
#include <agmutil.h> // Panic called in debug builds
#endif


// ------------------------------ TAgnRpt -------------------------------------------
inline TAgnDate TAgnRpt::StartDateAsAgnDate() const
	{ return (iStartDate); }

inline TAgnDate TAgnRpt::EndDateAsAgnDate() const
	{ return (iEndDate); }

inline void TAgnRpt::SetStartDate(TAgnDate aStartDate)
	{ iStartDate=aStartDate; }

inline void TAgnRpt::SetEndDate(TAgnDate aEndDate)
	{ iEndDate=aEndDate; }

inline TInt TAgnRpt::Interval() const
	{ return (iInterval); }

inline TBool TAgnRpt::DisplayNextOnly() const
	{ return (iDisplayNextOnly); }

inline TBool TAgnRpt::RepeatForever() const
	{ return (iRepeatForever); }

inline void TAgnRpt::SetDisplayNextOnly(TBool aDisplayNextOnly)
	{ iDisplayNextOnly=(TUint8)!!aDisplayNextOnly; }

inline void TAgnRpt::SetInterval(TUint aInterval)
	{ iInterval=(TUint16)aInterval; }




// ---------------------------- TAgnDailyRpt--------------------------------------
//inline TAgnDailyRpt::TAgnDailyRpt(const TAgnRpt& aRpt)
//	: TAgnRpt(aRpt)
//	{}



// ------------------------------ TAgnWeeklyRpt -------------------------------------
//inline TAgnWeeklyRpt::TAgnWeeklyRpt(const TAgnRpt& aRpt)
//	: TAgnRpt(aRpt)
//	{}

inline void TAgnWeeklyRpt::ClearDays()
	{ iWeeklyRptDays=0; }



// ------------------------------ TAgnMonthlyRpt -------------------------
inline TAgnMonthlyRpt::TAgnMonthlyRpt(const TAgnRpt& aRpt)
	: TAgnRpt(aRpt)
	{}


// ----------------------- TAgnMonthlyByDaysRpt --------------------------------
//inline TAgnMonthlyByDaysRpt::TAgnMonthlyByDaysRpt(const TAgnRpt& aRpt)
//	: TAgnMonthlyRpt(aRpt)
//	{}



// ------------------------------- TAgnMonthlyByDatesRpt ----------------------------
//inline TAgnMonthlyByDatesRpt::TAgnMonthlyByDatesRpt(const TAgnRpt& aRpt)
//	: TAgnMonthlyRpt(aRpt)
//	{}

inline void TAgnMonthlyByDatesRpt::ClearAllDates()
	{ iMonthlyRptDates=0; }


// --------------------------- CAgnRptDef -----------------------------------
inline CAgnRptDef::CAgnRptDef()
	{
	}

inline CAgnRptDef::TType CAgnRptDef::Type() const
	{ return (iType); }

inline const TAgnRpt* CAgnRptDef::RptDef() const 
	{ return (iRpt); }

inline const CAgnExceptionList* CAgnRptDef::Exceptions() const
	{ return (iExceptions); }
