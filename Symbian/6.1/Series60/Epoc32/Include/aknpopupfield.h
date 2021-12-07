/*
* ============================================================================
*  Name     : AknPopupField.h
*  Part of  : Avkon
*
*  Description:
*     Represents a combo box type control, used to implement the Series 60 pop-up field.
*     
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNPOPUPFIELD_H
#define AKNPOPUPFIELD_H

#include <eikcmobs.h>
#include <eiklbx.h>
#include <eikbctrl.h>
#include <eikcmbut.h>
#include <bamdesca.h>

#include <AknDesCArrayDecorator.h>
#include <AknListBoxLayoutDecorator.h>
#include <aknnotedialog.h>

class TResourceReader;
class CEikLabel;
class CEikCommandButton;
class CAknFormGraphicStyleListBox;
class MAknQueryValue;

class CAknPopupField;

/** 
 * this interface should be implemented by classes that need to know
 * about events occurring in the popup field control
 */
class MAknPopupFieldObserver
	{
public:
	enum TAknPopupFieldEvent
		{
		EAknPopupFieldEventModeChange,
		EAknPopupFieldEventValueChange
		};
public:
	/**
	 * Handle events from the popup field control, such as when it changes between
	 * selection list mode and label mode.
	 *
	 * @param aPopupField pointer to the popup field control that generated the event
	 * @param aEventType the type of event
	 * @param aHint for possible future use
	 *
	 */
	virtual void HandlePopupFieldEventL(CAknPopupField* aPopupField, TAknPopupFieldEvent aEventType, TInt aHint)=0;
	};


class CAknPopupField :
	public CEikBorderedControl, 
	public MCoeControlObserver, 
	public MEikCommandObserver, 
	public MEikListBoxObserver
	{
protected:
	/**
	 * Specialises bitmap button to make the layout correct for popup field
	 */
	class CAknPopupFieldBitmapButton : public CEikBitmapButton
		{
	public:
		/**
		 * Constructor
		 */
		CAknPopupFieldBitmapButton();
		};
protected:
	enum EAknPopupFieldSelectionMode
		{
		EAknPopupFieldLabelMode,
		EAknPopupFieldSelectionListMode
		};

	enum EAknFormMode
		{
		EAknFormModeView,
		EAknFormModeEdit,
		EAknFormModeViewWideWithGraphic,
		EAknFormModeViewWideWithoutGraphic,
		EAknFormModeEditWideWithGraphic,
		EAknFormModeEditWideWithoutGraphic
		};
public: 
	/**
	 * Constructor
	 */
	IMPORT_C CAknPopupField();

	/**
	 * Destructor
	 */
	IMPORT_C ~CAknPopupField();

	/** 
	 * 2nd phase construction
	 *
	 */
	IMPORT_C void ConstructL();

	/**
	 * Sets flag that enables user defined entry. Note that flag can also be set from resources, 
	 * but this method allows behaviour to be changed at runtime.
	 *
	 * @param aAllows	if ETrue, set flag; if EFalse, clear flag.
	 */
	IMPORT_C void SetAllowsUserDefinedEntry(TBool aAllows);

	/**
	 * Causes the list of pre-defined values to appear. 
	 * Use this method to activate the pop-up field from a menu option command. 
	 * Note that the desired control must have the focus before it can be activated.
	 *
	 */
	IMPORT_C void ActivateSelectionListL();

	/**
	 * Used by the client to set the query value used to represent the user defined 
	 * value belonging to this popup field control.
	 *
	 * @param aValue	pointer to value, ownership is not passed
	 *
	 */
	IMPORT_C void SetQueryValueL(MAknQueryValue* aValue);

	/**
	 * Set the font of the contained label.
	 *
	 * @param aFont		Font definition used to set the font of the contained label
	 *
	 */
	IMPORT_C void SetFont(const CFont* aFont);

	/**
	 * Set the flag which determines whether the indicators are shown
	 * In practice the indicators have the appearance of radio buttons
	 *
	 * @param aShowIndicators	
	 *		If ETrue, indicators are displayed; 
	 *		if EFalse, indicators are not displayed
	 *
	 */
	IMPORT_C void SetShowIndicatorsL(TBool aShowIndicators);

	/**
	 * number of lines used
	 *
	 * @returns number of lines being currently displayed by control, which is determined 
	 *		by the number of entries on the selection list, and whether the selection list is active.
	 *		NOTE that the number is limited by KAknMaxEditorLines
	 *
	 */
	IMPORT_C TInt NumLines() const;

	/**
	 * set an observer of this class to receive events from popup field
	 * 
	 * @param aObserver pointer to the class that implements the observer interface,
	 *
	 */
	IMPORT_C void SetPopupFieldObserver(MAknPopupFieldObserver* aObserver);

	/**
	 * sets the note to be displayed when the selection list has no items available
	 *
	 */
	IMPORT_C void SetEmptyListNoteL(TInt aResourceId,
									CAknNoteDialog::TTimeout aTimeout = CAknNoteDialog::EShortTimeout,
									CAknNoteDialog::TTone aTone = CAknNoteDialog::ENoTone);

	/**
	 * Sets the text to be displayed when the selection list has no items available
	 *
	 */
	IMPORT_C void SetEmptyTextL(const TDesC& aEmptyText);

	/**
	 * Sets the text to be added to the bottom of the array to enter user defined data
	 *
	 */
	IMPORT_C void SetOtherTextL(const TDesC& aOtherText);

	/**
	 * Sets the text for view state when none of the elements in the
	 * list are available.
	 * This can be enabled by SetCurrentValueIndex(-1);
	 *
	 * This is usually for "Invalid" -text when user has deleted
	 * popupfield element and the selected element is not valid.
	 */
	IMPORT_C void SetInvalidTextL(const TDesC &aInvalidText);

public: // from CCoeControl
	/** 
	 * Handle key press events
	 *
	 */
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

	/** 
	 * Construct from resources.
	 *
	 */
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

	/** 
	 * Report the minimum size of the control.
	 *
	 */
	IMPORT_C TSize MinimumSize();

	/**
	 * Handles a change to the control's resources of type aType
	 * which are shared across the environment, e.g. colors or fonts.
	 *
	 */
	IMPORT_C void HandleResourceChange(TInt aType);
public:
	/**
	 * Sets the maximium number of lines that can be displayed
	 *
	 * @param	aMaxNoLines	Number of lines 
	 */
	IMPORT_C void SetMaxNumberOfLinesPermitted(TInt aMaxNoLines);
protected: // from MCoeControlObserver
	/** 
	 * Handle control events
	 *
	 */
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
protected: // from MEikCommandObserver
	/**
	 * Processes events from the softkeys. Responds to EAknSoftkeyOk and EAknSoftkeyCancel
	 * to accept or cancel the pop-up.
	 *
	 * @param	aCommandId	Event Id from the soft-key
	 */
	IMPORT_C void ProcessCommandL(TInt aCommandId);	
protected: // From MEikListBoxObserver
	/**
	 * Processes key events from the listbox. Responds to EEventEnterKeyPressed to accept
	 * the pop-up.
	 *
	 * @param	aListBox	Listbox being observed
	 * @param	aEventType	Event observed
	 */
	IMPORT_C void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);
