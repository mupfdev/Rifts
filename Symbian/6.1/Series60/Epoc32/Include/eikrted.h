// EIKRTED.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKRTED_H__)
#define __EIKRTED_H__

#if !defined(__EIKGTED_H__)
#include <eikgted.h>
#endif

#if !defined(__APPARC_H__)
#include <apparc.h>
#endif

#if !defined(__TXTMRTSR_H__)
#include <txtmrtsr.h>
#endif

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

class CRichText;
class TResourceReader;
class TPictureHeader;
class CEikRubberBand;
class CBufStore;
class CStreamStore;
class CApaDoor;
class CEikParserManager;
class MEikRichTextEditorParserObserver;
class MParser;

class CEikRichTextEditor : public CEikGlobalTextEditor, public MApaEmbeddedDocObserver, public MRichTextStoreResolver, public MPictureFactory
	{
public:
	enum TObjectFormat
		{
		EAlwaysIconic,
		EGlassIfPossible
		};

	enum // user flag
		{
		EShowAllPicturesAsIconic	=0x00100000,
		ENoTextParsers				=0x00200000,
		};
public:
	IMPORT_C CEikRichTextEditor();
	IMPORT_C CEikRichTextEditor(const TGulBorder& aBorder);
	IMPORT_C ~CEikRichTextEditor();
	IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aNumberOfLines,TInt aTextLimit,TInt aEdwinFlags,TInt aFontControlFlags=EGulFontControlAll,TInt aFontNameFlags=EGulNoSymbolFonts);
	IMPORT_C CRichText* RichText() const;
	IMPORT_C void InsertObjectL(TObjectFormat aFormat);
	IMPORT_C void InsertObjectL(); // defaults to EGlassIfPossible
	IMPORT_C void InsertObjectL(const TDesC& aAppDllName,TUid aAppDllUid,TObjectFormat aFormat);
	IMPORT_C void InsertObjectL(TUid aPictureType,CBase* aData);
	IMPORT_C void ReEditObjectL();
	IMPORT_C TInt ObjectCursorPos() const;
	IMPORT_C TBool CheckForObjectL();
	IMPORT_C void EditPictureFormatL();
	IMPORT_C void PictureFormatChangedL();
	IMPORT_C void GetEmbeddedAppL(CApaDoor*& aDoor,CApaDocument*& aDoc,TInt aDocPos);
	IMPORT_C void UpdatePictureFormatL(); // only needed when pictures are temporarily iconic
	IMPORT_C void UpdatePictureFormatL(TInt aStartPos,TInt aLength); // ditto
	IMPORT_C void SetDefaultIconicDoorSize(const TSize& aSize); // doesn't affect existing doors
	IMPORT_C const TSize& DefaultIconicDoorSize() const;
	IMPORT_C void UpdatePictureSizeL();
	IMPORT_C void UpdatePictureSizeL(TInt aStartPos,TInt aLength);
	IMPORT_C void SetParserObserver(MEikRichTextEditorParserObserver* aObserver);
public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ActivateL();
public: // from CEikEdwin
	IMPORT_C void CopyDocumentContentL(CGlobalText& aInText,CGlobalText& aOutText);
protected:
	enum // internal flags
		{
		ECropFromLeft			=0x00010000,
		ECropFromRight			=0x00020000,
		ECropFromTop			=0x00040000,
		ECropFromBottom			=0x00080000,
		EReEditingObject		=0x00100000
		};
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
protected: // from MEditObserver
	IMPORT_C void EditObserver(TInt aStartEdit,TInt aEditLength);

private: // from CoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void Reserved_2();
private: // from CEikEdwin
	IMPORT_C void HandleTextPastedL(TInt aStartPos,TInt& aLength);
	IMPORT_C void Reserved_3();
private: // from MApaEmbeddedDocObserver
	IMPORT_C void NotifyExit(TExitMode aMode);
private: // from MRichTextStoreResolver
	IMPORT_C const CStreamStore& StreamStoreL(TInt aPos) const;
private: // from MPictureFactory
	IMPORT_C void NewPictureL(TPictureHeader& aHdr,const CStreamStore& aDeferredPictureStore) const;

private:
	void CommonConstructL();
	static TInt InsertEmbeddedDocL(TAny *aThis);
	static TInt DeleteEmbeddedDoc(TAny *aThis);
	static TInt UpdateEmbeddedDocL(TAny* aThis);
	static TInt TryDeleteEmbeddedDocL(TAny *aThis);
	void InsertPictureL(const TPictureHeader& aPictureHeader);
	void DoInsertPictureL(TBool& aFormatHasChanged,const TPictureHeader& aPictureHeader);
	void DoReEditObjectL(TInt aDocPos);
	void RoomForObjectL();
	void InsertObjectL(CApaDocument* aDoc,TObjectFormat aFormat);
	void SetTextObserver(CRichText& aText);
	inline void DoReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType);
protected:
	TSize iDefaultIconicDoorSize;
private:
	TPictureHeader iEmbeddedDoc;
	CIdle* iEmbeddedDocUpdate;
	CBufStore* iBufStore;
	CEikParserManager* iParserManager;
private:
	friend class CEikParserManager;
	};

class MEikRichTextEditorParserObserver
	{
public:
	virtual void HandleCursorOverParserL(const TDesC& aDoItText)=0;
	};

inline void CEikRichTextEditor::DoReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType)
	{ReportEdwinEventL(aEventType);}

#endif
