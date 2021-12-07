// UTF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__UTF_H__)
#define __UTF_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

class CnvUtfConverter
	{
public:
	enum TError
		{
		EErrorIllFormedInput=KErrCorrupt
		};
	enum {KStateDefault=0};
public:
	// the conversion functions return either one of the TError values above, or the number of unconverted elements left at the end of the input descriptor
	IMPORT_C static TInt ConvertFromUnicodeToUtf7(TDes8& aUtf7, const TDesC16& aUnicode, TBool aEncodeOptionalDirectCharactersInBase64);
	static TInt ConvertFromUnicodeToUtf7(TDes8& aUtf7, const TDesC16& aUnicode, TBool aIsImapUtf7, TBool aEncodeOptionalDirectCharactersInBase64);
	IMPORT_C static TInt ConvertFromUnicodeToUtf8(TDes8& aUtf8, const TDesC16& aUnicode);
	static TInt ConvertFromUnicodeToUtf8(TDes8& aUtf8, const TDesC16& aUnicode, TBool aGenerateJavaConformantUtf8);
	IMPORT_C static TInt ConvertToUnicodeFromUtf7(TDes16& aUnicode, const TDesC8& aUtf7, TInt& aState);
	static TInt ConvertToUnicodeFromUtf7(TDes16& aUnicode, const TDesC8& aUtf7, TBool aIsImapUtf7, TInt& aState);
	IMPORT_C static TInt ConvertToUnicodeFromUtf8(TDes16& aUnicode, const TDesC8& aUtf8);
	};

#endif

