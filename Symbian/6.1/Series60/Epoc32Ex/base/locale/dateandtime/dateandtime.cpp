// DateAndTime.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "CommonFramework.h" // standard example stuff

  // advance declarations
LOCAL_C void printDateTime(TDateTime);

  // do the example
LOCAL_C void doExampleL()
    {
	  // Time in microseconds since 0AD nominal Gregorian
	TTime time;

	  // Year-month-day-hour-minute-second-microsecond
	TDateTime dateTime;

	  // Set and print Universal date/time
	_LIT(KTxtUdatetime,"Universal date and time:\n");
	console->Printf(KTxtUdatetime);
	time.UniversalTime();             // Get Universal time (= GMT)     
	dateTime = time.DateTime();       // Convert to fields
	printDateTime(dateTime); 

	 // Set and print current date/time
	_LIT(KTxtDatimCurrent,"Date and time for current locale\n");
	console->Printf(KTxtDatimCurrent);
	time.HomeTime();                 // Set time to now, taking into account
	dateTime = time.DateTime();      // daylight saving and convert to fields

	 // print date/time numerically (locale independently) no offset
	printDateTime(dateTime); 

	TLocale locale;
	
	  // Set date to 31st December 1996
	  // Note that month and day are zero-offset !
	TInt year  = 1996;
    TInt month = 12;
	TInt day   = 31; 
	TInt error = dateTime.Set(year,TMonth(month-1),day-1,9,1,5,1000);

	  // Leave if error setting date & time.
	User::LeaveIfError(error);

	  // Change locale settings
	  // 1. Set new date separators
	_LIT(KTxtChangeLocale,"Changing locale \n");
	console->Printf(KTxtChangeLocale);
	locale.SetDateSeparator('-',1);
	locale.SetDateSeparator('-',2);
	locale.SetDateFormat(EDateEuropean); 
	locale.SetTimeFormat(ETime24);
	locale.SetAmPmSpaceBetween(ETrue);
	  // 2. Set new time zone and daylight saving zone
	  // Offset from universal time (36000 seconds = 10 hours)
	locale.SetUniversalTimeOffset(36000);
	  // set the locale to Southern hemisphere
	locale.SetHomeDaylightSavingZone(EDstSouthern);
	  // Daylight saving on for southern hemisphere
	locale.SetDaylightSaving(EDstSouthern);
	  // set system default settings
	locale.Set(); 
	// Calculate a locale's time from Universal time
	  // (Locale is in Southern Hemisphere)
	time.UniversalTime(); // Get Universal time and offset

	  // Add this locale's universal time offset to localTime
	TTimeIntervalSeconds universalTimeOffset(locale.UniversalTimeOffset());
	time+=universalTimeOffset;

	// If home daylight saving in effect, add one hour offset.
	if (locale.QueryHomeHasDaylightSavingOn())
		{
		TTimeIntervalHours daylightSaving(1);
		time+=daylightSaving;
		}
	_LIT(KTxtCalcLocale,"Calculating locale's time from universal time\n");
	console->Printf(KTxtCalcLocale);
	dateTime=time.DateTime();	
	printDateTime(dateTime);
	}


void formatDateTime(TDes& aBuffer, const TTime& aTime);

LOCAL_C void printDateTime(TDateTime aDateTime)
	{
	  // Print date/time
	  // Notes: 1. Print month as a TInt to preserve locale independence.
	  //        2. Day and month ranges begin at zero (0-30 and 0-11), 
	  //           so add one when printing.
	_LIT(KFormat1,"%d %d %d %d:%d:%d.%d\n");
	console->Printf(KFormat1,
		            aDateTime.Year(),
		            TInt(aDateTime.Month()+1),       // Note 1
				    aDateTime.Day()+1,               // Note 2
				    aDateTime.Hour(),
					aDateTime.Minute(),
					aDateTime.Second(),
		            aDateTime.MicroSecond()
	               );

	  // Print day with date suffix and month name
	TDateSuffix datesuffix(aDateTime.Day());
	TMonthName  monthname(aDateTime.Month());
	_LIT(KFormat2,"Day and month with date suffix: %d%S %S\n");
	console->Printf(KFormat2,aDateTime.Day()+1,&datesuffix,&monthname);

	  // Format to a descriptor and then print
	TBuf<45> dateTimeString;
	TTime time(aDateTime);
	formatDateTime(dateTimeString,time); 
	_LIT(KFormat3,"%S\n");
	console->Printf(KFormat3, &dateTimeString);
	}

void formatDateTime(TDes& aBuffer, const TTime& aTime)
	{ 
	aBuffer.Zero();
	_LIT(KTxtDattimLocDep,"Date and time formatted locale-dependently:\n");
	console->Printf(KTxtDattimLocDep);
	_LIT(KFormat4,"%/0%1%/1%2%/2%3%/3 %-B%:0%J%:1%T%:2%S%:3%+B");
	aTime.FormatL(aBuffer,KFormat4); 
		// gives dd/mm/yyyy hh:mm:ss am/pm, assuming 12 hour clock with 	
		// trailing am/pm text, am/pm space between, and European date format
	}

