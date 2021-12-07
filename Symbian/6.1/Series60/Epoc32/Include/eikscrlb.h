// EIKSCRLB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
		
#if !defined(__EIKSCRLB_H__)
#define __EIKSCRLB_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h>
#endif

#if !defined(__AKNSCBUT_H__)
#include <aknscbut.h>
#endif

#include <lafpublc.h>

class CEikCba;

const TInt KEikScrollEventFromVBar=0;
const TInt KEikScrollEventFromHBar=0x01;
const TInt KEikScrollEventBarMask=0x01;

const TInt KButtonPositionMask=KLafScrollBarButtonPositionMask; // sets all bits in EButtonsXxx range
const TInt KDisplayComponentsMask=0x1f; // sets all bits in determining which components exist

//
// TEikScrollBarModel class
//

class TEikScrollBarModel
	{
public:
	inline TEikScrollBarModel();
	IMPORT_C TEikScrollBarModel(TInt aScrollSpan,TInt aThumbSpan=0,TInt aThumbPosition=0);
	// operators
	IMPORT_C TBool operator==(const TEikScrollBarModel aModel) const;
	inline TBool operator!=(const TEikScrollBarModel aModel) const; 
public:
	IMPORT_C TBool ScrollBarUseful() const;
	IMPORT_C TInt MaxThumbPos() const;
	IMPORT_C void CheckBounds();
public:
	TInt iScrollSpan;
	TInt iThumbSpan;
	TInt iThumbPosition;            
	};

inline TEikScrollBarModel::TEikScrollBarModel() {}
inline TBool TEikScrollBarModel::operator!=(const TEikScrollBarModel aModel) const { return !(*this==aModel); }

//
// CEikScrollBar
//

class CEikScrollThumb;
class CEikScrollBarFrame;
  
/**
 * The CEikScrollBar class implements a scroll bar. Scroll bars are used when the contents of a view require a greater
 * area than can be physically displayed. Scroll bars allow a user to move different parts of the content
 * into the view and to indicate what proportion of the total contents are visible at any one time.
 */
class CEikScrollBar : public CEikBorderedControl, public MCoeControlObserver
	{
public:
	enum TOrientation
		{
		EVertical = SLafScrollBar::EVertical,
		EHorizontal = SLafScrollBar::EHorizontal
		};

public:
	IMPORT_C ~CEikScrollBar();
	IMPORT_C CEikScrollBar();
public:
	// second phase construction
	IMPORT_C virtual void ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
				TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);

	// set state functions
	IMPORT_C void SetLengthL(TInt aLength);
	IMPORT_C void SetModelL(const TEikScrollBarModel* aModel);
	IMPORT_C void SetModel(const TEikScrollBarModel* aModel);
	IMPORT_C void SetLengthAndModelL(TInt aLength,const TEikScrollBarModel* aModel);
	IMPORT_C void SetModelThumbPosition(TInt aThumbPos);
	IMPORT_C void SetFocusPosToThumbPos(TInt aFocusPosition);
	IMPORT_C static TInt DefaultScrollBarBreadth();
	inline void SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver);    // not available before Release 005u

	// information retreival functions
	inline const TEikScrollBarModel* Model() const;
	IMPORT_C TInt ThumbPosition() const;
	IMPORT_C TInt ScrollBarBreadth() const;
	IMPORT_C static TInt MinVisibleLength(const TInt aScrollBarFlags);

	// Button dimming functions
	IMPORT_C void SetDecreaseButtonsDimmed(TBool aDimmed);
	IMPORT_C void SetIncreaseButtonsDimmed(TBool aDimmed);
	IMPORT_C void SetAllButtonsDimmed(TBool aDimmed);

	inline CAknScrollButton* IncreaseNudgeButton() const;
	inline CAknScrollButton* DecreaseNudgeButton() const;

	// This function should only be used by CEikCba
	IMPORT_C void SetContainingCba(CEikCba* aCba);

	IMPORT_C void MakeVisible(TBool aVisible);

protected:      // from CCoeControl
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C TInt CountComponentControls() const;
private: // from MCoeControlObserver
	IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
private: // virtual - reserved from CCoeControl
	IMPORT_C virtual void Reserved_2();

