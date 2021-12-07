/*
* ============================================================================
*  Name     : AknUtils.h
*  Part of  : Avkon
*
*  Description:
*     General Avkon Utilities. Includes:
*		- listbox utilities
*		- layout utilities
* 
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNUTILS_H__
#define __AKNUTILS_H__

#include <BldVariant.hrh>
#include <eiktxlbm.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include <coedef.h>
#include <coecobs.h>
#include <w32std.h>
#include <gulalign.h>
#include <gulutil.h>
#include <eikenv.h>

#include <aknlayout.lag>

// These are for listbox column lengths (These are used to allocate memory from stack while drawing listboxes, they should be as small as possible, but not smaller!)
#ifdef __AVKON_APAC__
const TInt KMaxColumnDataLength = 80; // This is maximum length of data for one listbox column -- after that the data is truncated before drawing.
#endif
#ifdef __AVKON_ELAF__
const TInt KMaxColumnDataLength = 60; // This is maximum length of data for one listbox column -- after that the data is truncated before drawing.
#endif
const TInt KMaxTotalDataLength = 8*KMaxColumnDataLength;  // max of 5 columns can have full 80 characters...

/** AVKON utility module
 *
 * From this file, you can find several tools for making application development easier for Series 60
 *
 * 1) Conversion modules to convert coordinate data from european LAF to usable formats
 *     AknLayoutUtils, TAknLayoutRect, TAknLayoutText
 * 2) Utilities to clip text
 * 3) Part of selection service implementation
 * 4) Different classes that help using listboxes
 * 5) Handling colors in AKN_LAF_COLOR macro.
 * 6) Resource readers for different purposes
 * 7) Utility to find files without specifying the drive letter or path
 */


class CCoeControl;
class CEikTextListBox;
class CEikColumnListBox;
class CEikFormattedCellListBox;
class CGulIcon;
class CEikSettingsListBox;
class CAknLAF;
class CEikImage;
class CEikMfne;
class CEikListBox;
class CEikLabel;
class CEikEdwin;
class CEikMenuPane;
class CAknPopupField;
class CListBoxView;
class CAknColumnListBox;
class CEikSecretEditor;
class CFindExtension;
/**
 * Egul library had methods to clip text from right side, this class includes methods to clip from both sides.
 * It does add 3 dots to the end of the text.
 */
const TInt  KDefaultClipWidth = -1;
const TUint KDefaultClipChar  = TUint(0x2026);

