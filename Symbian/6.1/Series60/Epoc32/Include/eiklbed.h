// EIKLBED.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
   
#if !defined(__EIKLBED_H__)
#define __EIKLBED_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKLBM_H__)
#include <eiklbm.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__COEDEF_H__)
#include <coedef.h>
#endif

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

class CCoeControl;
class CEikEdwin;
class CParaFormatLayer;
class CCharFormatLayer;

/**
 * The MEikListBoxEditor class specifies an interface to a text editor which can be used inside
 * a list box.
 *
 * @since ER5U
 */
class MEikListBoxEditor
	{
public:
	/**
	 * Returns a pointer to the current editable item text.
	 */
	virtual TPtrC ItemText() = 0;

	/**
	 * Creates the editor inside the list box aContainer. The editor occupies the rectangle aRect
	 * and is used to editor the contents of the item at index aItemIndex up to a maximum length of
	 * aMaxLength characters..
	 */
	virtual void StartEditingL(const CCoeControl& aContainer,const TRect& aRect,TInt aItemIndex,TInt aMaxLength) = 0;

	/**
	 * Stops editing and deletes the item editor. 
	 */
	virtual void StopEditingL() = 0;

	/**
	 * Updates the list box model with the new item contents.
	 */
	virtual TBool UpdateModelL() = 0;

	/**
	 * Deletes the editor.
	 */
	virtual void Release() = 0;
private:
	IMPORT_C virtual void MEikListBoxEditor_Reserved_1();
	};

class MListBoxEditorObserver
	{
public:
	virtual TKeyResponse HandleListBoxEditorEventL(MEikListBoxEditor* aListBoxEditor, const TKeyEvent& aKeyEvent)=0;
	};

/**
 * The CEikListBoxTextEditor implements a text list box item editor.
 *
 * @since ER5U
 */
class CEikListBoxTextEditor : public CCoeControl, public MEikListBoxEditor
	{
public:
	IMPORT_C CEikListBoxTextEditor(MListBoxModel* aModel);
	IMPORT_C ~CEikListBoxTextEditor();
	IMPORT_C void SetFont(const CFont* aFont);
	IMPORT_C CEikEdwin* Editor();
	IMPORT_C void SetListBoxEditorObserver(MListBoxEditorObserver* aObserver);
public: // from MEikListBoxEditor
	IMPORT_C TPtrC ItemText();
	IMPORT_C void StartEditingL(const CCoeControl& aContainer, const TRect& aRect, TInt aItemIndex, TInt aMaxLength );
	IMPORT_C void StopEditingL();
	IMPORT_C TBool UpdateModelL();
	IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
protected: // from MEikListBoxEditor
	IMPORT_C void Release();
protected:
	IMPORT_C MListBoxModel* ListBoxModel();
	IMPORT_C TInt ItemIndex() const;
private: // from MEikListBoxEditor
	IMPORT_C void MEikListBoxEditor_Reserved_1();
protected:
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	void UseFontL( CEikEdwin& editor, const CFont& aFont );
	TPtrC EditableItemText(TRect* aRect=NULL);
private:
	MListBoxEditorObserver* iEditorObserver;
	MListBoxModel*  iModel;
	CEikEdwin*		iEditor;
	TInt            iItemIndex;
	CFont*          iFont;
	TInt			iItemPos;
	TInt			iItemLen;
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
	};

#endif
