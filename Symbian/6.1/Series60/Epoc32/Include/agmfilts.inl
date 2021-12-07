// AGMFILTS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// ---------------------------- TAgnFilter -------------------------------------
inline TBool TAgnFilter::AreTimedApptsIncluded() const
	{ return (iFilter & EIncludeTimedAppts); }

inline TBool TAgnFilter::AreUnTimedApptsIncluded() const
	{ return (iFilter & EIncludeUnTimedAppts); }

inline TBool TAgnFilter::AreEventsIncluded() const
	{ return (iFilter & EIncludeEvents); }

inline TBool TAgnFilter::AreAnnivsIncluded() const
	{ return (iFilter & EIncludeAnnivs); }

inline TBool TAgnFilter::AreTodosIncluded() const
	{ return (iFilter & EIncludeTodos); }

inline TBool TAgnFilter::AreRptsIncluded() const
	{ return (iFilter & EIncludeRpts); }
	
inline TBool TAgnFilter::AreNonRptsIncluded() const
	{ return (iFilter & EIncludeNonRpts); }

inline TBool TAgnFilter::RptNextInstanceOnly() const
	{ return (iFilter & EIncludeRptsNextInstanceOnly); }

inline TBool TAgnFilter::AreAlarmedOnlyIncluded() const
	{ return (iFilter & EIncludeAlarmedOnly); }

inline TBool TAgnFilter::AreCrossedOutIncluded() const
	{ return (iFilter & EIncludeCrossedOut); }

inline TBool TAgnFilter::AreCrossedOutOnlyIncluded() const
	{ return (iFilter & EIncludeCrossedOutOnly); }

// ---------------------------- TAgnSymbolFilter -------------------------------
inline TBool TAgnSymbolFilter::HasEntrySymbol() const
	{ return(iHasEntrySymbol);}

inline void TAgnSymbolFilter::SetHasEntrySymbol(TBool aHasEntrySymbol)
	{ iHasEntrySymbol = (TInt16)aHasEntrySymbol; }

inline TText16 TAgnSymbolFilter::EntrySymbol() const
	{ return (iEntrySymbol); }

inline void TAgnSymbolFilter::SetEntrySymbol(TText aEntrySymbol)
	{ 
	iEntrySymbol = aEntrySymbol;
	SetHasEntrySymbol(ETrue);
	}