class AknTextUtils 
    {
public:
    enum TClipDirection
	{
	EDoNotClip,
	EClipFromEnd,
	EClipFromBeginning
	};
    /** ClipToFit() Generic clipping
	
	@param aBuffer         String that needs to be clipped. will be modified by this call
	@param aFont           Font used in the code
	@param aMaxWidthInPixels Maximum length of text that will not be clipped.
	@param aDir            Where is the text clipped from. EDoNotClip, EClipFromEnd, EClipFromBeginning.
	@param aClipWidth      The length of the text after clipping. KDefaultClipWidth will make it use aMaxWidthInPixels.
	@param aClipString     The representation of three dots. (not really used anywhere - use the default value always or "")
       
	returns true if the text was clipped and 3 dots were added. 
    */
    
    IMPORT_C static TBool ClipToFit(TDes& aBuffer, const CFont& aFont, TInt aMaxWidthInPixels, TClipDirection aDir=EClipFromEnd, TInt aClipWidth = KDefaultClipWidth, const TDesC &aClipString=_L("..."));

    /** ClipToFit() for clipping text inside lists
     *
     * NOTICE: This method cannot handle situation where the text may dynamically change its size! Especially when you have bitmaps on the right side!
     *
     * This needs to be done AFTER the listbox has done its SizeChanged()!
     */
    IMPORT_C static TBool ClipToFit(TDes& aBuffer, TClipDirection aDir, CEikFormattedCellListBox *aListBox, TInt aItemIndex, TInt aSubCellNumber);

    /** ClipToFit() for clipping text inside lists
     *
     * NOTICE: This method cannot handle situation where the text may dynamically change its size! Especially when you have bitmaps on the right side!
     *
     * This needs to be done AFTER the listbox has done its SizeChanged()!
     */
    IMPORT_C static TBool ClipToFit(TDes& aBuffer, TClipDirection aDir, CEikColumnListBox *aListBox, TInt aItemIndex, TInt aColumnNumber);
            
    /**
    * Wraps a string to an array of pointers.
	* The number of lines and line widths are specified by aLineWidthArray.
	* The pointers in aWrappedArray point to positions inside aWrappedString.
    *
    * @param aStringToWrap      String that needs to be wrapped
    * @param aLineWidthArray    Line widths in pixels
    * @param aFont              Used font
    * @param aWrappedArray      Pointers to wrapped lines
    */
    IMPORT_C static void WrapToArrayL( 
        const TDesC& aStringToWrap,
	    const CArrayFix<TInt>& aLineWidthArray,
	    const CFont& aFont,
	    CArrayFix<TPtrC>& aWrappedArray);

    /**
    * Wraps a string to an array of pointers.
	* Constant line width is given.
	* The pointers in aWrappedArray point to positions inside aWrappedString.
    *
    * @param aStringToWrap      String that needs to be wrapped
    * @param aLineWidth         Constant line width in pixels
    * @param aFont              Used font
    * @param aWrappedArray      Pointers to wrapped lines
    */
    IMPORT_C static void WrapToArrayL( 
        const TDesC& aStringToWrap,
	    TInt aLineWidth,
	    const CFont& aFont,
	    CArrayFix<TPtrC>& aWrappedArray );

    /**
    * Wraps a string to an array of pointers and clips at the end
	* of the last line if there aren't enough lines to accomodate
	* the entire text. When clipping three dots are inserted at the
	* end of the last line.
	* The number of lines and line widths are specified by aLineWidthArray.
	* The pointers in aWrappedArray point to positions inside aWrappedString.
    *
	* Expect the string to be modified if clipping is needed.
	* (Clipping character KEllipsis is inserted at the ending point)
    *
    * @param aStringToWrap      String that needs to be wrapped
    * @param aLineWidthArray    Line widths in pixels
    * @param aFont              Used font
    * @param aWrappedArray      Pointers to wrapped lines
    */
    IMPORT_C static void WrapToArrayAndClipL( 
        TDes& aStringToWrap,             
	    const CArrayFix<TInt>& aLineWidthArray, 
	    const CFont& aFont,                     
	    CArrayFix<TPtrC>& aWrappedArray );       
	
	/**
    * Chops a string when a line break character is encountered.
	* Clips at the end of each line if there isn't enough space
	* on that line.
	* When clipping, KEllipsis (shown as 3 dots) is inserted at
    * the end of the line.
	* The number of lines and line widths are specified by aLineWidthArray.
	* The pointers in aChoppedArray point to positions inside aStringToChop.
    *
	* Expect the string to be modified if clipping is needed
	* (Clipping character KEllipsis is inserted in the end of the lines)
    *
    * @param aStringToChop      String that needs to be chopped
    * @param aLineWidthArray    Line widths in pixels
    * @param aFont              Used font
    * @param aChoppedArray      Pointers to chopped lines
    */
	IMPORT_C static void ChopToArrayAndClipL(
		TDes& aStringToChop,             
	    const CArrayFix<TInt>& aLineWidthArray, 
	    const CFont& aFont,                    
	    CArrayFix<TPtrC>& aChoppedArray);

	/**
    * Chops a string when a line break character is encountered.
	* Clips at the end of each line if there isn't enough space
	* on that line.
	* When clipping, KEllipsis (shown as 3 dots) is inserted at
    * the end of the line.
	* Constant line width is given.
	* The pointers in aChoppedArray point to positions inside aStringToChop.
    *
	* Expect the string to be modified if clipping is needed
	* (Clipping character KEllipsis is inserted in the end of the lines)
    *
    * @param aStringToChop      String that needs to be chopped
    * @param aLineWidth         Constant line width in pixels
    * @param aFont              Used font
    * @param aChoppedArray      Pointers to chopped lines
    */
	IMPORT_C static void ChopToArrayAndClipL(
		TDes& aStringToChop,             
	    TInt aLineWidth, 
	    const CFont& aFont,                    
	    CArrayFix<TPtrC>& aChoppedArray );

    /**
    * Wraps a string (aStringToWrap) into lines according to the
	* number of lines and line widths specified in aLineWidthArray. 
	* Inserts '\n' at the end of lines. 
	* Copies the result into aWrappedString.
    * Leaves if aWrappedString isn't big enough.
    *
    * @param aStringToWrap      String that needs to be wrapped
    * @param aLineWidthArray    Lines widths in pixels
    * @param aFont              Used font
    * @param aWrappedString     Wrapped string 
    */
    IMPORT_C static void WrapToStringL( 
        const TDesC& aStringToWrap,
	    const CArrayFix<TInt>& aLineWidthArray,
	    const CFont& aFont,
	    TDes& aWrappedString );

   /**
	* Wraps a string (aStringToWrap) into lines according to the
	* number of lines and line widths specified in aLineWidthArray. 
	* Inserts '\n' at the end of lines. 
	* Clips the last line if there aren't enough lines to
	* fit the entire string. 
	* Copies the result into aWrappedString.
    * Leaves if aWrappedString isn't big enough.
    *
    * @param aStringToWrap      String that needs to be wrapped
    * @param aLineWidthArray    Width of lines in pixels
    * @param aFont              Used font
    * @param aWrappedString     Wrapped string 
    */
	IMPORT_C static void WrapToStringAndClipL(
	    const TDesC& aStringToWrap, 
	    const CArrayFix<TInt>& aLineWidthArray, 
	    const CFont& aFont, 
	    TDes& aWrappedString ); 

    /**
     * This routine is used to strip away a set of characters from
     * a descriptor.
     *
     * Useful for example for listboxes to make sure strings from
     * network or typed by the end user does not have tab or linefeed
     * characters. (as those will make listbox broken.)
     * 
     * @param   aDes         Parameter to change
     * @param   aCharacters  A set of characters to remove
     *
     * There exists predefined character sets to remove:
     *    KAknStripTabs
     *    KAknStripListControlChars  (\t's and \n's and \r's)
     */
    IMPORT_C static void StripCharacters(TDes &aDes, const TDesC &aCharacters);

    /**
     * This routine is used to replace all control chars with a single 
     * character, usually a whitespace.
     *
     * @param   aDes         Parameter to change
     * @param   aCharacters  A set of characters to remove
     * @param   aReplacement a character used as replacement
     *
     *    KAknReplaceTabs
     *    KAknReplaceListControlChars  (\t's and \n's)
     */
    IMPORT_C static void ReplaceCharacters(TDes &aDes, const TDesC &aChars, TChar aReplacement);

    /**
     * This routine is used to remove extra whitespaces from text before 
     * showing on screen
     *
     * @param   aDes                   Parameter to change
     * @param   aWhiteSpaceCharacters  A set of whitespace characters to remove
     */
    IMPORT_C static void PackWhiteSpaces(TDes &aDes, const TDesC &aWhiteSpaceChars);

    // non-exported implementation

    static void WrapToStringL(
        const TDesC& aStringToWrap, 
	    const CArrayFix<TInt>& aLineWidthArray, 
	    const CFont& aFont, 
	    TDes& aWrappedString,
        TBool aClip );

    static void WrapToArrayL( 
        const TDesC& aStringToWrap,
        const CArrayFix<TInt>* aLineWidthArray, 
        const CFont& aFont,
        CArrayFix<TPtrC>& aWrappedArray,
        TInt aLineWidth,
        TBool aClip );

    static void ChopToArrayAndClipL(
		TDes& aStringToChop,             
	    const CArrayFix<TInt>* aLineWidthArray,
	    const CFont& aFont,                 
	    CArrayFix<TPtrC>& aChoppedArray,
        TInt aLineWidth );    

    static TInt FindLineBreak( const TDesC& aText );
    static TInt FindNextWrappablePlace( const TDesC& aText, TInt& aIndex );
    static TBool CanWrapBeforeOrAfter( const TText aChar );
    static TBool CanOnlyWrapAfter( const TText aChar, const TText aPreviousChar );
    static TBool IsSpace( const TText aChar );

    static TInt InsertEllipsis( 
        const TDesC& aText,
        TInt aEllipsisIndex,
        const CFont& aFont,
        TInt aLineWidth );


	/**
	* This utility is used to see if a text is empty according to the conventions of 
	* Avkon.
	*
	* @param	aTextToTest
	* @return	ETrue if the text is empty according to Avkon
	*/
	static TBool IsEmptyText( const TDesC& aTextToTest );
    };

_LIT(KAknStripTabs, "\t");
_LIT(KAknStripListControlChars, "\t\n");
_LIT(KAknReplaceTabs, "\t");
_LIT(KAknReplaceListControlChars, "\t\n");
_LIT(KAknCommonWhiteSpaceCharacters, " \n\t\r");

/**
 * These are part of Selection service and they should be called by application's HandleCommandL() to get
 * menus and cba's handled automatically for selection service.
 *
 * The right way to implement these would be to have dialogs with names "Selection List", "MultiSelection List"
 * and "Markable list" and make them keep a listbox inside it. (look at CAknPopupList, it does similar things)
 *
 * See CAknSelectionListDialog and CAknMarkableListDialog from aknselectionlist.h, they provide better
 * interface for applications.
 */
