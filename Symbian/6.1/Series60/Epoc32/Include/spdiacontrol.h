/*
* ============================================================================
*  Name        : SpdiaControl.h
*  Part of     : SpeedDial / SpdCtrl.dll
*  Interface   : 
*  Description : A utility that provides services to both the Speeddial and 
*                PhoneBook applications for getting and setting speeddial 
*                number configuration.
*  Version     : 
*
*  Copyright © 2002 Nokia Corporation.
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


#ifndef SPDIACONTROL_H
#define SPDIACONTROL_H

// INCLUDES
#include <coecntrl.h> 
#include <TPbkContactItemField.h>
#include <aknutils.h>
#include <MPbkContactDbObserver.h>
#include <MPbkThumbnailOperationObservers.h>

// FORWARD DECLARATIONS
class CAknGrid;
class CGulIcon;
class CEikonEnv;
class TSpdiaIndexData;
class CPbkContactEngine;
class RPbkViewResourceFile;
class CEikStatusPane;
class CPAlbImageData;
class CSpdiaGridDlg;
class CPbkContactChangeNotifier;
class CPbkSingleItemFetchDlg;
class CAknQueryDialog;

class CPAlbImageFactory;
class CPbkThumbnailManager;

// CLASS DECLARATION

/**
*  A utility that provides services to both the Speeddial and PhoneBook
*  applications for getting and setting speeddial number configuration.
*
*  @lib SpdCtrl.DLL
*  @since 
*/
class CSpdiaControl    : public CCoeControl,
                         public MPbkContactDbObserver,
                         private MPbkThumbnailGetObserver
    {
    public:     // SpdiaControl APIs
        /**
        * Creates a new instace of this class.
        */
        IMPORT_C static CSpdiaControl* NewL();

        /**
        * Creates a new instace of this class.
        *
        * @param aPbkEngine     reference of CPbkContactEngine.
        */
        IMPORT_C static CSpdiaControl* NewL(
                                CPbkContactEngine& aPbkEngine);

        /**
        * Puts a query on the screen asking for '...Assign it now'.
        * When the user goes through, it will assign speed dial.
        *
        * @param aLocation      a location to assign speed dial.
        * @param aStatusPane    not used.
        * @reutn    ETrue if success.
        */
        IMPORT_C TBool AssignDialNumberL(TInt aLocation, 
                            CEikStatusPane* aStatusPane = NULL);

        /**
        * Runs the Speed Dial Selection Grid Dialog.
        * If accepted sets speed dial key to aItem's aFieldId.
        * Note: Calls CPbkContactEngine::SetFieldAsSpeedDialL().
        *       If necessary, calls CPbkContactEngine::RemoveSpeedDialFieldL().
        *
        * @param aId        a contact item id. (Don't open)
        * @param aFieldId   index to aItems field set.
        * @return   nonzero if accepted, zero if canceled.
        */
        IMPORT_C TInt ExecuteLD(TContactItemId aId, TInt aFieldIdx);

        /**
        * Cancels and dismisses this dialog. In other words makes
        * ExecuteLD return just like cancel was pressed.
        * Used when user switches a application and all modal 
        * dialogs are closed.
        */
        IMPORT_C void Cancel();

        /**
        * The assigned number of the location is obtained.
        * Note: Voice mail number will be returned if the location
        *       is the position of Voice mail.
        * Note: If the location is empty, required dialog
        *       will be displayed and a location will be assigned.
        *
        * @param aLocation      a location of speed dial.
        * @param aPhonenumber   reference of phonenumber.
        * @param aStatusPane    not used.
        * @return   EFalse if user cancel or failed.
        */
        IMPORT_C TBool DialNumberL(TInt aLocation, TDes& aPhoneNumber,
                            CEikStatusPane* aStatusPane = NULL);

     public:     // Constructors and destructor
        /**
        * C++ default constructor.
        */
        IMPORT_C CSpdiaControl();

        /**
        * C++ constructor.
        */
        IMPORT_C CSpdiaControl(CPbkContactEngine* aPbkEngine);

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CSpdiaControl();

    public:     // New function
        /**
        * The number of voice mail returned, if voice mail is assigned.
        * Note: If the location is empty, required dialog
        * will be displayed and voice mail will be defined.
        *
        * @param aNumber    reference of phone number.
        * @retunr   EFalse if user cancel or failed.
        */
        IMPORT_C TBool VoiceMailL(TDes& aNumber);

        /**
        * Returns the owned Phone Book Engine.
        */
        IMPORT_C CPbkContactEngine* PbkEngine() const;

        /**
        * The value converted into the index of an array from 
        * the location of speeddial is returned.
        *
        * @param aDial      a location of speed dial.
        * @return   the index of a speeddial index data, if not found -1
        */
        IMPORT_C TInt Index(TInt aDial) const;

        /**
        * The value converted into the the location of speeddial
        * from index of an array is returned.
        *
        * @param aIndex     a index of array.
        * @return   location of speed dial(1-9), if not found -1
        */
        IMPORT_C TInt Number(TInt aIndex) const;

        /**
        * Returns the phone book contact item's id.
        *
        * @param aIndex     a index of array.
        * @return   a contact item's id, if not found -1
        */
        IMPORT_C TContactItemId ContactId(TInt aIndex) const;

        /**
        * Returns the phone number of a speed dial contact.
        * Note: A character invalid as a phone number is removed.
        *       calls PhCltUtils::RemoveInvalidChars()
        *
        * @param aDial      a location of speeddial.
        * @return   phone number
        */
        IMPORT_C const TDesC& PhoneDialNumber(TInt aDial) const;

        /**
        * Returns the phone number of a speed dial contact.
        * Note: left and right spaces are removed.
        *
        * @param aIndex     a index of array.
        */
        IMPORT_C const TDesC& PhoneNumber(TInt aIndex) const;

    public:   // SpeedDial internal API
        /**
        * Gets a title text from contact item's id.
        * Note:  calls CPbkContactItem::GetContactTitleOrNullL()
        *              or CPbkContactEngine::UnnamedTitle()
        *
        * @param aCid       contact item's id
        * @param aUnnamed   if title is empty, unname or NULL.
        * @return   a buffer containing the title. An unnametitle will
        *           be set if a title is empty.
        */
        IMPORT_C HBufC* ContactTitleL(TContactItemId aCid, TBool aUnnamed);

        /**
        * Returns the icon index of a grid array.
        *
        * @param aIndex     a index of array.
        */
        IMPORT_C TInt IconIndex(TInt aIndex) const;

        /**
        * Returns the thumbnail index of a grid array.
        *
        * @param aIndex     a index of array.
        */
        IMPORT_C TInt ThumbIndex(TInt aIndex) const;

        /**
        * Returns the array of icons
        */
        IMPORT_C CArrayPtr<CGulIcon>* IconArray() const;

        /**
        * Icons, thumbnails and text array for the grid are created.
        * Note: If a aIndex parameter is set, only the data of the value
        *       will be set up.
        * Note: CreateDataL() is used if App to be used is except SD.
        *
        * @param aGrid      the grid to set up
        * @param aIndex     (TInt) if <-1, All values are set up.
        */
        IMPORT_C TBool CreateGridDataL(CAknGrid* aGrid, TBool aIndex);

        /**
        * Assigns the index data at the index in the phone book's contact entry.
        *
        * @param aIndex     a index of array.
        */
        IMPORT_C TBool AssignDialIndexL(TInt aIndex);

        /**
        * Removes a speed dial from the phone book's contact entry.
        *
        * @param aIndex         a index of array.
        * @param aConfirmation  when remove, confirm is displayed.
        * @reutn    ETrue if success
        */
        IMPORT_C TBool RemoveDialIndexL(TInt aIndex,
                            TBool aConfirmation = ETrue);
        /** 
        * deprecated - do not use
        */
        IMPORT_C TBool AssignNumberL(TInt aIndex,
                            CEikStatusPane* aStatusPane,
                            CCoeControl* aContainer,
                            TBool aConfirmation);
        IMPORT_C void ApplyCellSpdiaPaneStyleL(CAknGrid& aListBox, TSize& aSize);
        IMPORT_C void DrawShadow(CWindowGc& aGc, const TSize& aSize);

        /**
        * The position which a shadow draws is set up.
        *
        * @param aRect       
        */
        IMPORT_C void SetLayout(const TRect& aRect);

        /** 
        * deprecated - do not use
        */
        IMPORT_C TInt Size() const;

        /**
        * Returns the position of voice mail box
        */
        IMPORT_C TInt VMBoxPosition() const;

        /**
        * Returns the icon index of grid array.
        */
        IMPORT_C TInt SpdIconIndex(TInt aIndex) const;

    public:
        /**
        * Creates a grid itemArray.
        * Note: It calls, when using a grid except SDM.
        *
        * @param aGrid      the grid to set up
        * @param aUpdate    updates in an event.
        */
        TBool CreateDataL(const CAknGrid& aGrid);

        /**
        * Returns the size of grid.
        */
        TSize GridSize() const;

        /**
        * Display confirmation dialog from id's
        *
        * @param aIndex     a index of array.
        * @param aId        resource id
        * @param aPromptId  prompt id
        */
        TBool ConfirmationNumberL(TInt aIndex,
                        TInt aId,
                        TInt aPromptId);

        /**
        * Thumbnail's shadow is drawn.
        *
        * @param aGc    window gc
        */
        void DrawShadow(CWindowGc& aGc) const;

    private:    // Functions from base classes
        // from MpblThumbnailOperation
        /**
        * Called when thumbnail loading is completed.
        *
        * @param aOperation    the completed operation.
        * @param aBitmap       The loaded bitmap. Callee is responsible of 
        *                      the bitmap.
        */
        void PbkThumbnailGetComplete(MPbkThumbnailOperation& aOperation,
                                     CFbsBitmap* aBitmap);

        /**
        * Called if the thumbnail loading fails.
        *
        * @param aOperation     the failed operation.
        * @param aError         error code of the failure.
        */
        void PbkThumbnailGetFailed
            (MPbkThumbnailOperation& aOperation, TInt aError);

    private:  // from CCoeControl
        /*
        * Draw this control
        */
        void Draw(const TRect& aRect) const;

    private:
        /**
        * From MContactDbObserver, Handles an event of type aEventType.
        */
        void HandleDatabaseEventL(TContactDbObserverEvent aEvent);

    private:    // functions
        /**
        * Constructor
        */
        void ConstructL();

        /**
        * Index data are initialized.
        */
        void InitIndexDataL();

        /**
        * Updates data set to match index of the owned index data array.
        */
        TBool UpdateIndexDataL(TInt aIndex);

        /**
        * Searches icon of grid array for a match.
        *
        * @param aId     phone book icon id to match to.
        * @return   the matching index, -1 if not found.
        */
        TInt FindIconIndex(TInt aId) const;

        /**
        * Returns the thumbnail type.
        *
        * @param aIndex     a index of array.
        */
        TInt ThumbType(TInt aIndex) const;

        /**
        * Returns the thumbnail size.
        *
        * @param aIndex     a index of array.
        */
        TSize ThumbSize(TInt aIndex) const;

        /**
        * Set phonebook contact itmes'id.
        *
        * @param aIndex     a index of array.
        * @param aCid       phone book contact item's id.
        */
        void SetContactId(TInt aIndex, TContactItemId aCid);
  
        /**
        * The position on the array that a grid uses from 
        * an item and a phone number is returned.
        *
        * @param aItem      contacd item
        * @param aDial      phone number
        */
        TInt IconPositionL(const CPbkContactItem& aItem, TInt aDial);

        /**
        * An icon array is created and set.
        *
        * @retunr   if need loadthumbL ETrue
        */
        TInt SetIconArrayL(CArrayPtrFlat<CGulIcon>* aArray);

        /**
        * Gets Item's descriptor for Grid.
        *
        * @param aIndex     a index of array.
        * @param aSdmData   reference to the data currently used.
        * @return   a buffer containing the descriptor text.
        */
        HBufC* ItemDescriptorLC(TInt aIndex, const TSpdiaIndexData& aSdmData);

        /**
        * Creates Item's descriptor for Grid.
        *
        * @param aSdmData   reference to the data currently used.
        * @returen  a buffer containing the descriptor text.
        */
        HBufC* CreateItemDescriptorLC(const TSpdiaIndexData& aSdmData);

        /**
        * A descriptor is added to a text.
        *
        * @param aSdmData   reference to the data currently used.     
        * @param aText      the text for storing 
        */
        void AppendTextL(const TSpdiaIndexData& aSdmData, TPtr& aText);

        /**
        * Searches contact item's fiels of this contact for a match.
        *
        * @param aItem      contact item to search.
        * @param aFieldId   field id to search.
        * @return   first field matching aFieldId, NULL if none found. 
        */
        TPbkContactItemField* FindFieldL(CPbkContactItem& aItem,
                                    TPbkFieldId aFieldId);

        /**
        * The descriptor for thumbnail is added. 
        *
        * @param aSdmData           reference to the data currently used.    
        * @param aText
        * @param aFixedLocation
        */
        void AppendThumbnail(const TSpdiaIndexData& aSdmData,
                            TPtr& aText, 
                            TBool aFixedLocation);

        /**
        * Returns the type from a size of thumbnail.
        *
        * @param aSize  a thumbnail size
        */
        TInt ConvThumbType(const TSize& aSize) const;

        /**
        * Operations to a CPbkThumbnailManager are set. 
        * Note: call GetThumbnailAsyncL().
        */
        void SetOperationsL();

        /**
        * The data of items are added to an array.
        *
        * @param aArray
        */
        void SetItemDataL(CDesCArray& aArray);

        /**
        * Assigns the index data at aDial in the phone book's contact entry
        *
        * @param aId
        * @param aDial
        */
        void AssignDialL(TContactItemId aId, TInt aFieldIdx, TInt aDial);

        /**
        * Checks if the Flash File System storage will fall below 
        * Critical Level. Warning will be displayed if sotrage
        * is below Critical Level.
        *
        * @return   ETrue   Below critical level
        */
        TBool CheckSpaceBelowCriticalLevelL();

        /**
        * Does it have a thumbnail operation object to match?
        *
        * @param aOperation     a thumbnail operation object to match to.
        * @return   index of speeddial index data array.
        */
        TInt HasOperation(const MPbkThumbnailOperation& aOperation);

        /**
        * A text array that a grid has is erased. 
        */
        void ResetArray();

        /**
        * Speeddial index data is set by the data of parameters.
        *
        * @param aIndex     a index of array.
        * @param aSdmData   reference to the data currently used.
        */
        void SetIndexDataL(TInt aIndex, TSpdiaIndexData& aSdmData);

        /**
        * Speeddial index data is changed by the data of parameters.
        *
        * @param aIndex     a index of array.
        * @param aSdmData   reference to the data currently used.
        */
        void CSpdiaControl::ChangeIndexDataL(TInt aIndex,
                                     const TSpdiaIndexData& aSdmData);

        /**
        * Creates icon data for SDM control data by the data of parameters.
        *
        * @param aIndex             a index of array.
        * @param aSdmData           reference to the data currently used.            
        * @param aSetUpdateThumb    thumbnail load start parameter set in index data
        */
        TBool CreateIndexIconL(TInt aIndex, TSpdiaIndexData& aSdmData,
                            TBool aSetUpdateThumb);

    private:    // Data
        // The type of the caller application.
        enum TGridUse
            {
            EGridUse,               // SpeedDial
            EGridUseAndUpdate,      // PhoneBook
            EGridNoUse              // PhoneClient
            };
        CPbkContactEngine* iEngine;                 // owned by this
        TBool iExEngine;                            // engine owned flags
        TGridUse iGridUsed;

        TInt iSdmCount;                             // Grid cell count(Row * col)

        CArrayFixFlat<TSpdiaIndexData>* iSdmArray;  // owned by this
        CArrayFixFlat<TAknLayoutRect>* iShadowLayout;     // owned by this

        CPbkContactChangeNotifier* iPbkNotifier;    // owned by this
        CPbkSingleItemFetchDlg* iPbkSingleItem;     // owned by this
        CAknQueryDialog* iQueryDialog;              // owned by this
        RPbkViewResourceFile* iPbkResourceFile;     // owned by this
        CSpdiaGridDlg* iGridDlg;                    // owned by this

        /// Own: thumbnail manager
        CPbkThumbnailManager* iManager;
        /// Own: factory for scaling to Thumbnails
        CPAlbImageFactory* iThumbFactory;

        CAknGrid* iGrid;
        TInt    iFileOffset;
        CArrayPtrFlat<CGulIcon>* iIconArray;
    };

#endif // SPDIACONTROL_H

// End of File

