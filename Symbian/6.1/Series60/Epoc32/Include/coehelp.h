// COEHELP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEHELP_H__)
#define __COEHELP_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

/**
 * The TCoeHelpContext class implements a means to access particular topics
 * in an application help file according to the state an application is in.
 *
 * @since ER5U
 */ 

typedef TBuf<30> TCoeContextName;

class TCoeHelpContext
	{
public:
	IMPORT_C TCoeHelpContext();

	/**
	 * Constructs the TCoeHelpContext object, identifying the major grouping
	 * of related help topics with aMajor and a particular topic with aContext. 
	 */
	IMPORT_C TCoeHelpContext(TUid aMajor,const TDesC& aContext);
	IMPORT_C TBool IsNull() const;
	IMPORT_C TBool operator==(const TCoeHelpContext& aContext) const;
	IMPORT_C TBool operator!=(const TCoeHelpContext& aContext) const;
public:
	TUid iMajor;
	TCoeContextName iContext;
	};

#endif
