// bsp.inl
//
// Copyright (c) 1999 Symbian Software plc.  All rights reserved.
//

inline void TMsvBIOEntry::SetBIOParserUid(const TUid aId)
	{
	iBioType = aId.iUid;
	}
	
inline const TUid TMsvBIOEntry::BIOParserUid() const
	{
	return TUid::Uid(iBioType);
	}

inline void TMsvBIOEntry::SetLocationOfData(const TMsvBIODataLocation aLocation)
	{
	iLocationOfData = aLocation;
	}

inline const TMsvBIODataLocation TMsvBIOEntry::LocationOfData() const
	{
	return iLocationOfData;
	}