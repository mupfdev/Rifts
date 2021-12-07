// FRMPARAM.H
//
// Copyright (C) 1999 Symbian Ltd. All rights reserved.
//

// FORM global parameters; held in thread-local storage.

#ifndef __FRMPARAM_H__
#define __FRMPARAM_H__

#include <gdi.h>

// A mixin class to provide global FORM parameters; a pointer to one of these is held in thread-local storage.

/**
 *
 * Specifies the protocol for getting system colours for use in text
 * views.
 *
 * A class which implements this protocol allows an application (or a
 * thread, because a pointer to the object is held in thread-local
 * storage) to use system colours in text views.You should create an
 * object of an <code>MFormParam</code>-derived class which implements
 * the <code>SystemColor()</code> function. Then, pass a pointer to the
 * object to the static function <code>MFormParam::Set()</code>. The
 * <code>MFormParam</code>-derived object is owned by the caller of
 * <code>Set()</code>. When system colours are no longer needed, you
 * should cancel them by calling <code>MFormParam::Set(NULL)</code>. It
 * is the caller's responsibility to cause the text view to be redrawn
 * after system colours are changed.<code>CTextLayout</code> uses the
 * colour translation function <code>SystemColor()</code> (if an
 * <code>MFormParam</code>-derived object is present) to set the pen and
 * brush colours for drawing components of the text view. It calls
 * <code>MFormParam::Get()</code> before each draw. This enables an
 * application to introduce system colours, change the parameter object,
 * or abolish system colours, and redraw everything correctly; no
 * information is left over from the last draw.
 *
 * @since 6.0
 * @lib ""
 */

class MFormParam
	{
	public:
		
	/**
	 *
	 * Translates 8-bit logical colour indices to physical colours pure
	 * virtual function.
	 *
	 * The colour index is stored in a <code>TLogicalRgb</code> object and is
	 * returned by <code>TLogicalRgb::SystemColorIndex()</code>.There are
	 * three reserved index values: Zero means the logical colour does not
	 * map to a system colour: the logical colour is in fact an ordinary
	 * <code>TRgb</code>. This function should not normally be called with
	 * this value254 and 255 are default foreground and background colours
	 * respectively, and should be converted to the GUI's standard foreground
	 * and background coloursThe values 1-253 are reserved for the use of the
	 * GUI and can be interpreted as convenient. These can be interpreted as
	 * <code>TLogicalColor::EColorWindowBackground</code> upward; this
	 * mapping can be done by subtracting one from the index number
	 * <code>aColorIndex</code>.
	 *
	 * @param     "TUint aColorIndex"
	 *            Logical colour index. Between 1 and 255 inclusive.
	 * @param     "TRgb aDefaultColor"
	 *            The default colour. This is the colour to be used if
	 *            no translation is performed. This allows translation
	 *            to change certain indices but not others, (by passing
	 *            the default colour back unchanged).
	 * @returns   "TRgb"
	 *            The physical colour which maps to the logical colour
	 *            index.
	 */

	virtual TRgb SystemColor(TUint aColorIndex,TRgb aDefaultColor) const = 0;
	IMPORT_C virtual void Reserved();
	IMPORT_C static void Set(const MFormParam* aParam);
	IMPORT_C static const MFormParam* Get();
	};

#endif // __FRMPARAM_H__
