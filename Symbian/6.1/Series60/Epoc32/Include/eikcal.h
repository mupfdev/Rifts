// EIKCAL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCAL_H__)
#define __EIKCAL_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKSCBUT_H__)
#include <eikscbut.h>
#endif

#if !defined(__EIKCMBUT_H__)
#include <eikcmbut.h>
#endif


class MEikCalendarObserver
	{
public:
	virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const=0;
	virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate)=0;
	};


#endif
