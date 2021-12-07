// D_DRVIF.H
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//

//
// This header provides the interface to DRVIF.LDD, which provides a set of
// direct interface functions with the DMedia objects in the local drive subsystem.
//


#if !defined(__D_DRVIF_H__)
#define __D_DRVIF_H__
#include "e32svr.h"  

class TCapsDrvIfV01
	{
public:
	TVersion version;
	};
//
class TMediaData
    {
public:
    inline TMediaData(TInt64 &aPos,TInt *aLength,const TAny *aPDes,TRequestStatus *aStatus) 
        : iPos(aPos), iLength(aLength), iPDes(aPDes), iReqStat(aStatus) 
        {}
public:
    TInt64 &iPos;
    TInt *iLength;
	const TAny *iPDes;
	TRequestStatus *iReqStat;
    };
//
class TMediaInfo
    {
public:
    inline TMediaInfo(TInt64 &aSize,TMediaType &aType) 
        : iTotalSizeInBytes(aSize), iType(aType) 
        {}
public:
	TInt64 &iTotalSizeInBytes;
    TMediaType &iType;
    }; 
//
class RLocalDriveMediaIf : public RBusLogicalChannel
	{
public:
	enum {EMajorVersionNumber=1,EMinorVersionNumber=0,EBuildVersionNumber=1};
    enum {ESvMediaStart,ESvMediaOpen,EExecMediaInfo,EExecMediaRead,EExecMediaWrite,ESvMcNotifier};
public:
	inline TInt Open(TInt aMediaNumber,const TVersion& aVer)
		{return(DoCreate(_L("DrvIf"),aVer,NULL,aMediaNumber,NULL,NULL));}
	inline TVersion VersionRequired() const
		{return(TVersion(EMajorVersionNumber,EMinorVersionNumber,EBuildVersionNumber));}
	inline TInt OpenMedia()
        {
        TRequestStatus rs=KRequestPending;
        DoSvControl(ESvMediaStart,(TAny*)&rs);
        User::WaitForRequest(rs);
        return((rs==KErrNone)?DoSvControl(ESvMediaOpen):rs.Int());
        }
	inline TInt Info(TInt64 &aTotalSizeInBytes,TMediaType &aType)
		{
		TMediaInfo mi(aTotalSizeInBytes,aType);
		return(DoControl(EExecMediaInfo,&mi));
		}
	inline void Read(TInt64 &aPos,TInt *aLength,TDes8 &aDes,TRequestStatus &aStatus)
		{
		TMediaData md(aPos,aLength,&aDes,&aStatus);
		DoControl(EExecMediaRead,&md);
		}
	inline void Write(TInt64 &aPos,TInt *aLength,const TDesC8 &aDes,TRequestStatus &aStatus)
		{
		TMediaData md(aPos,aLength,(TDes8*)&aDes,&aStatus);
		DoControl(EExecMediaWrite,&md);
		}
	inline TInt MediaChangeNotifier(TRequestStatus *aReqStat)
		{return(DoSvControl(ESvMcNotifier,(TAny*)aReqStat));}
	};
//
#endif
