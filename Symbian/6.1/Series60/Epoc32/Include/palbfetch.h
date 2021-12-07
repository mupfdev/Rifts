/*
* ============================================================================
*  Name     : PAlbFetch.h
*  Part of  : PhotoAlbum
*
*  Description:
*   Implements fetch popup for picture fetch and image fetch.
*  Version  :
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef __PALBFETCH_H
#define __PALBFETCH_H

// INCLUDES
#include <bldvariant.hrh>
#include <e32std.h>
#include <e32base.h>
#include <aknpopup.h>
#include <ConeResLoader.h>
#include <PAlbUtil.h>

// FORWARD DECLARATIONS
class CPAlbImageEngine;
class CPAlbPictureEngine;
class CPAlbImageData;
class CAknPopupList;
class CEikListBox;
class CAknGMSStyleGrid;
class CAknGMSPopupGrid;
class CPAlbPictureGridFormatter;
class CPAlbImagePopupList;
class CPAlbImageListBoxModel;
class CAknDoubleLargeGraphicPopupMenuStyleListBox;

// CLASS DECLARATION

// ============================================================================
// CPAlbImageFetchPopupList
// ============================================================================

/**
 *   Fetching an image name, path from PhotoAlbum. It uses internally a
 *   modified AknPopUpList class.
 *
 *   To launch this popup just call:
 *
 *   CPAlbImageData* data = CPAlbImageData::NewL();
 *   CleanupStack::PushL( data );
 *   TBool result( CPAlbImageFetchPopupList::RunL( data ) );
 *   ...
 *   CleanupStack::PopAndDestroy(); // data
 *
 * Returns ETrue if the user selected a picture.
 * The name and path of the selected picture are stored in the CPAlbImageData object.
 */
class CPAlbImageFetchPopupList : public CBase, public MPAlbSubscriber
    {
    public:
    /**
     * Runs first the memory selection dialog and and if user selects OK
     * launches the popup and fills the data if image is selected.
     * @param aData image data to fill, fetch result is here
     * @return ETrue is image is selected, otherwise EFalse
     */
    IMPORT_C static TBool RunL( CPAlbImageData* aData );

public: // Functions from base classes
    /**
     * Handle events sent by the publisher subscribed by this
     * class.
     *
     * @param aModel publisher of the event
     * @param aEvent event to be handled
     */
    void Update( const CPAlbPublisher* aModel, TInt aEvent );

private: // Constructors and destructor
    /**
     * Default constructor
     */
    CPAlbImageFetchPopupList();

    /**
     * 2nd phase constructor
     */
    void ConstructL();

    /**
     * Creates and returns an instance of this class
     * @return a new instance of this class
     */
    static CPAlbImageFetchPopupList* NewL();

    /**
     * destructor.
     */
    virtual ~CPAlbImageFetchPopupList();

private: // Functions from base classes
    /**
     * Creates popup and sets listbox.
     * This method is used by RunL
     * @return the popuplist
     * @see RunL
     */
    CAknPopupList* CreatePopupLC();

    /**
     * Fills the supplied image data with the image name and path.
     * @param aData image data to fill
     */
    void FillImageDataL( CPAlbImageData* aData );

    /**
     * Rreturns the used listbox.
     * @return the listbox
     */
    CEikListBox* ListBox();

    private:
    /**
     * Creates common dialogs memory selection popup dialog and sets
     * iBrowsePath.according to user's selection.
     * This method is used by RunL and it's only supported when __SERIES60_MMC
     * feature flag is defined (Panics with KErrNotSupported if not).
     * @return ETrue if memory selected, otherwise EFalse
     * @see RunL
     */
    TBool LaunchMemorySelectionDialogL();

    /**
     * Filters protected image files from fetcher popup if the fetcher
     * was NOT launched from Phonebook or General Settings
     * NOTE: Only has effect if __SERIES60_DRM is enabled
     */
    void FilterFilesL();

private: // Data

    // Owns: the used listbox
    CAknDoubleLargeGraphicPopupMenuStyleListBox* iList;

    // Own: the image engine which we use for the listbox
    CPAlbImageEngine* iEngine;

    // Own: The model creates dynamically the icons and descriptors for the listbox.
    CPAlbImageListBoxModel* iListModel;

    // Own: ResourceLoader
    RConeResourceLoader iResource;

    // Own: Stores the path returned from CAknMemorySelectionDialog
    // @see LaunchMemorySelectionDialogL()
    TFileName iBrowsePath;

    // Own: UID of the application that launched the image fetcher
    TInt iExecuterID;
    };

// ============================================================================
// CPAlbPictureFetchPopupList
// ============================================================================
/**
 * Fetching a picture name, path from PhotoAlbum. It uses internally a
 * modified AknPopUpList class.
 *
 * To launch this popup just call:
 *
 * CPAlbImageData* data = CPAlbImageData::NewL();
 * CleanupStack::PushL( data );
 * TBool result( CPAlbPictureFetchPopupList::RunL( data ) );
 * ...
 * CleanupStack::PopAndDestroy(); // data
 *
 * Returns ETrue if the user selected a picture.
 * The name and path of the selected picture are stored in the CPAlbImageData object.
 */
class CPAlbPictureFetchPopupList : public CBase
    {
    public:
    /**
     * Runs the popup and fills the data if picture is selected.
     * @param aData image data to fill
     * @return ETrue if picture is selected, otherwise EFalse
     */
    IMPORT_C static TBool RunL( CPAlbImageData* aData );

    /**
     * Runs the popup with custom title text and fills the aData 
     * if picture is selected.
     * @param aData image data to fill, fetch result is here
     * @param aTitle custom title text for the popup
     * @return ETrue if picture is selected, otherwise EFalse
     */
    IMPORT_C static TBool RunL( CPAlbImageData* aData, const TDesC& aTitle );

private: // Constructors and destructor

    /**
     * default constructor
     */
    CPAlbPictureFetchPopupList();

    /**
     * Second phase constructor
     */
    void ConstructL();

    /**
     * Creates and returns an instance of this class
     * @return instance of this class
     */
    static CPAlbPictureFetchPopupList* NewL();

    /**
     * destructor.
     */
    virtual ~CPAlbPictureFetchPopupList();

    private:
    /**
     *   Creates popup and sets listbox.
     *   This is used by RunL
     *   @todo replace CPAlbPopupList by a working AknPopupList
     *   @return the popuplist
     *   @see RunL
     */
    CAknPopupList* CreatePopupLC();

    /**
     * Fills the image data with the image name and path.
     * @param aData image data to fill
     */
    void FillImageDataL( CPAlbImageData* aData );

    /**
     * Returns the used listbox.
     * @return the listbox
     */
    CEikListBox* ListBox();

private:    // Data

    // Own: the use listbox
    CAknGMSStyleGrid* iGrid;

    // Own: the image engine which we use for the listbox
    CPAlbPictureEngine* iEngine;

    // Own: ResourceLoader
    RConeResourceLoader iResource;

    // Own: Custom title text
    HBufC*  iTitle;
    };

#endif      // __PALBFETCH_H

// End of File