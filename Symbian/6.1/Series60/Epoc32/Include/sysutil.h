/*
* ============================================================================
*  Name     : SysUtil from SysUtil.h
*  Part of  : SysUtil
*  Origin   : Calypso, NMP
*  Created  : Mon Feb 19 16:28:36 2001 by maparnan
*  Description:
*     This module offers API for applications to miscellanous system utils:
*     - Get SW version information
*     - Get Language package version information
*
*  Version  :
*   %version: 7 %, %date_modified: Mon Oct 28 14:01:53 2002 % by %derived_by: atnikula %
*  Copyright (c) 2000 Nokia Mobile Phones. All rights reserved.
*  ---------------------------------------------------------------------------
*  Version history:
*  Template version: 1.02, 21.6.2000 by maparnan
*  <ccm_history>
*  Version: 1, Tue Feb 20 8:00:00 2001 by maparnan
*  Initial version.

*  Version: 2, Thu Feb 22 8:00:00 2001 by maparnan
*  Comment fixed.
*
*  Version: 6, Sun May 05 10:05:10 2002 by maparnan
*  More disk level check methods added
*  (DiskSpaceBelowCriticalLevelL, MMCSpaceBelowCriticalLevelL)
*  </ccm_history>
* ============================================================================
*/

#ifndef SYSUTIL_H
#define SYSUTIL_H

// INCLUDES
#include <e32base.h>

// CONSTANTS
// Helper constant to allocate buffers for
// GetSWVersion, GetLangSWVersion, GetLangVersion
// The value is  bigger than really needed for future use.
const TInt KSysUtilVersionTextLength = 64;
// MACROS
// DATA TYPES
// FUNCTION PROTOTYPES
// FORWARD DECLARATIONS
// CLASS DECLARATION
class RFs;

/**
*  SysUtil Interface.
*  This class offers various utility methods for applications.
*/
class SysUtil
    {

    public: // New functions        

        /**
        * Returns Software version string.
        * The returned version has the following syntax
        * (\n is a linefeed):
        *   Vxx.xx\ndd-mm-yy\nNHL-2NA\n(c)NMP
        * @param aVersion The returned version string. The size
        *       of the buffer should be KSysUtilVersionTextLength.
        * @return Epoc standard error code.
        */
        IMPORT_C static TInt GetSWVersion(TDes& aValue);

        /**
        * Returns SW version with which the currently installed
        * Language package is compatible with.
        * The returned version has the same syntax SW
        * version (see GetSWVersion).
        * @param aVersion The returned version string. The size
        *       of the buffer should be KSysUtilVersionTextLength.
        * @return Epoc standard error code.
        */
        IMPORT_C static TInt GetLangSWVersion(TDes& aValue);

        /**
        * Returns version of the currently installed Language package.
        * The returned version has the following syntax:
        *   xxx
        * @param aVersion The returned version string. The size
        *       of the buffer should be KSysUtilVersionTextLength.
        * @return Epoc standard error code.
        */
        IMPORT_C static TInt GetLangVersion(TDes& aValue);
        
        /**
        * Checks if the free FFS (internal Flash File System) storage
        * space is or will fall below Critical Level (CL).
        * The CL and FFS drive letter is defined by this module.
        * @param aFs File server session.
        *        Must be given if available in the caller,
        *        e.g. from EIKON environment.
        *        If NULL this method will create a temporary session for
        *        a check, but then the check is more expensive.
        * @param aBytesToWrite number of bytes the caller is about to add
        *        FFS, if known by the caller beforehand.
        *        The default value 0 checks if the current
        *        space is already below the CL. 
        * @return ETrue if storage space would go below CL after adding
        *         aBytes more data, EFalse otherwise.
        *         Leaves on error.
        */
        IMPORT_C static TBool FFSSpaceBelowCriticalLevelL(
            RFs* aFs, TInt aBytesToWrite = 0);


        /**
        * Checks if the free MMC (Multi Media Card)  
        * space is or will fall below Critical Level (CL).
        * The CL and MMC drive letter is defined by this module.        
        * @param aFs File server session.
        *        Must be given if available in the caller,
        *        e.g. from EIKON environment.
        *        If NULL this method will create a temporary session for
        *        a check, but then the check is more expensive.
        * @param aBytesToWrite number of bytes the caller is about to add
        *        MMC, if known by the caller beforehand.
        *        The default value 0 checks if the current
        *        space is already below the CL.      
        * @return Returns ETrue if storage space would go
        *         below CL after adding aBytesToWrite more data,
        *         EFalse otherwise.
        *         Leaves on error: KErrNotSupported if system has no
        *         MMC drive support,
        *         otherwise another system-wide error code,
        *         e.g. KErrNotReady if drive contais no media.
        *        
        */
        IMPORT_C static TBool SysUtil::MMCSpaceBelowCriticalLevelL(
            RFs* aFs, TInt aBytesToWrite = 0);

        /**
        * Generic method to check if free drive storage
        * space is or will fall below Critical Level (CL).
        * The CL per drive is defined by this module.
        * @param aFs File server session.
        *        Must be given if available in the caller,
        *        e.g. from EIKON environment.
        *        If NULL this method will create a temporary session for
        *        a check, but then the check is more expensive.
        * @param aBytesToWrite number of bytes the caller is about to add
        *        FFS.The value 0 checks if the current
        *        space is already below the CL. 
        * @param aDrive number of the drive to be checked.
        *        (see TDriveNumber of f32file.h)
        * @return ETrue if storage space would go below CL after adding
        *         aBytesToWrite more data, EFalse otherwise.
        *         Leaves on error with one of system-wide error code.
        *         e.g. KErrNotReady if drive contais no media.
        */
        IMPORT_C static TBool SysUtil::DiskSpaceBelowCriticalLevelL(
            RFs* aFs, TInt aBytesToWrite, TInt aDrive);
        
		/**
        * Generates EKeyGripOpen or EKeyGripClose
		* (see UIKON.HRH) key event depending on the current the current
		* grip state. After calling this method the generated event must
        * be handled by the calling application.
        * @return KErrNone on success, otherwise an error code.
        */
		IMPORT_C static TInt GenerateGripEvent();

        /**
        * Returns the device specific user agent string, which
        * is used for example in HTTP headers.
        *
        * @return user agent string, ownership transfered to the caller.
        */
        IMPORT_C static HBufC8* UserAgentStringL();

    private:

    };

#endif