// Uansi.h
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__UANSI_H__)
#define __UANSI_H__

#include "Euniw.h"
#include "e32std.h"

IMPORT_C UNIW_CreateDirectory CreateDirectoryU();
IMPORT_C UNIW_CreateFile CreateFileU();
IMPORT_C UNIW_CreateMutex CreateMutexU();
IMPORT_C UNIW_CreateSemaphore CreateSemaphoreU();
IMPORT_C UNIW_DefWindowProc DefWindowProcU();
IMPORT_C UNIW_DeleteFile DeleteFileU();
IMPORT_C UNIW_DispatchMessage DispatchMessageU();
IMPORT_C UNIW_FindFirstFile FindFirstFileU();
IMPORT_C UNIW_FindNextFile FindNextFileU();
IMPORT_C UNIW_GetCurrentDirectory GetCurrentDirectoryU();
IMPORT_C UNIW_GetDiskFreeSpace GetDiskFreeSpaceU();
IMPORT_C UNIW_GetEnvironmentVariable GetEnvironmentVariableU();
IMPORT_C UNIW_GetFileAttributes GetFileAttributesU();
IMPORT_C UNIW_GetFullPathName GetFullPathNameU();
IMPORT_C UNIW_GetDriveType GetDriveTypeU();
IMPORT_C UNIW_GetMessage GetMessageU();
IMPORT_C UNIW_GetModuleFileName GetModuleFileNameU();
IMPORT_C UNIW_GetModuleHandle GetModuleHandleU();
IMPORT_C UNIW_GetObject GetObjectU();
IMPORT_C UNIW_GetTempPath GetTempPathU();
IMPORT_C UNIW_GetVolumeInformation GetVolumeInformationU();
IMPORT_C UNIW_LoadLibrary LoadLibraryU();
IMPORT_C UNIW_MoveFile MoveFileU();
IMPORT_C UNIW_OpenMutex OpenMutexU();
IMPORT_C UNIW_OutputDebugString OutputDebugStringU();
IMPORT_C UNIW_PeekMessage PeekMessageU();
IMPORT_C UNIW_PostMessage PostMessageU();
IMPORT_C UNIW_ReadConsoleInput ReadConsoleInputU();
IMPORT_C UNIW_RegisterClass RegisterClassU();
IMPORT_C UNIW_RemoveDirectory  RemoveDirectoryU();
IMPORT_C UNIW_SetConsoleTitle SetConsoleTitleU();
IMPORT_C UNIW_SetEnvironmentVariable SetEnvironmentVariableU();
IMPORT_C UNIW_SetFileAttributes SetFileAttributesU();
IMPORT_C UNIW_SetVolumeLabel SetVolumeLabelU();

IMPORT_C void InitUansi(TUint aCodePage,TBool aWin95=EFalse);

#endif
