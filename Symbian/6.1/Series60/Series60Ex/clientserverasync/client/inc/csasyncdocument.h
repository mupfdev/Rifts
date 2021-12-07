/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __CSASYNCDOCUMENT_H__
#define __CSASYNCDOCUMENT_H__


#include <eikdoc.h>

// Forward references
class CCSAsyncAppUi;
class CEikApplication;
class CCSAsyncRequestHandler;

/*! 
  @class CCSAsyncDocument
  
  @discussion An instance of class CCSAsyncDocument is the Document part of the AVKON
  application framework for the CSAsync example application
  */
class CCSAsyncDocument : public CEikDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CCSAsyncDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CCSAsyncDocument
  */
    static CCSAsyncDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CCSAsyncDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CCSAsyncDocument
  */
    static CCSAsyncDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CCSAsyncDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CCSAsyncDocument();

/*!
  @function UpdateTime
  
  @discussion Ask the time server to update this documents locally stored time
  */
    void UpdateTime();

/*!
  @function StopClock
  
  @discussion Stop the clock running
  */
    void StopClock();

/*!
  @function Time
  
  @discussion Return the currently stored time
  */
    TTime Time() const;

/*!
  @function ClockActive
  
  @discussion Return whether the clock has been started
  @result true if the clock has been started, false if the clock is stopped
  */
    TBool ClockActive() const;

public: // from CEikDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CCSAsyncAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CCSAsyncDocument object
  */
    void ConstructL();

/*!
  @function CCSAsyncDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CCSAsyncDocument(CEikApplication& aApp);

private: // data

    /** Active object for handling asynchronous requests */
    CCSAsyncRequestHandler* iHandler;
    };


#endif // __CSASYNCDOCUMENT_H__
