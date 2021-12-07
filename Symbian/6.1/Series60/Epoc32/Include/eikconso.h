// EIKCONSO.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCONSO_H__)
#define __EIKCONSO_H__
													   
#if !defined(__E32CONS_H__)
#include <e32cons.h>
#endif

#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h>
#endif

#if !defined(__EIKSBFRM_H__)
#include <eiksbfrm.h>
#endif

#define ATT_DOUBLEWIDTH					0x60
#define ATT_DOUBLETOP	   			0x20	
#define ATT_DOUBLEBOTTOM				0x40	
////////////////////////////////////////////
#define ATT_ITALIC						0x08	
#define ATT_INVERSE 					0x04
#define ATT_UNDERLINE					0x02
#define ATT_BOLD						0x01
////////////////////////////////////////////
#define ATT_COLORMASK					0x80	// &x!=0 : color
#define ATT_DOUBLEMASK					0x60 	// &x : only the bits relevant for doublewidth/doubleheight
#define ATT_RIGHTMASK					0x10	// |x to set RIGHT indicator
#define ATT_IGNORE_RIGHTLEFT			0xEF	// &x to clear the RIGHT/LEFT flag
#define ATT_IGNORE_INVERSE				0xFB	// &x to clear the INVERSE flag
////////////////////////////////////////////
#define ATT_MAXVALUE					0xFF	// all flags set (maximum value of attribute byte)
#define ATT_NORMAL						0		// the default character attribute

enum TEikConsWinUnits
	{
	EEikConsWinInPixels,
	EEikConsWinInChars
	};


