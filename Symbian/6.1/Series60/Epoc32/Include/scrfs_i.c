/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Mar 21 17:02:34 2002
 */
/* Compiler settings for scrfs.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation bounds_check stub_data 
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

const IID IID_IRFS = {0xEC000153,0xE5F3,0x11D2,{0xA9,0x53,0x00,0x10,0x5A,0x46,0xD6,0xE4}};


const IID IID_IRFSSink = {0xEC000154,0xE5F3,0x11D2,{0xA9,0x53,0x00,0x10,0x5A,0x46,0xD6,0xE4}};


const IID LIBID_SCRFSLib = {0xEC2000E1,0xE5F3,0x11D2,{0xA9,0x53,0x00,0x10,0x5A,0x46,0xD6,0xE4}};


const CLSID CLSID_RFS = {0xEC100153,0xE5F3,0x11D2,{0xA9,0x53,0x00,0x10,0x5A,0x46,0xD6,0xE4}};


const CLSID CLSID_RFSDataCallback = {0xEC100154,0xE5F3,0x11D2,{0xA9,0x53,0x00,0x10,0x5A,0x46,0xD6,0xE4}};


const CLSID CLSID_RFSConnection = {0xEC100155,0xE5F3,0x11D2,{0xA9,0x53,0x00,0x10,0x5A,0x46,0xD6,0xE4}};


#ifdef __cplusplus
}
#endif

