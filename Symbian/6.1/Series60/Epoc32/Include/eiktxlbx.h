// EIKTXLBX.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
   
#if !defined(__EIKTXLBX_H__)
#define __EIKTXLBX_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__EIKLBX_H__)
#include <eiklbx.h>
#endif

#if !defined(__EIKLBM_H__)
#include <eiklbm.h>
#endif

class CTextListBoxModel;

class CEikTextListBox : public CEikListBox
	{
public:
	IMPORT_C ~CEikTextListBox();
	IMPORT_C CEikTextListBox();
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags = 0);
	IMPORT_C CTextListBoxModel* Model() const;
public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
protected:
	IMPORT_C virtual void CreateItemDrawerL();
private:
	IMPORT_C virtual void CEikListBox_Reserved(); // listbox use only
protected:
	TInt iRequiredCellCharWidth;
private:
	TInt iSpare;		// Unused
	};


class CEikSnakingTextListBox : public CEikSnakingListBox
	{
public:
	IMPORT_C ~CEikSnakingTextListBox();
	IMPORT_C CEikSnakingTextListBox();
	IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags = 0);
	IMPORT_C CTextListBoxModel* Model() const;
public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	};


#endif
