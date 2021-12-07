/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __TIMESERVERSESSION_H__
#define __TIMESERVERSESSION_H__

#include <e32base.h>

/*! 
  @class RTimeServerSession
  
  @discussion this class provides the client-side interface to the server session
  */
class RTimeServerSession : public RSessionBase
    {
public:
/*!
  @function RTimeServerSession
  
  @discussion Construct the object
  */
	RTimeServerSession();

/*!
  @function Connect
  
  @discussion Connect to the server and create a session
  @result error code
  */
	TInt Connect();

/*!
  @function Version
  
  @discussion get the version number
  @result the version
  */
	TVersion Version() const;

/*!
  @function RequestTime
  
  @discussion issue a request to the server
  @param aTime the location for the server to write data into
  @param aStatus the TRequestStatus object to be used for async comms
  */
    void RequestTime(TTime& aTime,TRequestStatus& aStatus);

/*!
  @function CancelRequestTime
  
  @discussion cancel any outstanding request to the server
  */
    void CancelRequestTime() const;

private:

    /*! @var iTimeBuffer Buffer to write the time to */
    TPtr8   iTimeBuffer;
    };

#endif // __TIMESERVERSESSION_H__

