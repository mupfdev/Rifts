// CAPSVR.H
//
//	Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// EPOC Capabilities server opcodes

#if !defined(__CAPSVR_H__)
#define __CAPSVR_H__

enum TEPOCCapSvrEnum
{
	ECmdQueryVersion					=0x00,
	ECmdQuit							=0xff,

	ECmdCollectData						=0x01,
	ECmdMultipartCollectData			=0x02
};

const int KMaxEPOCCapBufferSize = 20048;

//	Capabilities Manager Version 0x00000001
#define KEPOCCapMajVer 1
#define KEPOCCapMinVer 0
#define KEPOCCapBldVer 1

#endif

