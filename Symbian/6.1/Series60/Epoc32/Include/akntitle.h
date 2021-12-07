/*
* ============================================================================
*  Name     : akntitle.h
*  Part of  : AVKON
*
*  Description:
*      A default control in the status pane's title pane.
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNTITLE_H
#define AKNTITLE_H

#include <coecntrl.h>
#include <coeccntx.h>

class CEikLabel;
class CEikImage;


/**
 * A default control in the status pane's title pane.
 */
class CAknTitlePane : public CCoeControl, public MCoeControlContext
	{
public:
    /**
    * Constructor.
    */
    IMPORT_C CAknTitlePane();

    /**
    * Destructor.
    */
    IMPORT_C ~CAknTitlePane();
    
    /**
    * 2nd phase constructor.
    */
    IMPORT_C void ConstructL();
    
    /**
    * Read title pane data from resource file and show it in the status pane's title pane.
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
    /**
    * Set a text and show it in the status pane's title pane. Descriptor
    * is copied to the title pane control and ownership of the original descriptor
    * leaves to the application.
    *
    * @param aText Text to be shown on the title pane.
    */
    IMPORT_C void SetTextL(const TDesC& aText);
    
    /**
    * Sets text to the title pane.
    * @param aText	new text. This object takes ownership of aText.
    */
    IMPORT_C void SetText(HBufC* aText);
    
    /**
    * Returns text currently in the status pane's title pane. Ownership is not 
    * transferred.
    * @return text currently shown in the title pane.
    */
    inline const TDesC* Text() const;
    
    /**
    * Set a picture to the title pane and show it in the status pane's title pane. 
    * Title pane object takes ownership of the picture.
    * If NULL bitmap is passed, previously set image is shown.
    * @param aBitmap bitmap to the title pane.
    * @parma aMaskBitmap mask of the bitmap.
    */
    IMPORT_C void SetPicture(const CFbsBitmap* aBitmap, const CFbsBitmap* aMaskBitmap = NULL);
    
    /**
    * Set a picture from file and show it in the status pane's title pane.
    * @param aFileName name of the bitmap file.
    * @param aMainId id of the bitmap in the bitmap file.
    * @param aMaskId id of the bitmap's mask in the bitmap file.
    */
    IMPORT_C void SetPictureFromFileL(const TDesC& aFileName, TInt aMainId, TInt aMaskId = -1);
    
    /**
    * Set data from resource file and show it in the status pane's title pane.
    */
    IMPORT_C void SetFromResourceL(TResourceReader& aReader);
    
    /**
    * Set default value to the status pane's title pane. Default value is the 
    * name of currently active application.
    */
    IMPORT_C void SetTextToDefaultL();
    
public: // from MCoeControlContext
    /** 
    * From MCoeControlContext. Allows to modify graphics context before Draw.
    *
    * @param aGc Graphics context to be modified.
    */
    IMPORT_C virtual void PrepareContext(CWindowGc& aGc) const;
    
protected: // From CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
	 * Handles a change to the control's resources of type aType
	 * which are shared across the environment, e.g. color scheme change.
	 * @param aType Event type.
	 */
    IMPORT_C virtual void HandleResourceChange(TInt aType);

    /**
    * From CCoeControl. Returns number of controls inside the context pane control.
    * @return Number of component controls.
    */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
    * From CCoeControl. Returns a control determined by control id.
    * @param anIndex Index of a control to be returned.
    * @return Pointer to control
    */
    IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
    
private:
    void CommonConstructL();
    TUid AppUid();

    TInt FormatTitlePaneLabelL( 
        const TInt aOneLineLayoutWidth,  const TInt aTwoLineLayoutWidth,
        const CFont* aOneLineFont,  const CFont* aTwoLineFont);

    void ReadFromResourceFileL(TResourceReader& aReader);
    
private: // From CCoeControl
    IMPORT_C virtual void Draw(const TRect& aRect) const;
    
private:
    HBufC* iTitleText;
    HBufC* iDefaultTitleText;
    CEikLabel* iTitleLabel;
    
    TBool iImageShown;
    CEikImage* iTitleImage;
    };


inline const TDesC* CAknTitlePane::Text() const
    { return(iTitleText); }


#endif // AKNTITLE_H
