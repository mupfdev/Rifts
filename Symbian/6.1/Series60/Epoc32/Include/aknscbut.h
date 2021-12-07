// AKNSCBUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNSCBUT_H__)
#define __AKNSCBUT_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

class CAknScrollIndicator;

class CAknScrollButton : public CCoeControl
	{
public:
	enum TType
		{
		ENudgeLeft,
		ENudgeUp,
		ENudgeRight,
		ENudgeDown,
		EPageLeft,
		EPageUp,
		EPageRight,
		EPageDown,
		EHome,
		ETop,
		EEnd,
		EBottom
		};

public:
	enum TTypeOfScrollBar
		{
		ENormal		=0x00,
		EArrowHead	=0x01
		};

public: // class specific functions
	IMPORT_C static CAknScrollButton* NewL(TType aType);
	IMPORT_C ~CAknScrollButton();
	IMPORT_C TType Type() const;
	IMPORT_C void CreateWindowOnlyForArrowsL(const CCoeControl* aParent);
	IMPORT_C TBool IsNormalScrollBarUsingButton() const;
	IMPORT_C void SetTypeOfScrollBarUsingButton(TTypeOfScrollBar aTypeOfScrollBar);
	IMPORT_C void SetPosition(const TInt aFocusPosition, const TInt aScrollSpan);
private: // class specific functions
	CAknScrollButton(TType aType);
	void ConstructL();
	void SizeChanged();
	void DrawIndicator() const;
private: // from CCoeControl
	virtual void Draw(const TRect& aRect) const;
private:
	friend class CAknScrollBar;
	TType iType;
	TInt iFlag;
	CAknScrollIndicator* iScrollIndicator;
	};


#endif
