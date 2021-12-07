// MPARSER.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MPARSER_H__
#define __MPARSER_H__

#include <e32base.h>
#include <e32std.h>

class CRichText;
class TCharFormat;

/**
 * @internal
 * Internal to Symbian
 */
class MParser
	{
public:
	virtual TBool ParseThisText(const CRichText& aTextObj,
								TBool aAllowBack,
								TInt aStartScan,
								TInt aScanLength,
								TInt& aStartTag,
								TInt& aTagLength) = 0;

	virtual const TDesC& CreateDoItText(const CRichText& aTextObj,
										TInt aStartText,
										TInt aLength) = 0;

	virtual void ActivateThisTextL(const CRichText& aTextObj,
								   TInt aStartText,
								   TInt aLength) = 0;

	IMPORT_C virtual TBool ReformatOnRecognise() const;

	IMPORT_C virtual TBool ReformatOnRollover() const;

	IMPORT_C virtual void GetRecogniseFormat(TCharFormat& aFormat);

	IMPORT_C virtual void GetRolloverFormat(TCharFormat& aFormat);

	IMPORT_C virtual void MParser_Reserved_1();
	IMPORT_C virtual void MParser_Reserved_2();

	//++ ADD COMMENT HERE (poss. provide default implement that panics)
	virtual void Release() = 0;
	};

#endif
