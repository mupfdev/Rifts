// VERSIT.INL
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//


//
// CVersitParser
//

inline void CLineReader::SetPlugIn(MVersitPlugIn* aPlugIn)
	{iPlugIn=aPlugIn;}


//
// CVersitParser
//

/**
 * Sets the versit observer.
 *
 * @param     "MVersitObserver* aObserver"
 *            The pointer to the observer.
 */
inline void CVersitParser::SetObserver(MVersitObserver* aObserver)
	{iObserver=aObserver;}

/**
 * Gets a pointer to the versit observer.
 *
 * @returns   "MVersitObserver*"
 *            The pointer to the observer.
 */
inline MVersitObserver* CVersitParser::Observer()
	{return iObserver;}

/**
 * Sets the versit plug in.
 *
 * This should be set before any properties are added to the parser, either by Internalising or by <code>AddPropertyL()</code> properties.
 *
 * @param     "MVersitPlugIn* aPlugIn"
 *            The pointer to the plug in.
 */
inline void CVersitParser::SetPlugIn(MVersitPlugIn* aPlugIn)
	{iPlugIn=aPlugIn;}

/**
 * Gets a pointer to the versit plug in.
 *
 * @returns   "MVersitPlugIn*"
 *            The pointer to the plug in.
 */
inline MVersitPlugIn* CVersitParser::PlugIn()
	{return iPlugIn;}

/**
 * Gets a pointer to the read buffer owned by the 
 * <code>CLineReader</code>
 *
 * @returns   " TPtr8& "
 *            Pointer to the read buffer.
 */
inline TPtr8& CVersitParser::BufPtr()
	{return iLineReader->iBufPtr;}

/**
 * Check the iFlags to see if <code>ESupportsVersion</code> is set
 *
 * @returns   " TBool "
 *            <code>ETrue</code> if the parser supports the version property
 *            <code>EFalse</code> otherwise
 */
inline TBool CVersitParser::SupportsVersion() const
	{return iFlags & ESupportsVersion;}

/**
 * Sets the iFlags to <code>ESupportsVersion</code>
 */
inline void CVersitParser::SetSupportsVersion()
	{iFlags |= ESupportsVersion;}

/**
 * Clear the bit of <code>ESupportsVersion</code> in iFlags'
 */
inline void CVersitParser::ClearSupportsVersion()
	{iFlags &= ~ESupportsVersion;}

/**
 * Gets a reference to <code>CVersitUnicodeUtils</code>
 * which is used for charset conversion 
 *
 * @returns   " CVersitUnicodeUtils&"
 *            reference to <code>CVersitUnicodeUtils</code>
 */
inline CVersitUnicodeUtils& CVersitParser::UnicodeUtils()
	{ return iStaticUtils->UnicodeUtils(); }
