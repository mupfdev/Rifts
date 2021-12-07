// EIKCTGRP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCTGRP_H__)
#define __EIKCTGRP_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#include <lafpublc.h>

class TEikGroupControl
	{
public:
	inline TEikGroupControl();
	inline TEikGroupControl(CCoeControl* aControl,TInt aId,TInt aLength,TInt aFlags);
public:
	CCoeControl* iControl;
	TInt iId;
	TInt iLongId;
public:
	inline TBool IsLengthSet() const;
	inline TInt Length() const;
	inline TBool IsStretchable() const;
	inline void SetLength(TInt aLength);
	inline void SetStretchable();
public:
	enum TControlFlags
		{
		ESetLength		=0x01,
		EAllowStretch	=0x02
		};
private:
	TInt iLength;
	TInt iFlags;
	};

class CEikControlGroup : public CEikBorderedControl
	{
friend class CTestControlGroup; // test code

// CEikCba made a friend to get at Orientation() private method
friend class CEikCba;
// -> 
public:
	enum TStartCorner
		{
		EFromTopLeft=SLafControlGroup::EFromTopLeft,
		EFromTopRight=SLafControlGroup::EFromTopRight,
		EFromBottomLeft=SLafControlGroup::EFromBottomLeft,
		EFromBottomRight=SLafControlGroup::EFromBottomRight
		};
	enum TOrientation
		{
		ELayHorizontally=SLafControlGroup::ELayHorizontally,
		ELayVertically	=SLafControlGroup::ELayVertically	
		};
public: // new functions
	IMPORT_C CEikControlGroup();
	IMPORT_C ~CEikControlGroup();
	IMPORT_C void ConstructL(TStartCorner aStart,TOrientation aOrientation);
	IMPORT_C virtual void AddControlL(CCoeControl* aControl,TInt aId);
	IMPORT_C virtual void AddControlL(TEikGroupControl& aGroupControl);
	IMPORT_C void InsertControlL(TEikGroupControl& aGroupControl,TInt aIndex);
	IMPORT_C void DeleteControl(TInt aIndex,TInt aCount);
	IMPORT_C void SetLengthInPixels(TInt aLength);
	IMPORT_C void SetBreadthInPixels(TInt aBreadth);
	IMPORT_C void SetControlSpacing(TInt aHSpacing,TInt aVSpacing);
	IMPORT_C void SetControlLayout(TStartCorner aStart,TOrientation aOrientation);
	IMPORT_C void SetNumberOfLines(TInt aNumLines,TBool aDistributeEvenly);
	IMPORT_C void SetControlsAllSameSize();
	IMPORT_C void LayoutControls();
	IMPORT_C CCoeControl* ControlById(TInt aId) const;
	IMPORT_C TInt IndexById(TInt aId) const;
	IMPORT_C void Reset();
	IMPORT_C TInt ControlId(CCoeControl* aControl) const;
	IMPORT_C CCoeControl* Control(TInt aIndex) const; // as requested by Bill
	IMPORT_C CArrayFix<TEikGroupControl>* ControlArray() const;
	IMPORT_C TOrientation Orientation() const;
	IMPORT_C void ControlSpacing(TInt& aHSpacing,TInt& aVSpacing) const;
public: // from CCoeControl
	IMPORT_C TSize MinimumSize();
    IMPORT_C TInt CountComponentControls() const;
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
protected:
	enum
		{
		EDistributeEvenly	=0x40,
		EAllSameSize		=0x80
		};
protected: // from CCoeControl
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // new functions
	IMPORT_C TInt Adjacent(TInt aRow,TInt aColumn,TInt aCtrlIndex,TInt aTotalRows,TInt aTotalColumns) const;
	IMPORT_C TStartCorner StartCorner() const;
	IMPORT_C void DeleteAllComponents();
	IMPORT_C TSize ControlMinimumSize(TInt aIndex) const;
	IMPORT_C TInt ControlMinimumLength(TInt aIndex);
	IMPORT_C TSize LargestControlSize() const;
	IMPORT_C TBool DistributeEvenly() const;
	IMPORT_C TBool AllSameSize();
private: // from CCoeControl
    IMPORT_C void SizeChanged();
	IMPORT_C void Draw(const TRect& aRect) const;
protected:
	CArrayFix<TEikGroupControl>* iControlArray;
private:
	TInt iLayout;
	TInt iLines;
	TInt iHSpacing;
	TInt iVSpacing;
	TInt iBreadth;
	TInt iLength;
	TSize iLargestControl;
	};


inline TEikGroupControl::TEikGroupControl()
	{ iControl=NULL; iId=iFlags=iLength=0; }
inline TEikGroupControl::TEikGroupControl(CCoeControl* aControl,TInt aId,TInt aLength,TInt aFlags)
	: iControl(aControl),iId(aId),iLength(aLength),iFlags(aFlags)
	{}
inline TBool TEikGroupControl::IsLengthSet() const
	{ return iFlags&ESetLength; }
inline TInt TEikGroupControl::Length() const
	{ return iLength; }
inline TBool TEikGroupControl::IsStretchable() const
	{ return iFlags&EAllowStretch; }
inline void TEikGroupControl::SetLength(TInt aLength)
	{ iLength=aLength; iFlags|=ESetLength; }
inline void TEikGroupControl::SetStretchable()
	{ iFlags|=EAllowStretch; }

#endif
