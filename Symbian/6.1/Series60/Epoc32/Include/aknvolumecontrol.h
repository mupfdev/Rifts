/*
* ============================================================================
*  Name     : CAknVolumeControl from Aknvolumecontrol.h
*  Part of  : Avkon
*
*  Description:
*     Volume editor class
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNVOLUMECONTROL_H
#define AKNVOLUMECONTROL_H

// CLASS DECLARATION
class CAknVolumeControl : public CCoeControl
	{
public:
	IMPORT_C CAknVolumeControl();
	IMPORT_C ~CAknVolumeControl();
	IMPORT_C void SetValue(TInt aValue);
	IMPORT_C TInt Value() const;
	
public: // from CCoeControl

    TSize MinimumSize();
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    /**
    *  Returns volume bitmap to "list pane for setting item" 
    *  (setting option item volume graphic). Ownership of the returned bitmap
    *  is transfered to the caller.
    *
    * @param  aValue Current value (1-10)
    * @return Volume bitmap. Ownership of the bitmap is transfered to the caller
    */
    IMPORT_C static CFbsBitmap* CreateBitmapL(TInt aValue);

protected: // from CCoeControl
	void SizeChanged();
	void Draw(const TRect& aRect) const;

private:
	void SetVolumeLayout(TInt aStyle);

private:	
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMaskBitmap;
	TPoint iStartPos;
	TPoint iEndPos;
	TPoint iBmpPos;
	TInt iValue;
	TInt iStyle;
};

#endif	// AKNVOLUMECONTROL_H
            
// End of File
