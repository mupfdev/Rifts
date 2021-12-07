// F32FSYS.INL
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//


// Class TDrive
inline TBool TDrive::IsMounted() const
	{return(iCurrentMount!=NULL);}
inline TBool TDrive::IsLocal() const
	{return(iAtt&KDriveAttLocal);}
inline TBool TDrive::IsRom() const
	{return(iAtt&KDriveAttRom);}
inline TBool TDrive::IsRemovable() const
	{return(iAtt&KDriveAttRemovable);}
inline TBool TDrive::IsSubsted() const
	{return(iAtt&KDriveAttSubsted);}//	KDriveAttSubsted = 0x08
inline CMountCB& TDrive::CurrentMount() const
	{return(*iCurrentMount);}
inline TDrive& TDrive::SubstedDrive()const
	{return(*iSubstedDrive);}
inline void TDrive::SetSubstedDrive(TDrive* aDrive)
	{iSubstedDrive=aDrive;}
inline HBufC& TDrive::Subst() const
	{return(*iSubst);}
inline void TDrive::SetSubst(HBufC* aSubst)
	{iSubst=aSubst;}
inline CObjectCon& TDrive::Mount() const
	{return(*iMount);}
inline CFileSystem& TDrive::FSys() const
	{return(*iFSys);}
inline CFileSystem*& TDrive::GetFSys()
	{return(iFSys);}
inline CSessionFs* TDrive::CurrentSession() const
	{return(iCurrentSession);}
inline void TDrive::SetSession(CSessionFs* aSession)
	{iCurrentSession=aSession;}


// Class CMountCB
inline TDrive& CMountCB::Drive() const
	{return(*iDrive);}
inline void CMountCB::SetDrive(TDrive* aDrive)
	{iDrive=aDrive;}
inline HBufC& CMountCB::VolumeName()
	{return(*iVolumeName);}
inline void CMountCB::SetVolumeName(HBufC* aName)
	{iVolumeName=aName;}
inline TBool CMountCB::GetNotifyUser() const
	{return(Drive().GetNotifyUser());}
inline void CMountCB::SetNotifyUser(TBool aValue)
	{Drive().SetNotifyUser(aValue);}
inline void CMountCB::IncLock()
	{iLockMount++;}
inline void CMountCB::DecLock()
	{iLockMount--;}
inline TInt CMountCB::LockStatus()
	{return(iLockMount);}
inline TInt CMountCB::Locked()
	{return iLockMount>0; }
inline TBool CMountCB::IsCurrentMount()
	{return(this==&iDrive->CurrentMount());}
inline TInt64 CMountCB::Size()
	{return(iSize);}

// Class CFileCB
inline TDrive& CFileCB::Drive()
	{return(*iDrive);}
inline void CFileCB::SetDrive(TDrive* aDrive)
	{iDrive=aDrive;}
inline TDrive& CFileCB::CreatedDrive()
	{return(*iCreatedDrive);}
inline void CFileCB::SetCreatedDrive(TDrive* aDrive)
	{iCreatedDrive=aDrive;}
inline CMountCB& CFileCB::Mount()
	{return(*iMount);}
inline void CFileCB::SetMount(CMountCB* aMount)
	{iMount=aMount;}
inline HBufC& CFileCB::FileName()
	{return(*iFileName);}
inline void CFileCB::SetFileName(HBufC* aName)
	{iFileName=aName;}
inline RArray<SFileShareLock>& CFileCB::Lock()
	{return(*iLock);}
inline void CFileCB::SetLock(RArray<SFileShareLock>* aLock)
	{iLock=aLock;}
inline TInt CFileCB::UniqueID() const
	{return(CObject::UniqueID());}
inline TShare CFileCB::Share()
	{return(iShare);}
inline void CFileCB::SetShare(TShare aShare)
	{iShare=aShare;}
inline TInt CFileCB::Size()
	{return(iSize);}
inline void CFileCB::SetSize(TInt aSize)
	{iSize=aSize;}
inline TInt CFileCB::Att()
	{return(iAtt);}
inline void CFileCB::SetAtt(TInt aAtt)
	{iAtt=aAtt;}	
inline TTime CFileCB::Modified()
	{return(iModified);}
inline void CFileCB::SetModified(TTime aModified)
	{iModified=aModified;}
inline TBool CFileCB::FileCorrupt()
	{return iFileCorrupt;}
inline void CFileCB::SetFileCorrupt(TBool aFileCorrupt)
	{iFileCorrupt=aFileCorrupt;}
inline TBool CFileCB::BadPower()
	{return (iBadPower);};
inline void CFileCB::SetBadPower(TBool aBadPower)
	{iBadPower=aBadPower;}

// Class CFileShare
inline CFileCB& CFileShare::File()
	{return(*iFile);}
inline void CFileShare::SetFile(CFileCB* aFile)
	{iFile=aFile;}

// Class CDirCB
inline TDrive& CDirCB::Drive()
	{return(*iDrive);}
inline void CDirCB::SetDrive(TDrive* aDrive)
	{iDrive=aDrive;}
inline CMountCB& CDirCB::Mount()
	{return(*iMount);}
inline void CDirCB::SetMount(CMountCB* aMount)
	{iMount=aMount;}
inline TBool CDirCB::Pending()
	{return iPending;}
inline void CDirCB::SetPending(TBool aPending)
	{iPending=aPending;}

// class CFormatCB
inline TDrive& CFormatCB::Drive()
	{return(*iDrive);}
inline void CFormatCB::SetDrive(TDrive* aDrive)
	{iDrive=aDrive;}
inline CMountCB& CFormatCB::Mount()
	{return(*iMount);}
inline void CFormatCB::SetMount(CMountCB* aMount)
	{iMount=aMount;}
inline TFormatMode CFormatCB::Mode()
	{return(iMode);}
inline void CFormatCB::SetMode(TFormatMode aMode)
	{iMode=aMode;}
inline TInt& CFormatCB::CurrentStep()
	{return(iCurrentStep);}

// class CRawDiskCB
inline TDrive& CRawDiskCB::Drive()
	{return(iMount->Drive());}
inline CMountCB& CRawDiskCB::Mount()
	{return(*iMount);}
inline TBool CRawDiskCB::IsWriteProtected() const
	{return(iIsWriteProtected);}
