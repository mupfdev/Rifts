/*
* ============================================================================
*  Name     : MAknFileFilter from MAknFileFilter.h
*  Part of  : Common File Dialogs
*
*  Description:
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
* ============================================================================
*/

#ifndef __MAKNFILEFILTER_H__
#define __MAKNFILEFILTER_H__

// INCLUDES
#include <E32DEF.H> // TBool

// FORWARD DECLARATIONS
class TEntry;

//  CLASS DEFINITION
/**
* An abstract interface class for filters.
*/
class MAknFileFilter
	{
	public:		// Constructors and destructors
		/**
		* A virtual destructor to ensure that correct destructor gets called.
		* Must have an empty implementation.
		*/
		virtual ~MAknFileFilter() { };

	public:
		/**
		* Checks if a file is accepted by the filter.
		* @param aDriveAndPath Drive and full path of the file.
		* @param aEntry A directory entry.
		* @return Returns ETrue if filter accepts the file.
		*/
		virtual TBool Accept( const TDesC& aDriveAndPath, const TEntry& aEntry ) const = 0;

	};

#endif // __MAKNFILEFILTER_H__

// End of File