protected: // from CCoeControl
	/** 
	 * Report number of component controls
	 *
	 */
	IMPORT_C TInt CountComponentControls() const;

	/** 
	 * Return a contained control
	 * 
	 * @param aIndex	0=button; 1=label
	 */
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

	/** 
	 * Respond to a change in control size.
	 *
	 */
	IMPORT_C void SizeChanged();
private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
protected: // personal
	/**
	 * Construction tasks common to both normal construction and construction from 
	 * resource.
	 *
	 */
	void CommonConstructL();
protected: // from MObjectProvider
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private: // personal
	/** 
	 * Create the label that will show the currently selected value.
	 *
	 */
	void ConstructLabelL();

	/** 
	 * Create the command button that will be used to show the other choices indicator.
	 *
	 */
	void ConstructCommandButtonL();

	/** 
	 * Create the command button that will be used to show the other choices indicator.
	 *
	 */
	void ConstructSelectionListL();

	/** 
	 * Set up the bitmap array for the "not pushed" and "pushed in" states
	 *
	 */
	void InitialiseRadioButtonBitmapsL();

	/**
	 * Handles the case where the selection list is closed. If necessary, 
	 * update the value of the text label that is displayed.
	 * 
	 * @return TBool ETrue always
	 */
	TBool HandleInteractionConfirmedL();

	/**
	 * Create the popup list. Warn the user if there are no entries in the list.
	 *
	 */
	void CreatePopoutL();

	/**
	 * Destroy the popup list and remove it from the stack
	 *
	 */
	void DestroyPopout();

	/**
	 * Checks to see if the popupfield is empty
	 *
	 */
	TBool IsEmpty() const;
	/**
	 * Checks to see if the popupfield is invalid
	 *
	 */
	TBool IsInvalid() const;
private: // Avkon
	/**
	 * Creates the CBA for use when the selection list is active
	 */
	void CreateCbaL();

	/**
	 * Configures the decoration according to the currently set flags.
	 * Should be called whenever the flags are changed. 
	 *
	 */
	void ConfigureDecorator();

	/**
	 * Configures the layout decoration according to the radio button flag
	 * Should be called whenever the flags are changed. 
	 *
	 */
	void ConstructLayoutDecoratorL();

	/**
	 * display a note when the selection list has no items available
	 *
	 */
	void ShowEmptyListNoteL();

	/**
	 * Re-defined method of the base class. Gets called when the 
	 * user tries to select a value. If required, an editor is created to 
	 * allow the user to input the user defined value. Otherwise, the
	 * normal selection behaviour of popup list is activated.
	 *
	 * @param aAccept	If ETrue, popup list was accepted; 
	 *								if EFalse, popup list was cancelled
	 *
	 */
	void AttemptExitL(TBool aAccept);

	/**
	 * Changes the mode of the popupfield to one of
	 * the EAknPopupFieldSelectionMode's
	 */
	void ChangeMode(EAknPopupFieldSelectionMode aNewMode);
private: // async 
	static TInt AttemptExitCallbackL(TAny* aThis);
	void DoAttemptExitL();
	void DoSizeChangedL();
protected:
	// the following members are owned
	CEikLabel* iLabel;
	CAknPopupFieldBitmapButton* iButton;
	CAknFormGraphicStyleListBox* iSelectionList;
	CAknListBoxLayoutDecorator* iLayoutDecorator;
	CEikButtonGroupContainer* iCba;
	CAsyncCallBack* iAttemptExitAsync;

	// the following fields are reflected in the POPUP_FIELD resource structure
	TInt iFlags;
	TInt iWidth;
	HBufC* iOtherText;
	HBufC* iEmptyText;
	HBufC* iInvalidText;
	TInt iEmptyNoteResourceId;
	
	// the following members are not owned
	MAknQueryValue* iValue;
	MAknPopupFieldObserver* iObserver;

	// the following values are member variables
	EAknFormMode iFormMode;
	CAknNoteDialog::TTimeout iEmptyNoteTimeout;
	CAknNoteDialog::TTone iEmptyNoteTone;
	TAknDesCArrayDecorator iDecorator;
	EAknPopupFieldSelectionMode iSelectionMode; 
	TInt iMaxNoLines;
	};

#endif
