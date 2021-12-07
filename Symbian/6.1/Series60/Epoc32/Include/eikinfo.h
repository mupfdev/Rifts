// EIKINFO.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKINFO_H__)
#define __EIKINFO_H__

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif

#include <aknnotedialog.h>

class CEikInfoDialog : public CAknNoteDialog, public MEikInfoDialog
	{
public:
	///Left here for backwards compatibility
	///Not used anymore
	enum TExitKeys
		{
		EAllowEnter,
		EIgnoreEnter
		};
public:
	IMPORT_C CEikInfoDialog(const TDesC& aTitle,const TDesC& aMsg,TExitKeys aExitKeys=EAllowEnter);
	CEikInfoDialog(TExitKeys aExitKeys=EAllowEnter);
	IMPORT_C static TBool RunDlgLD(const TDesC& aTitle,const TDesC& aMsg,TExitKeys aExitKeys=EAllowEnter);
private: // from MEikInfoDialog
	TBool RunDlgLD(TInt aResource, const TDesC& aTitle, const TDesC& aMsg);
private:
	void PreLayoutDynInitL();
private: 
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();
private:
	const TDesC* iTitle;
	const TDesC* iMessage;
	};

#endif
