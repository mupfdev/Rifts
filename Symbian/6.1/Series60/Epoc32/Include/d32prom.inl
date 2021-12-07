// D32PROM.INL
//
// Copyright (c) 1996-1999 Symbian Ltd.  All rights reserved.
//

_LIT(KRDevE2Prom,"E2Prom");
inline TInt RDevE2Prom::Open(TInt aUnit)
	{return(DoCreate(KRDevE2Prom,TVersion(0,1,1),NULL,aUnit,NULL,NULL));}

inline TInt RDevE2Prom::ReadData(TDes16& aBuffer)
	{return(DoControl(EE2PromReadData,(TAny*)&aBuffer));}

inline TInt RDevE2Prom::WriteData(TDesC16& aBuffer)
	{return(DoControl(EE2PromWriteData,(TAny*)&aBuffer));}

inline TInt RDevE2Prom::WriteAll(TInt aVal)
	{return(DoControl(EE2PromWriteAll,(TAny*)aVal));}

inline TInt RDevE2Prom::ProtectSet(TInt aAddr)
	{return(DoControl(EE2PromProtectSet,(TAny*)aAddr));}

inline TInt RDevE2Prom::ProtectClear()
	{return(DoControl(EE2PromProtectClear));}

inline TInt RDevE2Prom::ProtectRead()
	{return(DoControl(EE2PromProtectRead));}

inline TInt RDevE2Prom::ProtectLock()
	{return(DoControl(EE2PromProtectLock));}

inline TInt RDevE2Prom::EnableProtectLock()
	{return(DoControl(EE2PromEnableProtectLock));}

inline TInt RDevE2Prom::Caps(TDes8 &aCaps)
	{return(DoControl(EE2PromCapability,(TAny*)&aCaps));}
//

