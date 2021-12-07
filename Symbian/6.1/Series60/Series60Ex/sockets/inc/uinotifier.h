/* Copyright (c) 2001, Nokia. All rights reserved */


#ifndef __UINOTIFIER_H__
#define __UINOTIFIER_H__


/*! 
  @class MUINotifier
  
  @discussion This class specifies the console output functions.
  */
class MUINotifier
	{
public:
/*!
  @function PrintNotify

  @discussion Display the descriptor as text (with attributes) on the console
  @param aMessage message text
  @param aAttributes font attributes e.g. CEikGlobalTextEditor::EItalic
  */
	virtual void PrintNotify(const TDesC& aMessage, TUint aAttributes = 0) = 0;
/*!
  @function PrintNotify

  @discussion Display the descriptor as text (with attributes) on the console
  @param aMessage message text
  @param aAttributes font attributes e.g. CEikGlobalTextEditor::EItalic
  */
	virtual void PrintNotify(const TDesC8& aMessage, TUint aAttributes = 0) = 0;
/*!
  @function ErrorNotify

  @discussion Display an error message
  @param aErrMessage error message text
  @param aErrCode error code number
  */
	virtual void ErrorNotify(const TDesC& aErrMessage, TInt aErrCode) = 0;
/*!
  @function SetStatus

  @discussion Display the text in the 'status' window
  @param aStatus new status description text
  */
    virtual void SetStatus(const TDesC& aStatus) = 0;
	};

#endif