class AknSelectionService
    {
public:
    /** Helper function to implement ProcessCommandL() for selection list dialogs
     */
    IMPORT_C static void HandleSelectionListProcessCommandL(TInt aCommand, CEikListBox* aListBox);
    /** Helper function to implement ProcessCommandL() for selection list dialogs
     */
    IMPORT_C static void HandleMultiselectionListProcessCommandL(TInt aCommand, CEikListBox* aListBox);
    /** Helper function to implement ProcessCommandL() for markable list dialogs
     */
    IMPORT_C static void HandleMarkableListProcessCommandL(TInt aCommand, CEikListBox* aListBox);

    /** Helper function to implement ProcessCommandL() for menu lists
     */
    IMPORT_C static TKeyResponse HandleMenuListOfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType, CEikListBox* aListBox);
    /** Helper function to implement DynInitMenuPaneL() for markable list dialogs
     */
    IMPORT_C static void HandleMarkableListDynInitMenuPane(TInt aResourceId, CEikMenuPane *aMenu, CEikListBox *aListBox);
    /** Helper function to implement DynInitMenuPaneL() for markable list dialogs
     */
    IMPORT_C static void HandleMarkableListDynInitMenuItem(CEikMenuPane *aMenu, CEikListBox *aListBox, TInt aCommandId, TBool aCanBeAppliedToMultipleItems);
    /** Helper function to implement command handling for markable list dialogs
     */
    IMPORT_C static void HandleMarkableListUpdateAfterCommandExecution(CEikListBox *aListBox);

    /** Helper function to position list highlight correctly after item removal
     */
    IMPORT_C static void HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aValueOfCurrentItemIndexBeforeRemoval, TBool aCurrentItemWasRemoved);
    // This one updates selectionindexes too.
    /** Helper function to position list highlight correctly after item removal
     *
     * It also updates selection index array based on information about which
     * items were removed.
     */
    IMPORT_C static void HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aValueOfCurrentItemIndexBeforeRemoval, CArrayFix<TInt> &aIndexesOfRemovedItemsBeforeRemoval);
    };



class CAknSearchField;

/** This class implments Find requirements from component specifications
 * This class works also as documentation of how to use different find components. (The implementation has been
 * copied from the example application which implements find and replaced the code with calls to these static
 * functions)
 *
 * There is no reason for an application to use this class directly.
 * Application should use CAknSelectionListDialog instead. This class
 * is public only because sometimes it is necessary to access the
 * low level behaviour of find to implement similar functionality in
 * places independent of find; or if CAknSelectionListDialog is not
 * used for some reason.
 */
class AknFind
    {
public:
    IMPORT_C static void HandleFindPopupProcessCommandL(TInt aCommand, CEikListBox *aListBox, CAknSearchField *aSearchField, CCoeControl *aParentControl);
    IMPORT_C static TKeyResponse HandleFindOfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType, CCoeControl *aListBoxParent, CEikListBox *aListBox, CAknSearchField *aSearchField, TBool isFindPopup, TBool &aNeedRefresh);

    /** Note: If ispopup == EFalse, you can only use lists that use CAknColumnListBoxView!
     * => FormattedCell lists can only use popup find!
     *
     * NOTICE: HandleFindSizeChanged is deprecated!
     */
    IMPORT_C static void HandleFindSizeChanged(CCoeControl *aParentControl, 
					       CEikListBox *aListBox, 
					       CAknSearchField *aSearchField, 
					       TBool ispopup = ETrue, 
					       TInt aFindWindowResourceId = R_AVKON_POPUP_FIND_WINDOW, 
					       TInt aListResourceId = R_AVKON_LIST_GEN_PANE, 
					       TInt aListResourceIdWithFindPopup = R_AVKON_LIST_GEN_PANE_WITH_FIND_POPUP, 
					       TInt aFindWindowParentResourceId = R_AVKON_MAIN_PANE_WITH_STATUS_PANE);


    /** This is the new typesafe(and easier to use) version of HandleFindSizeChanged. Use this instead of (deprecated) HandleFindSizeChanged().
     */
    IMPORT_C static void HandleFixedFindSizeChanged(CCoeControl *aParentControl,
						    CAknColumnListBox *aListBox, // only available with column lists
						    CAknSearchField *aSearchField);
    
    /** This is the new typesafe(and easier to use) version of HandleFindSizeChanged. Use this instead of (deprecated) HandleFindSizeChanged().
     */
    IMPORT_C static void HandlePopupFindSizeChanged(CCoeControl *aParentControl,
						    CEikListBox *aListBox,  // available with all lists.
						    CAknSearchField *aSearchField);

public:
    /**
     * Returns ETrue if list box item text aItemText matches aSearchText in the 
     * sense described in Series 60
     */
    IMPORT_C static TBool IsFindMatch(const TDesC& aItemText, const TDesC& aSearchText);

    /**
     * Returns ETrue if aCh is a word separator character as described in Series 60
     */
    IMPORT_C static TBool IsFindWordSeparator(TChar aCh);


    /**
     * Helper function to handle find pane's visibility
     */
    static void HandleFindPaneVisibility(CAknSearchField *aSearchField, TBool ispopup, TBool textchanged, TBool &aNeedRefresh);

    };


/** 
 * Utility class to initialize editor control. 
 * Use this in conjunction with AknLayoutUtils::LayoutEdwin()
 * The class is not fully implemented yet.
 */
class AknEditUtils
    {
    public:
    struct SAknEditorParameters 
	{
	TInt iEditingSpace;
	TInt iEditingWindow;
	TInt iCharacterCase;
	TInt iJustification;
	TBool iAllowedToMoveInsertionPoint;
	TBool iCursorYesNo;
	TBool iOverflowYesNo;
	};

    IMPORT_C static void ConstructEditingL(CEikEdwin* aEdwin, TInt aResourceId);
    IMPORT_C static void ConstructEditingL(CEikEdwin* aEdwin, TResourceReader& aReader);
    IMPORT_C static void ConstructEditingL(CEikEdwin* aEdwin, const SAknEditorParameters &aParams);

/**
 *  Configures edwin editor. Use AknLayoutUtils::LayoutEdwin() with this method.
 *
 *  @param aEdwin Edwins created with new.
 *  @param aEditingSpace maximum number of characters for the editor
 *  @param aEditingWindow maximum number of lines in the editor
 *  @param aCharacterCase initial character case:
 *          EAknEditorCharactersUpperCase = EAknEditorUpperCase,
 *	        EAknEditorCharactersLowerCase = EAknEditorLowerCase,
 *	        EAknEditorCharactersTextCase = EAknEditorTextCase,
 *          EAknEditorCharactersTitleCase = EAknEditorTitleCase
 *
 *  @param aJustification alignment for the editor text ( EAknEditorAlignCenter, 
 *         EAknEditorAlignLeft, EAknEditorAlignRight)
 *  @param aAllowedToMoveInsertionPoint user can move cursor
 *  @param aCursorYesNo is cursor visible or not.
 *  @param aOverflowYesNo
 */
    IMPORT_C static void ConstructEditingL(CEikEdwin* aEdwin, 
					   TInt aEditingSpace, 
                       TInt aEditingWindow, 
                       TInt aCharacterCase, 
                       TInt aJustification, 
                       TBool aAllowedToMoveInsertionPoint, 
                       TBool aCursorYesNo, 
                       TBool aOverflowYesNo);

    };

