/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __CSSYNCDOCUMENT_H__
#define __CSSYNCDOCUMENT_H__


#include <eikdoc.h>
#include "TimeServerSession.h"

// Forward references
class CCSSyncAppUi;
class CEikApplication;


/*! 
  @class CCSSyncDocument
  
  @discussion An instance of class CCSSyncDocument is the Document part of the AVKON
  application framework for the CSSync example application
  */
class CCSSyncDocument : public CEikDocument
    {
public: // New methods

/*!
  @function NewL
  
  @discussion Construct a CCSSyncDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CCSSyncDocument
  */
    static CCSSyncDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CCSSyncDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CCSSyncDocument
  */
    static CCSSyncDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CCSSyncDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CCSSyncDocument();

/*!
  @function UpdateTime
  
  @discussion Ask the time server to update this documents locally stored time
  */
    void UpdateTime();

/*!
  @function GetTime
  
  @discussion Return the currently stored time
  */
    const TTime& GetTime() const;

public: // from CEikDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CCSSyncAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL(); 

private: 

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CCSSyncDocument object
  */
    void ConstructL();

/*!
  @function CCSSyncDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
     CCSSyncDocument(CEikApplication& aApp);

private: // data

    // Interface to the Time Server
    RTimeServerSession iServer;

    // The currently displayed time
    TTime iTime;
};


#endif // __CSSYNCDOCUMENT_H__
