/* ============================================================================
*  Name     : AknListQueryControl.h
*  Part of  : Avkon
*  Implementation notes:
*   Declaration of Avkon list query control.
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*/


#ifndef     __AKN_LIST_QUERY_CONTROL_H
#define     __AKN_LIST_QUERY_CONTROL_H

#include <coecntrl.h>
#include <aknpopupheadingpane.h>

class CEikFormattedCellListBox;
struct TAknPopupWindowLayoutDef;

/**
 * List query control class.
 */
class CAknListQueryControl : public CCoeControl
    {
    public:
        /**
        * Constructor
        */
        IMPORT_C CAknListQueryControl();
    
        /**
        * Constructs control from resources
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aRes);

        /**
        * Destructor
        */
        IMPORT_C virtual ~CAknListQueryControl();

        /**
        * From CCoeControl
        *
        * @return   Minimum size of the control
        */
        IMPORT_C TSize MinimumSize();

        /**
        * From CCoeControl
        *   Returns number of controls inside the query control
        * @return   Number of component controls
        */
        IMPORT_C TInt CountComponentControls() const;

        /**
        * From CCoeControl
        *   Returns a control determined by control id
        * @param    anIndex     Index of a control to be returned
        * @return   CCoeControl Pointer to control
        */
        IMPORT_C CCoeControl* ComponentControl(TInt anIndex) const;

        /**
        * From CCoeControl
        *   Handles key events - Gets called by CONE
        * @param    aKeyEvent   The key event
        * @param    aType       The type of the event
        * @return   Indicates whether or not the key event was
        *               used by this control
        */
        IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * From CCoeControl
        *   Draws the control
        * @param    aRect   The region of the control to be redrawn
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        /**
        * Sets layout for list query control
        * @param aLayout    Layout to be set
        */
        IMPORT_C void SetLayout(TAknPopupWindowLayoutDef* aLayout);

        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

        /**
        * Returns pointer to listbox
        * @return   Pointer to CEikFormattedCellListBox
		*/
        inline CEikFormattedCellListBox* Listbox() const;

        /**
        * Returns pointer to heading
        * @return   Pointer to CAknPopupHeadingPane
		*/
        inline CAknPopupHeadingPane* Heading() const;

        /**
        * Return type of the list
        * @return Type of the list
        */
        inline TInt Listtype() const;

    private:
        CEikFormattedCellListBox* iListBox;
        CAknPopupHeadingPane*     iHeading;
        TInt                      iListType;
        TAknPopupWindowLayoutDef* iLayout;

	public:
		/**
		 * Deprecated - do not use
		 */
        inline CEikFormattedCellListBox* listbox() const;
        inline CAknPopupHeadingPane* heading() const;
        inline TInt listtype() const;
    };

inline CEikFormattedCellListBox *CAknListQueryControl::Listbox() const 
	{ 
	return iListBox; 
	}

inline CAknPopupHeadingPane *CAknListQueryControl::Heading() const 
    {
    if ( iHeading && iHeading->Prompt() )
        return iHeading;
    return 0;
    }

inline TInt CAknListQueryControl::Listtype() const 
	{ 
	return iListType; 
	}

/**
 * Deprecated methods
 */
inline CEikFormattedCellListBox* CAknListQueryControl::listbox() const 
	{ 
	return Listbox();
	}

inline CAknPopupHeadingPane* CAknListQueryControl::heading() const 
	{ 
	return Heading(); 
	}

inline TInt CAknListQueryControl::listtype() const 
	{ 
	return Listtype(); 
	}

#endif