class CEikConsoleControl;
class CEikConsoleScreen : public CConsoleBase
	{
public:
	enum TEikConsoleFlags
		{
		EUseBackedUpWindow	=0x1,
		ENoInitialCursor	=0x2
		};
public:
	IMPORT_C CEikConsoleScreen();
	IMPORT_C ~CEikConsoleScreen();
	IMPORT_C TInt Create(const TDesC& aTitle,TSize aSize);
	IMPORT_C void Read(TRequestStatus& aStatus);
	IMPORT_C void ReadCancel();
	IMPORT_C TKeyCode KeyCode() const;
	IMPORT_C TUint KeyModifiers() const;
	IMPORT_C void ConstructL(const TDesC &aTitle,TInt aFlags);// use full screen 
	IMPORT_C void ConstructL(const TDesC &aTitle,const TSize &aSize,TInt aFlags,TEikConsWinUnits aUnit=EEikConsWinInChars); // place the screen at TPoint(0,0)
	IMPORT_C void ConstructL(const TDesC &aTitle,TPoint aTopLeft,const TSize &aSize,TInt aFlags,TEikConsWinUnits aUnit=EEikConsWinInChars); 
	IMPORT_C void SetConsWin(CEikConsoleControl *aConsWin); // use if you don't want WHOLE screen
	inline CEikConsoleControl* ConsoleControl() const {return iConsoleControl;};

	IMPORT_C void SetTitle(const TDesC &aTitle);
	IMPORT_C void SetTitleL(const TDesC &aTitle);
	inline HBufC *Title() const {return iConsoleTitle;};

	IMPORT_C TSize ScreenSize() const;

	IMPORT_C void FlushChars(); //new
	IMPORT_C TPoint CursorPos() const;
	IMPORT_C void SetCursorPosAbs(const TPoint &aPoint);		
	IMPORT_C void SetCursorPosRel(const TPoint &aPoint);		
	IMPORT_C void SetCursorHeight(TInt aPercentage);		
	IMPORT_C void Write(const TDesC &aDes);				   		
	
	IMPORT_C void ClearScreen();				
	IMPORT_C void ClearToEndOfLine();		
	IMPORT_C void ClearChars(const TRect &aRect,TUint aCharacterAttributes);	

	IMPORT_C TInt HideCursor(); // returns nonzero if cursor wasn't visible
	IMPORT_C void DrawCursor(); 
	IMPORT_C void DrawInSight(TPoint aPosition);
	IMPORT_C void DrawCursorInSight();
	
	IMPORT_C void Up(TUint aCount=1);		
	IMPORT_C void Down(TUint aCount=1);	
	IMPORT_C void Right(TUint aCount=1);	
	IMPORT_C void Left(TUint aCount=1);	
	IMPORT_C void Cr();							
	IMPORT_C void Lf();							

	IMPORT_C void ScrollChars(const TRect &anArea,const TPoint &aVector);

	IMPORT_C void Redraw(const TRect &aRect);	// called by CEikConsoleControl
	IMPORT_C void MoveTopLeft(TPoint aVector);	// called by CEikConsoleControl

	inline TUint HistorySize() const {return iNoChrExtra;}; // lines ACTUALLY stored				
	IMPORT_C void SetHistorySizeL(TUint aMaxChrExtra,TUint aMaxAttExtra);  // lines of back-scroll history resp. lines of ATTRIBUTED backscroll history (aMaxAttExtra<=aMaxChrExtra)
		
	inline TUint Att() const {return iAtt;};
	
	IMPORT_C void SetAtt(TUint aCharacterAttributes);		
	IMPORT_C void SetAtt(TUint aForegroundGray16,TUint aBackgroundGray16); 

	IMPORT_C void SetFontL(const TFontSpec &aFontDesc);	
	IMPORT_C const TFontSpec& Font() const;

	IMPORT_C void SetSelection(const TRect &aRange); 
	IMPORT_C void SelectCursor(); // empty selection starting and ending at cursor position
	IMPORT_C TRect Selection();
	IMPORT_C HBufC *RetrieveL(const TRect &aRange);	// returns selection in newly allocated buffer

	IMPORT_C void SetPureCRLF(TUint aFlag);
	IMPORT_C void SetAllPrintable(TUint aFlag);
	IMPORT_C void SetScrollLock(TUint aFlag);
	IMPORT_C void SetKeepCursorInSight(TUint aFlag);
	IMPORT_C void SetScrollBarVisibilityL(CEikScrollBarFrame::TScrollBarVisibility aHBarVisibility, CEikScrollBarFrame::TScrollBarVisibility aVBarVisibility);
	IMPORT_C TBool UpdateScrollBars();

private:
	// high-level history manipulation
	void MemScrPut(const TDesC &aString,TPoint aPos,TUint8 aCharacterAttributes);
	void MemScrClr(const TRect &aRect,TUint8 aCharacterAttributes);
	void MemScrScrollUp(TUint aLines=1);
	void MemScrMove(TPoint anOldPt,TPoint aNewPt,TUint aLen);
	void MemScrScroll(const TRect &aRect,TPoint aVector);
	// low-level history access
	TPtr	MemChrPtr(TPoint aPos,TUint aLen);
	TPtr8	MemAttPtr(TPoint aPos,TUint aLen);
	// console screen-to-visible window conversion
	TPoint 	ScrToVis(TPoint aPoint);
	TRect 	ScrToVis(const TRect &aRect);
	// recalculates iVisSize and iVisWin
	TBool RecalculateSize();	
	// calculate a TopLeft that would put aPosition in-sight
	TPoint GetAnInSightPosition(TPoint aPosition) const;
	// draw cursor or draw cursor in sight, depending on iKeepCursorInSight
	void DrawCursorWhereNeeded();
	// smart cursor-clipping: clips cursor to within screen, but allows it to be past the last character
	void ClipCursor();
	// redraw characters with doublewidth LEFT/RIGHT flag set depending on odd/even columns
	void CEikConsoleScreen::RedrawChars(TInt anX,TInt anY,TInt aLength,TUint aCharacterAttributes);
	// routines needed for selection
	void InvertOverlap(TPoint aStart,TPoint aEnd,TPoint bStart,TPoint bEnd);
	void InvertRange(const TRect &aRect);

private:
	CEikConsoleControl *iConsoleControl;// console window (handles redraw events)
	TSize iConsoleSize; 		// size of console in characters (e.g. 80x24)	
	HBufC *iConsoleTitle;		// console title
	TRect iSelection; 			// current selection
	TPoint iCursor;				// current cursor position
	TUint iAtt;					// current character attribute

	TInt iWriteNow;				// if FALSE, Write()-calls can be buffered
	TBuf<256> iWriteBuffer;		// the Write() buffer

	TInt	iMaxChrExtra;		// max nr of extra lines of characters stored
	TInt	iNoChrExtra;		// actual nr of extra lines of characters stored
	TInt	iMaxAttExtra;		// max nr of extra lines of character attributes stored
	TText	*iChrBuf;			// character history
	TUint8	*iAttBuf;			// attribute history

	TPoint	iTopLeft;			// coordinates of top left corner of visual display
	TRect iVisWin;				// RECT visible window
	TSize iVisSize;				// SIZE visible window

	// settings
	TUint iPureCRLF;			// FALSE by default. If TRUE, CR and LF are "pure"
	TUint iAllPrintable;		// FALSE by default. If TRUE, even chars 0-31 are printed
	TUint iScrollLock;			// FALSE by default. If TRUE, will not scroll at bottom line
	TUint iKeepCursorInSight;	// TRUE by default. If FALSE, cursor may be offscreen after a Write()
	TUint iCursorBlinking; 		// TRUE if cursor should be visible (i.e. user WANTS it to be visible)

	TInt iConsFlags;
	};

