// EIKALERT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKALERT_H__)
#define __EIKALERT_H__

#if !defined(__EIKDIALG_H__)
#include <eikdialg.h>
#endif

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif

#include <aknstaticnotedialog.h>

class CEikAlert : public CAknNoteDialog, public MEikAlertWin
	{
private:
	// Defined by the Mix-in class:
	void ConstructL();
	void RunAlert(const TDesC& aMsg1,const TDesC& aMsg2);
	void Release();
	CEikDialog* AsEikDialog();
private:
	void PreLayoutDynInitL();
private: 
	virtual void CEikDialog_Reserved_1();
	virtual void CEikDialog_Reserved_2();	
private: 
	virtual void CAknNoteDialog_Reserved();

protected:
	const TDesC* iMsg1;
	const TDesC* iMsg2;
	};


#endif
