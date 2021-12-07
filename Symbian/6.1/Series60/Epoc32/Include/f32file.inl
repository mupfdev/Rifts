// F32FILE.INL
//
// Copyright (c) 1996-1999 Symbian Ltd.  All rights reserved.
//


// Class TEntry
inline const TUid& TEntry::operator[](TInt anIndex) const
    {return(iType[anIndex]);}
inline TBool TEntry::IsUidPresent(TUid aUid) const
    {return(iType.IsPresent(aUid));}
inline TBool TEntry::IsTypeValid() const
    {return(iType.IsValid());}
inline TUid TEntry::MostDerivedUid() const
    {return(iType.MostDerived());}
//	Returns the entire size of the TEntry...
inline TInt EntrySize(const TEntry& anEntry)
	{return(sizeof(TUint)+sizeof(TInt)+sizeof(TTime)+sizeof(TInt)+sizeof(TUidType)+anEntry.iName.Size());}

// Class TFindFile
inline const TDesC& TFindFile::File() const
	{return iFile.FullName();}

// Class CDirScan
inline RFs& CDirScan::Fs()
	{return(*iFs);}

// Class TDriveUnit
inline TDriveUnit::operator TInt() const
	{return(iDrive);}
