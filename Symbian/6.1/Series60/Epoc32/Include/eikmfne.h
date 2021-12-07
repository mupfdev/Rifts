// EIKMFNE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMFNE_H__)
#define __EIKMFNE_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__COEDEF_H__)
#include <coedef.h>
#endif

#if !defined(__COEINPUT_H__)
#include <coeinput.h>
#endif

// For MEikCalendarObserver
#if !defined(__EIKCAL_H__)
#include <eikcal.h>	
#endif

//

class CEikonEnv;
class CTimeEditor;
class CDateEditor;

//

class CEikMfneField : public CBase
	{
public:
	enum THighlightType
		{
		EInverseVideo,
		ECursor
		};
protected:
	IMPORT_C CEikMfneField();
public:
	void Draw(CWindowGc& aGc, const CFont& aFont, const TPoint& aTopLeft) const;
	TInt WidthInPixels(const CFont& aFont) const;
	TInt DistanceFromStartOfFieldToEndOfTextInPixels(const CFont& aFont) const;
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize)=0;
	virtual TCoeInputCapabilities InputCapabilities() const=0;
	IMPORT_C virtual TBool IsEditable() const;
	IMPORT_C virtual TBool IsValid() const;
	// these functions may only be called if IsEditable returns ETrue - all TBool&/TInt& parameters in these functions must be first set to EFalse/0 by the caller
	IMPORT_C virtual THighlightType HighlightType() const;
	IMPORT_C virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
	IMPORT_C virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
protected:
	IMPORT_C void HandleLeftOrRightArrow(TChar aKey, TBool& aDataAltered, TInt& aHighlightIncrement);
private:
	virtual const TDesC& Text() const=0;
protected:
	TInt iMinimumWidthInPixels;
	};

//

class CEikMfneSeparator : public CEikMfneField
	{
private:
	CEikMfneSeparator(HBufC* aText);
public:
	IMPORT_C virtual ~CEikMfneSeparator();
	IMPORT_C static CEikMfneSeparator* NewL(TResourceReader& aResourceReader);
	IMPORT_C static CEikMfneSeparator* NewL(HBufC* aText); // ownership of aText is transferred when everything that can leave has successfully been done
	IMPORT_C void SetText(HBufC* aText); // allows later transfer of ownership of text - can only be called if aText was previously NULL
private: // framework
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
	virtual TCoeInputCapabilities InputCapabilities() const;
	virtual const TDesC& Text() const;
private:
	HBufC* iText;
	};

//

class CEikMfneNumber : public CEikMfneField
	{
public:
	enum
		{
		EFillWithLeadingZeros			=0x1,
		EPreserveOldWidthBeforeEditing	=0x2,
		ERepresentsYear					=0x4,
		EPublicallySettableFlags		=EFillWithLeadingZeros|EPreserveOldWidthBeforeEditing|ERepresentsYear
		};
private:
	enum
		{
		EIsBeingEditedWithCursor		=0x8
		};
private:
	CEikMfneNumber(TInt aMinimumValue, TInt aMaximumValue, TUint32 aFlags);
	void ConstructL();
public:
	IMPORT_C virtual ~CEikMfneNumber();
	IMPORT_C static CEikMfneNumber* NewL(const CFont& aFont, TResourceReader& aResourceReader);
	IMPORT_C static CEikMfneNumber* NewL(const CFont& aFont, TInt aMinimumValue, TInt aMaximumValue, TInt aInitialValue, TUint32 aFlags);
	IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue, const CFont& aFont); // only values inside the initial minimum and maximum are permitted
	IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;
	IMPORT_C void SetValue(TInt aValue, const CFont& aFont);
	IMPORT_C TInt Value() const;
	IMPORT_C virtual TBool IsValid() const;
public:
	TBool IsTextNull() const;
private: // framework
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
	virtual TCoeInputCapabilities InputCapabilities() const;
	virtual TBool IsEditable() const;
	virtual THighlightType HighlightType() const;
	virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
	virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
	virtual const TDesC& Text() const;
