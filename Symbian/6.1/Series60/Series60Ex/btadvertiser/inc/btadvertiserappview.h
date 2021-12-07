/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTADVERTISERAPPVIEW_H__
#define __BTADVERTISERAPPVIEW_H__

#include <coecntrl.h>
#include <btsdp.h>

/*! 
  @class CBTAdvertiserAppView
  
  @discussion An instance of the Application View object for the BTAdvertiser 
  example application
  */
class CBTAdvertiserAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CBTAdvertiserAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CBTAdvertiserAppView
  */
    static CBTAdvertiserAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CBTAdvertiserAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CBTAdvertiserAppView
  */
    static CBTAdvertiserAppView* NewLC(const TRect& aRect);


/*!
  @function ~CBTAdvertiserAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CBTAdvertiserAppView();

/*!
  @function StopAdvertiserL
  
  @discussion Removes the advertised service from the sdp
  */
	void StopAdvertiserL();

/*!
  @function StopAdvertiser
  
  @discussion Removes the advertised service from the sdp
  */
	void StopAdvertiser();

/*!
  @function StartAdvertiserL
  
  @discussion Add the service to the sdp
  */
    void StartAdvertiserL();

/*!
  @function IsAdvertising

  @result is the application aadvertising a service
  */
    TBool IsAdvertising();

public:  // from CCoeControl

/*!
  @function Draw
  
  @discussion Draw this CBTAdvertiserAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
  

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBTAdvertiserAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CBTAdvertiserAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CBTAdvertiserAppView();

private:

    /*! @var iSdpSession Handle to the SDP session */
    RSdp iSdpSession;

    /*! @var iSdbDatabase Handle to the SDP Database */
    RSdpDatabase iSdpDatabase;

    /*! @var iRecord Handle of the record in the SDP Database */
    TSdpServRecordHandle iRecord;

    /*! @var iIsConnected has a connection been made to the SDP Database */
    TBool iIsConnected;
    };


#endif // __BTADVERTISERAPPVIEW_H__
