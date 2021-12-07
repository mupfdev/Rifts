/*
* =============================================================================
*  Name     : CAknExPopFieldDocument
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXPOPFIELDDOCUMENT_H
#define AKNEXPOPFIELDDOCUMENT_H

// INCLUDES
#include <eikdoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
* CAknExPopFieldDocument application class.
*/
class CAknExPopFieldDocument : public CEikDocument
    {
    public: // Constructors and destructor

        /**
        * EPOC two-phased constructor.
        * @return Pointer to created Document class object.
        * @param aApp Reference to Application class object.
        */
        static CAknExPopFieldDocument* NewL( CEikApplication& aApp );

        /**
        * Destructor.
        */
        virtual ~CAknExPopFieldDocument();

    private: // Constructors

        /**
        * Overload constructor.
        * @param aApp Reference to Application class object.
        */
        CAknExPopFieldDocument( CEikApplication& aApp );

    private: // From CEikDocument

        /**
        * From CEikDocument, CreateAppUiL.
        * Creates CAknExPopFieldAppUi "App UI" object.
        * @return Pointer to created AppUi class object.
        */
        CEikAppUi* CreateAppUiL();

    };

#endif

// End of File
