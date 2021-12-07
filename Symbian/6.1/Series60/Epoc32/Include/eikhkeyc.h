// EIKHKEYC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKHKEYC_H__)
#define __EIKHKEYC_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

class CEikHotKeyTable;
class MEikCommandObserver;

class CEikHotKeyControl : public CCoeControl
	{
public:
	CEikHotKeyControl(CEikHotKeyTable* aTable,MEikCommandObserver* aObserver);
	~CEikHotKeyControl();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // framework
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
	CEikHotKeyTable* iTable;
	MEikCommandObserver* iObserver;
	};

#endif
