// EIKSCBUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSCBUT_H__)
#define __EIKSCBUT_H__

#include <eikbutb.h>
#include <lafpublc.h>

class CEikScrollButton : public CEikButtonBase
	{
public:
	enum TType
		{
		ENudgeLeft=SLafScrollButton::ENudgeLeft,
		ENudgeUp=SLafScrollButton::ENudgeUp,
		ENudgeRight=SLafScrollButton::ENudgeRight,
		ENudgeDown=SLafScrollButton::ENudgeDown,
		EPageLeft=SLafScrollButton::EPageLeft,
		EPageUp=SLafScrollButton::EPageUp,
		EPageRight=SLafScrollButton::EPageRight,
		EPageDown=SLafScrollButton::EPageDown,
		EHome=SLafScrollButton::EHome,
		ETop=SLafScrollButton::ETop,
		EEnd=SLafScrollButton::EEnd,
		EBottom=SLafScrollButton::EBottom
		};

public:
	enum TTypeOfScrollBar
		{
		ENormal		=0x00,
		EArrowHead	=0x01
		};

public: // class specific functions
	IMPORT_C ~CEikScrollButton();
	IMPORT_C CEikScrollButton(TType aType);
	IMPORT_C TType Type() const;
	};


//
// CEikArrowHeadScrollButton
//

class CEikArrowHeadScrollButton : public CEikScrollButton
	{

public:
	IMPORT_C static CEikArrowHeadScrollButton* NewL(const CCoeControl* aParent, TType aType);
private:
	CEikArrowHeadScrollButton();
	};



#endif
