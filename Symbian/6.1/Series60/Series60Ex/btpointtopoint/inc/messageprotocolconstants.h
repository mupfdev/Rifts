/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __CMESSAGE_PROTOCOL_CONSTANTS__
#define __CMESSAGE_PROTOCOL_CONSTANTS__

#include <e32def.h>
#include <bt_sock.h>

const TInt KRfcommChannel = 1;
const TInt KServiceClass = 0x1101;    //  SerialPort

const TUid KUidBTPointToPointApp = {0x10005B8B};

_LIT(KServiceName,"Serial Port");
_LIT(KServiceDescription,"Simple point to point data transfer example");
_LIT(KServerTransportName,"RFCOMM");

#endif //__CMESSAGE_PROTOCOL_CONSTANTS__