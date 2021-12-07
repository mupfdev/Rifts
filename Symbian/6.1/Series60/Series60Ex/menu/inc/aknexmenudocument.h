/*
* ============================================================================
*  Name     : CAknExMenuDocument from CEikDocument
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXMNEUDOCUMENT_H
#define AKNEXMNEUDOCUMENT_H

// INCLUDES
#include <eikdoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CAknExMenuDocument application class.
*/
class CAknExMenuDocument : public CEikDocument
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        * @param aApp Reference to Application class object
        */
        static CAknExMenuDocument* NewL(CEikApplication& aApp);

        /**
        * Destructor.
        */
        virtual ~CAknExMenuDocument();

    public: // New functions

    public: // Functions from base classes

    protected:  // New functions

    protected:  // Functions from base classes

    private:

        /**
        * C++ default constructor.
        * @param aApp Reference to Application class object
        */
        CAknExMenuDocument(CEikApplication& aApp);

        /**
        * EPOC default constructor.
        */
        void ConstructL();

    private:

        /**
        * From CEikDocument, create CAknExMenuAppUi "App UI" object.
        * @return Pointer to created AppUi class object.
        */
        CEikAppUi* CreateAppUiL();
    };

#endif    // AKNEXMNEUDOCUMENT_H

// End of File

