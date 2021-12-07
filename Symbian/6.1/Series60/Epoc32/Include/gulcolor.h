// GULCOLOR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GULCOLOR_H__)
#define __GULCOLOR_H__

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

enum TLogicalColor
	{
	// Windows
	EColorWindowBackground,
	EColorWindowText,
	// Controls
	EColorControlBackground,
	EColorControlText, 
	EColorControlSurroundBackground,
	EColorControlSurroundText,
	EColorControlHighlightBackground, 
	EColorControlHighlightText,
	EColorControlDimmedBackground, 
	EColorControlDimmedText,
	EColorControlDimmedHighlightBackground,
	EColorControlDimmedHighlightText,
	// Dialogs
	EColorDialogBackground,
	EColorDialogText,
	EColorDialogTitle,
	EColorDialogTitlePressed,
	EColorDialogTitleText,
	EColorDialogTitleTextPressed,
	// Menus
	EColorMenubarBackground,
	EColorMenubarText,
	EColorMenubarTitleBackground,
	EColorMenubarTitleText,
	EColorMenuPaneBackground,
	EColorMenuPaneText,
	EColorMenuPaneHighlight,
	EColorMenuPaneTextHighlight,
	EColorMenuPaneDimmedHighlight,
	EColorMenuPaneDimmedText,
	EColorMenuPaneDimmedTextHighlight,
	// Command buttons
	EColorButtonFaceClear,
	EColorButtonFaceSet,
	EColorButtonFaceSetPressed,
	EColorButtonFaceClearPressed,
	EColorButtonText,
	EColorButtonTextPressed,
	EColorButtonTextDimmed,		
	// Message windows
	EColorMsgWinForeground,
	EColorMsgWinBackground,
	// Scrollbars
	EColorScrollBarBorder,
	EColorScrollBarShaft,
	EColorScrollBarShaftDimmed,
	EColorScrollBarShaftPressed,
	EColorScrollBarNoShaftOrThumb,
	EColorScrollButtonIcon,
	EColorScrollButtonIconPressed,
	EColorScrollButtonIconDimmed,
	EColorScrollButtonThumbBackground,
	EColorScrollButtonThumbBackgroundPressed,
	EColorScrollThumbDimmed,
	EColorScrollThumbEdge,
	// Toolbars
	EColorToolbarBackground,
	EColorToolbarText,
	// Status pane
	EColorStatusPaneBackground,
	EColorStatusPaneText,
	// Labels
	EColorLabelText,
	EColorLabelTextEmphasis,
	EColorLabelDimmedText,
	EColorLabelHighlightPartialEmphasis,
	EColorLabelHighlightFullEmphasis,
	};

class RReadStream;
class RWriteStream;
class CColorArray;

// not available before Release 005
class CColorList : public CBase
	{
public:
	IMPORT_C static CColorList* NewL(CArrayFix<TRgb>* aColors);
	IMPORT_C ~CColorList();
	// Accessors
	IMPORT_C TRgb Color(TLogicalColor aColor) const;
	IMPORT_C TRgb Color(TUid aApp,TInt aColor) const;
	IMPORT_C CColorArray* ColorArray(TUid aApp) const;
	IMPORT_C TBool ContainsColorArray(TUid aApp) const;
	// Manipulators
	IMPORT_C void SetColor(TLogicalColor aLogicalColor,TRgb aColor);
	IMPORT_C void AddColorArrayL(TUid aApp,CColorArray* aArray); // takes ownership
	IMPORT_C void DeleteColorArray(TUid aApp);
public:
	static CColorList* NewLC();
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	void MergeL(const CColorList& aList);
private:
	CColorList(CArrayFix<TRgb>* aColors);
	TInt Find(TUid aApp) const;
private:
	class TAppColorList
		{
	public:
		inline TAppColorList(TUid aApp,CColorArray* aColorArray);
	public:
		TUid iApp;
		CColorArray* iColorArray;
		};
private:
	CArrayFix<TRgb>* iEikColors;
	CArrayFix<TAppColorList>* iAppColors;
	};

// not available before Release 005
class CColorArray : public CBase
	{
public:
	IMPORT_C static CColorArray* NewL();
	IMPORT_C static CColorArray* NewLC();
	IMPORT_C ~CColorArray();
	IMPORT_C TRgb Color(TInt aLogicalColor) const;
	IMPORT_C void SetColor(TInt aLogicalColor,TRgb aColor);
	IMPORT_C TBool Contains(TInt aLogicalColor) const;
	IMPORT_C TInt Count() const;
	IMPORT_C void Reset();
	IMPORT_C void AddL(TInt aLogicalColor,TRgb aColor);
	IMPORT_C void Remove(TInt aLogicalColor);
public:
	static CColorArray* NewLC(const CColorArray& aArray);
public:
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	CColorArray();
	void ConstructL();
	TInt Find(TInt aLogicalColor) const;
private:
	class TColor
		{
	public:
		inline TColor();
		inline TColor(TRgb aColor,TInt aLogicalColor);
	public:
		void InternalizeL(RReadStream& aStream);
		void ExternalizeL(RWriteStream& aStream) const;
	public:
		TRgb iColor;
		TInt iLogicalColor;
		};
	CArrayFixFlat<TColor> iColors;
	};

_LIT(KGulColorSchemeFileName,"C:\\System\\Data\\Colorscm.dat");

#endif
