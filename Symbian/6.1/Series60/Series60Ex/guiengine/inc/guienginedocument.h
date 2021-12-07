/* Copyright (c) 2001, Nokia. All rights reserved */
/*!
	@header GuiEngineDocument
	
*/

#ifndef __GUIENGINEDOCUMENT_H__
#define __GUIENGINEDOCUMENT_H__


#include <eikdoc.h>

#include "ShapeListManager.h"

// Forward references
class CGuiEngineAppUi;
class CEikApplication;


/*!
  @class CGuiEngineDocument
  @discussion An instance of class CGuiEngineDocument is the Document part of the CKON
  application framework for the GuiEngine example application
  */
class CGuiEngineDocument : public CEikDocument
    {
public: // New methods

/*!
  @function NewLC
  @abstract Constructs a CGuiEngineDocument for the application aApp, 
  and return a pointer to the created object
  @result Returns a pointer to the instance which is also on the cleanup stack
  */
    static CGuiEngineDocument* NewLC(CEikApplication& aApp);
/*!
  @function NewL
  @abstract Constructs a CGuiEngineDocument for the application aApp, 
  and return a pointer to the created object
  @result Returns a pointer to the instance
  */
    static CGuiEngineDocument* NewL(CEikApplication& aApp);

/*!
  @function ~CGuiEngineDocument
  @abstract Destroys the object and release all memory objects
  */
    ~CGuiEngineDocument();

/*!
  @function Model
  @abstract Gets the model associated with the document
  @result Returns a reference to a pointer to the model
  */
	CShapeListManager* Model();

public:	// from CApaDocument
/*!
  @function StoreL
  @abstract Stores the document to the store
  @param aStore the store to save the data to
  @param aStreamDict the dictionary to hold the stream id of the data stream
  */
    void StoreL(CStreamStore& aStore, CStreamDictionary& aStreamDic) const;

/*!
  @function RestoreL
  @abstract Restores the document from the store
  @param aStore the store to containing the data to
  @param aStreamDict the dictionary that holds the stream id of the data stream
  */
    void RestoreL(const CStreamStore& aStore, const CStreamDictionary& aStreamDic);

private: // New methods

/*!
  @function CGuiEngineDocument
  @abstract Performs the first phase of two phase construction 
  @param aApp the application
  */
    CGuiEngineDocument(CEikApplication& aApp);

/*!
  @function ConstructL
  @abstract Performs the second phase construction of a CGuiEngineDocument object
  */
    void ConstructL();

/*!
  @function CreateAppUiL
  @abstract Creates a CGuiEngineAppUi object and return a pointer to it
  @result Returns a pointer to the Application's User Interface object
  */
    CEikAppUi* CreateAppUiL();

private:
	/*! @var iModel The model	*/
	CShapeListManager* iModel;

	};


#endif // __GUIENGINEDOCUMENT_H__
