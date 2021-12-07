/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Mar 21 17:01:59 2002
 */
/* Compiler settings for G:\mRouter\mRouterAccessPoint\mRouterAccessPoint.idl:
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

const IID IID_IClientDevice = {0x3EB39CA1,0x564D,0x4F32,{0x97,0x52,0x28,0xC7,0xC7,0x3E,0x49,0xC1}};


const IID IID_IClientDeviceEnumerator = {0x1E8AB0AA,0x19F0,0x486C,{0xBA,0x22,0x87,0x8A,0xFA,0x5E,0x8E,0x3C}};


const IID IID_ImRouterAccessPoint = {0x154B9423,0x7D3D,0x4020,{0x89,0x1B,0xE7,0x2D,0x19,0x37,0x17,0x47}};


const IID LIBID_MROUTERACCESSPOINTLib = {0xA67E77B8,0x2DA8,0x4635,{0xA4,0x02,0xA0,0x4A,0xD6,0x6A,0x69,0xF7}};


const CLSID CLSID_AccessPoint = {0x246A43F9,0x6B2D,0x4A50,{0x84,0x7C,0x88,0xA0,0xC9,0x47,0x55,0xF6}};


const CLSID CLSID_ClientDevice = {0x80F5AE67,0xE6C0,0x4287,{0x8E,0x96,0xB0,0xCF,0xE6,0xF6,0x82,0x64}};


const CLSID CLSID_ClientDeviceEnumerator = {0xB21B14F5,0x513A,0x4342,{0x90,0x38,0xBF,0xE1,0x9E,0x7A,0xFE,0xE0}};


#ifdef __cplusplus
}
#endif

