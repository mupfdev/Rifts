/*
* ============================================================================
*  Name     : TAknExPbarTimerModel of struct
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


#ifndef AKNEXPBARTIMERMODEL_H
#define AKNEXPBARTIMERMODEL_H

//  INCLUDES
#include <e32def.h>

// STRUCT DECLARATION

/**
*  Struct of Timer Model
*/
struct TAknExPbarTimerModel
    {
    TInt iHundredths;
    TInt iIncrement;
    TBool iRunning;
    };

#endif // AKNEXPBARTIMERMODEL_H

// End of File
