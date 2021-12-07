// EIKPROGI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKPROGI_H__)
#define __EIKPROGI_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKON_HRH__)
#include <eikon.hrh>
#endif

class TGulBorder;

class CEikProgressInfo : public CEikBorderedControl
	{
public:
	struct SInfo
		{
		TEikProgressTextType iTextType;
		TInt iSplitsInBlock;
		TInt iFinalValue;
		TInt iWidth;
		TInt iHeight;
		};


	struct SLayout
		{
		TRgb iFillColor;
		TRgb iEmptyColor;
		TRgb iFillTextColor;
		TRgb iEmptyTextColor;
		const CFont* iFont;
		TInt iGapBetweenBlocks;
		};



	IMPORT_C ~CEikProgressInfo();
	IMPORT_C CEikProgressInfo();
	IMPORT_C CEikProgressInfo(const SInfo& aProgInfo);

	IMPORT_C void IncrementAndDraw(TInt aInc);
	IMPORT_C void SetAndDraw(TInt aValue);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void SetLayout(const SLayout& aLayout);
	IMPORT_C void SetBorder(const TGulBorder& aBorder);
	IMPORT_C void SetFinalValue(TInt aFinalValue);
	IMPORT_C void ConstructL(); // AKNLAF

	inline const SInfo& Info() const { return(iInfo); }
	inline const SLayout& Layout() const { return(iLayout); }
	inline TInt CurrentValue() const { return(iCurrentValue); }
protected:
	IMPORT_C virtual const TDesC* EvaluateText(TDes& aTextBuf) const;
public: // from CCoeControl
	IMPORT_C void ActivateL();
	IMPORT_C TSize MinimumSize();
	IMPORT_C void SizeChanged();
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void Reserved_2();	
private: // internal use
	void Construct();
	void CheckSizeCalculated();
	void DrawPartial()const; // AKNLAF
	void DrawProgressBarForeground(CWindowGc& aGc) const; //AKNLAF
	void DrawProgressBarBackground(CWindowGc& aGc) const; //AKNLAF
	TInt FilledWidth() const; //AKNLAF

private:
	SInfo iInfo;
	SLayout iLayout;
	TInt iCurrentValue;
	TBool iHeightWasSupplied;
	CFbsBitmap* iBitmap; // AKNLAF
	CFbsBitmap* iBackgroundBitmap; // AKNLAF
	CFbsBitmap* iBitmapMask; // AKNLAF
	CFbsBitmap* iBackgroundBitmapMask; // AKNLAF
	};



#endif
