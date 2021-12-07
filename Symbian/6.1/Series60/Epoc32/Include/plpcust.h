// PLPCUST.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__PLPCUST_H__)
#define __PLPCUST_H__

#if !defined (__PLPRFILE_H__)
#include <plprfile.h>
#endif

const TUint KDefaultCustomSlots=1;
const TInt KDefaultBufferSize = MAX_DATACHUNK_SIZE;

class RPlpCustomSession : public RRemoteSessionBase
    {
    
public:
    IMPORT_C TInt Open(const TDesC8& aServiceName, TInt aMaxPduSize=KDefaultBufferSize, TUint aInterface=KPlpInterfaceDevice0, TInt aMessageSlots=KDefaultCustomSlots);
    IMPORT_C TVersion Version() const;
    IMPORT_C void SendReceive(TRequestStatus& aStatus, TDes8& aData);
    IMPORT_C void QueryVersion(TRequestStatus& aStatus, TDes8& aQueryVersion);
    IMPORT_C void Quit(TRequestStatus& aStatus);
    };

#endif