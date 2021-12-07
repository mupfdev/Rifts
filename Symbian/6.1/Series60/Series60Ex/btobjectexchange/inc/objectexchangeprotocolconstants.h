/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __CBTOBEX_SDP_PROTOCOL__
#define __CBTOBEX_SDP_PROTOCOL__

#include <e32def.h>
#include <bt_sock.h>

const TUid KUidBTObjectExchangeApp = {0x10005b8e};

// See entry for OBEX in table 4.3 "Protocols"
// at the url http://www.bluetooth.org/assigned-numbers/sdp.htm
const TUint KBtProtocolIdOBEX = 0x0008;

const TUint KRfcommChannel = 1;

// See entry for OBEXObjectPush in table 4.4 "Service Classes"
// at the url http://www.bluetooth.org/assigned-numbers/sdp.htm
const TUint KServiceClass = 0x1105; 

_LIT(KServiceName,"OBEX");
_LIT(KServiceDescription,"Object Push");
_LIT(KServerTransportName,"RFCOMM");

#endif //__CBTOBEX_SDP_PROTOCOL__