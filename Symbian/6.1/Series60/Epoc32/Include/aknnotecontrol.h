/*
* ============================================================================
*  Name     : AknNoteControl.h
*  Part of  : Avkon
*
*  Description:
* 
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/


#ifndef AKNNOTECONTROL_H
#define AKNNOTECONTROL_H

#include <coecntrl.h>
#include "aknutils.h"

#include <aknprogresstimer.h>
#include <aknbitmapanimation.h>

class CEikImage;
class CEikLabel;
class CEikProgressInfo;
class CAknNoteAttributes;
class CAknTextControl;

/**
 * The control for a note dialog.
 *
 * Manage layout of elements in a note dialog:- the text, the image and
 * animation, the progress bar.
 *
 * @see CAknNoteDialog, CAknNoteAttributes, CAknText
 */
class CAknNoteControl : public CCoeControl 
{
friend CAknNoteAttributes;

public:	
	IMPORT_C CAknNoteControl();
	IMPORT_C virtual ~CAknNoteControl();
	void ConstructFromResourceL(TResourceReader& aRes);

public:
    IMPORT_C void SetImageL(CEikImage* aImage);
	IMPORT_C void SetAnimationL(TInt aResource);
    IMPORT_C void SetIconL(CEikImage* aIcon);
	
	IMPORT_C void SetFinalProgressValue(TInt aValue);
	IMPORT_C TInt IncrementBarsAndDraw(TInt aIncrement);
	IMPORT_C void CreateProgressBarL();
	IMPORT_C CEikProgressInfo* GetProgressInfo();
	
	IMPORT_C void StartAnimationL();
	IMPORT_C TInt CancelAnimation();

	IMPORT_C void ResetText();
	IMPORT_C void SetTextL(const TDesC& aText);
	IMPORT_C void SetTextL(const TDesC& aText,TInt aLineNum);
	
	IMPORT_C void SetTextNumberL(const TInt aNumber);
	IMPORT_C void SetTextPluralityL(const TBool aIsPlural);
	IMPORT_C TInt NumberOfLines() const;

public:
	IMPORT_C void Layout();
	IMPORT_C TAknWindowLineLayout WindowLayout() const;

	IMPORT_C TInt NoteHeight() const;
	IMPORT_C TInt NoteWidth() const;

public:
	//Interface to CAknNoteDialog
	TSize MinimumSize();
	CAknNoteAttributes* Attributes() const;
	void Reset();

public:
		/**
		 * Manage indexes into LAF tables
		 */
		class TIndex 
		{	
		public:		
			TIndex(TInt aNumberOfLines, TBool aHasNti = EFalse, TSize aImageSize = TSize(0,0));	
		
		public:	
			TInt Lines() const;	
			
		public:	
			TInt WNPWindowTextsLine1(TInt aLineNum) const;

			TInt NWIPWindowTextsLine1L(TInt aLineNum) const;
			TInt NWIPWindowTextsLine1R(TInt aLineNum) const;
			TInt NWIPWindowTextsLine1B(TInt aLineNum) const;
			TInt NWIPWindowTextsLine1W(TInt aLineNum) const;
			
			TInt PopupNoteWindow() const;
			TInt PopupNoteWaitWindow() const;

		private:	
			void SelfTest() const;	
			TInt ImageWidthIndex() const;
			TInt ImageHeightIndex() const;
			TInt HasNtiIndex() const;

		private:	
			TInt  iNumberOfLines;
			TBool iHasNti;
			TSize iImageSize;
		};	

private:
	//COECONTROL METHODS
	void Draw(const TRect& aRect) const;
	void SizeChanged();
	void DoLayout();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt anIndex) const;
	
	//LAYOUT METHODS
	TInt NumberTypeIndicationIndex() const;
	TInt ImageWidthIndex() const;

	TInt AnimationIndex();
	void AnimationNoteLayout();

	//Layout for general notes
	void GeneralNoteLayout();
	void GeneralNoteLabelLayout();
	void GeneralNoteIconLayout();

	//Layout for progress and wait notes
	void ProgressNoteLayout();
	void ProgressNoteLabelLayout();
	void ProgressNoteProgressBarLayout();
	void ProgressNoteIconLayout();
	void ProgressNoteNumberTypeIndicationLayout();

	//Layout for image notes
	void ImageNoteLayout();
	void ImageNoteLabelLayout();
	void ImageNoteImageLayout();
	void ImageNoteShadowLayout();
	void ImageNoteNumberTypeIndicationLayout();

	TAknWindowLineLayout GetImageLayout(const TSize& aSize); 
	TAknWindowLineLayout GetImageShadowLayout(const TSize& aSize); 

	TRect LayoutRect() const;
	void SetLineWidthsL();

	void CreateDefaultImageL();
	void ReduceImageIfNeeded();

	void ParseTextL();

private:
	CAknTextControl*    TextControl() const; 

	CEikImage* Image() const; 
	CEikImage* Icon() const; 
	
	CEikProgressInfo* ProgressBar() const; 
	
	CAknProgressTimer* Timer() const; 
	CAknBitmapAnimation* Animation() const; 
	
	TBitFlags&  Flags() const; 

private:
	TInt                iNoteLayout;
	TAknLayoutRect      iShadowRect;
	TBool               iImageHasShadow;
	
	CAknNoteAttributes*  iAttributes;
	CArrayFixFlat<TInt>* iLineWidths;

public:
	/**
	 * @deprecated - Following methods are deprecated by SetTextL() methods
	 */
	IMPORT_C void SetDynamicTextL(const TDesC& aText);
	IMPORT_C void UpdateAndFormatLabelsL(const TDesC& aLabels);
	IMPORT_C void UpdateLabelsL(const TDesC& aLabel1, const TDesC& aLabel2=KNullDesC, const TDesC& aLabel3=KNullDesC);
	IMPORT_C void UpdateLabels(const TDesC& aLabel1, const TDesC& aLabel2=KNullDesC, const TDesC& aLabel3=KNullDesC);
	IMPORT_C void SetLabelReserveLengthL(TInt aLength1=0, TInt aLength2=0, TInt aLength3=0);
	
	/**
	 * @deprecated - Following methods were never implemented 
	 * and currently panic
	 */
	IMPORT_C void SetNumberOfNotificationBorders(TInt aNumber);
	IMPORT_C void SetImageNoteThumbnailSize();

	/**
	 * @deprecated - use SetTextNumberL
	 */
	IMPORT_C void SetDynNumberL(const TInt aNumber);

	/**
	 * @deprecated - use SetTextPluralityL
	 */
	IMPORT_C void SetPluralityL(const TBool isPlural);

	/**
	 * @deprecated - Use NumberOfLines()
	 */
	IMPORT_C TInt NumberOfLabelLines() const;
	};

#endif // AKNNOTECONTROL_H
