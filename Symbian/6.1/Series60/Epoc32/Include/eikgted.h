// EIKGTED.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKGTED_H__)
#define __EIKGTED_H__

#if !defined(__EIKEDWIN_H__)
#include <eikedwin.h>
#endif


#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined(__EIKON_HRH__)
#include <eikon.hrh>
#endif

class CGlobalText;
class CControlEnv;
class CEikDialogToolBar;
class CPrintSetup;
class CTextPageRegionPrinter;
class CEikDialogToolBar;

class CEikGlobalTextEditor : public CEikEdwin
	{
public:


	enum TFontStyleFlags
		{
		EStandard	=0x00,
		EBold		=0x01,
		EItalic		=0x02,
		EUnderline	=0x04
		};

public: // construction and destruction
	IMPORT_C CEikGlobalTextEditor();
	IMPORT_C CEikGlobalTextEditor(const TGulBorder& aBorder);
	IMPORT_C ~CEikGlobalTextEditor();
	IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aNumberOfLines,TInt aTextLimit,TInt aEdwinFlags,TInt aFontControlFalgs,TInt aFontNameFlags);
	// This feature is not supported in Avkon; type made more general for source compatibility
	IMPORT_C void SetButtonGroup(CCoeControl* aButtonGroup);
	// This feature is not supported in Avkon
	IMPORT_C void SetLineCursorBitmapL(CFbsBitmap* aBitmap);
public: // formatting dialogs
	IMPORT_C TBool RunFontDialogL(TInt aFontFlags=EGulNoSymbolFonts,CGraphicsDevice* aGraphicsDevice=NULL,TInt aFontControlFlags=EGulFontControlAll);
	IMPORT_C void RunTabsDialogL(TInt aPageWidth);
	IMPORT_C void RunIndentsDialogL(TInt aPageWidth);
	IMPORT_C void SetGraphicsDevice(CGraphicsDevice* aGraphicsDevice);
	IMPORT_C void RunFindDialogL();
	IMPORT_C void RunFindAgainDialogL();
	IMPORT_C void RunReplaceDialogL();
	IMPORT_C void InitFindL(SEdwinFindModel*& aModel,CDesCArray*& aFindList,CDesCArray*& aReplaceList);
	IMPORT_C TBool DoFindL();
	IMPORT_C void RunParaDialogsL(TInt aCommand);	
	IMPORT_C TBool RunPaginateDialogL(CPrintSetup* aPrintSetup,CArrayFix<TInt>* aCharsPerPage);
public: // other functions
	IMPORT_C CGlobalText* GlobalText() const;
	IMPORT_C void ApplyParaFormatL(CParaFormat* aParaFormat,TParaFormatMask& aParaMask);
	IMPORT_C void ApplyCharFormatL(TCharFormat& aCharFormat,TCharFormatMask& aCharMask);
	IMPORT_C void BoldItalicUnderlineEventL(TInt aFontFlag);
	IMPORT_C void UpdateButtonGroup();
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void ActivateL();
public: // from CEikEdwin
	IMPORT_C TInt LineCursorWidth() const;
protected:
	IMPORT_C void BaseConstructL();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CoeControl
	IMPORT_C void Reserved_2();
private: // from CEikEdwin
	IMPORT_C void Reserved_3();
private:
	void CheckDocumentNotEmptyL();
	void CreateFindModelL();
	void GetTextForFindL();
protected:
	CCharFormatLayer* iCharFormatLayer;
	CParaFormatLayer* iParaFormatLayer;
private:
	CDesCArray* iFindList; 
	CDesCArray* iReplaceList;
	SEdwinFindModel* iFindModel;
	CEikDialogToolBar* iButGroup;
	TInt iLineCursorWidth;
	CFbsBitmap* iLineCursor;
	TInt iFontControlFlags;
	TInt iFontNameFlags;
	CGraphicsDevice* iGraphicsDevice;
	};


#endif
