/*
* ============================================================================
*  Name     : mtm uid definitions from SenduiMtmUids.h
*  Part of  : Sendui
*  Description:
*     Collected all the mtm uids to same file.
*
*  Version  : %version: 7 %
*       %date_modified: Fri Oct 25 15:35:29 2002 %
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing,  adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef INC_SENDUIMTMUIDS_H
#define INC_SENDUIMTMUIDS_H

#include <e32std.h>

#define KSenduiMtmSmtpUidValue      0x10001028
#define KSenduiMtmImap4UidValue     0x1000102A
#define KSenduiMtmPop3UidValue      0x10001029
#define KSenduiMtmSmsUidValue       0x1000102C
#define KSenduiMtmMmsUidValue       0x100058E1
#define KSenduiMtmIrUidValue        0x100053A4
#define KSenduiMtmBtUidValue        0x10009ED5
#define KSenduiMtmPushMtm1UidValue  0x100099D1
#define KSenduiMtmPushMtm2UidValue  0x100099D2
#define KSenduiMtmPushMtm3UidValue  0x100099D3
#define KSenduiMtmBioUidValue       0x10001262

#define KSenduiMailEditorUidValue   0x101F4CD6
#define KSenduiMMSEditorUidValue    0x100058DE

#define KSenduiMtmFaxUidValue       0x1000102B
// fax not used

const TUid KSenduiMtmSmtpUid     = { KSenduiMtmSmtpUidValue     };
const TUid KSenduiMtmImap4Uid    = { KSenduiMtmImap4UidValue    };
const TUid KSenduiMtmPop3Uid     = { KSenduiMtmPop3UidValue     };
const TUid KSenduiMtmSmsUid      = { KSenduiMtmSmsUidValue      };
const TUid KSenduiMtmMmsUid      = { KSenduiMtmMmsUidValue      };
const TUid KSenduiMtmIrUid       = { KSenduiMtmIrUidValue       };
const TUid KSenduiMtmBtUid       = { KSenduiMtmBtUidValue       };
const TUid KSenduiMtmPushMtm1Uid = { KSenduiMtmPushMtm1UidValue };
const TUid KSenduiMtmPushMtm2Uid = { KSenduiMtmPushMtm2UidValue };
const TUid KSenduiMtmPushMtm3Uid = { KSenduiMtmPushMtm3UidValue };
const TUid KSenduiMtmBioUid      = { KSenduiMtmBioUidValue      };

const TUid KSenduiMailEditorUid  = { KSenduiMailEditorUidValue  };
const TUid KSenduiMMSEditorUid   = { KSenduiMMSEditorUidValue   };

const TUid KSenduiMtmFaxUid      = { KSenduiMtmFaxUidValue      };
// fax not used

#endif

// End of File
