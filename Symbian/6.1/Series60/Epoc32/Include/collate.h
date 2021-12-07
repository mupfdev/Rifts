// COLLATE.H
//
// Copyright (c) 1996-1999 Symbian Ltd. All rights reserved.

/*
Definitions needed for Unicode collation.

Collation is the comparison of two Unicode strings to produce an ordering
that may be used in a dictionary or other list.

Collation is implemented using the Standard Unicode Collation algorithm. There
are four levels of comparison:

primary: basic character identity
secondary: accents and diacritics
tertiary: upper and lower case, and other minor attributes
quaternary: Unicode character value

Punctuation is normally ignored but can optionally be taken into account.
Strings are fully expanded using the standard Unicode canonical expansions before
they are compared. Thai and Lao vowels are swapped with the following character
if any.

EUSER contains the 'basic collation method'. This method assigns the standard Unicode collation key values
to the characters in the WGL4 repertoire, plus commonly used control characters and fixed-width spaces, plus
the CJK ideograms (for which the keys can be generated algorithmically). Other characters are collated after
all the characters for which keys are defined, and ordered by their Unicode values.

Locales can supply any number of other collation methods. They will usually supply a 'tailoring' of the standard
method. This is done by using the standard table as the main key table (signalled by placing NULL in
TCollationMethod::iMainTable) and specifying an override table (TCollationMethod::iOverrideTable).
Locale-specific collation data resides in ELOCL.
*/

#ifndef __COLLATE_H__
#define __COLLATE_H__ 1

#include <e32std.h>

/*
This material is used in the Unicode build only.
*/
#ifdef _UNICODE

/**
 * Collation key table structure.
 */
struct TCollationKeyTable
	{
public:
	/**
	 * Masks for the various parts of the elements of the iKey array.
	 */
	enum
		{
		ELevel0Mask = 0xFFFF0000,	// primary key - basic character identity
		ELevel1Mask = 0x0000FF00,	// secondary key - accents and diacritics
		ELevel2Mask = 0x000000FC,	// tertiary key - case, etc.
		EIgnoreFlag = 0x2,			// if set, this key is normally ignored
		EStopFlag = 0x1				// if set, this key is the last in a sequence representing a Unicode value or values
		};

	/**
	 * An array containing all of the keys and strings of keys concatenated
	 * together. Each key has EStopFlag set only if it is the last key in its
	 * string. Eack key contains the keys for levels 0, 1 and 2, and a flag
	 * EIgnoreFlag if the key is usually ignored (for punctuation & spaces
	 * etc.).
	 */
	const TUint32* iKey;
	/**
	 * An array of indices into the iKey array. Each element has its high 16
	 * bits indicating a Unicode value and its low 16 bits indicating an index
	 * into the iKey array at which its key starts. The elements are sorted by
	 * Unicode value.
	 */
	const TUint32* iIndex;
	/**
	 * The size of the iIndex array.
	 */
	TInt iIndices;
	/**
	 * Concatenated Unicode strings. Each is a strings that is to be converted
	 * to keys differently from how it would be if each letter were converted
	 * independently. An example is "ch" in Spanish, which sorts as though it
	 * were a single letter. Each Unicode string is preceeded by a 16-bit value
	 * indicating the string's length. The end of the string is not delimited.
	 */
	const TUint16* iString;
	/**
	 * An array of elements mapping elements of iString to elements of iIndex.
	 * Each element has its high 16 bits indicating the index of the start of
	 * an element of iString, and its low 16 bits indicating the corresponding
	 * element in iIndex. This array is sorted on the string index.
	 */
	const TUint32* iStringIndex;
	/**
	 * The size of the iStringIndex array.
	 */
	TInt iStringIndices;
	};

/*
A collation method object specifies a table of collation keys, and optionally 
a tailoring table that contains those keys for which the values in the main table are overridden.
*/
struct TCollationMethod
	{
	public:
	TUint iId;									// the UID of this collation method
	const TCollationKeyTable* iMainTable;		// the main collation key table; if null, use the standard table
	const TCollationKeyTable* iOverrideTable;	// if non-null, tailoring for collation keys
	enum
		{
		EIgnoreNone = 1,		// don't ignore any keys - punctuation, etc., is normally ignored
		ESwapCase = 2,			// reverse the normal order for characters differing only in case
		EAccentsBackwards = 4,	// compare secondary keys, which represent accents, in reverse order;
								// this is needed for French
		ESwapKana = 8,			// reverse the normal order for characters differing only in whether
								// they are katakana or hiragana
		EFoldCase = 16			// fold all characters to lower case before extracting keys; needed
								// for comparison of filenames, for which case is ignored but other
								// level-2 distinctions are not
		};
	TUint iFlags;				// flags as defined above
	};

// A collation data set provides any collation methods needed by a locale.
struct TCollationDataSet
	{
	public:
	const TCollationMethod* iMethod;
	TInt iMethods;
	};

class TCollationValueIterator;
class SCollationPosition;

