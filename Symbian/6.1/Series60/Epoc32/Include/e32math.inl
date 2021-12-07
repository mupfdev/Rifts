// E32MATH.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__E32MATH_INL__)
#define __E32MATH_INL__

// class TRealX

TBool TRealX::operator==(const TRealX &aVal) const
	{
	return(Compare(aVal)&EEqual);
	}

TBool TRealX::operator!=(const TRealX &aVal) const
	{
	return(Compare(aVal)&(ELessThan|EGreaterThan));
	}

TBool TRealX::operator>=(const TRealX &aVal) const
	{
	return(Compare(aVal)&(EEqual|EGreaterThan));
	}

TBool TRealX::operator<=(const TRealX &aVal) const
	{
	return(Compare(aVal)&(ELessThan|EEqual));
	}

TBool TRealX::operator>(const TRealX &aVal) const
	{
	return(Compare(aVal)&EGreaterThan);
	}

TBool TRealX::operator<(const TRealX &aVal) const
	{
	return(Compare(aVal)&ELessThan);
	}

#endif