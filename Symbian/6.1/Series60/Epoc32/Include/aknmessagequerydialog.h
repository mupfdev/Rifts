/*
* ============================================================================
*  Name     : aknmessagequerydialog.h
*  Part of  : AVKON
*
*  Description:
* 
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#if !defined(__AKNMESSAGEQUERYDIALOG_H__)
#define __AKNMESSAGEQUERYDIALOG_H__

#include <aknquerydialog.h>
class CEikImage;

/** 
 * Message query dialog. The dialog contains text that can be scroller page by page.
 */
class CAknMessageQueryDialog : public CAknQueryDialog
	{
public:
	IMPORT_C static CAknMessageQueryDialog* NewL(TDesC& aMessage, const TTone& aTone = ENoTone);

	/**
	 * Destructor.
	 */
	IMPORT_C ~CAknMessageQueryDialog();

	/**
     * @deprecated - will become protected
     * @param aTone Tone played with the dialog (not implemanted)
     */
    IMPORT_C CAknMessageQueryDialog(const TTone aTone);

public:
	/**
     * Set message text. 
     * @param aMessage Message text inside query. Insert '\n' to get new line.
     */
	IMPORT_C void SetMessageTextL(const TDesC& aMessage);

	/**
     * Set header text.
     * @param aHeader Message query header text
	 *
	 * @deprecated - use Heading() + CAknPopupHeadingPane API instead
     */
	IMPORT_C void SetHeaderTextL(const TDesC& aHeader);  

    /**
     * Set (replace) header image. 
	 * Ownership of a parameter is transfered to the dialog.
     * @param aImage Image to message query header
	 *
	 * @deprecated - use Heading() + CAknPopupHeadingPane API instead
     */
    IMPORT_C void SetHeaderImage(CEikImage* aImage);     

    /**
     * Set header animation.
     *  If set, the image will be overriden.
     * @param aResourceId Resource id of the animation
	 * 
	 * @deprecated - use Heading() + CAknPopupHeadingPane API instead
     */
    IMPORT_C void SetHeaderAnimation( TInt aResourceId );

public: // from CCoeControl
   	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode);

protected: // from CEikDialog
	IMPORT_C virtual void PreLayoutDynInitL();
	IMPORT_C virtual void SetSizeAndPosition(const TSize& aSize);
	IMPORT_C virtual void PostLayoutDynInitL();

private: 
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();	
private: 
	IMPORT_C virtual void CAknDialog_Reserved();
private:
	IMPORT_C virtual void CAknQueryDialog_Reserved();
private:
    TDesC* iMessage;
    TDesC* iHeader;
    CEikImage* iHeaderImage;
    TInt iAnimationId;

public:
	/**
	 * FOLLOWING METHODS ARE DEPRECATED !!!
	 * Will be removed, do not use
	 */
    // @deprecated
	IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, TDesC* aHeader); 
    // @deprecated
    IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, TDesC* aHeader, CEikImage *aHeaderImage); 
    // @deprecated
    IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, TDesC* aHeader, const TTone aTone); 
    // @deprecated
    IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, TDesC* aHeader, CEikImage *aHeaderImage, const TTone aTone); 
    // @deprecated
    IMPORT_C void SetMessageText(TDesC* aMessage); 
    // @deprecated
	IMPORT_C void SetMessageText(const TDesC& aMessage);
    // @deprecated
    IMPORT_C void SetHeaderText(TDesC* aHeader);  
    // @deprecated
	IMPORT_C void SetHeaderText(const TDesC& aHeader);  

	// @deprecated
    IMPORT_C CAknMessageQueryDialog();
	};


#endif // __AKNMESSAGEQUERYDIALOG_H__

//  End of File  
