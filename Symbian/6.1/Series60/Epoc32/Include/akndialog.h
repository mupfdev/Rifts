/*
*	Name : AknDialog.h
*	Part of : Avkon
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNDIALOG_H__
#define __AKNDIALOG_H__


#include <eikdialg.h>
#include <eikmobs.h>


class CAknDialog : public CEikDialog, public MEikMenuObserver
	{
	public :
		// Construction.  Owns a menu so needs ConstructL()  
		IMPORT_C CAknDialog() ;
		IMPORT_C void ConstructL( TInt aMenuTitleResourceId ) ;
		IMPORT_C ~CAknDialog() ;

		// From CEikDialog
		IMPORT_C TInt ExecuteLD( TInt aResourceId ) ;
		IMPORT_C  void PrepareLC(TInt aResourceId);
		IMPORT_C TInt RunLD();

		// From MEikMenuObserver
		IMPORT_C virtual void SetEmphasis( CCoeControl* aMenuControl,TBool aEmphasis ) ;
		IMPORT_C virtual void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane ) ;
		// From MEikCommandObserver
		IMPORT_C virtual void ProcessCommandL( TInt aCommandId ) ;

		// From CCoeControl
		IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType) ;
		IMPORT_C void FocusChanged(TDrawNow aDrawNow); 

	private: // formerly from MTopSetMember<CEikMenuBar>, now reserved
		IMPORT_C virtual void Reserved_MtsmPosition();
		IMPORT_C virtual void Reserved_MtsmObject();

	protected:
		// From CEikDialog
		IMPORT_C virtual TBool OkToExitL( TInt aButtonId ) ;

		IMPORT_C void DisplayMenuL() ;
		IMPORT_C void HideMenu() ;
		IMPORT_C TBool MenuShowing() const ;
		void CreateMenuBarL(TInt aMenuTitleResourceId);

	protected: // from MObjectProvider
		IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: // new function 
		IMPORT_C virtual void CAknDialog_Reserved();
	protected:
		// Owned
		CEikMenuBar* iMenuBar ;
private:
	enum TAknDialogFlag
	    {
	    EAknDialogFlagDialogDeleted = 1,
        EAknDialogFlagDefaultSounds = 2
	    };
	TInt iAknDialogFlags;  // Was TInt iSpare;
protected:
	} ;

#endif 
