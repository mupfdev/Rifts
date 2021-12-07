/*
* =============================================================================
*  Name     : CAknExListDocument
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTDOCUMENT_H
#define AKNEXLISTDOCUMENT_H

// INCLUDES
#include <eikdoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
* CAknExListDocument application class.
*/
class CAknExListDocument : public CEikDocument
    {
    public: // Constructors and destructor

        /**
        * EPOC two-phased constructor.
        * @return Pointer to created Document class object.
        * @param aApp Reference to Application class object.
        */
        static CAknExListDocument* NewL( CEikApplication& aApp );

        /**
        * Destructor.
        */
        virtual ~CAknExListDocument();

        /**
        * Overload constructor.
        * @param aApp Reference to Application class object.
        */
        CAknExListDocument( CEikApplication& aApp );

        /**
        * EPOC constructor.
        */
        void ConstructL();

    private: // From CEikDocument

        /**
        * From CEikDocument, CreateAppUiL.
        * Creates CAknExListAppUi "App UI" object.
        * @return Pointer to created AppUi class object.
        */
        CEikAppUi* CreateAppUiL();

    };

#endif

// End of File
