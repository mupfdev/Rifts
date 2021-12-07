/*
* ============================================================================
*  Name     : CAknExGridDocument from CEikDocument
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDDOCUMENT_H
#define AKNEXGRIDDOCUMENT_H

// INCLUDES
#include <eikdoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CAknExGridDocument application class.
*/
class CAknExGridDocument : public CEikDocument
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        */
        static CAknExGridDocument* NewL( CEikApplication& aApp );

        /**
        * Destructor.
        */
        virtual ~CAknExGridDocument();

    public: // New functions

    public: // Functions from base classes

    protected:  // New functions

    protected:  // Functions from base classes

    private:

        /**
        * EPOC default constructor.
        */
        CAknExGridDocument( CEikApplication& aApp );
        void ConstructL();

    private:

        /**
        * From CEikDocument, create CAknExGridAppUi "App UI" object.
        */
        CEikAppUi* CreateAppUiL();
    };

#endif

// End of File

