/*
* ============================================================================
*  Name     : AknForm.h
*  Part of  : Avkon
*
*  Description:
*
* Support for Form component.  
* Also has CAknDialog which specialized CEikDialog (adds menu capability)
* Note that most support for Avkon Forms is contained within CEikDialog
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/


#ifndef __AKNFORM_H__
#define __AKNFORM_H__


#include <aknDialog.h>

class CEikMenuBar ;

class CAknForm : public CAknDialog
	{
	public :
		IMPORT_C CAknForm() ;
		IMPORT_C void ConstructL( TInt aMenuBarId=0 ) ;
		IMPORT_C ~CAknForm() ;

		// From MEikMenuObserver
		IMPORT_C virtual void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane ) ;

		// From MEikCommandObserver
		IMPORT_C virtual void ProcessCommandL( TInt aCommandId ) ;


	protected:
		// From CEikDialog
		IMPORT_C virtual TBool OkToExitL( TInt aButtonId ) ;
		// From CEikDialog (thence  MEikDialogPageObserver )
		IMPORT_C virtual void PrepareForFocusTransitionL();

// New virtual functions.  Defaults provided.

	/**
	 * SaveFormDataL
	 * This routine should be re-implemented by the client to save the contents of the form.
	 * The re-implementation can call this function to display the 'Saved' dialog.
	 * (CAknForm::SaveFormDataL())
	 *
	 * @return ETrue iff the editable state can be left.
	 *
	 * The return value should reflect whether or not the form is to leave the editable state.
	 *
	 * A real system problem saving should generate an EPOC Leave.
	 * 
	 */
		IMPORT_C virtual TBool SaveFormDataL() ; 
	/**
	 * This routine should be implemented by the client for dealing with the occasion 
	 * of a change from edit->view mode but the user does not wish to save the changes.
	 * 
	 * A typical implementation would set the controls back to their old values 
	 * 
	 */
		IMPORT_C virtual void DoNotSaveFormDataL() ; 

	/**
	 * This routine may be overridden.  Default displays 'Save Changes Dialog Yes/No'
	 *
	 * Data validation may occur here as an alternative to overriding OkToExit
	 *
	 * @return ETrue if Changes are to be Saved. Save of data is not performed here bu in 
	 * SaveFormDataL()
	 * 
	 */
		IMPORT_C virtual TBool QuerySaveChangesL() ;
		IMPORT_C virtual void EditCurrentLabelL() ;
		IMPORT_C virtual void DeleteCurrentItemL() ;
		IMPORT_C virtual void AddItemL() ;
		IMPORT_C void SetChangesPending(TBool aChangesPending);
		IMPORT_C void PostLayoutDynInitL();
		IMPORT_C void HandleControlStateChangeL(TInt aControlId);
		IMPORT_C void SetInitialCurrentLine();

		IMPORT_C TBool UnsavedEdit() const  ; // Required by OkToExit
		IMPORT_C TBool Deleting() const ;	// Required by PrepareForFocusTransitionL

		enum TFlags
			{
			EDeleting = 0x1,
			EUnsavedEdit = 0x2
			} ;

	/**
	 * Set the form flag indicated
	 * 
	 * @param aFlagPattern	pattern of bits to set or clear
	 * @param aSetTheFlag	if ETrue, sets the pattern; if EFalse, clear the pattern
	 */
		IMPORT_C void SetFormFlag( TFlags aFlagPattern, TBool aSetTheFlag );

	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknDialog_Reserved();
	private:// new function  
		IMPORT_C virtual void CAknForm_Reserved();
	private :
		TInt iMenuBarId ;  // resource ID

		TInt iFlags ;
		TInt iSpare;
	} ;


#endif
