// Basics.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// NOTE, to aid clarity, all literal text constructed using the _LIT macro
//       is declared immediately before use.
//       In production code, it may be more efficient for _LIT macros to be
//       declared at file scope. 
//       

#include "CommonFramework.h" // standard example stuff


// advance declarations
void printDateTime(TTime);
void showDateProperties(TTime);
void showFormatting(TTime);
void printDifferences(TTime, TTime);


void WaitForKey()
	{
	_LIT(KMsgPressAnyKey,"Press any key to continue\n\n");
	console->Printf(KMsgPressAnyKey);
	console->Getch();
	}


LOCAL_C void doExampleL()
    {
	TTime time;         // time in microseconds since 0AD nominal Gregorian
	TDateTime dateTime; // year-month-day-hour-minute-second-microsecond


		//
		// set and print current date/time
		//
	time.HomeTime(); // set time to home time

	_LIT(KTxt1,"Current date and time in fields (locale independent):\n");
	console->Printf(KTxt1);


		//
		// print all seven fields
		//
	dateTime=time.DateTime();    // convert to fields
	_LIT(KFormat1,"%d %d %d %d:%d:%d.%d\n");
	console->Printf(KFormat1,
		dateTime.Year(),
		TInt(dateTime.Month()+1),// <-- Print month as a TInt to preserve
		                         //     locale independence
		dateTime.Day()+1,        // <-- Day and month ranges begin 
		                         //     at zero (0-30 and 0-11), 
				                 //     so add one when printing
		dateTime.Hour(), dateTime.Minute(), dateTime.Second(),
		dateTime.MicroSecond());
		

		//
		// reset date to 31st December 1996
		//
	TInt year=1996, month=12, day=31; // date, as if from text input
	TInt error=dateTime.Set(year,TMonth(month-1),day-1,23,59,59,999999);// note: month and 
	                                                                    // day are 
	                                                                    // zero-offset!
	User::LeaveIfError(error);        // check date/time set ok
	time=dateTime;	                  // Time = 31st December 1996 23:59 

	_LIT(KTxt2,"Resetting date and time...\n");
	console->Printf(KTxt2);
	printDateTime(time); 
	WaitForKey();

		//
		// Add intervals to time
		//
	TTimeIntervalMonths timeIntervalMonths(2);
	time+=timeIntervalMonths;         // Add two months 
	_LIT(KTxt3,"Adding 2 months to date...\n");
	console->Printf(KTxt3);
	printDateTime(time); 

	time-=timeIntervalMonths;         // Subtract two months 
	_LIT(KTxt4,"Subtracting 2 months from date...\n");
	console->Printf(KTxt4);
	printDateTime(time); 

	WaitForKey();

	TTimeIntervalSeconds timeIntervalSeconds(2147483647);
	time+=timeIntervalSeconds;        // Add max. seconds +1 to time to show overflow
	_LIT(KTxt5,"Adding 2147483648 seconds to date/time - should overflow...\n");
	console->Printf(KTxt5);
	printDateTime(time); 

	timeIntervalSeconds=2147483647;
	time+=timeIntervalSeconds;        // Add max. seconds to time
	_LIT(KTxt6,"Adding 2147483647 seconds to date/time...\n");
	console->Printf(KTxt6);
	printDateTime(time); 

	WaitForKey();

		//
		// Set date to Monday 6th Jan 1997 
		//
	day=5, month=1, year=1997; 
	dateTime.SetMonth(TMonth(month-1));
	dateTime.SetDay(day);
	dateTime.SetYear(year);
	time=dateTime;
	
	_LIT(KTxt7,"Resetting date ...\n");
	console->Printf(KTxt7);
	printDateTime(time); 

	showDateProperties(time);         // Date property functions for Mon 6 Jan 1997 
	WaitForKey();
	showFormatting(time);	          // Date and time formatting
	WaitForKey();

		
		//
		// Create a new date, set it to 6th Jan 1996 to
		// show TTime::MonthsFrom()
		//
	TDateTime newDateTime(1996,EJanuary,5,23,59,59,999999);
	TTime newTime(newDateTime);
	printDifferences(time, newTime);

		//
		// Set newTime to 7th January 1996 00:00:00:000000
		// and print difference in months again
		//
	TTimeIntervalMicroSeconds timeIntervalMicroSeconds(1);
	newTime+=timeIntervalMicroSeconds;
	printDifferences(time, newTime);
	
		//
		// Set newTime to 6th January 1998 23:23:59:999999
		//
	newDateTime.SetYear(1998);
	newTime=newDateTime;
	printDifferences(time, newTime);
		//
		// Set newTime to 7th January 1998 00:00:00:000000
		//
	newTime+=timeIntervalMicroSeconds;
	printDifferences(time, newTime);
	}

