// EIKLABEL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKLABEL_H__)
#define __EIKLABEL_H__


#if !defined(__EIKALIGN_H__)
#include <eikalign.h>
#endif

#if !defined(__COECCNTX_H__)
#include <coeccntx.h>
#endif

class CEikLabel : public CEikAlignedControl, public MCoeControlContext
	{
public:  // new functions
	IMPORT_C ~CEikLabel();
	IMPORT_C CEikLabel();
public:  // from CCoeControl
	IMPORT_C TSize MinimumSize();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C void HandleResourceChange(TInt aType);			// not available before Release 005u
protected: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
protected: // from MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const; // Do not use
public:  
	enum TTextEmphasis
		{
		ENoEmphasis		 =0x00,
		EPartialEmphasis =0x10,
		EFullEmphasis	 =0x20
		};
public:  // new functions
	IMPORT_C void SetTextL(const TDesC& aText);
	inline const TDesC* Text() const;
	IMPORT_C void CropText();
	IMPORT_C void SetBufferReserveLengthL(TInt aLength);
	IMPORT_C void SetFont(const CFont* aFont);
	inline const CFont* Font() const;
	IMPORT_C void SetEmphasis(TTextEmphasis aEmphasis);
	IMPORT_C void SetPixelGapBetweenLines(TInt aGap);
	IMPORT_C TInt PixelGapBetweenLines() const;
	inline TBool IsUnderlined() const;
	IMPORT_C void SetUnderlining(TBool aUnderLining);
	inline TBool IsStrikethrough() const;
	IMPORT_C void SetStrikethrough(TBool aStrikethrough);
	IMPORT_C TSize CalcMinimumSize(TPtrC& aText) const;
	inline TUint8 NumberOfLines();
	IMPORT_C TInt BufferReserveLength() const;

protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	IMPORT_C void Reserved_2();
private: // new functions
	TInt HeightInPixels() const;
	TInt WidthInPixels(TPtrC& aText) const;
	void SetupGcForEmphasis(CGraphicsContext& aGc) const;
protected:
	enum TLabelFlags
		{
		EUnderlining=0x02,
		EStrikethrough=0x04
		};
	HBufC* iText;
	const CFont* iFont;
	TUint8 iNumberOfLines;
	TUint8 iLabFlags;
	TInt iGapBetweenLines;
private:
	TInt iReserveLength;
	TInt iSpare;
	};


inline const TDesC* CEikLabel::Text() const
	{ return(iText); }
inline const CFont* CEikLabel::Font() const
	{ return(iFont); }
inline TBool CEikLabel::IsUnderlined() const
    {return iLabFlags&EUnderlining;}
inline TBool CEikLabel::IsStrikethrough() const
    {return iLabFlags&EStrikethrough;}
inline TUint8 CEikLabel::NumberOfLines()
	{return iNumberOfLines;}	

#endif
