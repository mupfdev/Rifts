/*
* =============================================================================
*  Name     : CAknExListBaseContainer
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTBASECONTAINER_H
#define AKNEXLISTBASECONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <aknsfld.h>

// CONSTANTS
const TInt KAknExListDirBufLength = 256; // for lenght.
// for initialization.
const TInt KAknExListInitOutlineId = 0;
const TInt KAknExListInitListResourceId = 0;
const TInt KAknExListInitEmptyResourceId = 0;
const TInt KAknExListMessageInitId = 0;
const TInt KAknExListAddInitCount = 0;
const TInt KAknExListRemoveInitCount = 0;
const TInt KAknExListGraphicGulIconIndex = 10;
const TInt KAknExListDefaultFlag = 0;
// for number of adding and removing item.
const TInt KAknExListNumberOfItemType1 = 1;
const TInt KAknExListNumberOfItemType2 = 10;
const TInt KAknExListNumberOfItemType3 = 100;
const TInt KAknExListNumberOfItemType4 = 1000;
const TInt KAknExListNumberOfItemType5 = 10000;
// for key event.
#define AKNEXLIST_ADDINGTYPE1_KEY '1'
#define AKNEXLIST_ADDINGTYPE2_KEY '2'
#define AKNEXLIST_ADDINGTYPE3_KEY '3'
#define AKNEXLIST_ADDINGTYPE4_KEY '4'
#define AKNEXLIST_ADDINGTYPE5_KEY '5'
#define AKNEXLIST_REMOVINGTYPE1_KEY '6'
#define AKNEXLIST_REMOVINGTYPE2_KEY '7'
#define AKNEXLIST_REMOVINGTYPE3_KEY '8'
#define AKNEXLIST_REMOVINGTYPE4_KEY '9'
#define AKNEXLIST_REMOVINGTYPE5_KEY '0'
#define AKNEXLIST_AUTONUMBERING_KEY '0'

// FORWARD DECLARATIONS
class CEikListBox;
class CEikTextListBox;
class CEikColumnListBox;
class CEikFormattedCellListBox;
class CTextListBoxModel;

// CLASS DECLARATION

/**
* CAknExListBaseContainer  container control class.
*/
class CAknExListBaseContainer : public CCoeControl
    {

    protected: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExListBaseContainer();

        /**
        * Destructor.
        */
        virtual ~CAknExListBaseContainer();

    protected: // New functions

        /**
        * Sets listbox from resource using ConstructFromResourceL() of
        * CEikColumnListBox class.
        * @param aListBox Pointer of listbox.
        * @param aResourceId Resource ID of listbox.
        */
        void SetListBoxFromResourceL(
            CEikColumnListBox* aListBox,
            const TInt aResourceId );

        /**
        * Sets listbox from resource using ConstructFromResourceL() of
        * CEikFormattedCellListBox class.
        * @param aListBox Pointer of listbox.
        * @param aResourceId Resource ID of listbox.
        */
        void SetListBoxFromResourceL(
            CEikFormattedCellListBox* aListBox,
            const TInt aResourceId );

        /**
        * Sets listbox from inner description using ConstructL() of
        * CEikColumnListBox class.
        * @param aListBox Pointer of listbox.
        * @param aFlags Flags of listbox.
        * @param textArray List items as CDesCArray.
        */
        void SetListBoxFromInnerDescriptionL(
            CEikColumnListBox* aListBox,
            const TInt aFlags = KAknExListDefaultFlag,
            CDesCArray* textArray = NULL );

        /**
        * Sets listbox from inner description using ConstructL() of
        * CEikFormattedCellListBox class.
        * @param aListBox Pointer of listbox.
        * @param aFlags Flags of listbox.
        * @param textArray List items as CDesCArray.
        */
        void SetListBoxFromInnerDescriptionL(
            CEikFormattedCellListBox* aListBox,
            const TInt aFlags = KAknExListDefaultFlag,
            CDesCArray* textArray = NULL );

        /**
        * Creates scrollbar.
        * @param aListBox Pointer of created listbox.
        */
        void CreateScrollbarL( CEikListBox* aListBox );

        /**
        * Update scroll bar.
        * @param aListBox Pointer of created listbox.
        */
        void UpdateScrollBar(CEikListBox* aListBox);

        /**
        * Creates FindBox and returns it's pointer.
        * @param aListBox Pointer of listbox.
        * @param aModel Pointer of model.
        * @param aStyle Style of FindBox.
        * @return Pointer of CAknSearchField.
        */
        CAknSearchField* CreateFindBoxL(
            CEikListBox* aListBox,
            CTextListBoxModel* aModel,
            CAknSearchField::TSearchFieldStyle aStyle );

        /**
        * Automatic numbering of list item.
        * @param aListBox Pointer of listbox.
        */
        void AutoNumberingL( CEikTextListBox* aListBox );

        /**
        * Sets graphic icon using listbox as CEikColumnListBox.
        * @param aListBox Pointer of listbox.
        */
        void SetGraphicIconL( CEikColumnListBox* aListBox );

        /**
        * Sets graphic icon using listbox as CEikFormattedCellListBox.
        * @param aListBox Pointer of listbox.
        */
        void SetGraphicIconL( CEikFormattedCellListBox* aListBox );

        /**
        * Sets empty list for listbox.
        * @param aListBox Pointer of listbox.
        * @param Resource ID using text for empty list.
        */
        void SetEmptyListL( CEikListBox* aListBox, const TInt aResourceId );

        /**
        * Adds list items at the bottom of the list.
        * @param aListBox Pointer of listbox.
        * @param aModel Pointer of model.
        * @param aCount Count of added items.
        * @param aResourceId Resource ID useing added list items.
        */
        void AddItemL(
            CEikListBox* aListBox,
            CTextListBoxModel* aModel,
            const TInt aCount,
            const TInt aResourceId );

        /**
        * Removes list itmes.
        * @param aListBox Pointer of listbox.
        * @param aModel Pointer of model.
        * @param aCount Count of removed items.
        */
        void RemoveItemL(
            CEikListBox* aListBox,
            CTextListBoxModel* aModel,
            const TInt aCount );

        /**
        * Displays information message.
        * @param aMessageId The ID of resource(Information message).
        */
        void InfoMessage( const TInt aMessageId );

        /**
        * Displays information message of total number for list items.
        * @param aModel Pointer of model.
        */
        void CountMessage( CTextListBoxModel* aModel );

        /**
        * Displays message to main pane.
        * @param Message
        */
        void ShowMessageL(const TDesC & aMessage);

        /**
        * Displays information of marked item index.
        * @param : aIndexArray : Array of marked item index
        */
        void InfoMarkedItemIndexL(const CArrayFix<TInt>* aIndexArray);

    private: // New Function

        /**
        * Appends graphics data.
        * @param Pointer of icon using graphics for listbox.
        */
        virtual void GraphicIconL( CArrayPtr<CGulIcon>* aIcons );

    private: // From CoeControl
        /**
        * From CCoeControl, Draw.
        * Fills the window's rectangle.
        * @param aRect Region of the control to be (re)drawn.
        */
        void Draw( const TRect& aRect ) const;

    };

#endif

// End of File
