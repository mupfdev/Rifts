// INSTAPP.H
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//
// Installer application constants
//

#if !defined(__INSTAPP_H__)
#define __INSTAPP_H__

// name of install app file
_LIT(KInstallAppName,"Instapp.app");

// NOTE: following must be given even length due to problem with
// CApaCommandLine::NewL(fullCmdLine)) in EikDll::StartAppL()!
// keywords at end of InstApp command line which tell it what to do
_LIT8(KUninstallCommandLineTail,"UNINSTALLX");
_LIT8(KInstallCommandLineTail,"INSTALLX");

// constant shared between InstApp and InstCtrl
enum TInstallMode {EUninstall,EInstall}; 

#endif