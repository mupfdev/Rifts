/*
* ============================================================================
*  Name     : PbkUID.h
*  Part of  : Phonebook.app
*
*  Description:
*    Common header for Phonebook application UIDs. All subcomponents should
*    use the UID constants defined in this file.
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

#ifndef __PbkUID_H__
#define __PbkUID_H__

//  MACROS  

/// Phonebook application UID3
#define KPbkUID3 0x101f4cce

// Sim PD application UID3
#define KSimPdUID3 0x101f4cf6

// SDN application UID3
#define KSdnUID3 0x101f4cf0

/// CPbkViewState Uid used with the view server
#define KPbkViewStateUid 0x101f4ccf

/// Custom field content type UID 1
#define KPbkCustomContentTypeUid1 0x101f4cf1

/// Custom field content type UID 2
#define KPbkCustomContentTypeUid2 0x101f4cf2

//
// Common system UIDs
// For some reason these are not available in .mmp usable form (macros)
// in Symbian OS SDK.
//
#define KEPOCAppUID2 0x100039ce
#define KEPOCStaticDllUID2 0x1000008d


#endif // __PbkUID_H__

// End of File
