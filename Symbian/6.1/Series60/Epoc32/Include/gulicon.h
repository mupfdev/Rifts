// GULICON.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__GULICON_H__)
#define __GULICON_H__  

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CFbsBitmap;

/**
 * The CGulIcon class packages two bitmaps, one each for an icon image and its mask.
 *
 * @since ER5U
 */
class CGulIcon : public CBase
	{
public:
	IMPORT_C static CGulIcon* NewLC();
	IMPORT_C static CGulIcon* NewL();
	IMPORT_C static CGulIcon* NewL(CFbsBitmap* aBitmap, CFbsBitmap* aMask=NULL);
	//
	IMPORT_C void SetBitmap(CFbsBitmap* aBitmap);
	IMPORT_C void SetMask(CFbsBitmap* aMask);
	IMPORT_C CFbsBitmap* Bitmap() const;
	IMPORT_C CFbsBitmap* Mask() const;
	IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);
	IMPORT_C TBool BitmapsOwnedExternally() const;
	//
	IMPORT_C ~CGulIcon();
private:
	CGulIcon();
private:
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMask;
	TBool iBitmapsOwnedExternally;
	};

#endif