// IN_STD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __IN_STD_H__
#define __IN_STD_H__

#include <nifmbuf.h>

// Added from INET.H and TCP.H as they are needed in VJCOMP

// Room for all layer of headers
const TUint KInetMaxHeaderSize = 128;

const TUint KTcpFIN = 0x01;
const TUint KTcpSYN = 0x02;
const TUint KTcpRST = 0x04;
const TUint KTcpPSH = 0x08;
const TUint KTcpACK = 0x10;
const TUint KTcpURG = 0x20;

class CNifIfBase;
class RMBufRecvInfo : public RMBufPktInfo
	{
public:
	CNifIfBase* iInterface;
	};

#endif
