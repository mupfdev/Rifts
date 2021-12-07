/* Copyright (c) 2001, Nokia. All rights reserved */
/*!
	@header GuiEngineAppUi
	
*/

#ifndef __GUIENGINEAPPUI_H__
#define __GUIENGINEAPPUI_H__

#include <aknappui.h>
#include <eikmenup.h>

#include "ShapeListManager.h"

class CGuiEngineAppView;
class CGuiEngineDocument;


/*!
  @class	CGuiEngineAppUi

  @discussion	The Application User Interface.
  */
class CGuiEngineAppUi : public CAknAppUi
{
public: 

/*!
  @function	ConstructL
  @abstract	Performs any second stage construction.
  */
    void ConstructL();

/*!
  @function	CGuiEngineAppUi
  @abstract	Performs any first stage construction.
  @param aModel the model
  */
    CGuiEngineAppUi(CGuiEngineDocument* aDocument);

/*!
  @function	~CGuiEngineAppUi
  @abstract	Destroys the instance, and releases any resources.
  */
    ~CGuiEngineAppUi();

/*!
  @function	StoreL
  @abstract	Stores the user interface settings to a store
  @param aStore the store to save the data to
  @result  Returns the id of the stream containing the data
  */
    TStreamId StoreL(CStreamStore& aStore) const;

/*!
  @function	RestoreL
  @abstract	Restores the user interface settings from a store
  @param aStore the store to read the data from
  @param aStreamId the id of the stream containing the data
  */
    void RestoreL(const CStreamStore& aStore, TStreamId aStreamId);

public:	//	from CEikAppUi
/*!
  @function	HandleModelChangeL
  @abstract	Updates the system to reflect changes in the model
  */
    void HandleModelChangeL();

/*!
  @function	HandleCommandL
  @abstract	Carries out a command
  @param aCommand the command to execute
  */
    void HandleCommandL(TInt aCommand);

private:
    /*! @var iAppView The application view */
    CGuiEngineAppView* iAppView;

	/*! @var iDocument The current document */
	CGuiEngineDocument* iDocument;
	};


#endif // __GUIENGINEAPPUI_H__

