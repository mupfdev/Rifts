// PLPLOG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__PLPLOG_H__)
#define __PLPLOG_H__

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

class MPlpLogRedirector
    {
public:
    virtual TInt PlpLogWrite(const TDesC &aDes)=0; 
    };

class RMBufChain;
class CPlpLog : public CBase
    {
public:
    IMPORT_C static CPlpLog* NewL(TInt aSize, const TDesC &aFileName, TInt aLogMask, TBool aUseTls=ETrue);
    IMPORT_C static CPlpLog* Tls();
    IMPORT_C static void DeleteTls();
    IMPORT_C void SetFileNameL(const TDesC &aFileName);
    IMPORT_C void SetLogMask(TInt aLogMask);
    IMPORT_C void AddL(const TDesC &aEntry);
    IMPORT_C TInt Printf(TRefByValue<const TDesC> aFmt, ...);
    IMPORT_C TInt FlushEachLine(TBool aYes=ETrue);
    IMPORT_C TInt Flush();
    IMPORT_C TInt SetRedirector(MPlpLogRedirector *aRedirector);
    IMPORT_C TInt LogMask();

    IMPORT_C TInt PrintHex(const TDesC &aName, const TDesC8 &aDes);
    IMPORT_C TInt PrintLSE(TAny *Id, TInt aEvent, TInt aState, TInt aSeq);
    IMPORT_C TInt PrintPlpPdu(RMBufChain& aPdu, TInt aLength);
    IMPORT_C ~CPlpLog();        

protected:
    IMPORT_C void ConstructL(TInt aSize, const TDesC &aFileName, TInt aLogMask);
    IMPORT_C CPlpLog();

    void DoDumpL();
    TInt OpenFile();

private:
    CCirBuf<HBufC *> *iCircleBuf;    
    TBool iIsFlushingEachLine;
    HBufC *iFileName;
    TInt iEntryNumber;
    TInt iLogMask;
    RFile iFile;
    RFs iFs;
    MPlpLogRedirector *iRedirector;
    };

#if defined ( _USE_LOG )
 #define _LOG_DECL(x) x
 #define _LOG_FUNC(m, x) { CPlpLog* _p=CPlpLog::Tls(); if((_p) && (_p->LogMask()&(m)) ) _p->x }
#else
 #define _LOG_DECL(x)
 #define _LOG_FUNC(m, x)
#endif

const TInt KLogNone      = 0x00000000;
const TInt KLogFrame     = 0x00000001;
const TInt KLogLink      = 0x00000002;
const TInt KLogTimer     = 0x00000004;
const TInt KLogWatch     = 0x00000008;
const TInt KLogPlpProt   = 0x00000010;
const TInt KLogLinkProt  = 0x00000020;
const TInt KLogPlpBuf    = 0x00000040;
const TInt KLogPlpProvd  = 0x00000080;
const TInt KLogPlpFlow   = 0x00000100;
const TInt KLogPlpFail   = 0x00000200;
const TInt KLogRemSv     = 0x00000400;
const TInt KLogRpcsSv    = 0x00000800;
const TInt KLogLinkSeq   = 0x00001000;
const TInt KLogRemCli    = 0x00002000;
const TInt KLogReadCount = 0x00004000;
const TInt KLogAll       = 0xFFFFFFFF;

#define LOG_DIR _L("C:\\")

#endif __PLPLOG_H__
    