private:
	TInt MaximumNumberOfDigits() const;
	TInt NumberOfDigits() const;
	void SetTextToValue(TInt aValue, const CFont& aFont);
	TInt ValueFromText() const;
	TBool ConvertsIntoValidValue(TInt& aValue) const;
private:
	TInt iMinimumValue;
	TInt iMaximumValue;
	TInt iMaxDigits;
	TUint32 iFlags;
	HBufC* iText;
	TChar iNudgeCharMinus;
	TChar iNudgeCharPlus;
	TInt iMaxDigitsMinimumValue;
    TInt iMaxDigitsMaximumValue;
	};

//

class CEikMfneSymbol : public CEikMfneField
	{
public:
	class CItem : public CBase
		{
	private:
		CItem(TInt aId, TChar aKeyToMatch, HBufC* aText);
	public:
		IMPORT_C virtual ~CItem();
		IMPORT_C static CItem* NewL(TResourceReader& aResourceReader);
		IMPORT_C static CItem* NewL(TInt aId, TChar aKeyToMatch, HBufC* aText); // ownership of aText is transferred when everything that can leave has successfully been done
		IMPORT_C void SetText(HBufC* aText); // allows later transfer of ownership of text - can only be called if aText was previously NULL
	private:
		friend class CEikMfneSymbol;
	private:
		TInt iId;
		TCharF iKeyToMatch;
		HBufC* iText;
		};
private:
	CEikMfneSymbol(TInt aNumSymbolicItems);
public:
	IMPORT_C virtual ~CEikMfneSymbol();
	IMPORT_C static CEikMfneSymbol* NewL(TResourceReader& aResourceReader);
	IMPORT_C static CEikMfneSymbol* NewL(TInt aNumSymbolicItems);
	IMPORT_C void AddSymbolicItem(CItem* aSymbolicItem, TBool aMakeCurrent); // to be called by container only if not constructed from resource - ownership of aSymbolicItem is transferred to "this"
	IMPORT_C void SetCurrentSymbolicItemToId(TInt aId);
	IMPORT_C TInt IdOfCurrentSymbolicItem() const;
private: // framework
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
	virtual TCoeInputCapabilities InputCapabilities() const;
	virtual TBool IsEditable() const;
	virtual THighlightType HighlightType() const;
	virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
	virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
	virtual const TDesC& Text() const;
private:
	TInt iNumSymbolicItems;
	TInt iCurrentSymbolicItem;
	CItem** iSymbolicItems;
	};

//

