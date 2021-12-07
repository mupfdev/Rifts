// EIKCMBUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCMBUT_H__)
#define __EIKCMBUT_H__

#if !defined(__EIKBUTB_H__)
#include <eikbutb.h>
#endif

#if !defined(__COECCNTX_H__)
#include <coeccntx.h>
#endif

#if !defined(__GULUTIL_H__)
#include <gulutil.h>
#endif

class CEikLabel;
class CEikImage;
class CEikAlignedControl;
class TResourceReader;
class CEikCommandStack;

class CEikCommandButtonBase : public CEikButtonBase, public MCoeControlContext
	{
public:
	enum TWhichComponent
		{
		EFirst,
		ESecond
		};
	enum TDisplayContent
		{
		EFirstOnly	=0x0100,
		ESecondOnly	=0x0200,
		EBoth		=0x0300
		};
	enum TLayout
		{
		EFirstRightSecondLeft=0x0000,
		EFirstBottomSecondTop=0x0001,
		EFirstTopSecondBottom=0x0002,
		EFirstLeftSecondRight=0x0003,
		EDenseFont			 =0x0008
		};
	enum TExcess
		{
		EShare		=0x0000,
		EToFirst	=0x0010,
		EToSecond	=0x0020
		};

public: // new functions
	IMPORT_C ~CEikCommandButtonBase();
	IMPORT_C void SetButtonLayout(TLayout aLayout);
	IMPORT_C void SetExcessSpace(TExcess aExcess);
	IMPORT_C void SetDisplayContent(TDisplayContent aContent);
	IMPORT_C void LayoutComponents();
	IMPORT_C void StartConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ConstructLabelFromResourceL(TResourceReader& aReader,TWhichComponent aWhich);
	IMPORT_C void ConstructImageFromResourceL(TResourceReader& aReader,TWhichComponent aWhich);
	IMPORT_C virtual void UpdateComponentAlignment();
	IMPORT_C void SetDefault(TBool aIsDefault);
public:	// from CCoeControl
	IMPORT_C void SetDimmed(TBool aDimmed);
	IMPORT_C TSize MinimumSize();
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void ActivateL();
	IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode /*aType*/);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
public: // but not exported
	CEikCommandStack* CommandStack() const;
	TInt ButFlags() const;
	TBool IsDefault() const;
protected: // from CEikButtonBase
    IMPORT_C void StateChanged();
protected:
	IMPORT_C CEikCommandButtonBase();
	IMPORT_C void SetTextL(const TDesC& aText,CEikAlignedControl*& aComponent);
	IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask,CEikAlignedControl*& aComponent);
	IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask,CEikAlignedControl*& aComponent);
	inline void CheckCreateCommandStackL();
protected: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
protected:
	void SetImageAttributes(CEikImage* aImage);
	inline TInt Behavior() const;
protected:
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
    IMPORT_C void SizeChanged();
	IMPORT_C void Reserved_2();
private: // from CEikButtonBase
	IMPORT_C void Reserved_3();
private: // from MCoeControlContext
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
private:
	IMPORT_C virtual void Reserved_4();
private:
	void SetComponentExtents(const TRect& aRect);
	void SetNewComponentExtentL();
    TBool LayoutIsVertical() const;
protected:
	TMargins8 iMargins;
	CEikAlignedControl* iComponents[2];
    TInt iCmdFlags;
private:
	TInt iDrawOffset;
	CEikCommandStack* iCommandStack;
	TInt iDummy;
	TBool iDefault;
	};

class CEikCommandButton : public CEikCommandButtonBase
	{
public:
	enum TLayout
		{
		ETextRightPictureLeft=0x000,
		ETextBottomPictureTop=0x001,
		ETextTopPictureBottom=0x002,
		ETextLeftPictureRight=0x003
		};
	enum TExcess
		{
		EShare		=0x0000,
		EToText		=0x0010,
		EToPicture	=0x0020
		};
	enum TDisplayContent
		{
		ETextOnly		=0x0100,
		EPictureOnly	=0x0200,
		ETextAndPicture	=0x0300
		};
public:
	IMPORT_C CEikCommandButton();
	IMPORT_C ~CEikCommandButton();
	IMPORT_C void SetTextL(const TDesC& aText);
	IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask=NULL);
	IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1);
	IMPORT_C CEikLabel* Label() const;
	IMPORT_C CEikImage* Picture() const;
	IMPORT_C void SetButtonLayout(TLayout aLayout);
	IMPORT_C void SetExcessSpace(TExcess aExcess);
	IMPORT_C void SetDisplayContent(TDisplayContent aContent);
	IMPORT_C void SetCommandL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	IMPORT_C void AddCommandToStackL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	IMPORT_C TBool RemoveCommandFromStack(TInt aCommandId);
	IMPORT_C TInt PopCommandFromStack();
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
public: // from CEikCommandButtonBase
	IMPORT_C void UpdateComponentAlignment();