void printDateTime(TTime aTime)
	{
	TBuf<40> dateTimeString;

	_LIT(KFormat2,"%D%M%Y%/0%1%/1%2%/2%3%/3 %:0%H%:1%T%:2%S.%C%:3");
	aTime.FormatL(dateTimeString,KFormat2);

	_LIT(KFormat3,"new date and time: %S \n");
	console->Printf(KFormat3,&dateTimeString);
	}

void showDateProperties(TTime aTime)
	{
	//
	// Demonstrate date property functions
	//
	TBuf<10> nameString;

	_LIT(KFormat4,"%F%N");
	aTime.FormatL(nameString,KFormat4); // Get month name

	_LIT(KFormat5,"Days in month (%S) = %d\n");
	console->Printf(KFormat5,&nameString,aTime.DaysInMonth());

	_LIT(KFormat6,"%E");
	aTime.FormatL(nameString,KFormat6); // Get day name

	_LIT(KFormat7,"Day number in year is %d\n");
	console->Printf(KFormat7,aTime.DayNoInYear());	

	_LIT(KFormat8,"Day number in week = %d (%S)\n");
	console->Printf(KFormat8,aTime.DayNoInWeek(),&nameString);

		//
		// Demonstrate first week in year rules
		//
	_LIT(KFormat9,"Week number in year = %d\n");
	console->Printf(KFormat9,aTime.WeekNoInYear());
	
		//
		// Change week number in year rule
		//
	_LIT(KFormat10,"Counting first full week as week 1,\nweek number in year = %d\n");
	console->Printf(KFormat10,aTime.WeekNoInYear(EFirstFullWeek));
	}


void showFormatting(TTime aTime)
	{
	//
	// Format date and time, using system default locale settings
	//
	_LIT(KTxt8,"Formatting the date and time\n");
	console->Printf(KTxt8);

		//
		// Print full day name, day number in month with leading zeros, 
		// date suffix, month name, year
		//	
	TBuf<40> dateString; // This holds the formatted date and time string
	
	_LIT(KFormat11,"%E%D%X%N%Y %1 %2 %3");
	aTime.FormatL(dateString,KFormat11); 

	_LIT(KFormat12,"Full date with date suffix = %S\n");
	console->Printf(KFormat12,&dateString);

		//
		// Print abbreviated day name, day number in month, 
		// date suffix, abbreviated month name, year
		//
	_LIT(KFormat13,"%*E%*D%X%*N%Y %1 %2 %3");
	aTime.FormatL(dateString,KFormat13); 

	_LIT(KFormat14,"Full date with abbreviated names= %S\n");
	console->Printf(KFormat14,&dateString);

		//
		// Print date in numeric form with leading zeros, using default 
		// date ordering (European) and default date separator characters
		//
	_LIT(KFormat15,"%D%M%Y%/0%1%/1%2%/2%3%/3");
	aTime.FormatL(dateString,KFormat15); 

	_LIT(KFormat16,"dd/mm/yyyy = %S\n");
	console->Printf(KFormat16,&dateString);

	
		//
		// Print time using default time separator characters 
		// in 12 and 24 hour clock formats
		//
	_LIT(KFormat17,"%:0%H%:1%T%:2%S.%*C3%:3");
	aTime.FormatL(dateString,KFormat17);

	_LIT(KFormat18,"Hour, minute, second, microsecond (24 hr clock) = %S\n");
	console->Printf(KFormat18,&dateString);

	_LIT(KFormat19,"%:0%I%:1%T%:2%S.%*C3%:3%A");
	aTime.FormatL(dateString,KFormat19);

	_LIT(KFormat20,"Hour, minute, second, microsecond (12 hr clock) = %S\n");
	console->Printf(KFormat20,&dateString);
	}

void printDifferences(TTime aTime, TTime aNewTime)
	{
	//
	// Print number of months difference between two dates
	//
	TBuf<40> dateString;
	TBuf<40> newDateString;

	_LIT(KFormat21,"%D%M%Y%/0%1%/1%2%/2%3%/3 %:0%H%:1%T%:2%S.%C%:3");
	aTime.FormatL(dateString,KFormat21);

	_LIT(KFormat22,"%D%M%Y%/0%1%/1%2%/2%3%/3 %:0%H%:1%T%:2%S.%C%:3");
	aNewTime.FormatL(newDateString,KFormat22);

	_LIT(KFormat23,"Number of months between:\n%S and\n%S = %d\n");
	console->Printf(KFormat23,&dateString,&newDateString,aTime.MonthsFrom(aNewTime));	
	}

