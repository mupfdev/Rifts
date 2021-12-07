// PLPRPC.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline TRemoteQueryDrive::TRemoteQueryDrive()
    : iCount(0)
    { }

inline TUid TRemoteRegEntry::Category() const
    { return iCategory; }

inline TPtrC8 TRemoteRegEntry::Name() const
    { return TPtrC8(iName, iNameLength); }

inline TInt TRemoteRegEntry::Size(const TRemoteRegEntry& aEntry)
    {  return sizeof(TUid)+sizeof(TInt)*2+Align4(aEntry.iNameLength)+aEntry.iValueLength; }

inline TText8* TRemoteRegEntry::ValueOffset() const
    { return (TText8*)iName+Align4(iNameLength); }

inline TPtrC8 TRemoteRegEntry::Value() const
    { return TPtrC8(ValueOffset(), iValueLength); }

inline TRemoteRegArray::TRemoteRegArray()
    { iCount=0; }
