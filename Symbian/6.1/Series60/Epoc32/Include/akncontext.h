/*
* ============================================================================
*  Name     : akncontext.h
*  Part of  : AVKON
*
*  Description:
*     A default control in the status pane's context pane.
*     
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNCONTEXT_H
#define AKNCONTEXT_H

#include <coecntrl.h>

class CEikImage;

/**
 * A default control in the status pane's context pane.
 */
class CAknContextPane : public CCoeControl
	{
public:
    
    /**
    * Standard constructor
    */
    IMPORT_C CAknContextPane();
    
    /**
    * Destructor
    */
    IMPORT_C ~CAknContextPane();
    
    /** 
    * 2nd phase construction
    *
    */
    IMPORT_C void ConstructL();
    
    /** 
    * Construct from resources.
    * @param aReader resource reader.
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
    /**
    * Sets bitmap with mask to the context pane and shows it in the status pane's 
    * context pane. Context pane object takes ownership of the bitmap.
    * @param aBitmap new bitmap to the context pane.
    * @param aMaskBitmap mask of the bitmap.
    */
    IMPORT_C void SetPicture(const CFbsBitmap* aBitmap, 
        const CFbsBitmap* aMaskBitmap = NULL);
    
    /**
    * Sets bitmap to the context pane and shows it in the status pane's 
    * context pane. Context pane object takes ownership of the bitmap.
    * @param aImage new bitmap and its mask.
    */
    IMPORT_C void SetPicture(CEikImage* aImage);
    
    /**
    * Sets bitmap to the context pane from file and shows it in the status pane's 
    * context pane.
    * @param aFileName name of the bitmap file.
    * @param aMainId id of the bitmap in the bitmap file.
    * @param aMaskId id of the bitmap's mask in the bitmap file.
    */
    IMPORT_C void SetPictureFromFileL(const TDesC& aFileName, 
                                                               TInt aMainId, TInt aMaskId = -1);
    
    /**
    * Set data from resource file and show it in the status pane's context pane.
    */
    IMPORT_C void SetFromResourceL(TResourceReader& aReader);
    
    /**
    * Show context pane's default bitmap. Application's AIF file icon is used if it exists.
    */
    IMPORT_C void SetPictureToDefaultL();
    
    /**
    * Returns a reference to the current context pane bitmap. The reference is lost when
    * context pane bitmap is changed with any Set -method including 
    * SetPictureToDefaultL and SwapPicture)
    * @return Reference to the current context pane bitmap.
    */
    IMPORT_C const CEikImage& Picture() const;
    
    /**
    * Sets bitmap with mask to the context pane and shows it in the status pane's 
    * context pane. Context pane object takes ownership of the bitmap.
    * Old bitmap is returned and the caller is responsible of deleting the returned object.
    * @param aNewImage new bitmap to the context pane. This object takes ownership of aNewImage.
    * @return Previous context pane bitmap. The caller is responsible of deleting the returned object.
    */
    IMPORT_C CEikImage* SwapPicture(CEikImage* aNewImage);
    
    
protected: // from CCoeControl

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

private: // new functions
    void CommonConstructL();
    
    /** 
    * Returns application's Uid. In embedded applications, root application's Uid is returned.
    * @return Application's Uid. Root application's Uid is returned in embedded applications.
    */
    TUid AppUid();
    void ReadFromResourceFileL(TResourceReader& aReader);

private: // From CCoeControl
    IMPORT_C virtual void Draw(const TRect& aRect) const;

private:
    CEikImage* iContextImage;
    CEikImage* iDefaultContextImage;
	};


#endif // AKNCONTEXT_H
