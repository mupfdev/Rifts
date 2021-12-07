// EIKLBBUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__EIKLBBUT_H__)
#define __EIKLBBUT_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>
#endif

class CEikCommandButtonBase;
class CEikLabel;

class CEikLabeledButton : public CCoeControl, private MCoeControlObserver
	{
public:
	enum TFlags
		{
		EShowHotKey		=0x01,
		EPlainHotKey	=0x02
		};
public:
	IMPORT_C CEikLabeledButton();
	IMPORT_C ~CEikLabeledButton();
	IMPORT_C void ConstructL(CEikCommandButtonBase* aButton,TInt aHotKeyCode,TInt aFlags);
	IMPORT_C CEikCommandButtonBase* Button() const;
	IMPORT_C CEikLabel* Label() const;
	IMPORT_C TInt HotKeyCode() const;
	IMPORT_C TBool ShowsHotKey() const;
	IMPORT_C TBool PlainHotKey() const;
	IMPORT_C void Animate();
	IMPORT_C void UpdateHotKey(TInt aKeyCode,TFlags aFlags);
public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C void SetDimmed(TBool aDimmed);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C TCoeInputCapabilities InputCapabilities() const; // not available before Release 006
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    void SizeChanged();
	void Reserved_2();
private: // from MCoeControlObserver
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
private:
	void CreateLabelL();
	void UpdateHotKeyL();
private:
	CEikCommandButtonBase* iButton;
	CEikLabel* iLabel;
	TInt iHotKeyCode;
	TInt iLButFlags;
	};

#endif
