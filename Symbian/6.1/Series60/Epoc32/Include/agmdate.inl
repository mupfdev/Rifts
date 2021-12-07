// AGMDATE.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//



// ---------------------------- TAgnDateTime -----------------------------------
inline TAgnDateTime::TAgnDateTime()
	{ iDate=AgnDateTime::NullDate(); }

inline TAgnDateTime::TAgnDateTime(TAgnDate aDate,TAgnTime aTime)
	: iDate(aDate),iTime(aTime)
	{}
	
inline TAgnDateTime::TAgnDateTime(TAgnDate aDate)
	: iDate(aDate),iTime(AgnDateTime::NullTime())
	{}

inline TAgnDate TAgnDateTime::Date() const
	{ return (iDate); }

inline TAgnTime TAgnDateTime::Time() const
	{ return (iTime); }

inline void TAgnDateTime::SetDate(TAgnDate aDate)
	{ iDate=aDate; }

inline void TAgnDateTime::SetTime(TAgnTime aTime)
	{ iTime=aTime; }

inline TAgnDateTime::operator TTime() const
	{ return (AgnDateTime::AgnDateTimeToTTime(*this)); }

inline TAgnDateTime::operator TAgnDate() const 
	{ return (iDate); };


// ---------------------------- AgnDateTime ------------------------------------
//inline TTimeIntervalMinutes AgnDateTime::DefaultDisplayTime() 
//	{ return (NullTime()); }

inline TAgnDate AgnDateTime::MinDate()
	{ return (0); }  	

inline TAgnDate AgnDateTime::MaxDate()
	{ 
	return 44194;	
//	return ((TAgnDate)(((TTimeIntervalDays)MaxDateAsTTime().DaysFrom(MinDateAsTTime())).Int()));
	}

inline TAgnDate AgnDateTime::NullDate()
	{ return (0xFFFF); }	 // largest figure that can be stored in a TUint16

inline TAgnTime AgnDateTime::NullTime()
	{ return (0xFFFF); }

inline TUint AgnDateTime::MaxTime()
	{ return 1439; }
//	{ return ((23 * 60) + 59); }

inline TTimeIntervalDays AgnDateTime::MinDateAsTTimeIntervalDaysFrom0AD()
	{ return 723192;}
//	{ return MinDateAsTTime().DaysFrom(TTime(0));}

inline TTimeIntervalDays AgnDateTime::MaxDateAsTTimeIntervalDaysFrom0AD()
	{ return 767386; }
//	{ return MaxDateAsTTime().DaysFrom(TTime(0)); }
