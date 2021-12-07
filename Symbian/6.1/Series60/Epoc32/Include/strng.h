// Header STRNG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __STRNG_H__
#define __STRNG_H__

#include <string.h>
#include <stdlib.h>
#include <iostream.h>

#include "gdr.h"

class String	// NB only byte strings supported, no Unicode yet
    {
public:
	inline String();
	inline String(const char* aText);
	inline String(int aLength,char* aText);
	inline String(const String& aString);
	inline String& operator = (const char* aText);
	inline String& operator = (const String& aString);
	inline String& operator += (const char aChar);
	inline String& operator += (const String& aString);
	inline int operator == (const String& aString) const;
	inline char& operator [] (const int aNum) const;
	inline int Length() const;
	inline const char* Text();
	IMPORT_C virtual void Externalize(ostream& out);
protected:
	inline void CopyText(char* aDest,const char* aSource,int aLength) const;
	IMPORT_C int CreateText(const int aLength);
	IMPORT_C void DeleteText(char* aText) const;
public:
	IMPORT_C ~String();
protected:
	int32 iLength;	   // length of string
	char* iText; // data
friend ostream& operator << (ostream& out, const String& aString);
    };

#include <strng.inl>

#endif
