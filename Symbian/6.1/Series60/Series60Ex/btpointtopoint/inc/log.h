/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __LOG_H__
#define __LOG_H__

/*! 
  @class MLog
  
  @discussion An instance of MLog has the ability to log text.
  */
class MLog
    {
public:

/*!
  @function LogL
  
  @discussion Add an entry to the log.
  @param aText the text of the entry
  */
    virtual void LogL(const TDesC& aText) = 0;

/*!
  @function LogL
  
  @discussion Add an entry to the log.
  @param aText the text of the entry
  @param aExtraText extra text to append onto the entry
  */
    virtual void LogL(const TDesC& aText, const TDesC& aExtraText) = 0;

/*!
  @function LogL
  
  @discussion Add an entry to the log.
  @param aText the text of the entry
  @param aNumber a number to append onto the entry
  */
    virtual void LogL(const TDesC& aText, TInt aNumber) = 0;

    };




#endif // __LOG_H__
