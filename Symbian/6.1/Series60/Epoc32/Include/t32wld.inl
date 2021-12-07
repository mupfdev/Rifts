// T32WLD.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Written by BLB, June 1995
//

// TWorldId
inline TWldSelect TWorldId::Select() const
	{
	return(iSelect);
	}
inline const TCityName& TWorldId::City() const
	{
	return(iCity);
	}
inline const TCountryName& TWorldId::Country() const
	{
	return(iCountry);
	}
inline void TWorldId::SetSelect(TWldSelect aSelector)
	{
	iSelect=aSelector;
	}

// TLatLong
inline TInt TLatLong::MinutesLat() const
	{
	return(iLat);
	}
inline TInt TLatLong::MinutesLong() const
	{
	return(iLong);
	}

