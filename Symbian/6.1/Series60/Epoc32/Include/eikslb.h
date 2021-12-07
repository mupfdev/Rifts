/*
* ============================================================================
*  Name     : Eikslb.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

// EIKSLB.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKSLB_H__)
#define __EIKSLB_H__

#include <bldvariant.hrh>
#include <eikfrlb.h>
class MTextListBoxModel;
class CFont;
class CSettingsListBoxData;
class CSettingsListBoxView;

class CSettingsListBoxItemDrawer : public CFormattedCellListBoxItemDrawer
	{
public:
	IMPORT_C CSettingsListBoxItemDrawer(MTextListBoxModel* aTextListBoxModel,
					    const CFont* aFont,
					    CSettingsListBoxData* aSettingsData);

	IMPORT_C ~CSettingsListBoxItemDrawer();
	IMPORT_C CSettingsListBoxData* SettingsData() const;
public: // from CTextListItemDrawer
	IMPORT_C void DrawItemText(TInt aItemIndex,
				   const TRect& aItemTextRect,
				   TBool aItemIsCurrent,
				   TBool aViewIsEmphasized,
				   TBool aItemIsSelected) const;
private:
	IMPORT_C void CFormattedCellListBoxItemDrawer_Reserved();

	};

class CEikSettingsListBox : public CEikFormattedCellListBox
	{
public:
      	IMPORT_C CEikSettingsListBox();
public:
	IMPORT_C CSettingsListBoxItemDrawer* ItemDrawer() const;
protected:
	IMPORT_C void CreateItemDrawerL();
public: // from CEikListBox
	IMPORT_C CListBoxView* MakeViewClassInstanceL();
public: // from CCoeControl
	
protected:
	CSettingsListBoxView* View() { return (CSettingsListBoxView*)iView; }
private: // listbox use only
	IMPORT_C virtual void CEikListBox_Reserved(); 
	};

class CSettingsListBoxView : public CFormattedCellListBoxView
	{
public: // from CListBoxView
	CSettingsListBoxView() {}
	IMPORT_C void Draw(const TRect* aClipRect = NULL) const;
	IMPORT_C void DrawItem(TInt aItemIndex) const;
	inline CSettingsListBoxItemDrawer *ItemDrawer() const;
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
	};


inline CSettingsListBoxItemDrawer* CSettingsListBoxView::ItemDrawer() const
	{ return (CSettingsListBoxItemDrawer*)iItemDrawer; }


#endif



