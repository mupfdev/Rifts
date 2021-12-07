// BACLIPB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Started by DS, October 1996
// Clipboard
//

#if !defined(__BACLIPB_H__)
#define __BACLIPB_H__

#if !defined(__e32std_h__)
#include <e32std.h>
#endif

#if !defined(__e32base_h__)
#include <e32base.h>
#endif

#if !defined(__s32file_h__)
#include <s32file.h>
#endif

// Provdes a clipboard class, capable of storing multiple data *types*
// All data *types* stored must be registered prior to closing this clipboard.

class CClipboard : public CBase
    {
public:
	IMPORT_C static CClipboard* NewForReadingLC(RFs& aFs);
	IMPORT_C static CClipboard* NewForReadingL(RFs& aFs);
	IMPORT_C static CClipboard* NewForWritingLC(RFs& aFs);
	IMPORT_C static TInt Clear(RFs& aFs);
	IMPORT_C ~CClipboard();
	//
	// Necessary only when writing
	IMPORT_C void CommitL();
	//
	inline CStreamStore& Store() const;
	inline CStreamDictionary& StreamDictionary() const;

    // Provide functionality to read and write floating point numbers
    // in a native format.
    // (see note below)

    IMPORT_C void  CopyToL     ( TReal aReal );
    IMPORT_C TBool PasteFromL  ( TReal& aReal );
    // Get a number from the clipboard, return false if it is not present
    // in which case the parameter is unmodified.

private:
	inline CClipboard(RFs& aFs);
	static CClipboard* NewLC(RFs& aFs);
	void ConstructReadL();
private:
	CFileStore* iStore;
	CStreamDictionary* iStreamDictionary;
	RFs& iFs;
    };

inline CStreamStore& CClipboard::Store() const
	{ return *iStore; }

inline CStreamDictionary& CClipboard::StreamDictionary() const
	{ return *iStreamDictionary; }


// NB the floating point copy and paste member functions are currently the only
// ones of this type defined in the class.  Most clipboard data consists of
// more complex objects known only at a higher level than BAFL.  This raises the
// question of whether the clipboard should provide equivalent functionality
// for other basic data types or whether there should be a utility class
// elsewhere to do all such operations in a standard format and handle the
// multiple representations too. - PNJ, January 1997.






#endif
