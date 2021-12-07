// EIKAMNT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKAMNT_H__)
#define __EIKAMNT_H__

#include <e32base.h>

class CGulIcon;
class MEikAutoMenuObserver;

/**
 * A menu title that will be added to a standard resource constructed menu bar.
 * If added to the CEikAutoMenuTitleArray stored by CEikonEnv during standard app startup, the pane specified
 * will appear in all apps.  The menu observer passed in will be notified of any events on such panes in
 * preference to the usual observer (C<MyApp>AppUi).
 */
class CEikAutoMenuTitle : public CBase
	{
public:
	enum TTitlePos { EStart, EEnd };
	enum { ENominalTextLength=40 };
public:
	IMPORT_C static CEikAutoMenuTitle* NewLC(TTitlePos aPos,const TDesC& aText,MEikAutoMenuObserver& aMenuObserver,
										TInt aMenuPaneResourceId=0,CGulIcon* aIcon=NULL);
	IMPORT_C ~CEikAutoMenuTitle();
private:
	CEikAutoMenuTitle(TTitlePos aPos,const TDesC& aText,MEikAutoMenuObserver& aMenuObserver,
										TInt aMenuPaneResourceId,CGulIcon* aIcon);
public:
	TTitlePos iPos;
	TBuf<ENominalTextLength> iText;
	MEikAutoMenuObserver& iMenuObserver;
	TInt iMenuPaneResourceId;
	CGulIcon* iIcon;
	};

/**
 * Standard Epoc array of CEikAutoMenuTitles
 * If more than one title is specified for the start or end, they will be placed in the same order they appear
 * in the array (so the first EStart in the array will be the first on a menu bar also but the last EEnd will
 * be the last).
 */
class CEikAutoMenuTitleArray : public CArrayPtrFlat<CEikAutoMenuTitle>
	{
public:
	CEikAutoMenuTitleArray();
	~CEikAutoMenuTitleArray();
	};

#endif
