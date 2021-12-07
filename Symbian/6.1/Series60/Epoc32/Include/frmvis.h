// FRMVIS.H
//
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//

#ifndef __FRMVIS_H__
#define __FRMVIS_H__

#include <e32std.h>
#include <e32base.h>

class RReadStream;
class RWriteStream;

/**
 *
 * A set of flags to indicate which non-printing characters (e.
 *
 * g. space, tab, paragraph break, etc.) should be drawn using symbols.
 * By default, all non-printing characters are hidden.An instance of this
 * class is used in
 * <code>CTextLayout::SetNonPrintingCharsVisibility()</code>.
 *
 * @since 5.0
 * @lib "form.lib"
 */

class TNonPrintingCharVisibility
	{
private:
	enum TShowFormatChars
		{
		EFNothingVisible=0x000,
		EFTabsVisible=0x001,
		EFSpacesVisible=0x002,
		EFParagraphDelimitersVisible=0x004,
		EFLineBreaksVisible=0x008,
		EFPotentialHyphensVisible=0x010,
		EFNonBreakingHyphensVisible=0x020,
		EFNonBreakingSpacesVisible=0x040,
		EFPageBreaksVisible=0x080,
		EFEverythingVisible=0xffffffff
		};
public:
	IMPORT_C TNonPrintingCharVisibility();
	IMPORT_C TNonPrintingCharVisibility(const TNonPrintingCharVisibility& aVisibility);
	IMPORT_C TNonPrintingCharVisibility& operator=(const TNonPrintingCharVisibility& aVisibility);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void SetAllVisible();
	IMPORT_C void SetNoneVisible();
	IMPORT_C void SetTabsVisible(TBool aVisible);
	IMPORT_C void SetSpacesVisible(TBool aVisible);
	IMPORT_C void SetParagraphDelimitersVisible(TBool aVisible);
	IMPORT_C void SetLineBreaksVisible(TBool aVisible);
	IMPORT_C void SetPotentialHyphensVisible(TBool aVisible);
	IMPORT_C void SetNonBreakingHyphensVisible(TBool aVisible);
	IMPORT_C void SetNonBreakingSpacesVisible(TBool aVisible);
	IMPORT_C void SetPageBreaksVisible(TBool aVisible);
	
	/**
	 *
	 * Tests whether all non-printing characters are visible.
	 *
	 * @returns   "TBool"
	 *            True if all non-printing characters are visible. False
	 *            if any or all hidden.
	 */

	inline TBool AllVisible()const{return iVisible==EFEverythingVisible;};
	
	/**
	 *
	 * Tests whether all non-printing characters are hidden.
	 *
	 * @returns   "TBool"
	 *            True if all non-printing characters are hidden. False
	 *            if any are visible.
	 */

	inline TBool NoneVisible()const{return iVisible==EFNothingVisible;};
	
	/**
	 *
	 * Tests whether tab stop characters are visible.
	 *
	 * @returns   "TBool"
	 *            True if tab stop characters are visible. False if
	 *            hidden.
	 */

	inline TBool TabsVisible()const{return iVisible&EFTabsVisible;};
	
	/**
	 *
	 * Tests whether space characters are visible.
	 *
	 * NoteTo get the the visibility of non-breaking space characters, use
	 * <code>NonBreakingSpacesVisible()</code> instead.
	 *
	 * @returns   "TBool"
	 *            True if space characters are visible. False if hidden.
	 */

	inline TBool SpacesVisible()const{return iVisible&EFSpacesVisible;};
	
	/**
	 *
	 * Tests whether paragraph delimiters are visible.
	 *
	 * @returns   "TBool"
	 *            True if paragraph delimiters are visible. False if
	 *            hidden.
	 */

	inline TBool ParagraphDelimitersVisible()const{return iVisible&EFParagraphDelimitersVisible;};
	
	/**
	 *
	 * Tests whether forced line break characters are visible.
	 *
	 * @returns   "TBool"
	 *            True if forced line break characters are visible.
	 *            False if hidden.
	 */

	inline TBool LineBreaksVisible()const{return iVisible&EFLineBreaksVisible;};
	
	/**
	 *
	 * Tests whether potential hyphen characters (inserted before a line
	 * break within a word) are visible.
	 *
	 * @returns   "TBool"
	 *            True if potential hyphen characters are visible. False
	 *            if hidden.
	 */

	inline TBool PotentialHyphensVisible()const{return iVisible&EFPotentialHyphensVisible;};
	
	/**
	 *
	 * Tests whether non-breaking hyphens (enclosing word is always kept on
	 * the same line) are visible.
	 *
	 * @returns   "TBool"
	 *            True if non-breaking hyphens are visible. False if
	 *            hidden.
	 */

	inline TBool NonBreakingHyphensVisible()const{return iVisible&EFNonBreakingHyphensVisible;};
	
	/**
	 *
	 * Tests whether non-breaking spaces are visible.
	 *
	 *
	 *
	 * @returns   "TBool"
	 *            True if non-breaking spaces are visible. False if
	 *            hidden.
	 */

	inline TBool NonBreakingSpacesVisible()const{return iVisible&EFNonBreakingSpacesVisible;};
	
	/**
	 *
	 * Tests whether page break characters are visible.
	 *
	 * @returns   "TBool"
	 *            True if page break characters are visible. False if
	 *            hidden.
	 */

	inline TBool PageBreaksVisible()const{return iVisible&EFPageBreaksVisible;};
private:
	TUint32 iVisible;
	};

#endif


