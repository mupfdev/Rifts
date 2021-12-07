/*
* ============================================================================
*  Name     : CAknExGridDialogFillingOrder from CAknDialog
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDDIALOGFILLINGORDER_H
#define AKNEXGRIDDIALOGFILLINGORDER_H

// INCLUDES
#include <AknForm.h>        // for CAknDialog
//#include <AknQueryValueText.h>

// CONSTANTS
// FORWARD DECLARATIONS
class CAknExGridContainerAsSelection;

// CLASS DECLARATION


// class CAknExGridDialogFillingOrder : public CAknDialog
//     {
// 
//     public: // Constructors and destructor
//        /**
//         * Constructor
//         * @param aContainer the pointer to CAknExGridContainerAsSelection.
//         */
//         CAknExGridDialogFillingOrder( CAknExGridContainerAsSelection* aContainer );
// 
//     public: // New functions
// 
//     public: // Functions from base classes
// 
//        /**
//         * From CAknDialog set parameters before showing dialog.
//         */
//         void PreLayoutDynInitL( void );
// 
//         /**
//         * From CAknDialog update member variables of CAknExGridContainerAsSelection.
//         * @param aKeycode The ID of the button that was activated.
//         * @return Should return ETrue if the dialog should exit, and EFalse if it should not
//         */
//         TBool OkToExitL( TInt aKeycode );
// 
//     private: // Functions from base classes
// 
// 
//     private: //data
// 
//         CAknExGridContainerAsSelection* iContainer;
//     };

class CAknExPopFieldFillingOrder : public CAknDialog
    {
public:
    CAknExPopFieldFillingOrder(CAknExGridContainerAsSelection* aContainer);

public: // Functions from base classes
    void PreLayoutDynInitL( void );
    TBool OkToExitL(TInt aButtonId);

private: // Functions from base classes

private: //data

    CAknExGridContainerAsSelection* iContainer;
    };



#endif      // AKNEXGRIDDIALOGFILLINGORDER_H

// End of File
