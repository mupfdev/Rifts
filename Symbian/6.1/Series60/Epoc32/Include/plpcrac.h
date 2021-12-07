// PLPCRAC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__PLPCRAC_H__)
#define __PLPCRAC_H__

#ifdef __WINC__

#ifndef _T
	#define _T(a) _L(a)
#endif

/*
	PLP Registry keys for epoc connect when interopping should match values in cracstru.h in epoc connect.
*/

#define KSoftware_EPOC_Symbian  _T("SOFTWARE\\EPOCU\\Symbian")
#define KPathPLP_RegStr			_T("\\PLP")

#define KPlp_Win32_RegStr		_T("Win32RegKey")
#define KPlp_Device_RegStr		_T("Device%d")			// %d indicates a value added dynamically by PLP.
#define KPlp_BaudRate_RegStr	_T("BaudRate")
#define KPlp_Access_RegStr		_T("Access")
#define KPlp_PortName_RegStr	_T("PortName")
#define KPlp_Config_RegStr		_T("Config")
#define KPlp_ModuleName_RegStr	_T("Module")
#define KPlp_DeviceID_RegStr	_T("DeviceID")


/*
	PLP Semaphores. & mutexs
*/
#define KPlpRemoteFileSystemSemaphore	_T("__PLPREMOTEFILESEMAPHORE_WIDE__")
#define KPlpRemoteLinkConfigSemaphore	_T("__PLPREMOTELINKCONFIGSEMAPHORE_WIDE__")
#define KPlpRemoteLinkSemaphore			_T("__PLPREMOTELINKSEMAPHORE_WIDE__")
#define KPlpRemoteFileSystemMutex		_T("__PLPREMOTEFILEMUTEX_WIDE__")
#define KPlpRemoteLinkStartupMutex		_T("__PLPREMOTELINKSTARTUPMUTEX_WIDE__")


#endif
#endif
