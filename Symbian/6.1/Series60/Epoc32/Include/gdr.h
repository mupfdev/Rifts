// Header GDR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GDR_H__)
#define __GDR_H__

typedef char chardim;               // used for character dimensions, can be increased to short int (2 bytes)
typedef unsigned char uint8;	// used for values which are written as unsigned short int
typedef unsigned short int uint16;	// used for values which are written as unsigned short int
typedef signed long int32;	        // used for file signature
typedef unsigned long uint32;
typedef signed int uid;

typedef uint8 boolean;
const boolean efalse=0;
const boolean etrue=1;

const int MaxLineLen=256;   // maximum line length
const int KUndefinedInteger=0x7fff;

#define IMPORT_C __declspec(dllexport)
#define EXPORT_C __declspec(dllexport)

#endif