/** Automatic numbering for list items. (DEPRECATED)
 * Just create this kind of object and attach it to a listbox, and you'll
 * have automatic numbering. 
 *
 *
 * You'll need to call UpdateL() each time you modify the listbox's model!
 */
class CListBoxNumbers : public CBase
	{
public:
	IMPORT_C CListBoxNumbers(CEikTextListBox* aListBox);
	IMPORT_C void ConstructL();
	IMPORT_C void UpdateL();
private:
	CEikTextListBox* iListBox;
	};

class CAknListBoxFilterItems;

/** This class shows how application should build its model for filtered items. 
 *
 * Notice, application should not use this directly, if he has his own model or if there's
 * any special things needed for MatchableTextArray(). Application can derive from this though.
 *
 * All listboxes use CAknFilteredTextListBoxModel by default. CreateFilter call enables it.
 */
class CAknFilteredTextListBoxModel : public CTextListBoxModel, private MDesCArray
    {
public: // public interface for apps
    /**
     * Creates a CAknListBoxFilterItems and thus enables filtering of list items.
     */
    IMPORT_C void CreateFilterL(CEikListBox* aListBox, CAknSearchField* aSearchField);
    /**
     * Access function for the filter
     */
    IMPORT_C CAknListBoxFilterItems* Filter() const;
    /**
     * Destructor
     */
    IMPORT_C ~CAknFilteredTextListBoxModel();
public: // from CTextListBoxMode
    /**
     * Implementation of CTextListBoxModel::NumberOfItems()
     */
    IMPORT_C virtual TInt NumberOfItems() const;
    /**
     * Implementation of CTextListBoxModel::ItemText()
     */
    IMPORT_C virtual TPtrC ItemText(TInt aItemIndex) const;
public: // from MEikTextListBoxModel (default filtering string conversions)
    /**
     * Implementation of CTextListBoxModel::MatchableTextArray()
     */
    IMPORT_C const MDesCArray* MatchableTextArray() const;

private:
    CAknListBoxFilterItems* iFilter; // owned
private: // From MdesCArray (these implement default matchabletextarray for filtering.)
    IMPORT_C TInt MdcaCount() const;
    IMPORT_C TPtrC MdcaPoint(TInt aIndex) const;
private: // from MListBoxModel
	IMPORT_C virtual TAny* MListBoxModel_Reserved();
    };

/** Listbox item filtering
 *
 * This module has methods you need to call from your own model
 *
 * This class is designed to be stored inside a listbox model and the model should call this
 * in its NumberOfItems() and ItemText() implementation. The model must be given to this class
 * and it must have MatchableTextArray() implemented correctly.
 *
 * HandleOfferKeyEvent() should be called from the same offerkeyevent implementation which forwards the
 * keys to listbox and searchfield
 *
 * If you have both markable list and Find at the same time, you should call ResetFiltering() before
 * executing the command for marked items. This ensures that the ListBox's SelectionIndexes() returns
 * all items instead of only those items that are visible.
 *
 * This will modify list's SelectionIndexes() to move selected items when
 * list is filtered. All selected items can be found under 
 * CAknListBoxFilterItems::SelectionIndexes().
 * 
 */
