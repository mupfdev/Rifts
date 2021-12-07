/*
* ============================================================================
*  Name     : CAknExPbarDocument from CEikDocument
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXPBARDOCUMENT_H
#define AKNEXPBARDOCUMENT_H

// INCLUDES
#include <eikdoc.h>


// FORWARD DECLARATIONS
class  CEikAppUi;
class  CAknExPbarAppUi;


// CLASS DECLARATION

/**
*  CAknExPbarDocument document class.
*/
class CAknExPbarDocument : public CEikDocument
    {
    public: // Constructors and destructor
       
        /**
        * Two-phased constructor.
        */
        static CAknExPbarDocument* NewL( CEikApplication& aApp );

        /**
        * Destructor.
        */
        virtual ~CAknExPbarDocument();


    private:  // EPOC default constructor
       
        /**
        * EPOC default constructor.
        */
        CAknExPbarDocument( CEikApplication& aApp );

        /**
        * EPOC default constructor.
        */
        void ConstructL();

    private:  // From CEikDocument
        
        /**
        * From CEikDocument,
        * create CAknExPbarAppUi "App UI" object.
        * @return A pointer to the created "App UI" object.
        */
        CEikAppUi* CreateAppUiL();

    };

#endif // AKNEXPBARDOCUMENT_H

// End of File

