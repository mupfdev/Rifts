/*
* ============================================================================
*  Name     : CAknExSpaneDocument from CEikDocument
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSPANEDOCUMENT_H
#define AKNEXSPANEDOCUMENT_H

// INCLUDES
#include <eikdoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CAknExSpaneDocument application class.
*/
class CAknExSpaneDocument : public CEikDocument
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        */
        static CAknExSpaneDocument* NewL(CEikApplication& aApp);

        /**
        * Destructor.
        */
        virtual ~CAknExSpaneDocument();

    public: // New functions

    public: // Functions from base classes

    protected:  // New functions

    protected:  // Functions from base classes

    private:
        
        /**
        * C++ default constructor.
        */
        CAknExSpaneDocument(CEikApplication& aApp);

        /**
        * EPOC default constructor.
        */
        void ConstructL();

    private:

        /**
        * From CEikDocument, create CAknExSpaneAppUi "App UI" object.
        */
        CEikAppUi* CreateAppUiL();
    };

#endif // AKNEXSPANEDOCUMENT_H

// End of File

