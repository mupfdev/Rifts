/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Mar 21 17:00:44 2002
 */
/* Compiler settings for G:\mRouter\mRouterRuntime\mRouterRuntime.idl:
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

const IID IID_ImRouterComMap = {0xE7417920,0xFC8C,0x487C,{0x8E,0x4D,0x91,0xB9,0xDD,0xB4,0xF0,0x1B}};


const IID IID_ImRouterRuntimeNat = {0xC98CA569,0xB190,0x441B,{0x80,0xC3,0x70,0x38,0xC7,0x59,0xBA,0x48}};


const IID LIBID_MROUTERRUNTIMELib = {0xDFDA94D6,0x9AF1,0x4B01,{0x97,0x46,0x38,0xAA,0x7F,0x74,0x53,0xC9}};


const CLSID CLSID_mRouterComMap = {0x5337DE69,0x39E2,0x4720,{0x9A,0xE3,0x0C,0x2D,0x17,0x02,0x48,0x69}};


const CLSID CLSID_mRouterRuntimeNat = {0xB823FFF4,0x0FD9,0x449D,{0xBF,0x75,0x21,0xF5,0xAD,0x91,0xC9,0x7D}};


#ifdef __cplusplus
}
#endif

