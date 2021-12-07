/*
* ============================================================================
*  Name     : CAknExGridDocument from CEikDocument
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXPOPLISTDOCUMENT_H
#define AKNEXPOPLISTDOCUMENT_H

// INCLUDES
#include <eikdoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CAknExPopListDocument application class.
*/
class CAknExPopListDocument : public CEikDocument
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        */
        static CAknExPopListDocument* NewL(CEikApplication& aApp);

        /**
        * Destructor.
        */
        virtual ~CAknExPopListDocument();

    private:

        /**
        * C++ default constructor.
        */
        CAknExPopListDocument(CEikApplication& aApp);

        /**
        * Epoc default constructor.
        */
        void ConstructL();

    private:

        /**
        * From CEikDocument, create CAknExPopListAppUi "App UI" object.
        */
        CEikAppUi* CreateAppUiL();
    };

#endif  // AKNEXPOPLISTDOCUMENT_H

// End of File