class CEikMfne : public CEikBorderedControl
	{
public:
	// miscellaneous functions
	IMPORT_C CEikMfne();
	IMPORT_C virtual ~CEikMfne();
	IMPORT_C void CreateFieldArrayL(TInt aNumFields); // to be called by container only if not constructed from resource
	IMPORT_C void AddField(CEikMfneField* aField); // to be called by container only if not constructed from resource - ownership of aField is transferred to "this"
	IMPORT_C TMargins BorderMargins() const;
	IMPORT_C void DrawNowAndLeaveWithTimeDateFormatInfoMsgL(TInt aResourceId, const TTime& aTimeDate) const;
	IMPORT_C CEikMfneField* Field(TInt aField) const;
public:
	// some utility functions which other classes may find useful
	IMPORT_C static TTime ReadTime(TResourceReader& aResourceReader);
	IMPORT_C static TTime ReadDate(TResourceReader& aResourceReader);
	IMPORT_C static TTime ReadTimeAndDate(TResourceReader& aResourceReader);
	IMPORT_C static TTimeIntervalSeconds ReadDuration(TResourceReader& aResourceReader);
	IMPORT_C static TTimeIntervalSeconds ReadTimeOffset(TResourceReader& aResourceReader);
	IMPORT_C static TTimeIntervalSeconds Convert(const TTime& aTime);
	IMPORT_C static TTime Convert(const TTimeIntervalSeconds& aTimeIntervalSeconds);
    //
    inline TInt CurrentField() const;
    inline TInt NumFields() const;

public: // AVKON addition
    IMPORT_C void SetMfneAlignment(TInt aAlignment);
    IMPORT_C void SetUpAndDownKeysConsumed(TBool aConsume);

    // Highlights a field
    void HighlightField(  TInt aFieldPosition );

	IMPORT_C const CFont* Font() const;
	IMPORT_C void SetFont(const CFont* aFont);

public:	// from CCoeControl
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	IMPORT_C virtual void PrepareForFocusLossL();
	IMPORT_C virtual TSize MinimumSize();
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
protected:
	// framework
	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	// miscellaneous functions
	IMPORT_C void HandleInteraction(TBool aHandleDeHighlight, TInt aNewCurrentField, TInt aOldWidthInPixelsOfOldCurrentField,
								CEikMfneField::THighlightType aOldHighlightTypeOfOldCurrentField, TBool& aDataAltered, TBool& aError);
	IMPORT_C virtual void FieldIsAboutToBeDeHighlighted(CEikMfneField* aField, TBool& aDrawAllFields); // first occurrence of this virtual function - does nothing by default
	IMPORT_C TSize MfneSize() const;
	IMPORT_C TSize MfneSize(TBool aShrinkToMinimumSize);

private:
	// framework
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	// new virtual functions
	IMPORT_C virtual void CreatePopoutIfRequiredL();
	// miscellaneous functions
	void DrawRange(CWindowGc& aGc, TInt aFirstField, TInt aLastField) const;
	CWindowGc& PreparedGc() const;
	void SetGcToNormalVideo(CWindowGc& aGc) const;
	void SetGcToInverseVideo(CWindowGc& aGc) const;
	void SetGcToDimmedVideo(CWindowGc& aGc) const;
	void DrawCursor();
	void HideCursor();
	IMPORT_C void Reserved_2();
	IMPORT_C virtual void CEikMfne_Reserved();
private:
	enum {ENullIndex=KMaxTInt};
private:
	TInt iNumFields;
	TInt iCurrentField;
	CEikMfneField** iFields;
	TInt  iSpare;
	const CFont* iFont;
    TInt iAlignment;
    TBool iConsumeUpAndDownKeys;
	};



inline TInt CEikMfne::CurrentField() const
    {
    return(iCurrentField);
    }

inline TInt CEikMfne::NumFields() const
    {
    return(iNumFields);
    }

//

class CEikNumberEditor : public CEikMfne
	{
public:
	// miscellaneous functions
	IMPORT_C CEikNumberEditor();
	IMPORT_C void ConstructL(TInt aMinimumValue, TInt aMaximumValue, TInt aInitialValue); // to be called by container only if not constructed from resource
	IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial minimum and maximum are permitted
	IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;
	IMPORT_C void SetNumber(TInt aNumber);
	IMPORT_C TInt Number() const; // can only be called if PrepareForFocusLossL() succeeded
	// framework
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
private:
	IMPORT_C virtual void CEikMfne_Reserved();

private:
	// none of these pointers owns anything
	CEikMfneNumber* iNumber;
	TInt iSpare;
	};


//

struct SEikRange
	{
	TInt iLowerLimit;
	TInt iUpperLimit;
	};

//

class CEikRangeEditor : public CEikMfne
	{
public:
	// miscellaneous functions
	IMPORT_C CEikRangeEditor();
	// ConstructL to be called by container only if not constructed from resource, also ownership of aSeparatorText is transferred when everything that can leave has successfully been done
	IMPORT_C void ConstructL(TInt aMinimumValue, TInt aMaximumValue, const SEikRange& aInitialRange, HBufC* aSeparatorText);
	IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial minimum and maximum are permitted
	IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;
	IMPORT_C void SetRange(const SEikRange& aRange);
	IMPORT_C SEikRange Range() const; // can only be called if PrepareForFocusLossL() succeeded
	// framework
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
private:
	virtual void FieldIsAboutToBeDeHighlighted(CEikMfneField* aField, TBool& aDrawAllFields);
	IMPORT_C virtual void CEikMfne_Reserved();

private:
	// none of these pointers owns anything
	CEikMfneNumber* iLowerLimit;
	CEikMfneNumber* iUpperLimit;
	TInt iSpare;
	};


//

