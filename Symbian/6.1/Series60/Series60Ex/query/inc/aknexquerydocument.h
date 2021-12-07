/*
* =============================================================================
*  Name     : CAknExQueryDocument
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYDOCUMENT_H
#define AKNEXQUERYDOCUMENT_H

// INCLUDES
#include <eikdoc.h>

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CAknExQueryDocument application class.
*/
class CAknExQueryDocument : public CEikDocument
    {
    public: // Constructors and destructor

        /**
        * EPOC two-phased constructor.
        * @return Pointer to created Document class object.
        * @param aApp Reference to Application class object.
        */
        static CAknExQueryDocument* NewL( CEikApplication& aApp );

        /**
        * Destructor.
        */
        virtual ~CAknExQueryDocument();

    private: // Constructors

        /**
        * Overload constructor.
        * @param aApp Reference to Application class object.
        */
        CAknExQueryDocument( CEikApplication& aApp );

    private: // From CEikDocument

        /**
        * From CEikDocument, CreateAppUiL.
        * Creates CAknExQueryAppUi "App UI" object.
        * @return Pointer to created AppUi class object.
        */
        CEikAppUi* CreateAppUiL();

    };

#endif

// End of File
