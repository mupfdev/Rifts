/*
* ============================================================================
*  Name     : CAknExGridDialogChangeSize from CAknDialog
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDDIALOGCHANGESIZE_H
#define AKNEXGRIDDIALOGCHANGESIZE_H

// INCLUDES
#include <AknForm.h>        // for CAknDialog

// CONSTANTS

// Enumeration

// FORWARD DECLARATIONS
class CAknExGridContainerAsSelection;

// CLASS DECLARATION


class CAknExGridDialogChangeSize : public CAknDialog
    {

    public: // Constructors and destructor
       /**
        * Constructor
        * @param aContainer the pointer to CAknExGridContainerAsSelection.
        */
        CAknExGridDialogChangeSize( CAknExGridContainerAsSelection* aContainer );

    public: // New functions

    public: // Functions from base classes

        /**
        * From CAknDialog set parameters before showing dialog.
        */
        void PreLayoutDynInitL( void );

        /**
        * From CAknDialog update member variables of CAknExGridContainerAsSelection.
        * @param aKeycode The ID of the button that was activated.
        * @return Should return ETrue if the dialog should exit, and EFalse if it should not
        */
        TBool OkToExitL( TInt aKeycode );

    private: // Functions from base classes


    private: //data

        CAknExGridContainerAsSelection* iContainer;
    };


#endif      // AKNEXGRIDDIALOGCHANGESIZE_H

// End of File
