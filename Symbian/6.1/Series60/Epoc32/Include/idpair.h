/*
* ============================================================================
*  Name     : IdPair from IdPair.h
*  Part of  : ConnectionManager
*
*  Description:
*     This class is created to provide possibility ot set up pairs of ids
*
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/
#ifndef ID_PAIR_H
#define ID_PAIR_H


//A class for defining a pair of ids
class TIdPair
	{
public:
	IMPORT_C TIdPair( TUint32 aFirstPreference, TUint32 aSecondPreference = 0 );
	IMPORT_C TIdPair();
	TUint32 iFirstPreference;
	TUint32 iSecondPreference;
	};

#endif// End of File
