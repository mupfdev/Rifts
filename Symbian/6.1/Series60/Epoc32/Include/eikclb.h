// EIKCLB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCLB_H__)
#define __EIKCLB_H__

#include <eiklbi.h>
#include <eiktxlbx.h>
#include <eiklbed.h>

class CColumnListBoxData;

class CColumnListBoxItemDrawer : public CTextListItemDrawer
	{
public:
    IMPORT_C CColumnListBoxItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CColumnListBoxData* aColumnData);
    IMPORT_C ~CColumnListBoxItemDrawer();
    IMPORT_C CColumnListBoxData* ColumnData() const;
public:
	/** The SetProperties is convinience method for normal cases.
	 * NOTE that it does NOT work correctly if you can insert/delete
	 * items from the list -- You need to update all properties if
	 * any changes to the item text array happen! Often it is convinient
	 * to override the Properties() method. Further, use this only
	 * for small lists as it causes O(n) time if you need to set
	 * all properties.
	 *
	 * It has been implemented as sorted list of (index,Property) pairs.
	 */
	struct SListProperties 
	    {
	    TInt iItem; // must be first
	    TListItemProperties iProperties;
	    };
    IMPORT_C void ClearAllPropertiesL();
	/** 
	 * If you're using find, aItemIndex for this method is the same as you give in
	 * MdcaPoint() --> the default Properties() does conversion between
	 * indexes.
	 */
    IMPORT_C void SetPropertiesL(TInt aItemIndex, TListItemProperties aProperty);
    IMPORT_C virtual TListItemProperties Properties(TInt aItemIndex) const;
public: // from CTextListItemDrawer
    IMPORT_C void DrawItemText(TInt aItemIndex,const TRect& aItemTextRect,TBool aItemIsCurrent,TBool aViewIsEmphasized, TBool aItemIsSelected) const;
	// the next one is for avkon
	IMPORT_C void DrawItemMark(TBool aItemIsSelected, TBool aViewIsDimmed, const TPoint& aMarkPos) const;
public: // from CListItemDrawer
	IMPORT_C TSize MinimumCellSize() const;
	IMPORT_C TInt ItemWidthInPixels(TInt aItemIndex) const;	
private: // from CListItemDrawer
	IMPORT_C TAny* Reserved_1();
private: // defining reserved method.
	IMPORT_C void CColumnListBoxItemDrawer_Reserved();
protected:
	void DrawCurrentItemRect(const TRect& aRect) const;
	CArrayFix<SListProperties>* iPropertyArray;
	TInt iSpare;
	};

class CEikColumnListBox : public CEikTextListBox
	{
public:
	IMPORT_C CEikColumnListBox();
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
    IMPORT_C void ConstructL( const CCoeControl* aParent,TInt aFlags=0);
    IMPORT_C void EditItemL(TInt aColumn, TInt aMaxLength);
protected:
    IMPORT_C virtual void CreateItemDrawerL();
    IMPORT_C virtual void CreateModelL();
public:
    IMPORT_C CTextListBoxModel* Model() const;
    IMPORT_C CColumnListBoxItemDrawer* ItemDrawer() const;
public: // from CEikListBox
	IMPORT_C CListBoxView* MakeViewClassInstanceL();
public:	// from CCoeControl
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
private:
	IMPORT_C virtual void CEikListBox_Reserved(); // listbox use only
	};

/**
 * The CEikColumnListBoxEditor class implements an item editor for column list boxes. 
 *
 * @since ER5U
 */
class CEikColumnListBoxEditor : public CEikListBoxTextEditor
    {
public:
    IMPORT_C CEikColumnListBoxEditor(MListBoxModel* aModel);
    IMPORT_C ~CEikColumnListBoxEditor();
    IMPORT_C void ConstructL(TInt aColumn);   // just set column index
public: // from MEikListBoxEditor
    IMPORT_C TPtrC ItemText();
    IMPORT_C TBool UpdateModelL();
protected:
    IMPORT_C TInt Column() const;
private:
    TInt iColumnIndex; // refers to list box column
    };

class CColumnListBoxView : public CListBoxView
	{
public: // from CListBoxView
	IMPORT_C void Draw(const TRect* aClipRect = NULL) const;
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
	};

#endif