class CEikConsoleControl : public CCoeControl, public MEikScrollBarObserver 
	{
public:	
	// constructors, destructors, initialization
	IMPORT_C CEikConsoleControl();
	IMPORT_C ~CEikConsoleControl();
	IMPORT_C void	ConstructL(TInt aFlags);
	IMPORT_C void	ConstructL(TPoint aTopLeft,const TSize &aSize,TInt aFlags,TEikConsWinUnits aUnit);
	IMPORT_C void 	SetRedrawer(CEikConsoleScreen *aConsole);

	// font stuff
	IMPORT_C void	SetFontL(const TFontSpec &aFontSpec,const CFbsFont* aFont);		// change to font aFontSpec
	inline const TFontSpec& Font() const {return iFontSpec;};	// returns current fontspec

	inline const TSize& CharSize() const {return iCharSize;};	
	IMPORT_C TSize	VisibleSize() const;						// returns maximal visible nr of visible characters

	// cursor stuff
	IMPORT_C void	SetCursorHeight(TUint aPercentage);	// set cursor height (0-100%)
	IMPORT_C void	DrawCursor(TPoint aPosition);		// draw cursor at character position
	IMPORT_C void	HideCursor();						// hide cursor

	// basic graphic functions
	IMPORT_C void	DrawChars(const TDesC &aString,const TPoint &aPosition,TUint aCharacterAttributes);	// draw aString at character position aPosition using
	IMPORT_C void	ClearChars(const TRect &anArea,TUint aCharacterAttributes);	// clear the character area
	IMPORT_C void	InvertChars(const TRect &anArea);	// invert the character area
	IMPORT_C void	ScrollChars(const TRect &anArea,const TPoint &aVector);	// scroll characters inside anArea by the given vector

	// scrollbar stuff
	IMPORT_C TInt	SetScrollBarVisibilityL(CEikScrollBarFrame::TScrollBarVisibility aHBarVisibility, CEikScrollBarFrame::TScrollBarVisibility aVBarVisibility);
	IMPORT_C TBool	UpdateScrollbarsL(const TSize &aDataSize,const TSize& aVisibleSize,TPoint aPos);
	IMPORT_C void	HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);
	IMPORT_C void	UpdateArea();

public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u

protected:	// virtual
	// window stuff
	IMPORT_C void	Draw(const TRect& aRect) const;	
	IMPORT_C void	SizeChanged();
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C virtual TInt CountComponentControls() const;
	IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:  // virtual - Reserved from CCoeControl
	IMPORT_C virtual void Reserved_2();

private:
	TPoint	CharsToPixels(TPoint aPoint);
	TRect	CharsToPixels(const TRect &aRect);
	TRect	PixelsToChars(const TRect &aRect);
	void	ClearPixels(const TRect &anArea,TRgb aColor) const;

	void 	NextFontL(); 			
	void	InterpretAttribute(TUint AnAtt);
	void	InterpretColorBits(TUint aCharacterAttributes);
	inline 	CEikConsoleControl &M() const {return((CEikConsoleControl&)(*this));}
 	void CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout) const;
	void	InitFontSpecL();

private:
	CEikConsoleScreen *iConsole;	// the console that owns this window
	TRgb iBackGray16;				// current background color 
	TRgb iPenGray16;				// current pen color for characters
	TUint iLastAtt;					// last attribute, to see if we need to change the gc
	TUint iLastFontFlags;			// last attribute, to see if we need to load another font

	TSize iCharSize;				// size of a single character (in pixels)
	TSize iViewInPixels;			// size of area available for characters (in pixels)
	TSize iViewInChars;				// size of area available for characters (in characters)

	TTextCursor iTextCursor;		// cursor to use
	TUint iCursorHeightPercentage;	// required height of cursor (as a percentage)

	TInt iRedrawing;				// NONZERO IF BUSY REDRAWING
	
	CEikScrollBarFrame* iSBFrame;
	CEikScrollBarFrame::TScrollBarVisibility	iHBarVisibility;
	CEikScrollBarFrame::TScrollBarVisibility	iVBarVisibility;
	TPoint	iLastThumbPos;

	const CFont *iCurrentFont;		// Current font
	TFontSpec iFontSpec;			// Current font spec
	TFontUnderline iFontUnderline;	// Current font spec underline
	TUint iFontHeight;				// Height of current font when not doubleheight/doublewidth
	TUint iFontIsProportional; 		// nonzero if font is proportional
	};



#endif
