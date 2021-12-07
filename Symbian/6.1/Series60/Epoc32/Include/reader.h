// Header READER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__READER_H__)
#define __READER_H__
#if !defined(__LEXICAL_H__)
#include "lexical.h"
#endif
#if !defined(__RECORD_H__)
#include "record.h"
#endif

class Reader
	{
public:
	Reader();
	virtual boolean Read(const String& aFilename)=0;
	~Reader();
protected:
	boolean Open(const String& aFilename);
    boolean _EOF();
    boolean NL();
    boolean Number(int& aNumber);
    boolean Ident();
    boolean IdentComp(const String& aIdent);
    boolean IdentCopy(String& aIdent);
    boolean StringCopy(String& aString);
    boolean Operator(char& aCh);
	IMPORT_C void Error(const String& aString);
protected:
	LexAnal *iLexAnal;
	Lexical *iLex;
	};

#endif
