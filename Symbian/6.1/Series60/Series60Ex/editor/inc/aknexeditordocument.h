/*
* ============================================================================
*  Name     : CAknExEditorDocument from CEikDocument
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef AKNEXEDITORDOCUMENT_H
#define AKNEXEDITORDOCUMENT_H

// INCLUDES
#include <eikdoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CAknExEditorDocument application class.
*/
class CAknExEditorDocument : public CEikDocument
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        */
        static CAknExEditorDocument* NewL(CEikApplication& aApp);

        /**
        * Destructor.
        */
        virtual ~CAknExEditorDocument();

    public: // New functions

    public: // Functions from base classes

    protected:  // New functions

    protected:  // Functions from base classes

    private:

        /**
        * EPOC default constructor.
        */
        CAknExEditorDocument(CEikApplication& aApp): CEikDocument(aApp) { }
        void ConstructL();

    private:

        /**
        * From CEikDocument, create CAknExEditorAppUi "App UI" object.
        */
        CEikAppUi* CreateAppUiL();
    };

#endif

// End of File

