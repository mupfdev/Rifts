// Header LEXICAL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __LEXICAL_H__
#define __LEXICAL_H__

#if defined(__VC32__)
#pragma warning( disable : 4511 )	// copy constructor could not be generated
#pragma warning( disable : 4512 )	// assignment operator could not be generated
#pragma warning( disable : 4514 )	// unreferenced inline function has been removed
#pragma warning( disable : 4699 )	// Note: Using precompiled header %s
#pragma warning( disable : 4710 )	// function not inlined
#endif

#include <strng.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>

#include "gdr.h"

enum LexType
    {
    ELexEOF,         // end of file
    ELexNL,          // newline (newlines, white-space and comments stripped)
    ELexNumber,      // integer (no optional plus or minus)
    ELexIdent,       // identifier beginning with a..z, A..Z, or _ and continuing with 0..9
    ELexString,      // string delimited at start by "
    ELexOperator     // any other single character
    };

class Lexical
    {
public:
    Lexical();
    Lexical(const Lexical& aLex);
    Lexical& operator = (const Lexical& aLex);
    int CovertStringToHex();
private:
	int HexDigit(char aDigit,int& decimalEquivalent);
public:
    LexType iType;
    int iNumber; // for ELexNumber
    char iText[MaxLineLen+1]; // for ELexIdent, ELexString, ELexOperator
friend ostream& operator << (ostream& out, Lexical& aLex);
    };

class LexAnal
	{
public:
    LexAnal(const char* aFilename);
    Lexical Read(); // read next lexical into iLex
	Lexical ReadNextLine(); // read first lex on next line
	void Report();
    ~LexAnal();
public:
    ifstream iFin;
    Lexical iLex;
    int iLineNo;
	char iLine[MaxLineLen+1];
	char* iLexPtr; // Position in current lexical
	char* iCurPtr; // Position of current lexical in line
private:
	void GetNextLex();
	void GetNextLine();
    Lexical ReadEOF();
    Lexical ReadNL();
    Lexical ReadNumber();
    Lexical ReadIdent();
    Lexical ReadString();
    Lexical ReadOperator();
	String iFilename;
};

#endif