class CAknListBoxFilterItems : public CBase, public MCoeControlObserver
    {
public:
    IMPORT_C CAknListBoxFilterItems(CEikListBox *aListBox, CAknSearchField *aSearchField, MListBoxModel *aModel, CListBoxView *aView);
    IMPORT_C void ConstructL(); // for setting empty list text.
    /** ResetFiltering
     *
     * To be called when filter is cleared
     */
    IMPORT_C void ResetFilteringL();
    /** 
     * The next one will update FilterItems state from the
     * searchfield and listbox.
     */
    IMPORT_C void UpdateCachedDataL(); // updates iOldSearchCriteria and selection indexes.
    IMPORT_C ~CAknListBoxFilterItems();    

public: 
    /** this one gives all indexes, not just the ones that are visible.
     */
    IMPORT_C CArrayFix<TInt> *SelectionIndexes();
    /** This will syncronize the selection indexes from the listbox.
	If you use SelectionIndexes(), call this before...

	This is heavy operation - goes through all list items. Need to be 
        called if listbox's SelectionIndexes might have changed...
     */
    IMPORT_C void UpdateSelectionIndexesL();
    IMPORT_C void UpdateSelectionIndexL(TInt aVisibleIndex);

public: // Applications should call this in their listbox model implementation
    /** FilteredNumberOfItems() is like MdcaCount(), it is used to ask how many list items
     *  are available after filter has been used. Counts visible list items.
     */
    IMPORT_C TInt FilteredNumberOfItems() const;
    /** FilteredItemIndex is like MdcaPoint(TInt). It is used to fetch the content of a list
     *  item after filter has been used. The content is indexes to the real list item array.
     *  Thus we return TInt from this.
     * @param aVisibleItemIndex the list item index. This counts the visible items only.
     * @return index to the original item array.
     */
    IMPORT_C TInt FilteredItemIndex(TInt aVisibleItemIndex) const;

public: // Needed to change the correct item.

    /** NonFilteredNumberOfItems() returns number of original list items.
     */
    IMPORT_C TInt NonFilteredNumberOfItems() const; // this always returns >= FilteredNumberOfItems()
    /** 
     * Finds the list item on the screen when the item array index is given.
     *
     * @param aOriginalIndex finds index of list item when item from the original array is given.
     *
     * VisibleItemIndex returns -1 if the aOriginalIndex is not visible.
     */
    IMPORT_C TInt VisibleItemIndex(TInt aOriginalIndex) const;
public: 
    /** For building MdcaPoint() of the model's MatchableTextArray.
     *
     *  This method builds the default value for MatchableTextArray.
     */
    IMPORT_C TPtrC DefaultMatchableItemFromItem(TPtrC aText);

public: 
    /** Applications should call this in offerkeyevent which gives keys to listbox and searchfield.
     */
    IMPORT_C void HandleOfferkeyEventL();
    /** 
     *	When you change the whole list item array, call this method to let find also know about the change.
     */
    IMPORT_C void HandleItemArrayChangeL();

public: // MCoeControlObserver
    /**
     * Gives ability to follow what events searchfield gives to find. Standard observer API.
     */
    IMPORT_C void SetObserver(MCoeControlObserver *aObserver);
    /**
     * Searchfield calls this method to inform about changes in find state.
     */
    IMPORT_C void HandleControlEventL(CCoeControl *aControl, TCoeEvent aEventType);

public: // For FEP
    /**
     * Sends key events to fep. This is used to resend key event to fep if AknFind's HandleOfferKeyEventL()
     * gets the key while searchfield has no focus. If searchfield has a focus, the key events go directly
     * to the editor and this is not called.
     *
     * NOTE, this method does only handle single key event at the time and it sends KEYDOWN, KEYEVENT and KEYUP 
     * events.
     */
    IMPORT_C void DeferredSendKeyEventToFepL(TUint aValue);
    /**
     * This does the actual sending of a key event. Does not support more than one event at the time.
     */
    static TInt IdleCallBack(TAny *aFilterItems);

public: // For size changed
    /**
     * AknFind uses this to inform us who is the parent control owning the listbox and searchfield.
     * This control should be window-owning control and it will be used to resize the listbox when
     * changes to the filtering happens.
     */
    IMPORT_C void SetParentControl(CCoeControl *aControl);
   /**
    * AknFind uses this to inform us that we have popup find. Applications shouldnt call this. 
    * Instead, you should use CAknSelectionListDialog or AknFind.
    */
    IMPORT_C void SetPopup();

public:
    IMPORT_C CCoeControl *FindBox() const;

private:
    void NoCriteriaL(); // remove criteria completely.
    void TightenCriteriaL(const TDesC& aCriteria); // slow operation (do when adding new characters to search criteria)
    void ReleaseCriteriaL(const TDesC& aCriteria); // very slow operation (do when removing characters from search criteria)
    // EmptyListText handling
    void InstallEmptyTextL();
    void UninstallEmptyTextL();
    // Selections -- these methods form a pair, 
    // you must call Fetch first and then push.
    void FetchSelectionIndexesFromListBoxL();
    void PushSelectionIndexesToListBoxL();

    // HandleItemAddition without ResetFilteringL() call
    void HandleItemAdditionL();
    void HandleItemRemovalL();
private:
    TBool IsItemVisible(const TDesC& aMatchableItemString, const TDesC& aSearchText);
    static TBool IsSeparatorCharacter(TChar c);
    TBool IsItemSelected(TInt aRealIndex) const;
private:
    CArrayFix<TInt> *iShownIndexes; // own // uses non-filtered indexes
    CArrayFix<TInt> *iSelectionIndexes; // own   // this uses non-filtered indexes
    HBufC *iOldSearchCriteria; // own
    MListBoxModel *iModel;
    CListBoxView *iView;
    TInt iOldItemCount;
    HBufC* iEmptyListText; // own
    CEikListBox* iListBox;
    CAknSearchField* iSearchField;
    TBuf<256> iMatchableText;
    MCoeControlObserver *iObserver;
    CFindExtension *iExtension;
    TUint iKeyValue;
    CCoeControl *iParentControl;
    TBool iIsPopup;
    TBool iDisableChangesToShownIndexes;
    };


/** Removing optimization that breaks listbox views 
 * A view which removes optimization from CListBoxView which breaks with lists where all items are not
 * the same layout.
 * Use it like this: 
 *   CListBoxView* MakeViewClassInstanceL() { return new(ELeave) NoOptimizationView<CListBoxView>; }
 */
template<class T>
class NoOptimizationView : public T
    {
public:
    virtual void VScrollTo(TInt aNewTopItemIndex, TRect& aMinRedrawRect)
	{
	// AVKON LAF
	if (RedrawDisabled())
		return;
	if (iTopItemIndex == aNewTopItemIndex)
		return;
	aMinRedrawRect.SetRect(iViewRect.iTl,iViewRect.Size());
	SetTopItemIndex(aNewTopItemIndex);
	Draw(&aMinRedrawRect);
	// end of AVKON LAF
	}
    };


/** This is private class, do not use it except for drawing controls!
 * 
 * Do not use it in applications.
 */


class AknLAFUtils 
	{
public:
	static void DrawLines(CGraphicsContext* aGc, 
			      const TRect& mainpane,
			      TInt x);
	IMPORT_C static void ReplaceColumn(TPtr aTarget, TDesC* aSource, TDesC* aReplacement, TChar aColumnSeparator, TInt aColumn);
	};


/**
 * Resource reader class
 *
 * This is utility class for reading listbox resouces.
 *
 * This should be derived from and it reads resource file for you.
 *
 * This seems to be only used by listbox resource readers. (Do not use it in applications)
 */
struct SAknLayoutGfx;
struct SAknLayoutText;
struct SAknLayoutCmd;
struct SAknLayoutGfx;
// Not for apps
struct SAknLayoutPos 
    {
    TInt l, t, r, b, W, H;

    typedef SAknLayoutPos ItemType;
    static void ReadResource(TResourceReader& aReader, ItemType& aTarget);    
    };
template<class T> class CArrayReader;
class CAknGenericReader : public CBase
    {
public:
    IMPORT_C void ConstructL(TInt aResourceId);
    IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
    IMPORT_C ~CAknGenericReader();

    IMPORT_C const SAknLayoutGfx* GfxItem(TInt aIndex) const;
    IMPORT_C const SAknLayoutText* TextItem(TInt aIndex) const;
    IMPORT_C const SAknLayoutCmd* CmdItem(TInt aIndex) const;
    IMPORT_C const SAknLayoutGfx* AreaItem(TInt aIndex) const;

    CArrayReader<SAknLayoutGfx>* iGfx;
    CArrayReader<SAknLayoutText>* iText;
    CArrayReader<SAknLayoutCmd>* iCmd;
    CArrayReader<SAknLayoutGfx>* iArea;
    };



// Use this to mark that the position in LAF specification is empty.
const TInt AknLayoutUtilsNoValue = ELayoutEmpty;

