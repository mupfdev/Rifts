// VCARD.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// CParserPropertyValueAgent
//
/**
 * Gets the agent object owned by the property value.
 *
 * @returns   " CParserVCard* "
 *            A pointer to the agent property value.
 */
inline CParserVCard* CParserPropertyValueAgent::Value() const
	{return iValue;}

/**
 * Sets the array of grouped property names as the member of the class
 *
 * @param     " CDesC8Array* aArrayOfGroups "
 *            Pointer to an array of descriptors. Each one specifies
 *            a group name. 
 */
inline void CParserGroupedProperty::SetGroups(CDesC8Array* aArrayOfGroups)
	{iArrayOfGroups=aArrayOfGroups;}

/**
 * Gets the array of grouped property names
 *
 * @returns     " CDesC8Array* "
 *            Pointer to an array of descriptors. Each one specifies
 *            a group name. 
 */
inline const CDesC8Array* CParserGroupedProperty::Groups()
	{return iArrayOfGroups;}
