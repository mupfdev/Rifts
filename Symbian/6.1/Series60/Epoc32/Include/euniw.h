// Euniw.h
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EUNIW_H__)
#define __EUNIW_H__

#include "e32def.h"
#define WIN32_LEAN_AND_MEAN
#pragma warning( disable : 4201 ) // nonstandard extension used : nameless struct/union
#include <windows.h>
#pragma warning( default : 4201 ) // nonstandard extension used : nameless struct/union

#ifdef __cplusplus
extern "C" {
#endif


// Declare function pointers for each function
typedef WINBASEAPI BOOL (WINAPI *UNIW_CreateDirectory) (LPCTSTR ,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
typedef WINBASEAPI HANDLE (WINAPI *UNIW_CreateFile) (LPCTSTR ,DWORD ,DWORD ,LPSECURITY_ATTRIBUTES ,DWORD ,DWORD ,HANDLE);
typedef WINBASEAPI HANDLE (WINAPI *UNIW_CreateMutex) (LPSECURITY_ATTRIBUTES , BOOL, LPCTSTR);
typedef WINBASEAPI HANDLE (WINAPI *UNIW_CreateSemaphore) (LPSECURITY_ATTRIBUTES ,LONG ,LONG ,LPCTSTR);
typedef WINUSERAPI LRESULT (WINAPI *UNIW_DefWindowProc) (HWND hWnd, UINT,WPARAM ,LPARAM);
typedef WINBASEAPI BOOL (WINAPI *UNIW_DeleteFile) (LPCTSTR);
typedef WINUSERAPI LONG (WINAPI *UNIW_DispatchMessage) (CONST MSG*);
typedef WINBASEAPI HANDLE (WINAPI *UNIW_FindFirstFile) (LPCTSTR ,LPWIN32_FIND_DATA);
typedef WINBASEAPI BOOL (WINAPI *UNIW_FindNextFile) (HANDLE ,LPWIN32_FIND_DATA);
typedef WINBASEAPI DWORD (WINAPI *UNIW_GetCurrentDirectory) (DWORD ,LPTSTR);
typedef WINBASEAPI BOOL (WINAPI *UNIW_GetDiskFreeSpace) (LPCTSTR ,LPDWORD ,LPDWORD ,LPDWORD ,LPDWORD);
typedef WINBASEAPI UINT (WINAPI *UNIW_GetDriveType) (LPCTSTR);
typedef WINBASEAPI DWORD (WINAPI *UNIW_GetEnvironmentVariable) (LPCTSTR ,LPTSTR ,DWORD);
typedef WINBASEAPI DWORD (WINAPI *UNIW_GetFileAttributes) (LPCTSTR);
typedef WINBASEAPI DWORD (WINAPI *UNIW_GetFullPathName) (LPCTSTR ,DWORD ,LPTSTR ,LPTSTR*);
typedef WINUSERAPI BOOL (WINAPI *UNIW_GetMessage) (LPMSG ,HWND ,UINT ,UINT);
typedef WINBASEAPI DWORD (WINAPI *UNIW_GetModuleFileName)(HMODULE , LPTSTR ,DWORD);
typedef WINBASEAPI HMODULE (WINAPI *UNIW_GetModuleHandle) (LPCTSTR);
typedef WINGDIAPI int  (WINAPI *UNIW_GetObject) (HGDIOBJ, int, LPVOID);
typedef WINBASEAPI DWORD (WINAPI *UNIW_GetTempPath) (DWORD ,LPTSTR);
typedef WINBASEAPI BOOL (WINAPI *UNIW_GetVolumeInformation) (LPCTSTR ,LPTSTR ,DWORD ,LPDWORD ,LPDWORD ,LPDWORD ,LPTSTR,DWORD);
typedef WINBASEAPI HMODULE (WINAPI *UNIW_LoadLibrary) (LPCTSTR);
typedef WINBASEAPI BOOL (WINAPI *UNIW_MoveFile) (LPCTSTR ,LPCTSTR);
typedef WINBASEAPI HANDLE (WINAPI *UNIW_OpenMutex) (DWORD , BOOL ,LPCTSTR);
typedef WINBASEAPI VOID (WINAPI *UNIW_OutputDebugString) (LPCTSTR);
typedef WINUSERAPI BOOL (WINAPI *UNIW_PeekMessage) (LPMSG ,HWND ,UINT ,UINT ,UINT);
typedef WINUSERAPI BOOL (WINAPI *UNIW_PostMessage) (HWND ,UINT ,WPARAM ,LPARAM);
typedef WINBASEAPI BOOL (WINAPI *UNIW_RemoveDirectory) (LPCTSTR);
typedef WINBASEAPI BOOL (WINAPI *UNIW_ReadConsoleInput) (HANDLE , PINPUT_RECORD, DWORD, LPDWORD);
typedef WINUSERAPI ATOM (WINAPI *UNIW_RegisterClass) (CONST WNDCLASS *);
typedef WINUSERAPI BOOL (WINAPI *UNIW_SetConsoleTitle) (LPCTSTR);
typedef WINBASEAPI BOOL (WINAPI *UNIW_SetEnvironmentVariable) (LPCTSTR ,LPCTSTR);
typedef WINBASEAPI BOOL (WINAPI *UNIW_SetFileAttributes) (LPCTSTR ,DWORD);
typedef WINBASEAPI BOOL (WINAPI *UNIW_SetVolumeLabel) (LPCTSTR ,LPCTSTR);

typedef struct _tagEuniwInit {

	UNIW_CreateDirectory* CreateDirectoryU;
	UNIW_CreateFile* CreateFileU;
	UNIW_CreateMutex* CreateMutexU;
	UNIW_CreateSemaphore* CreateSemaphoreU;
	UNIW_DeleteFile* DeleteFileU;
	UNIW_FindFirstFile* FindFirstFileU;
	UNIW_FindNextFile* FindNextFileU;
	UNIW_GetCurrentDirectory* GetCurrentDirectoryU;
	UNIW_GetDiskFreeSpace* GetDiskFreeSpaceU;
	UNIW_GetEnvironmentVariable* GetEnvironmentVariableU;
	UNIW_GetFileAttributes* GetFileAttributesU;
	UNIW_GetFullPathName* GetFullPathNameU;
	UNIW_GetDriveType* GetDriveTypeU;
	UNIW_GetModuleFileName* GetModuleFileNameU;
	UNIW_GetModuleHandle* GetModuleHandleU;
	UNIW_GetTempPath* GetTempPathU;
	UNIW_GetVolumeInformation* GetVolumeInformationU;
	UNIW_LoadLibrary* LoadLibraryU;
	UNIW_MoveFile* MoveFileU;
	UNIW_OpenMutex* OpenMutexU;
	UNIW_OutputDebugString* OutputDebugStringU;
	UNIW_ReadConsoleInput* ReadConsoleInputU;
	UNIW_RegisterClass* RegisterClassU;
	UNIW_RemoveDirectory*  RemoveDirectoryU;
	UNIW_SetConsoleTitle* SetConsoleTitleU;
	UNIW_SetEnvironmentVariable* SetEnvironmentVariableU;
	UNIW_SetFileAttributes* SetFileAttributesU;
	UNIW_SetVolumeLabel* SetVolumeLabelU;
	} EUNIWINIT;

void InitEuniw(EUNIWINIT*,TUint);

#ifdef __cplusplus
	}
#endif

#endif