/** Utility classes to build layout based on European LAF from resource files. (can be used by applications)
 *
 * Methods in this class are designed to be called from your control's SizeChanged() method!
 *
 * This class knows the specification's coordinate data format and ensures that different types of
 * controls are positioned and setup correctly according to European LAF. 
 * 
 * This class helps you with positioning labels, controls, rects and other things to according to LAF specification.
 * (It is NOT trivial to get it correct and this adjusts easily to changes in the LAF specification - if you're not
 * using this, remember to read the whole LAF specification - especially the beginning and the end with color and
 * especially how text margins and widths interact!!)
 *
 * (idea of this class is that when specification of one component changes, only resource file needs to be changed and when you 
 * get new product with new specification format, only this module needs to be changed and resources rewritten from the specification. 
 * And when component's specification changes, only the component need to be changed (usually only change is what components are
 * inside it and how it calls this module.).. => all controls have common format that decides its layout!
 *
 * Parent rectangles are always coordinates of LAF specification's parent rectangle in the screen.
 * 
 * To use this, call one of the methods in your SizeChanged() and then you'll need to make sure you
 * draw the area between controls using ClearBetweenRects() call from egul library. (CCoeControl::Rect() helps with that...)
 *
 * A Tip: You do not want to use any dynamic calculation of layouts! It is almost always an error to do so!
 *        => Do not allow layouts that have not been specified!
 *
 * (If LAF spec has many numbers and you need to dynamically choose between them, then keep the numbers in
 * code as function-local using SAknLayoutText/SAknLayoutRect/... -structs..)
 *
 * You'll want to use TAknLayoutRect and TAknLayoutText too to build layout
 * for your custom controls.
 */
class AknLayoutUtils
    {
public:

    struct SAknLayoutText
	{
	TInt iFont, iC, iL, iR, iB, iW, iJ;
	};
    struct SAknLayoutTextMultiline
	{
	TInt iFont, iC, iL, iR, iB, iW, iJ, iNumberOfLinesShown, iNextLineB;
	};
    typedef SAknLayoutTextMultiline SAknLayoutLabel;
    typedef SAknLayoutTextMultiline SAknLayoutEdwin;
    typedef SAknLayoutText SAknLayoutMfne;
    typedef SAknLayoutText SAknLayoutSecEd;
    struct SAknLayoutRect
	{
	TInt iC, iL, iT, iR, iB, iW, iH;
	};
    typedef SAknLayoutRect SAknLayoutControl;
    typedef SAknLayoutRect SAknLayoutImage;

    /** Sets CEikLabel's position, colors and fonts based on LAF specification
     * AVKON_LAYOUT_LABEL -resource is used with these
     */
    /** 
	Layouts a label via resource AVKON_LAYOUT_LABEL
	@param aLabel        the label to change
	@param aLabelParent  the parent of a label
	@param aResourceId   the resource id
	@param aCustomFont   a font used, if resource file uses EFontCustom
     */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, TInt aResourceId, const CFont* aCustomFont=0);
    /** Layouts a label via resource AVKON_LAYOUT_LABEL
	@param aReader   the resource reader
     */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, TResourceReader& aReader, const CFont* aCustomFont=0);
    /** Layouts a label via a structure of layout parameters
	@param aLayout   the structure
     */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, const SAknLayoutLabel& aLayout, const CFont *aCustomFont=0);
    /** Layouts a label via a layout compiler output
	@param aLayout   a define from aknlayout.lag file
     */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, const TAknMultiLineTextLayout& aLayout, const CFont *aCustomFont=0);
    /** Layouts a label via a layout compiler output
	@param aLayout   a define from aknlayout.lag file
     */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, const TAknTextLineLayout& aLayout, const CFont *aCustomFont=0);
    /** Layouts a label via parameters from the specification
	@param aLayout   a define from aknlayout.lag file
	@param font      font id, ELatinPlain12, ELatinBold12, ELatinBold13, ELatinBold17, ELatinBold19 etc..
	@param C         colour index, 0..255
	@param l         left margin
	@param r         right margin
	@param B         Baseline from top of the parent rectangle
	@param W         text width in pixels
	@param J         justification. ELayoutAlignNone; ELayoutAlignCenter; ELayoutAlignLeft; ELayoutAlignRight
	@param NextLineB baseline of 2nd line for multi-line labels/editors
	@param aCustomFont   a font used, if resource file uses EFontCustom
     */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, TInt font, TInt C, TInt l, TInt r, TInt B, TInt W, TInt J, TInt NextLineB=0, const CFont* aCustomFont=0);

    /** Sets CEikEdwin's position, text colors, fonts etc based on LAF specification
     * AVKON_LAYOUT_EDWIN is used with this
     */
    IMPORT_C static void LayoutEdwin(CEikEdwin* aEdwin, const TRect& aEdwinParent, TInt aResourceId, TInt aNumberOfLines = 0, const CFont* aCustomFont=0, TBool aMinimizeEdwinView=EFalse);
    /** Layouts an editor via resource AVKON_LAYOUT_LABEL
	@param aReader   the resource reader
     */
    IMPORT_C static void LayoutEdwin(CEikEdwin* aEdwin, const TRect& aEdwinParent, TResourceReader& aReader, TInt aNumberOfLines = 0, const CFont* aCustomFont=0, TBool aMinimizeEdwinView=EFalse);
    /** Layouts an editor via a structure of layout parameters
	@param aLayout   the structure
     */
    IMPORT_C static void LayoutEdwin(CEikEdwin* aEdwin, const TRect& aEdwinParent, const SAknLayoutEdwin& aLayout, const CFont* aCustomFont=0, TBool aMinimizeEdwinView=EFalse);
    /** Layouts an editor via a structure of layout parameters
	@param aLayout   the structure
     */

	IMPORT_C static void LayoutEdwin(CEikEdwin* aEdwin, const TRect& aEdwinParent, const TAknMultiLineTextLayout& aLayout, const CFont* aCustomFont=0, TBool aMinimizeEdwinView=EFalse);
 

   IMPORT_C static void LayoutEdwin(CEikEdwin* aEdwin, const TRect& aEdwinParent, const TAknTextLineLayout& aLayout, const CFont* aCustomFont=0, TBool aMinimizeEdwinView=EFalse);
    /** Layouts an editor via parameters from the specification
	@param aLayout   a define from aknlayout.lag file
	@param font      font id, ELatinPlain12, ELatinBold12, ELatinBold13, ELatinBold17, ELatinBold19 etc..
	@param C         colour index, 0..255
	@param l         left margin
	@param r         right margin
	@param B         Baseline from top of the parent rectangle
	@param W         text width in pixels
	@param J         justification. ELayoutAlignNone; ELayoutAlignCenter; ELayoutAlignLeft; ELayoutAlignRight
	@param aNumberOfLinesShown number of lines visible for the editor
	@param NextLineB baseline of 2nd line for multi-line labels/editors
	@param aMinimizeEdwinView whether to use minimum size. You need to use MinimizedEdwinRect() if you use ETrue here.
     */
    IMPORT_C static void LayoutEdwin(CEikEdwin* aEdwin, const TRect& aEdwinParent, TInt font, TInt C, TInt l, TInt r, TInt B, TInt W, TInt J, TInt aNumberOfLinesShown, TInt aNextLineBaseline, const CFont* aCustomFont=0 , TBool aMinimizeEdwinView=EFalse);
    /** Use this, if you give aMinimizeEdwinView to LayoutEdwin as true.
     * The edwin will not draw the whole rectangle allocated for the control.
     */
    IMPORT_C static TRect MinimizedEdwinRect(const CEikEdwin *aEdwin);


    /** Sets CEikMfne's position, text colors, fonts etc based on LAF specification
     * AVKON_LAYOUT_MFNE is used with this
     */
    IMPORT_C static void LayoutMfne(CEikMfne* aMfne, const TRect& aMfneParent, TInt aResourceId);
    IMPORT_C static void LayoutMfne(CEikMfne* aMfne, const TRect& aMfneParent, TResourceReader& aReader);
    IMPORT_C static void LayoutMfne(CEikMfne* aMfne, const TRect& aMfneParent, const SAknLayoutMfne& aLayout);
    IMPORT_C static void LayoutMfne(CEikMfne* aMfne, const TRect& aMfneParent, const TAknTextLineLayout& aLayout);
    IMPORT_C static void LayoutMfne(CEikMfne* aMfne, const TRect& aMfneParent, TInt font, TInt C, TInt l, TInt r, TInt B, TInt W, TInt J);

    /** Placing controls based on LAF specification
     * does SetRect() for any control based on LAF specification
     * AVKON_LAYOUT_CONTROL is used with these.  (Currently it ignores the C parameter)
     */
    IMPORT_C static void LayoutControl(CCoeControl* aControl, const TRect& aControlParent, TInt aResourceId);
    IMPORT_C static void LayoutControl(CCoeControl* aControl, const TRect& aControlParent, TResourceReader& aReader);
    IMPORT_C static void LayoutControl(CCoeControl* aControl, const TRect& aControlParent, const SAknLayoutControl& aLayout);
    IMPORT_C static void LayoutControl(CCoeControl* aControl, const TRect& aControlParent, const TAknWindowLineLayout& aLayout);
    IMPORT_C static void LayoutControl(CCoeControl* aControl, const TRect& aControlParent, TInt /*C*/, TInt l, TInt t, TInt r, TInt b, TInt W, TInt H);

    /** Sets CEikImage's position, colors and fonts based on LAF specification
     * AVKON_LAYOUT_IMAGE -resource is used with these
     */
    IMPORT_C static void LayoutImage(CEikImage* aImage, const TRect& aParent, TInt aResourceId);
    IMPORT_C static void LayoutImage(CEikImage* aImage, const TRect& aParent, TResourceReader& aReader);
    IMPORT_C static void LayoutImage(CEikImage* aImage, const TRect& aParent, const SAknLayoutControl& aLayout);
    IMPORT_C static void LayoutImage(CEikImage* aImage, const TRect& aParent, const TAknWindowLineLayout& aLayout);
    IMPORT_C static void LayoutImage(CEikImage* aImage, const TRect& aParent, TInt C, TInt l, TInt t, TInt r, TInt b, TInt W, TInt H);

    /** Sets CEikSecretEditor's position, colors and fonts based on LAF specification
     *
     */
    IMPORT_C static void LayoutSecretEditor(CEikSecretEditor* aSecEd, const TRect& aParent, const SAknLayoutText& aLayout);
    IMPORT_C static void LayoutSecretEditor(CEikSecretEditor* aSecEd, const TRect& aParent, const TAknTextLineLayout& aLayout);

