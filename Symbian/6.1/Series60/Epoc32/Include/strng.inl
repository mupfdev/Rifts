// Header STRNG.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


inline String::String():
	iLength(0),
	iText(NULL)
	{
	}

inline String::String(const char* aText):
	iLength(0),
	iText(NULL)
	{
	if (aText && CreateText(strlen(aText)))
		{
		CopyText(iText,aText,iLength);
		iText[iLength]='\0';
		}
	}

inline String::String(int aLength,char* aText):
	iLength(0),
	iText(NULL)
	{
	if (aText && CreateText(aLength))
		{
		CopyText(iText,aText,aLength);
		iText[iLength]='\0';
		}
	}

inline String::String(const String& aString):
	iLength(0),
	iText(NULL)
	{
	if (CreateText(aString.iLength))
		{
		CopyText(iText,aString.iText,iLength);
		iText[iLength]='\0';
		}
	}

inline String& String::operator = (const char* aText)
	{
	char* text=iText;
	if (CreateText(strlen(aText)))
		{
		CopyText(iText,aText,iLength);
		iText[iLength]='\0';
		DeleteText(text);
		}
	return *this;
	}

inline String& String::operator = (const String& aString)
	{
	String string(aString);
	char* text=iText;
	if (CreateText(string.iLength))
		{
		CopyText(iText,string.iText,iLength);
		iText[iLength]='\0';
		DeleteText(text);
		}
	return *this;
	}

inline String& String::operator += (const char aChar)
	{
	char* text=iText;
	if (CreateText(iLength+1))
		{
		CopyText(iText,text,iLength-1);
		iText[iLength-1]=aChar;
		iText[iLength]='\0';
		DeleteText(text);
		}
	return *this;
	}

inline String& String::operator += (const String& aString)
	{
	char* text=iText;
	int length=iLength;
	if (CreateText(length+aString.iLength))
		{
		CopyText(iText,text,length);
		CopyText(iText+length,aString.iText,aString.iLength);
		iText[iLength]='\0';
		DeleteText(text);
		}
	return *this;
	}

inline int String::operator == (const String& aString) const
	{
	boolean same=etrue;
	if (iLength!=aString.iLength)
		same=efalse;
	else
		{
		for (int i=0; i<iLength; i++)
			same = same && ((*this)[i]==aString[i]);
		}
	return same;
	}

inline char& String::operator [] (const int aNum) const
	{
	return iText[aNum];
	}

inline int String::Length() const
	{
	return iLength;
	}

inline const char* String::Text()
	{
	return iText;
	}

inline void String::CopyText(char* aDest,const char* aSource,int aLength) const
	{
	for (int i=0; i<aLength; i++)
		aDest[i]=aSource[i];
	}

