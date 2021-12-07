// APGCTL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APGCTL_H__
#define __APGCTL_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

// classes defined:
class CApaSystemControl;
class CApaSystemControlList;
//
// classes referenced:
class RFs;
class CApaAppFinder;
class CApaMaskedBitmap;
//

#ifdef _UNICODE
#define KUidSystemControlDll KUidSystemControlDll16
#else
#define KUidSystemControlDll KUidSystemControlDll8
#endif

const TInt KSystemControlDllUidValue8=0x10000297;
const TUid KUidSystemControlDll8={KSystemControlDllUidValue8};
const TUid KUidSystemControlDll16={0x10003A34};


class CApaSystemControl : public CBase
	{
public:
	IMPORT_C void CreateL();
	IMPORT_C TUid Type()const;
	IMPORT_C TFileName FileName()const;
	IMPORT_C CApaMaskedBitmap* Icon()const; // one size of icon, 48x48?
	IMPORT_C TPtrC Caption()const;
	IMPORT_C TPtrC ShortCaption()const;
private:
	static CApaSystemControl* NewL(const TDesC& aFullPath,const TUidType aUidType,const TDesC& aDefaultAppInfoFileName);
	~CApaSystemControl();
	//
	CApaSystemControl();
	void ConstructL(const TDesC& aFullPath,const TUidType aUidType,const TDesC& aDefaultAppInfoFileName);
	void GetCaptionsFromFile(RFs& aFs);
	private:
	CApaSystemControl* iNext;
	RLibrary iDll;
	HBufC* iCaption;
	HBufC* iShortCaption;
	CApaMaskedBitmap* iIcon;
	TBool iExists; // used during updating
	TFileName iFullPath;
	TUidType iUidType;
	//
	friend class CApaSystemControlList;
	};


class CApaSystemControlList : public CBase
	{
public:
	IMPORT_C static CApaSystemControlList* NewL(RFs& aFs,CApaAppFinder& aCtlFinder,const TDesC& aDefaultAppInfoFileName);
	IMPORT_C ~CApaSystemControlList();
	//
	IMPORT_C TInt Count()const;
	IMPORT_C TInt Index(TUid aType)const;
	IMPORT_C CApaSystemControl* Control(TInt aIndex)const;
	IMPORT_C CApaSystemControl* Control(TUid aType)const;
	//
	IMPORT_C void UpdateL();
	inline TInt UpdateCount()const;
private:
	CApaSystemControlList(RFs& aFs,CApaAppFinder& aCtlFinder);
	void ConstructL(const TDesC& aDefaultAppInfoFileName);
	CApaSystemControl* PreviousControl(CApaSystemControl* aControl)const;
private:
	TInt iUpdateCount;
	RFs& iFs;
	HBufC* iAif; // name of the default aif containing the default control icon
	CApaAppFinder* iCtlFinder;
	CApaSystemControl* iControl;
	};


//
// inlines
//


inline TInt CApaSystemControlList::UpdateCount()const
	{ return iUpdateCount; }



#endif