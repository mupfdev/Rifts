/*
* ============================================================================
*  Name     : CAknExSpaneNaviTabDialog from CAknDialog
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSPANENAVITABDIALOG_H
#define AKNEXSPANENAVITABDIALOG_H

// INCLUDES
#include <aknform.h>

// CONSTANTS

// FORWARD DECLARATIONS
class CAknExSpaneNaviViewContainer;

// CLASS DECLARATION
/**
*  CAknExSpaneNaviTabDialog  
*  dialog control class.
*  
*/
class CAknExSpaneNaviTabDialog : public CAknForm
    {
    public: // Constructors and destructor
       /**
        * Constructor
        * @param aContainer the pointer to CAknExSpaneNaviTabDialog.
        */
        CAknExSpaneNaviTabDialog(CAknExSpaneNaviViewContainer* aContainer, TInt aCommand);

    public: // New functions
    public: // Functions from base classes
        /**
        * From CAknDialog update member variables of CAknExGridContainerAsSelection.
        * @param aKeycode The ID of the button that was activated.
        * @return Should return ETrue if the dialog should exit, and EFalse if it should not
        */
        void  PreLayoutDynInitL();
        TBool OkToExitL(TInt aKeycode);

    private: // Functions from base classes

    private: //data
        CAknExSpaneNaviViewContainer* iContainer;
        TInt iCommand;
    };

#endif // AKNEXSPANENAVITABDIALOG_H

// End of File