public:
    /** Different conversions
     * Fonts: ELatinPlain12, ELatinBold12, ELatinBold13, ELatinBold17, ELatinBold19, ENumberPlain5, ClockBold30, LatinClock14, ECustomFont
     * Alignments: ELayoutAlignNone, ELayoutAlignCenter, ELayoutAlignLeft, ELayoutAlignRight with these..
     */
    IMPORT_C static TRect TextRectFromCoords(const TRect& aParent, const CFont* aFont, TInt l, TInt r, TInt B, TInt W, TInt LB = 0);
    IMPORT_C static TRect RectFromCoords(const TRect& aParent, TInt l, TInt t, TInt r, TInt b, TInt W, TInt H);
    IMPORT_C static const CFont* FontFromId(TInt aFontId, const CFont* aCustomFont=0);
    IMPORT_C static const CFont* FontFromName(const TDesC& aName); 

	IMPORT_C static CGraphicsContext::TTextAlign TextAlignFromId(TInt aId);
    IMPORT_C static TGulAlignment GulAlignFromId(TInt aId);

	IMPORT_C static TInt CursorHeightFromFont(const TFontSpec& aFont);
	IMPORT_C static TInt CursorWidthFromFont (const TFontSpec& aFont);
	IMPORT_C static TInt CursorAscentFromFont(const TFontSpec& aFont);
	IMPORT_C static void CursorExtensionsFromFont(const TFontSpec& /*aFont*/, TInt& aFirstExtension, TInt& aSecondExtension);

	IMPORT_C static TInt HighlightLeftPixelsFromFont (const TFontSpec& aFont);
	IMPORT_C static TInt HighlightRightPixelsFromFont(const TFontSpec& aFont);
    static void HighlightExtensionsFromFont(const CFont* aFont, TInt& aLeft, TInt& aRight, TInt&  aTop, TInt& aBottom);

	IMPORT_C static EVariantFlag Variant();
	IMPORT_C static ESubVariantFlag SubVariant();
    };

/** Low level drawing based on European LAF document (can be used by application's custom controls)
 *
 * This class reads AVKON_LAYOUT_TEXT resources
 */
class TAknLayoutText
    {
public:
    IMPORT_C TAknLayoutText();
    /** Read resources and calculate information needed to draw text.
     *
     * LayoutText() call should be placed to control's SizeChanged() method.
     */
    IMPORT_C void LayoutText(const TRect& aParent, TInt aResourceId, const CFont* aCustomFont=0);
    IMPORT_C void LayoutText(const TRect& aParent, TResourceReader& aReader, const CFont* aCustomFont=0);
    IMPORT_C void LayoutText(const TRect& aParent, const AknLayoutUtils::SAknLayoutText& aLayout, const CFont* aCustomFont=0);
    IMPORT_C void LayoutText(const TRect& aParent, const TAknTextLineLayout& aLayout, const CFont* aCustomFont=0);
    IMPORT_C void LayoutText(const TRect& aParent, TInt fontid, TInt C, TInt l, TInt r, TInt B, TInt W, TInt J, const CFont* aCustomFont=0);

    /** Do the actual drawing, should be placed to control's Draw() method.
     */
    IMPORT_C void DrawText(CGraphicsContext& aGc, const TDesC& aText) const;
public:
    /** This returns rectangle that is used to draw the text.
     *
     * This allows you to divide screen space for egul's TextUtils::ClearBetweenRect()
     * without knowing exact coordinates => when coordinates change, your code does not need to change.
     */
    IMPORT_C TRect TextRect() const;
    const CFont *Font() const { return iFont; }
    TRgb Color() const { return AKN_LAF_COLOR_STATIC(iColor); }
    CGraphicsContext::TTextAlign Align() const { return iAlign; }
private:
    TRect iTextRect;
    const CFont *iFont; // not owned..
    TInt iColor;
    TInt iOffset;
    CGraphicsContext::TTextAlign iAlign;
    };