class CEikTTimeEditor : public CEikMfne
	{
public:
	virtual void SetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime)=0;
	virtual void GetMinimumAndMaximum(TTime& aMinimumTime, TTime& aMaximum) const=0;
	virtual void SetTTime(const TTime& aTime)=0;
	virtual TTime GetTTime() const=0; // can only be called if PrepareForFocusLossL() succeeded
	};


class CEikTimeEditor : public CEikTTimeEditor
	{
public:
	// miscellaneous functions
	IMPORT_C CEikTimeEditor();
	IMPORT_C virtual ~CEikTimeEditor();
	IMPORT_C void ConstructL(const TTime& aMinimumTime, const TTime& aMaximumTime, const TTime& aInitialTime, TUint32 aFlags); // to be called by container only if not constructed from resource
	IMPORT_C void SetTime(const TTime& aTime);
	IMPORT_C TTime Time() const;
	// from CEikTTimeEditor
	IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime); // only values inside the initial minimum and maximum are permitted
	IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumTime, TTime& aMaximumTime) const;
	// from CCoeControl
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C virtual void PrepareForFocusLossL();
private:
	// from CEikTTimeEditor
	virtual void SetTTime(const TTime& aTime);
	virtual TTime GetTTime() const; // can only be called if PrepareForFocusLossL() succeeded
private:
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime);
	IMPORT_C virtual void CEikMfne_Reserved();
private:
	CTimeEditor* iTimeEditor;
	TTime iMinimumTime;
	TTime iMaximumTime;
	TInt iSpare;
	};


//

// note: TDateTime uses zero based day numbers, so -1 on the day field
#define KAknMinimumDate (TTime(TDateTime(0001, EJanuary, 1-1, 0, 0, 0, 0)))
#define KAknMaximumDate (TTime(TDateTime(9999, EDecember, 31-1, 23, 59, 59, 999999)))

class CEikDateEditor : public CEikTTimeEditor, private MEikCalendarObserver
	{
public:
	// miscellaneous functions
	IMPORT_C CEikDateEditor();
	IMPORT_C virtual ~CEikDateEditor();
	IMPORT_C void ConstructL(const TTime& aMinimumDate, const TTime& aMaximumDate, const TTime& aInitialDate, TBool aWithoutPopoutCalendar); // to be called by container only if not constructed from resource
	IMPORT_C void SetDate(const TTime& aDate);
	IMPORT_C TTime Date() const;
	// from CEikTTimeEditor
	IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumDate, const TTime& aMaximumDate); // only values inside the initial minimum and maximum are permitted
	IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumDate, TTime& aMaximumDate) const;
	// from CCoeControl
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C virtual void PrepareForFocusLossL();

private:
	// from CEikMfne
	virtual void CreatePopoutIfRequiredL();
	// from CEikTTimeEditor
	virtual void SetTTime(const TTime& aDate);
	virtual TTime GetTTime() const; // can only be called if PrepareForFocusLossL() succeeded
private:
	// from MEikCalendarDialogObserver
	virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const;
	virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate);
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTime& aMinimumDate, const TTime& aMaximumDate);
	IMPORT_C virtual void CEikMfne_Reserved();

private:
	CDateEditor* iDateEditor;
	TTime iMinimumDate;
	TTime iMaximumDate;
	TInt iSpare;
	};


//

class CEikTimeAndDateEditor : public CEikTTimeEditor, private MEikCalendarObserver
	{
public:
	// miscellaneous functions
	IMPORT_C CEikTimeAndDateEditor();
	IMPORT_C virtual ~CEikTimeAndDateEditor();
	// ConstructL to be called by container only if not constructed from resource, also ownership of aInterveningText is transferred when everything that can leave has successfully been done
	IMPORT_C void ConstructL(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate, const TTime& aInitialTimeAndDate, TUint32 aFlags, HBufC* aInterveningText=NULL);
	IMPORT_C void SetTimeAndDate(const TTime& aTimeAndDate);
	IMPORT_C TTime TimeAndDate() const;
	// from CEikTTimeEditor
	IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate); // only values inside the initial minimum and maximum are permitted
	IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumTimeAndDate, TTime& aMaximumTimeAndDate) const;
	// from CCoeControl
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C virtual void PrepareForFocusLossL();
private:
	// from CEikMfne
	virtual void CreatePopoutIfRequiredL();	
	IMPORT_C virtual void CEikMfne_Reserved();
	// from CEikTTimeEditor
	virtual void SetTTime(const TTime& aTimeAndDate);
	virtual TTime GetTTime() const; // can only be called if PrepareForFocusLossL() succeeded
