/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Mar 21 17:02:15 2002
 */
/* Compiler settings for G:\mRouterClients\mRouterSocket\mRouterSocket.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ImRouterSock = {0x8EA9C24C,0x3DE0,0x49ED,{0xBE,0x38,0x8C,0x9D,0xEB,0x87,0x2C,0x59}};


const IID LIBID_MROUTERSOCKETLib = {0x11759AB9,0xC979,0x4E26,{0x8B,0xBF,0xBD,0xE0,0x05,0xCC,0x51,0xCD}};


const CLSID CLSID_mRouterSock = {0x24D6B2C6,0x8A5C,0x4405,{0x93,0xED,0x13,0xFD,0xF9,0x90,0xCB,0xCC}};


#ifdef __cplusplus
}
#endif

