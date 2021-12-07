/*
* ============================================================================
*  Name     : RPbkViewResourceFile from RPbkViewResourceFile.h
*  Part of  : PbkView.dll
*
*  Description:
*     Helper class for loading PbkView resources.
*  Version:
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

#ifndef __RPbkViewResourceFile_H__
#define __RPbkViewResourceFile_H__

//  INCLUDES
#include <e32std.h>
#include "ConeResLoader.h"

// CLASS DECLARATION

/**
 * Helper class for loading PbkView DLL resource file.
 */
class RPbkViewResourceFile
    {
    public:  // Interface
        /**
         * Constructor.
         * @param aEnv CONE environment where to load the resource file.
         */
        IMPORT_C RPbkViewResourceFile(CCoeEnv& aEnv);

        /**
         * Opens the PbkView dll resource file for use. Leaves if the
         * resource file is already open.
         */
        IMPORT_C void OpenL();

        /**
         * Returns ETrue if the resource file is open.
         */
        IMPORT_C TBool IsOpen() const;
    
        /**
         * Closes the PbkView dll resource file.
         * You must always remember to close the resource file when finished 
         * using it.
         */
        IMPORT_C void Close();

    private:  // Data
		/// Own: resource loader
        RConeResourceLoader iLoader;
		/// Own: file open flag
        TBool iOpen;
    };

#endif // __RPbkViewResourceFile_H__

// End of File
