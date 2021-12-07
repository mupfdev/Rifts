// AGMFILTS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMFILTS_H__
#define __AGMFILTS_H__

#include <s32stor.h>
#include "agmutil.h"
#include "agmcomon.h"

class CAgnSortEntry;
class CAgnEntryModel;

class TAgnFilter
	{
public:
	enum TType {EAgnFilter, EDayFilter, ESymbolFilter, EFindFilter, ETidyFilter};
	IMPORT_C TAgnFilter();
	IMPORT_C virtual TBool IsValid(const CAgnSortEntry* aElement) const;
	IMPORT_C TBool IsValid(const TAgnLiteEntry& aLiteEntry) const;
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
	IMPORT_C void SetIncludeCrossedOutOnly(TBool aIncludeCrossedOutOnly);
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
	inline TBool AreCrossedOutOnlyIncluded() const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C virtual TAgnFilter::TType Type();
private:
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
		EIncludeAlarmedOnly=0x200,			// include alarmed entries
		EIncludeCrossedOutOnly=0x400,		// include crossed out entries only
		EIncludeAll=EIncludeTimedAppts|EIncludeUnTimedAppts|EIncludeEvents|
					EIncludeAnnivs|EIncludeTodos|EIncludeRpts|EIncludeNonRpts|
					EIncludeCrossedOut // include them all
		};
	TUint32 iFilter;
	};


class TAgnDayFilter : public TAgnFilter
	{
public:
	IMPORT_C TAgnDayFilter(CAgnEntryModel* aEntryModel);
	IMPORT_C virtual TBool IsValid(const CAgnSortEntry* aElement) const;
	IMPORT_C virtual TAgnFilter::TType Type();
private:
	CAgnEntryModel* iEntryModel;
	};

class TAgnSymbolFilter : public TAgnDayFilter
	{
public:
	IMPORT_C TAgnSymbolFilter(CAgnEntryModel* aEntryModel);
	IMPORT_C virtual TBool IsValid(const CAgnSortEntry* aElement) const;
	inline TBool HasEntrySymbol() const;
	inline void SetHasEntrySymbol(TBool aHasEntrySymbol);
	inline TText16 EntrySymbol() const;
	inline void SetEntrySymbol(TText aEntrySymbol);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C virtual TAgnFilter::TType Type();
private:
	TInt16				iHasEntrySymbol;
	TText16 			iEntrySymbol; 
	};


class TAgnsrvFindFilter : public TAgnFilter
	{
public:
	IMPORT_C TAgnsrvFindFilter();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C virtual TBool IsValid(const CAgnSortEntry* aElement) const;
	//
	IMPORT_C void SetIncludeOneSymbolOnly(TBool aOneSymbol);
	IMPORT_C void SetEntrySymbol(TChar aSymbol);
	IMPORT_C TBool IncludeOneSymbolOnly() const;
	IMPORT_C TChar EntrySymbol() const;
	IMPORT_C TAgnFilter::TType Type();
private:
	TBool iOnlyOneSymbol;
	TChar iSymbol;
	};

class TAgnsrvTidyFilter : public TAgnFilter
	{
public:
	IMPORT_C TAgnsrvTidyFilter();
//	void InternalizeL(RReadStream& aStream);
//	void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C virtual TBool IsValid(const CAgnSortEntry* aElement) const;
	//
	IMPORT_C void SetIncludeCrossedOutOnly(TBool aIncludeCrossedOutOnly);
	IMPORT_C TBool IncludeCrossedOutOnly() const;
	IMPORT_C TAgnFilter::TType Type();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
private:
	TBool iIncludeCrossedOutOnly;
	};


#include "agmfilts.inl"

#endif
