// EIKSECED.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSECED_H__)
#define __EIKSECED_H__

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#include <fepbase.h>

class TResourceReader;

class CEikSecretEditor : public CEikBorderedControl, public MCoeFepAwareTextEditor, public MCoeFepAwareTextEditor_Extension1
	{
public:
	enum { EMaxSecEdBufLength=32, EMaxSecEdSecArrayLength = 255 };
public:
	IMPORT_C CEikSecretEditor();
	IMPORT_C ~CEikSecretEditor();
public:	// from CCoeControl
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C virtual TSize MinimumSize();
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);	// not available before Release 005u
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
public:	// specific
	/**
	* Copy the contents of the internal buffer to the passed descriptor
	*
	* @param aText	This descriptor must be capable of holding the maxlength of the internal buffer
	*/
	IMPORT_C void GetText(TDes& aText) const;
	/**
	* Set the contents of the character buffer
	* @param aText 
	*/
	IMPORT_C virtual void SetText(const TDesC& aText);
	/**
	*
	* Set the initial display of the secret editor.
   * Calling this routine doesn't affect the actual character buffer.
	* 
	* @param aNumberOfCharacters	Must be >=0 and <= EMaxSecEdBufLength
	*/
	IMPORT_C virtual void InitializeDisplay(TInt aNumberOfChars);
	IMPORT_C void Reset();
	/** 
	*
	* Set the length of the usable part of the internal buffer to the passed parameter
	* 
	* @param aMaxLength	New maximum length of the buffer
	*/
	IMPORT_C void SetMaxLength(TInt aMaxLength);


	IMPORT_C void AknSetFont(const CFont &aFont);

	IMPORT_C void AknSetAlignment(const CGraphicsContext::TTextAlign &aAlign);
	/**
	* 
	* @return the current maximum length of the internal buffer
	*/
	IMPORT_C TInt MaxLength() const;

	/**
	* Access method for getting at the buffer without copying out from it
	*
	* @return Non-modifiable descriptor reference to the contained buffer
	*/
	IMPORT_C const TDesC& Buffer() const;


	/**
	* Method to reveal (or hide) the currently input editor contents.
	*
	* @param TBool aReveal - if ETrue, reveals the contents; if EFalse hides them 
	*/
	IMPORT_C void RevealSecretText( TBool aReveal );

protected:	// inherited
    // methods to enable CAknNumericSecretEditor to inherit from CEikSecretEditor
    IMPORT_C virtual void AppendCharacterL( TInt aKeyCode );
    IMPORT_C virtual void Update();
	void InsertSecretChar();
    IMPORT_C void SizeChanged();
private: // virtual
	IMPORT_C virtual void Draw(const TRect& aRect) const;

private: // from MCoeFepAwareTextEditor
	IMPORT_C void StartFepInlineEditL(const TDesC& aInitialInlineText, TInt aPositionOfInsertionPointInInlineText, TBool aCursorVisibility, const MFormCustomDraw* aCustomDraw, MFepInlineTextFormatRetriever& aInlineTextFormatRetriever, MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit);
	IMPORT_C void UpdateFepInlineTextL(const TDesC& aNewInlineText, TInt aPositionOfInsertionPointInInlineText);
	IMPORT_C void SetInlineEditingCursorVisibilityL(TBool aCursorVisibility);
	IMPORT_C void CancelFepInlineEdit();
	IMPORT_C TInt DocumentLengthForFep() const;
	IMPORT_C TInt DocumentMaximumLengthForFep() const;
	IMPORT_C void SetCursorSelectionForFepL(const TCursorSelection& aCursorSelection);
	IMPORT_C void GetCursorSelectionForFep(TCursorSelection& aCursorSelection) const;
	IMPORT_C void GetEditorContentForFep(TDes& aEditorContent, TInt aDocumentPosition, TInt aLengthToRetrieve) const;
	IMPORT_C void GetFormatForFep(TCharFormat& aFormat, TInt aDocumentPosition) const;
	IMPORT_C void GetScreenCoordinatesForFepL(TPoint& aLeftSideOfBaseLine, TInt& aHeight, TInt& aAscent, TInt aDocumentPosition) const;
	IMPORT_C void DoCommitFepInlineEditL();
	IMPORT_C MCoeFepAwareTextEditor_Extension1* Extension1(TBool& aSetToTrue);
	IMPORT_C void SetStateTransferingOwnershipL(CState* aState, TUid aTypeSafetyUid);
	IMPORT_C CState* State(TUid aTypeSafetyUid); // this function does *not* transfer ownership

private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private: // from MCoeFepAwareTextEditor
	IMPORT_C void MCoeFepAwareTextEditor_Reserved_2();
private:  // from MCoeFepAwareTextEditor_Extension1
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_2();
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_3();
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_4();

private: // specific
	void DrawText() const;
	void InsertChar();
    TInt CharsFitOnEditor() const;
	IMPORT_C virtual MCoeFepAwareTextEditor_Extension1::CState* CreateFepStateL();

private:
	typedef TBuf<EMaxSecEdBufLength> TSecEdBuf;
protected:
    HBufC* iSecCharArr;
	TInt iSecPos;
	TSecEdBuf iBuf;
	TInt iMaxLen;
	TInt iCharWidth;
	TInt iAscent;
	TBool iBufferFull;

public: // timer methods
	void StartTimer();
private:
	static TInt TimerCallback(TAny* aThis);
private:
	CPeriodic* iTimer;
	const CFont *iFont;
	CGraphicsContext::TTextAlign iAlign;
	TBool iRevealSecretText; // holds the state of whether text is shown or not
	TInt iSpare;
	CState* iFepState;
	const TDesC* iInlineEditText;
	};

#endif