/** Low level rectangle management based on European LAF document (can be used by application's custom controls)
 * 
 * This allows you to draw images, rectangles, lines or just calculate rectangles based on LAF spec.
 *
 * This class reads AVKON_LAYOUT_RECT resources.
 *
 * Instances of this class should be placed inside controls for reading low level layout from resources.
 */
class TAknLayoutRect
    {    
public:
    IMPORT_C TAknLayoutRect();
    /** LayoutRect should be called from control's SizeChanged() method.
     */
    IMPORT_C void LayoutRect(const TRect &aParent, TInt aResourceId);
    IMPORT_C void LayoutRect(const TRect &aParent, TResourceReader &aReader);
    IMPORT_C void LayoutRect(const TRect &aParent, const AknLayoutUtils::SAknLayoutRect &aLayout);
    IMPORT_C void LayoutRect(const TRect &aParent, const TAknWindowLineLayout &aLayout);
    IMPORT_C void LayoutRect(const TRect &aParent, TInt C, TInt l, TInt t, TInt r, TInt b, TInt W, TInt H);
    
    /** Color() can be called from control's Draw() method. 
	
	DO NOT CALL it in SizeChanged(), ConstructL() or ActivateL() method, because 
	it messes up color scheme changes. Especially if you're using colors 226-248.
	If you store color values, be prepared to update TRgb's you store when color
	palette is changed! Best thing to do is to make your Draw() methods call
	AKN_LAF_COLOR().
     */    
    IMPORT_C TRgb Color() const;
    /** Rect() can be called from control's Draw() or in SizeChanged() as input for some other table's layout code.
     */
    IMPORT_C TRect Rect() const;

    /** DrawRect() and DrawImage() should be called from control's Draw() method.
     */
    IMPORT_C void DrawRect(CWindowGc& aGc) const;
    IMPORT_C void DrawOutLineRect(CWindowGc& aGc) const;
    IMPORT_C void DrawImage(CBitmapContext& aGc, CFbsBitmap* aBitmap, CFbsBitmap* aMask) const;
private:
    TInt iColor;
    TRect iRect;
    };

/**
 * Helper functions for drawing empty lists and window shadows
 */
class AknDraw 
    {
public:
    /** 
	Draws standard empty list
	@param aRect the client rectangle
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyList(const TRect& aRect, CWindowGc& aGc, TPtrC aText);
    /** 
	Draws empty list for setting item editing
	@param aRect the rectangle of setting page's content
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyListForSettingPage(const TRect &aRect, CWindowGc &aGc, TPtrC text); // only for setting page with empty layout.
    /** 
	Draws empty list for lists with find
	@param aRect the client rectangle
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyListWithFind(const TRect& aClientRect, CWindowGc& aGc, TPtrC aText); // only for fixed find pane used with single graphics listbox..
    /** 
	Draws empty list for lists with heading
	@param aRect the client rectangle
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyListHeading(const TRect &aClientRect, CWindowGc& aGc, TPtrC aText); // only heading style lists.
    // The following is optimization for drawing window shadows.
    /** 
	Draws a window shadow
	@param aCoverRect the area covered by the shadow
	@param aSecondShadowRect the area used for second shadow
	@param aFirstShadowRect  the area of first shadow
	@param aOutliineFrameRect the area of black outline frame
	@param aInsideAreaRect   the area of content inside the window
     */
    IMPORT_C static void DrawWindowShadow(CWindowGc& aGc, const TAknLayoutRect& aCoverRect, const TAknLayoutRect& aSecondShadowRect, const TAknLayoutRect& aFirstShadowRect, const TAknLayoutRect& aOutlineFrameRect, const TAknLayoutRect& aInsideAreaRect);
public:

    /** 
	The main implementation routine for empty list drawing.
	@param aRect the client rectangle
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
	@param aLayoutLine1 Resource id of AVKON_LAYOUT_TEXT for first line layout 
	@param aLayoutLine2 Resource id of AVKON_LAYOUT_TEXT for second line layout 
     */
    IMPORT_C static void DrawEmptyListImpl(const TRect& aRect, CWindowGc& aGc, TPtrC aText, TInt aLayoutLine1, TInt aLayoutLine2);
    
    };



// Browser and calculator fonts will not be placed here. Application
// can use them themselves with CEikonEnv::Static()->Font() call.
IMPORT_C const CFont *LatinPlain12();
IMPORT_C const CFont *LatinBold12();
IMPORT_C const CFont *LatinBold13();
IMPORT_C const CFont *LatinBold17();
IMPORT_C const CFont *LatinBold19(); 
IMPORT_C const CFont *NumberPlain5();
IMPORT_C const CFont *ClockBold30();
IMPORT_C const CFont *LatinClock14();



IMPORT_C const CFont *ApacPlain12();
IMPORT_C const CFont *ApacPlain16();


/**
* CompletePathWithAppPath
*   All the components that are specified in the given descriptor (drive letter,
*   path and file name, including extension) are put into the result;
*   any missing components (path and drive letter) are taken from the app's path.
*
*   Can be used e.g. to load a bitmap file when an application don't know where
*   it has been installed.
*
*   Example1:
*        TFilename fname = _L("\testdir\pics.mbm"); // Use _LIT instead
*        CompletePathWithAppPath( fname );
*        Result:
*            fname == "c:\testdir\pics.mbm" if application was installed to c:
*
*   Example2:
*        TFilename fname = _L("pics.mbm"); // Use _LIT instead
*        CompletePathWithAppPath( fname );
*        Result:
*            fname == "c:\system\apps\myapp\pics.mbm" if application was 
*                installed to c:\system\apps\myapp
*
* @param    aFileName   FileName which will be completed with application's path
* @return   Error code if an error occured. In case of an error aFileName will
*               not be changed
*/
IMPORT_C TInt CompleteWithAppPath( TDes& aFileName );

#endif //  __AKNUTILS_H__

// End of file









