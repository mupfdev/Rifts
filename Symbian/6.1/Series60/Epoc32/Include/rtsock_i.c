/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Mar 21 17:02:23 2002
 */
/* Compiler settings for G:\mRouterClients\rtsock\RtSock.idl:
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

const IID IID_ImConnectionStatusCallback = {0x5839A9A9,0xD72A,0x46de,{0xAD,0x52,0x09,0x4D,0x3E,0x08,0xC1,0x7D}};


const IID IID_ImRouterSocket = {0xB6917997,0x0434,0x4283,{0x8F,0xCA,0xFA,0x40,0x74,0xC3,0x8E,0xF4}};


const IID IID_ImRouterSimpleTransport = {0xF6648C13,0x972E,0x4f7b,{0x8D,0xF6,0xC2,0xF4,0xE0,0xAC,0x7F,0x5B}};


const IID LIBID_RTSOCKLib = {0xFE7A8E2F,0x3D2D,0x48ef,{0xBB,0x87,0x35,0x11,0xA5,0x46,0x8C,0xAD}};


const CLSID CLSID_RouterSimpleTransport = {0x5FFECA89,0xBCE4,0x4231,{0xB0,0x08,0xA2,0x53,0x63,0x86,0x12,0x3D}};


const CLSID CLSID_RouterSocket = {0x171689EE,0x8C61,0x4ef6,{0x81,0x60,0xCD,0x03,0x15,0xAC,0xB8,0xCF}};


#ifdef __cplusplus
}
#endif

