// GSMUPDU.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
// Adapted by Mikko Rintala



inline CSmsPDU::TSmsPDUType CSmsPDU::Type() const
	{
	return iSmsPDUType;
	}

inline TBool CSmsDeliverReport::IsRPError() const
	{
	return iIsRPError;
	}

inline void CSmsDeliverReport::SetIsRPError(TBool aIsRPError)
	{
	iIsRPError=(TUint8) aIsRPError;
	}
	
inline TBool CSmsSubmitReport::IsRPError() const
	{
	return iIsRPError;
	}

inline void CSmsSubmitReport::SetIsRPError(TBool aIsRPError)
	{
	iIsRPError=(TUint8) aIsRPError;
	}

inline TBool CSmsStatusReport::ParameterIndicatorPresent() const
	{
	return iParameterIndicatorPresent;
	}

inline void CSmsStatusReport::SetParameterIndicatorPresent(TBool aPresent)
	{
	iParameterIndicatorPresent=(TUint8) aPresent;
	}

	