private:
	// from MEikCalendarDialogObserver
	virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const;
	virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate);
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate);
private:
	CTimeEditor* iTimeEditor;
	CDateEditor* iDateEditor;
	TTime iMinimumTimeAndDate;
	TTime iMaximumTimeAndDate;
	TInt iSpare;
	};


//

class CEikDurationEditor : public CEikMfne
	{
public:
	// miscellaneous functions
	IMPORT_C CEikDurationEditor();
	IMPORT_C virtual ~CEikDurationEditor();
	IMPORT_C void ConstructL(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration, const TTimeIntervalSeconds& aInitialDuration, TUint32 aFlags);
	IMPORT_C void SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration); // only values inside the initial minimum and maximum are permitted
	IMPORT_C void GetMinimumAndMaximum(TTimeIntervalSeconds& aMinimumDuration, TTimeIntervalSeconds& aMaximumDuration) const;
	IMPORT_C void SetDuration(const TTimeIntervalSeconds& aDuration);
	IMPORT_C TTimeIntervalSeconds Duration() const; // can only be called if PrepareForFocusLossL() succeeded
	// framework
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C void PrepareForFocusLossL();
private:
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration);
	IMPORT_C virtual void CEikMfne_Reserved();
private:
	CTimeEditor* iTimeEditor;
	TTimeIntervalSeconds iMinimumDuration;
	TTimeIntervalSeconds iMaximumDuration;
	TInt iSpare;
	};


class CEikTimeOffsetEditor : public CEikMfne
	{
public:
	// miscellaneous functions
	IMPORT_C CEikTimeOffsetEditor();
	IMPORT_C virtual ~CEikTimeOffsetEditor();
	IMPORT_C void ConstructL(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset, const TTimeIntervalSeconds& aInitialTimeOffset, TUint32 aFlags);
	IMPORT_C void SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset); // only values inside the initial minimum and maximum are permitted
	IMPORT_C void GetMinimumAndMaximum(TTimeIntervalSeconds& aMinimumTimeOffset, TTimeIntervalSeconds& aMaximumTimeOffset) const;
	IMPORT_C void SetTimeOffset(const TTimeIntervalSeconds& aTimeOffset);
	IMPORT_C TTimeIntervalSeconds TimeOffset() const; // can only be called if PrepareForFocusLossL() succeeded
	// framework
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C void PrepareForFocusLossL();
private:
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset);
	IMPORT_C virtual void CEikMfne_Reserved();
private:
	CTimeEditor* iTimeEditor;
	TTimeIntervalSeconds iMinimumTimeOffset;
	TTimeIntervalSeconds iMaximumTimeOffset;
	// none of these pointers owns anything
	CEikMfneSymbol* iSign;
	TInt iSpare;
	};




//
// Longitude and Latitude editors removed 2.4.2002:

enum
	{
	EEikOrientationNorthSouth   =0x1000,
	EEikOrientationWestEast     =0x2000,
	EEikOrientationMask=EEikOrientationNorthSouth|EEikOrientationWestEast
	};


enum
	{
	EEikDirectionNegative,
	EEikDirectionPositive,
	EEikDirectionMask=EEikDirectionNegative|EEikDirectionPositive
	};


enum TEikCompass
	{
	EEikCompassNorth=EEikOrientationNorthSouth|EEikDirectionNegative,
	EEikCompassSouth=EEikOrientationNorthSouth|EEikDirectionPositive,
	EEikCompassEast=EEikOrientationWestEast|EEikDirectionNegative,
	EEikCompassWest=EEikOrientationWestEast|EEikDirectionPositive
	};


struct SEikDegreesMinutesDirection
	{
	TInt iDegrees;
	TInt iMinutes;
	TInt iSeconds;
	TEikCompass iDirection;
	};

#endif
// End of file
