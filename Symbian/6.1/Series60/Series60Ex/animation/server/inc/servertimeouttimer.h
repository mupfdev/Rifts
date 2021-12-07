/* Copyright (c) 2001, Nokia. All rights reserved */
#if !defined(__SERVERTIMEOUTTIMER_H__)
#define __SERVERTIMEOUTTIMER_H__

#if !defined __E32BASE_H__
#include <e32base.h>
#endif

class MTimeoutNotify;

/*! 
  @class CTimeOutTimer
  
  @discussion An instance of CTimeoutTimer is a timer for scheduling animation
  */
class CTimeOutTimer: public CTimer
    {
public: // New methods
/*!
  @function NewL
  
  @discussion Create a CTimeOutTimer object using two phase construction,
              and return a pointer to the created object
  @param aPriority the priority to use for the active object
  @param aTimeOutNotify the observer to notify
  */
    static CTimeOutTimer* NewL(const TInt aPriority, MTimeoutNotify& aTimeOutNotify);

/*!
  @function NewLC
  
  @discussion Create a CTimeOutTimer object using two phase construction,
              and return a pointer to the created object
  @param aPriority the priority to use for the active object
  @param aTimeOutNotify the observer to notify
  */
    static CTimeOutTimer* NewLC(const TInt aPriority, MTimeoutNotify& aTimeOutNotify);

/*!
  @function ~CTimeOutTimer
  
  @discussion Destroy any utilised resources
  */
    ~CTimeOutTimer();

public: // From CTimer
/*!
  @function RunL
  
  @discussion Handle the event when the timer expires
  */
    void RunL();

protected: // New methods
/*!
  @function CTimeOutTimer
  
  @discussion Perform the first phase of two phase construction
  @param aPriority the priority to use for the active object
  @param aTimeOutNotify the observer to notify
  */
    CTimeOutTimer(const TInt aPriority, MTimeoutNotify& aTimeOutNotify);

protected: // From CTimer
/*!
  @function ConstructL
  
  @discussion Perform the second phase of two phase construction
  */
    void ConstructL();

private:
/** Reference to object implementing the notify interface. Called on timeout. */
    MTimeoutNotify& iNotify;
    };

#endif //__SERVERTIMEOUTTIMER_H__