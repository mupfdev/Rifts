/*
* ============================================================================
*  Name     : CAknExEditorDialog from CEikDialog
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXEDITORDIALOG_H
#define AKNEXEDITORDIALOG_H

// INCLUDES
#include <aknview.h>
#include <eikdialg.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
*  Dialog class
*  Test various controls.
*/
class CAknExEditorDialog:public CEikDialog
    {
    public: // Constructors and destructor
        /**
        * Constructor
        */      
        CAknExEditorDialog();
        
        /**
        * From CAknDialog set parameters before showing dialog.
        */
        void PreLayoutDynInitL();

        /**
        * From CAknDialog update member variables of CAknExEditorDialog.
        * @param aButtonId The ID of the button that was activated.
        * @return Should return ETrue if the dialog should exit,
        *    and EFalse if it should not
        */
        TBool OkToExitL(TInt aButtonId);
    private:
    };

#endif //AKNEXEDITORDIALOG_H

// End of File