private:
	void UpdateLabelReserveLengthL(const TDesC* aText);
private:
	TInt iDummy;
	};

/**
 * The CEikTwoPictureCommandButton class is a command button which can hold two pictures as
 * well as label text. If a second picture is set for the button it is shown when the button
 * is pressed.
 *
 * @since ER5U
 */
class CEikTwoPictureCommandButton : public CEikCommandButtonBase
	{
public:
	enum TLayout
		{
		ETextRightPictureLeft=0x000,
		ETextBottomPictureTop=0x001,
		ETextTopPictureBottom=0x002,
		ETextLeftPictureRight=0x003
		};
	enum TExcess
		{
		EShare		=0x0000,
		EToText		=0x0010,
		EToPicture	=0x0020
		};
	enum TDisplayContent
		{
		ETextOnly		=0x0100,
		EPictureOnly	=0x0200,
		ETextAndPicture	=0x0300
		};
private:
	enum TPictureButtonType
		{
		EPictureButWithBorders		=0x0000,
		EPictureButWithoutBorders	=0x1000
		};
	enum TExternalPicture
		{
		EPictureNotOwnedExternally	=0x00,
		EPictureOwnedExternally		=0x01
		};
public:
	IMPORT_C CEikTwoPictureCommandButton();
	IMPORT_C ~CEikTwoPictureCommandButton();
	IMPORT_C TBool IsSecondPictureOwnedExternally();
	IMPORT_C CEikImage* Picture() const;
	IMPORT_C void ConstructImagesFromResourceL(TResourceReader& aReader,TWhichComponent aWhich);
	IMPORT_C void SetTextL(const TDesC& aText);
	IMPORT_C void SetTwoPicturesL(const CFbsBitmap* aMain,const CFbsBitmap* aMask=NULL,const CFbsBitmap* aSecondMain=NULL, const CFbsBitmap* aSecondMask=NULL);
	IMPORT_C void SetSecondPicture(const CFbsBitmap* aSecondMain, const CFbsBitmap* aSecondMask=NULL);
	IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1);
	IMPORT_C void SetSecondPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1);
	IMPORT_C void SetSecondPictureOwnedExternally(TBool aOwnership);
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ActivateL();
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw(const TRect& /*aRect*/) const;
    IMPORT_C void StateChanged();
private: // from MCoeControlContext
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
private:
	void SwapPictures(CEikImage* aImage);
private:
	const CFbsBitmap* iSecondBitmap;
	const CFbsBitmap* iSecondMaskBitmap;
	TInt iPictureFlags;
	TInt iDummy;
	};

/**
 * The CEikInverterCommandButton class is a command button which swaps the foreground and background
 * colors used to draw the button contents when the button is pressed.
 *
 * @since ER5U
 */
class CEikInverterCommandButton : public CEikCommandButton
	{
public:
	IMPORT_C CEikInverterCommandButton();
	IMPORT_C ~CEikInverterCommandButton();
protected:
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from MCoeControlContext
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
private:
	TInt iFlag;
	TInt iDummy;
	};

//
// CEikTextButton
//

class CEikTextButton : public CEikCommandButtonBase
	{
public:
	IMPORT_C CEikTextButton();
	IMPORT_C ~CEikTextButton();
	IMPORT_C void SetTextL(const TDesC& aText,TWhichComponent aWhich=EFirst);
	IMPORT_C CEikLabel* Label(TWhichComponent aWhich=EFirst) const;
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
private:
	TInt iDummy;
	};

class CEikBitmapButton : public CEikCommandButtonBase
	{
public:
	IMPORT_C CEikBitmapButton();
	IMPORT_C ~CEikBitmapButton();
	IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask=NULL,TWhichComponent aWhich=EFirst);
	IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1,TWhichComponent aWhich=EFirst);
	IMPORT_C CEikImage* Picture(TWhichComponent aWhich=EFirst) const;
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
private:
	TInt iDummy;
	};

#endif
