/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __TESTLOGGER_H__
#define __TESTLOGGER_H__

#include <e32base.h>

/*! 
  @class MTestLogger
  
  @discussion a class capable of logging test results
  */
class MTestLogger
	{

public:

	enum TLogType
		{
		ELogTypeFile,
		ELogTypeScreen
		};

public:
	
	/*! 
	  @class TLoggingSelection

	  @discussion An instance of class TLoggingSelection stores information about how to log data
	  */
	class TLoggingSelection
		{
	public:
		
	/*!
	  @function TLoggingSelection

	  @discussion Create an instance with no logging turned on 
	  */
		TLoggingSelection();

	/*!
	  @function TurnOn

	  @discussion Turn on logging for a particular type
	  @param aType The type of logging
	  */
		void TurnOn(TLogType aType);

	/*!
	  @function TurnOff

	  @discussion Turn off logging for a particular type
	  @param aType The type of logging
	  */
		void TurnOff(TLogType aType);

	/*!
	  @function Logging

	  @discussion Determine whether or not logging is turned on for a particular type
	  @param aType The type of logging
	  @result A boolean representing the state of logging for a particular type
	  */
		TBool Logging(TLogType aType) const;

	private:

	    /*! @var iFile Keeps track of file logging*/
		TBool iFile;
	    /*! @var iScreen Keeps track of screen logging*/
		TBool iScreen;
		};


public:

/*!
  @function SetLogTypeL
  
  @discussion set which method will be used for logging
  */
	virtual void SetLogTypeL(TLoggingSelection aLogType) = 0;

/*!
  @function BeginTest
  
  @discussion log that the test has begun
  @param aTestName name of the test started
  */
	virtual void BeginTest(const TDesC& aTestName) = 0;

/*!
  @function Failed
  
  @discussion log that the test has failed
  @param aReason reason why the test failed
  */
	virtual void Failed(const TDesC& aReason) = 0;

/*!
  @function Passed
  
  @discussion log that the test has passed
  */
	virtual void Passed() = 0;

/*!
  @function Info
  
  @discussion log some information
  @param aReason the information
  */
	virtual void Info(const TDesC& aReason) = 0;
	};


#endif //__TESTLOGGER_H__
