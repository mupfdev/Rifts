/*
* ============================================================================
*  Name     : CAknExEditorView6 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXEDITORVIEW6_H
#define AKNEXEDITORVIEW6_H

// INCLUDES
#include <aknview.h>

// CONSTANTS
// UID of view
const TUid KViewId6 = {6};

// FORWARD DECLARATIONS
class CAknExEditorContainer6;

// CLASS DECLARATION

/**
*  CAknExEditorView6 view class.
* 
*/
class CAknExEditorView6 : public CAknView
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor
        */
        CAknExEditorView6();

        /**
        * EPOC default constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExEditorView6();

    public: // Functions from base classes
        
        /**
        * From CAknView, Returns the ID of view.
        * @return Returns the ID of view.
        */
        TUid Id() const;

        /**
        * From CAknView, Handles the commands.
        * @pram aCommand Command to be handled.
        */
        void HandleCommandL(TInt aCommand);

        /**
        * From CAknView, Handles the clientrect.
        */
        void HandleClientRectChange();

    private:

        /**
        * From CAknView, Creates the Container class object.
        * @param aPrevViewId This is not used now.
        * @param aCustomMessage This is not used now.
        * @param aCustomMessage This is not used now.
        */
        void DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                         TUid /*aCustomMessageId*/,
                         const TDesC8& /*aCustomMessage*/);

        /**
        * From AknView, Deletes the Container class object.
        */
        void DoDeactivate();

    private: // Data
        CAknExEditorContainer6* iContainer;
    };

#endif  // AKNEXEDITORVIEW6_H

// End of File