protected:
	friend class CEikScrollBarFrame;
	// enums
	enum TPrivateScrollBarFlags
		{
		ENoComponentsToDisplay          =0x10000,
		EIncreaseButtonsDimmed          =0x20000,
		EDecreaseButtonsDimmed          =0x40000
		};

	enum TPointerDownOn
		{
		ENone,
		EHomeButton,
		EDecreasePageButton,
		EDecreaseNudgeButton,
		EDecreaseShaft,
		EThumb,
		EIncreaseShaft,
		EIncreaseNudgeButton,
		EIncreasePageButton,
		EEndButton
		};

	enum TShaftRedrawRequired
		{
		ENoRedrawRequired,
		ERedrawShaft
		};

	enum TWhichButtons
		{
		EIncreaseOnly,
		EDecreaseOnly,
		EAll
		};

	struct SEikScrollBarButtons
		{
		CAknScrollButton* iDecreaseNudge;
		CAknScrollButton* iIncreaseNudge;
		};

public:
	enum TEikScrollBarFlags
		{
		EEikScrollBarDefaultBehaviour   =SLafScrollBar::EEikScrollBarDefaultBehaviour,
		EEikScrollBarNoNudgeButtons		=SLafScrollBar::EEikScrollBarNoNudgeButtons,
		EEikScrollBarHasPageButtons		=SLafScrollBar::EEikScrollBarHasPageButtons,	
		EEikScrollBarHasHomeEndButtons	=SLafScrollBar::EEikScrollBarHasHomeEndButtons,
		EEikScrollBarNoShaftOrThumb		=SLafScrollBar::EEikScrollBarNoShaftOrThumb,	
		EEikScrollBarShaftButNoThumb	=SLafScrollBar::EEikScrollBarShaftButNoThumb,	
		EButtonsAtStartOfShaft			=SLafScrollBar::EButtonsAtStartOfShaft,	
		EButtonsAtEndOfShaft			=SLafScrollBar::EButtonsAtEndOfShaft,			
		EButtonsEitherSideOfShaft		=SLafScrollBar::EButtonsEitherSideOfShaft,
		ENoAutoDimming					=SLafScrollBar::ENoAutoDimming		
		};

	typedef TEikScrollBarFlags TAknScrollBarFlags;

private:
	// construction/destruction
	IMPORT_C virtual void CreateButtonL(CAknScrollButton*& aButton,CAknScrollButton::TType aType);

	void SizeChanged();

	// set state functions
	void DoSetModel(const TEikScrollBarModel* aModel);

	CEikCba* Cba() const;

	// These functions are for use only be CEikScrollBarFrame (a friend class)
	void AddExternalFrameL(CEikScrollBarFrame* aFrame);
	void RemoveExternalFrame(CEikScrollBarFrame* aFrame);

	void DisconnectExternalFrames();

protected:
	void CreateRequiredComponentsL();
	void DestroyButton(CAknScrollButton*& aButton);
	IMPORT_C virtual void SetButtonPositionL(CAknScrollButton* aButton);
public:
	TDblQueLink iSBLink;
protected:
	SEikScrollBarButtons iButtons;
	TOrientation iOrientation;
private:
	TEikScrollBarModel iModel;

private:
	class CEikScrollBarExtension : public CBase
		{
	public:
		CEikScrollBarExtension();

	public: // all member data is owned by CEikScrollBar
		CEikCba* iCba;
		CArrayFixFlat<CEikScrollBarFrame*> iExternalFrames;
		};

	CEikScrollBarExtension* iExtension;
	};


/**
 * The CEikArrowHeadScrollBar class is a scroll bar which uses only
 * two small nudge button arrows to scroll up and down. It has no shaft.
 * It therefore takes up very little space.
 *
 * @since ER5U 
 * @ internal
 * Internal to Symbian
 *
 */
class CEikArrowHeadScrollBar : public CEikScrollBar
	{
public:
	IMPORT_C CEikArrowHeadScrollBar(CCoeControl* aParentWindow);
	IMPORT_C ~CEikArrowHeadScrollBar();
public: // from CEikScrollBar
	IMPORT_C void ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
				TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);
private: // from CEikScrollBar
	void CreateButtonL(CAknScrollButton*& aButton,CAknScrollButton::TType aType);
	void SetButtonPositionL(CAknScrollButton* aButton);
private:
	CCoeControl* iParentControl;
	};


//
// Inlines
//

inline void CEikScrollBar::SetScrollBarObserver(MEikScrollBarObserver* /*aScrollBarObserver*/)
	{ }

inline const TEikScrollBarModel* CEikScrollBar::Model() const
	{ return &iModel; }

inline CAknScrollButton* CEikScrollBar::IncreaseNudgeButton() const
	{ return iButtons.iIncreaseNudge; }

inline CAknScrollButton* CEikScrollBar::DecreaseNudgeButton() const
	{ return iButtons.iDecreaseNudge; }


#endif
