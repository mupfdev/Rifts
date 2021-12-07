// COEINPUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEINPUT_H__)
#define __COEINPUT_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

// classes defined in FEPBASE, declared here
class MCoeFepAwareTextEditor;
class MCoeCaptionRetrieverForFep;

class MObjectProvider;

/**
 * The TCoeInputCapabilities class provides a means to describe which forms of
 * text input are consumed by a control or view.
 *
 * @since ER5U
 */ 
class TCoeInputCapabilities
	{
public:
	enum
		{
		ENone							=0,
		EWesternNumericIntegerPositive	=0x00000001,
		EWesternNumericIntegerNegative	=0x00000002,
		EWesternNumericReal				=0x00000004,
		EWesternAlphabetic				=0x00000008,
		EJapaneseHiragana				=0x00000010,
		EJapaneseKatakanaHalfWidth		=0x00000020,
		EJapaneseKatakanaFullWidth		=0x00000040,
		EDialableCharacters				=0x00000080,
		ESecretText						=0x00000100,
		EAllText						=0x01000000,
		ENavigation						=0x02000000
		};
	class MCoeFepSpecificExtensions; // to be defined by concrete FEPs, declared here
public:
	// all these functions are exported (rather than inline) so that binary compatibility becomes easier to maintain
	IMPORT_C TCoeInputCapabilities(TUint aCapabilities);
	IMPORT_C TCoeInputCapabilities(TUint aCapabilities, MCoeFepAwareTextEditor* aFepAwareTextEditor, MCoeCaptionRetrieverForFep* aCaptionRetrieverForFep);
	IMPORT_C TCoeInputCapabilities(TUint aCapabilities, MCoeFepAwareTextEditor* aFepAwareTextEditor, MCoeCaptionRetrieverForFep* aCaptionRetrieverForFep, TUid aFepUid, MCoeFepSpecificExtensions* aFepSpecificExtensions);
	IMPORT_C TCoeInputCapabilities(const TCoeInputCapabilities& aAnother); // defined so that iSpareForFutureUse is not copied
	IMPORT_C TCoeInputCapabilities& operator=(const TCoeInputCapabilities& aAnother); // defined so that iSpareForFutureUse is not copied
	IMPORT_C TBool operator==(const TCoeInputCapabilities& aAnother) const; // defined so that iSpareForFutureUse is not tested
	IMPORT_C TBool operator!=(const TCoeInputCapabilities& aAnother) const; // defined so that iSpareForFutureUse is not tested
	IMPORT_C void MergeWith(const TCoeInputCapabilities& aAnother);
	IMPORT_C void SetCapabilities(TUint aCapabilities);
	IMPORT_C TUint Capabilities() const;
	IMPORT_C TBool IsNone() const;
	IMPORT_C TBool SupportsWesternNumericIntegerPositive() const;
	IMPORT_C TBool SupportsWesternNumericIntegerNegative() const;
	IMPORT_C TBool SupportsWesternNumericReal() const;
	IMPORT_C TBool SupportsWesternAlphabetic() const;
	IMPORT_C TBool SupportsJapaneseHiragana() const;
	IMPORT_C TBool SupportsJapaneseKatakanaHalfWidth() const;
	IMPORT_C TBool SupportsJapaneseKatakanaFullWidth() const;
	IMPORT_C TBool SupportsDialableCharacters() const;
	IMPORT_C TBool SupportsSecretText() const;
	IMPORT_C TBool SupportsAllText() const;
	IMPORT_C TBool SupportsNavigation() const;
	IMPORT_C MCoeFepAwareTextEditor* FepAwareTextEditor() const;
	IMPORT_C MCoeCaptionRetrieverForFep* CaptionRetrieverForFep() const;
	IMPORT_C MCoeFepSpecificExtensions* FepSpecificExtensions(TUid aFepUid) const;
    IMPORT_C MObjectProvider* ObjectProvider() const;
    IMPORT_C void SetObjectProvider(MObjectProvider* aObjectProvider);

private:
	TUint iCapabilities;
	MCoeFepAwareTextEditor* iFepAwareTextEditor;
	MCoeCaptionRetrieverForFep* iCaptionRetrieverForFep;
	TUint iFepUid;
	MCoeFepSpecificExtensions* iFepSpecificExtensions;
    MObjectProvider* iObjectProvider;
    TAny* iSpareForFutureUse[5];
	};

#endif
