/*
* ============================================================================
*  Name     : aknnavilabel.h
*  Part of  : AVKON
*
*  Description:
*   Label control to the status pane's navigation pane.
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNNAVILABEL_H
#define AKNNAVILABEL_H

#include <coecntrl.h>

/**
 * Label control to the status pane's navigation pane.
 */
class CAknNaviLabel : public CCoeControl
	{
public:
    enum TNaviLabelType
        {
        ENavigationLabel,
        EAdditionalInfoLabel,
        EHintText
        };

public:  // new functions

    /**
    * Constructor.
    */
    IMPORT_C CAknNaviLabel();

    /**
    * Destructor.
    */
    IMPORT_C ~CAknNaviLabel();

    /**
     * Set type of the label.
     * @param aNaviLabelType navigation label type.
     */
    IMPORT_C void SetNaviLabelType(TNaviLabelType aNaviLabelType);

    /**
     * Returns type of the label.
     * @return navigation label type.
     */
    IMPORT_C TNaviLabelType NaviLabelType();

    /**
     * Sets navigation label text.
     * @param aText reference to the navigation text.
     */
    IMPORT_C void SetTextL(const TDesC& aText);

    /**
     * Returns the current label text.
     * @return label text. Ownership of the text is not transfered.
     */
    inline const TDesC* Text() const;

protected: // from CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
    * From CCoeControl.  Draw a control.  
    *
    * @param aRect The region of the control to be redrawn.   
    */
    IMPORT_C void Draw(const TRect& aRect) const;

private:
	HBufC* iText;
    HBufC* iTruncatedText;
    const CFont* iFont;
    TInt iLeftMargin;
    TInt iRightMargin;
    TInt iBaseline;
    TInt iRightOffset;
    TInt iColor; 

    TNaviLabelType iLabelType;
	};


inline const TDesC* CAknNaviLabel::Text() const
	{ return(iText); }


#endif // AKNNAVILABEL_H
