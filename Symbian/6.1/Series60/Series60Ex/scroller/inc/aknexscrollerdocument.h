/*
* ============================================================================
*  Name     : CAknExScrollerDocument from CEikDocument
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


#ifndef AKNEXSCROLLERDOCUMENT_H
#define AKNEXSCROLLERDOCUMENT_H


// INCLUDES
#include <eikdoc.h>


// FORWARD DECLARATIONS
class  CEikAppUi;


// CLASS DECLARATION
/**
*  CAknExScrollerDocument
*  Document class.
*
*/
class CAknExScrollerDocument : public CEikDocument
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        * @param aApp Reference to Application class object.
        * @return Pointer to created Document class object.
        */
        static CAknExScrollerDocument* NewL( CEikApplication& aApp );

        /**
        * Destructor.
        */
        virtual ~CAknExScrollerDocument();

    private: // Default constructor is private
             // To prevent to be accessed by outside
        /**
        * C++ default constructor.
        * @param aApp Reference to Application class object.
        */
        CAknExScrollerDocument( CEikApplication& aApp );

        /**
        * EPOC default constructor.
        */
        void ConstructL();

    private:
        /**
        * From CEikDocument, create CAknExScrollerAppUi "App UI" object.
        * @return Pointer to created AppUi class object.
        */
        CEikAppUi* CreateAppUiL();
    };

#endif

// End of File

