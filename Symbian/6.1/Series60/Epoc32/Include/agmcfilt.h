// AGMCFILT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Connectivity specific filters as a seperate DLL
// 

#ifndef __AGMCFILT_H__
#define __AGMCFILT_H__

#include <e32base.h> 
#include "agmids.h"
#include "agmcomon.h"



_LIT(KAgnDefaultFilter,"nofilter");
const TUid KUidAgnCFilterDLL={0x1000585F};

class TAgnConnectivityFilter
	{
public:
	IMPORT_C TVersion Version() const;
	IMPORT_C TAgnConnectivityFilter();
	IMPORT_C TBool IsValid(const TAgnSmartLiteEntry& aSmartLiteEntry) const;
	IMPORT_C virtual TBool ConnectivityIsValid(const TAgnSmartLiteEntry& aSmartLiteEntry) const;
	IMPORT_C void SetDate(const TTime& aDate);
	IMPORT_C void SetIncludeTimedAppts(TBool aIncludeTimedAppts);
	IMPORT_C void SetIncludeUnTimedAppts(TBool aIncludeUntimedAppts);
	IMPORT_C void SetIncludeEvents(TBool aIncludeEvents);
	IMPORT_C void SetIncludeAnnivs(TBool aIncludeAnnivs);
	IMPORT_C void SetIncludeTodos(TBool aIncludeTodos);
	IMPORT_C void SetIncludeRpts(TBool aIncludeRpts);
	IMPORT_C void SetIncludeNonRpts(TBool aIncludeNonRpts);
	IMPORT_C void SetIncludeRptsNextInstanceOnly(TBool aIncludeRptsNextInstanceOnly);
	IMPORT_C void SetIncludeCrossedOut(TBool aIncludeCrossedOut);
	IMPORT_C void SetIncludeAlarmedOnly(TBool aIncludeAlarmed);
	inline TBool AreTimedApptsIncluded() const;
	inline TBool AreUnTimedApptsIncluded() const;
	inline TBool AreEventsIncluded() const;
	inline TBool AreAnnivsIncluded() const;
	inline TBool AreTodosIncluded() const;
	inline TBool AreRptsIncluded() const;
	inline TBool AreNonRptsIncluded() const;
	inline TBool RptNextInstanceOnly() const;
	inline TBool AreCrossedOutIncluded() const;
	inline TBool AreAlarmedOnlyIncluded() const;
	IMPORT_C void Initialise(const TAgnConnectivityFilter& aFilter);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void ReservedExport();
	IMPORT_C void ReservedExport2();
private:
	TTime           iDate;
	enum 
		{
		EIncludeTimedAppts=0x01,			// include timed appointments
		EIncludeUnTimedAppts=0x02,			// include untimed appointments
		EIncludeEvents=0x04,				// include events
		EIncludeAnnivs=0x08,				// include anniversaries
		EIncludeTodos=0x10,					// include todos
		EIncludeRpts=0x20,					// include repeating entries
		EIncludeRptsNextInstanceOnly=0x40, 	// include next only repeat
		EIncludeNonRpts=0x80, 				// include non repeating
		EIncludeCrossedOut=0x100,			// include crossed out entries
		EIncludeAlarmedOnly=0x200,				// include alarmed entries
		EIncludeAll=EIncludeTimedAppts|EIncludeUnTimedAppts|EIncludeEvents|
					EIncludeAnnivs|EIncludeTodos|EIncludeRpts|EIncludeNonRpts|
					EIncludeCrossedOut // include them all
		};
	TUint32 iFilter;
public:
	TTime			iReserved1;
	TTime			iReserved2;
	TTime			iReserved3;
	TTime			iReserved4;
	TTime			iReserved5;
	TInt			iReserved6;
	TInt			iReserved7;
	TChar			iReserved8;
	};


inline TBool TAgnConnectivityFilter::AreTimedApptsIncluded() const
	{ return (iFilter & EIncludeTimedAppts); }

inline TBool TAgnConnectivityFilter::AreUnTimedApptsIncluded() const
	{ return (iFilter & EIncludeUnTimedAppts); }

inline TBool TAgnConnectivityFilter::AreEventsIncluded() const
	{ return (iFilter & EIncludeEvents); }

inline TBool TAgnConnectivityFilter::AreAnnivsIncluded() const
	{ return (iFilter & EIncludeAnnivs); }

inline TBool TAgnConnectivityFilter::AreTodosIncluded() const
	{ return (iFilter & EIncludeTodos); }

inline TBool TAgnConnectivityFilter::AreRptsIncluded() const
	{ return (iFilter & EIncludeRpts); }
	
inline TBool TAgnConnectivityFilter::AreNonRptsIncluded() const
	{ return (iFilter & EIncludeNonRpts); }

inline TBool TAgnConnectivityFilter::RptNextInstanceOnly() const
	{ return (iFilter & EIncludeRptsNextInstanceOnly); }

inline TBool TAgnConnectivityFilter::AreAlarmedOnlyIncluded() const
	{ return (iFilter & EIncludeAlarmedOnly); }

inline TBool TAgnConnectivityFilter::AreCrossedOutIncluded() const
	{ return (iFilter & EIncludeCrossedOut); }

#endif


