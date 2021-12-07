// PLPRFILE.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//////////////////////////////////////////////////////////////////////////////
//
// TRemoteEntry
//
//////////////////////////////////////////////////////////////////////////////

inline const TEntry& TRemoteEntry::Entry() const
    { return iEntry; }

inline TText* TRemoteEntry::ShortNameOffset() const
    { return (TText*)this + (2*sizeof(TInt) + Align4(EntrySize(iEntry)))/sizeof(TText); }

inline TPtrC TRemoteEntry::ShortName() const
    { return TPtrC(ShortNameOffset(), iShortNameLength); }

inline TPtrC8 TRemoteEntry::DataType() const
	{ return TPtrC8(DataTypeOffset(), iDataTypeLength); }

inline TBool TRemoteEntry::HasShortName() const
    { return iShortNameLength ? 1 : 0; }

inline TText8* TRemoteEntry::DataTypeOffset() const
	{ return (TText8*)(ShortNameOffset() + iShortNameLength);}

inline TInt TRemoteEntry::Size(const TRemoteEntry &aEntry)
    { return 2*sizeof(TInt) + Align4(EntrySize(aEntry.iEntry)) + aEntry.iShortNameLength*sizeof(TText) + aEntry.iDataTypeLength; }

//////////////////////////////////////////////////////////////////////////////
//
// TRemoteEntryArray
//
//////////////////////////////////////////////////////////////////////////////

inline TRemoteEntryArray::TRemoteEntryArray()
    : iCount(0)
	{}

//////////////////////////////////////////////////////////////////////////////
//
// Query version
//
//////////////////////////////////////////////////////////////////////////////

inline TQueryVersion::TQueryVersion()
    { iMajor=0; iMinor=0; iIsSupported=0; }

inline TQueryVersion::TQueryVersion(TInt aMajor, TInt aMinor)
    { iMajor = (TInt8)aMajor; iMinor = (TInt8)aMinor; iIsSupported=0; }

inline TBool TQueryVersion::IsSupported() 
    { return iIsSupported >= 0; }