// The TCollate object provides low-level collation functions.
struct LCharSet;
class TCollate
	{
public:
	/**
	 * Construct a TCollate object based on the collation method specified
	 * within aCharSet, if any. If there is none, or aCharSet is null, the
	 * standard collation method will be used. aMask and aFlags provide a
	 * method for overriding the flags in the collation method: Each flag set
	 * to 1 in aMask is a flag that will be overridden and set to the
	 * corresponding flag value in aFlags. Ownership of aCharSet is not passed.
	 * @internal
	 */

	TCollate(const LCharSet* aCharSet,TUint aMask = 0,TUint aFlags = 0xFFFFFFFF);

	/**
	 * Construct a TCollate object based on an already constructed
	 * TCollationMethod specified in aMethod. Ownership is not passed.
	 * @internal
	 */

	TCollate(const TCollationMethod& aMethod);

	enum TComparisonResult
		{
		ELeftComparesLessAndIsNotPrefix = -2,
		ELeftIsPrefixOfRight = -1,
		EStringsIdentical = 0,
		ERightIsPrefixOfLeft = 1,
		ERightComparesLessAndIsNotPrefix = 2
		};

	/**
	 * Compare the string beginning at aString1 of length aLength1 against the
	 * string beginning at aString2 of length aLength2. The strings are
	 * considered to hold 16-bit values if aNarrow is false, if it is true,
	 * aString1 and aString2 are considered cast const TUint8 pointers.
	 * aMaxLevel determines the tightness of the collation. At level 0, only
	 * character identities are distinguished. At level 1 accents are
	 * distinguished as well. At level 2 case is distinguishes as well. At
	 * level 3 all valid different Unicode characters are considered different.
	 *
	 * @since 6.1
	 */
	TComparisonResult Compare(const TUint16* aString1,TInt aLength1,const TUint16* aString2,TInt aLength2,
				 TBool aNarrow,TInt aMaxLevel = 3) const;
	/**
	 * Find the string beginning at aString2 of length aLength2 in the string
	 * beginning at aString1 of length aLength1. The strings are considered to
	 * hold 16-bit values if aNarrow is false, if it is true, aString1 and
	 * aString2 are considered cast const TUint8 pointers. aMaxLevel determines
	 * the tightness of the collation, see Compare for details.
	 *
	 * @see Compare
	 * @since 6.1
	 */
	TInt Find(const TUint16 *aString1,TInt aLength1,const TUint16 *aString2,TInt aLength2,
			  TBool aNarrow,TInt aMaxLevel,TUint aString2WildChar = 0) const;
	/**
	 * Test if the string beginning at aSearchTerm of length aSearchTermLength
	 * matches the string beginning at aCandidate of length aCandidateLength.
	 * The strings are considered to hold 16-bit values if aNarrow is false, if
	 * it is true, aString1 and aString2 are considered cast const TUint8
	 * pointers. aMaxLevel determines the tightness of the collation, see
	 * Compare for details. The search term may have wild card characters as
	 * specified by aWildChar (for matching a single grapheme- i.e. character
	 * and any characters that combine with it, such as accents) and
	 * aWildSequenceChar (for matching any sequence of whole graphemes). The
	 * return value is KErrNotFound iff the search term does not match the
	 * candidate string exactly. To find a match within the candidate string,
	 * the search term must begin and end with a wild sequence character. If
	 * the search term does match the candidate string, 0 will be returned,
	 * unless the first character of the search term is a wild sequence
	 * character in which case the value returned will be the index into
	 * aCandidate at which the first non-wild sequence character matched.
	 * aWildSequenceChar must be a valid (non-surrogate) Unicode character
	 * below FFFE.
	 *
	 * @see Compare
	 * @since 6.1
	 */
	TInt Match(const TUint16 *aCandidate, TInt aCandidateLength,
		const TUint16 *aSearchTerm,TInt aSearchTermLength,
		TBool aNarrow, TInt aMaxLevel,
		TUint aWildChar = '?', TUint aWildSequenceChar = '*') const;

	/**
	 * Compare values output from the iterators. After the comparison, if
	 * ERightIsPrefixOfLeft or EStringsIdentical is returned, then aLeft and
	 * aRight will be pointing at the next key (at MaxLevel) after the match.
	 * If right is shown to be a prefix of left, this means that it has been
	 * checked at all requested levels. If it is reported that the right is a
	 * prefix of the left, then this will mean also that there are no unmatched
	 * combining characters on the left.
	 *
	 * @internal
	 * @since 6.1
	 */
	TComparisonResult CompareKeySequences(TCollationValueIterator& aLeft,
		TCollationValueIterator& aRight,
		TInt aMaxLevel, TInt aRightStringWildChar) const;
	/**
	 * Finds search term inside candidate string. Returns KErrNotFound if there
	 * is no match, returns the offset into the candidate string at which the
	 * search term was found (note that this is the offset from the start of
	 * the iteration, not from where the iteration was when the function was
	 * called). If a string was found, the search term iterator is left
	 * pointing at the end of the search term, and the candidate iterator is
	 * left pointing just after the matched keys. aMatchPos returns where in
	 * the candidate string the match was found.
	 *
	 * @internal
	 * @since 6.1
	 */
	TInt FindKeySequence(TCollationValueIterator& aCandidate,
		TCollationValueIterator& aSearchTerm,
		TInt aMaxLevel, TInt aWildChar, SCollationPosition* aMatchPos = 0) const;

private:
	TCollationMethod iMethod;
	};

// Panic numbers
enum
	{
	ENullCollationMethodRepertoire = 1	// null collation method repertoire pointer
	};

// Collation method IDs
const TUint KUidBasicCollationMethod = 0x10004F4E;
const TUint KUidStandardUnicodeCollationMethod = 0x10004E96;


#endif // _UNICODE

#endif // __COLLATE_H__
