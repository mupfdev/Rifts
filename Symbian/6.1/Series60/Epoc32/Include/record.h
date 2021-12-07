// Header RECORD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __RECORD_H__
#define __RECORD_H__

#include "lexical.h"
#include "lst.h"
#include "strng.h"

const boolean Proportional=1;
const boolean Serif=2;
const boolean Symbol=4;

class Record 
	{
public:
	IMPORT_C Record();
	virtual void Externalize(ostream& out)=0;
	virtual void ExternalizeComponents(ostream&) {};
public:
	String iLabel;
	streampos iStreamId;
	};

class RecordList : public ObjectList<Record*> 
	{
public:
	void ExternalizeIds(ostream& out);
	void Externalize(ostream& out);
	void ExternalizeComponents(ostream& out);
	IMPORT_C void Add(Record* aRecord);
	IMPORT_C Record *LabelToRecord(const String& aLabel);
	IMPORT_C void Destroy();
	IMPORT_C ~RecordList();
	}; 
		   
class Typeface
	{
public:
	IMPORT_C Typeface();
	void Externalize(ostream& out);
public:
	String iName;
	boolean iFlags;
	};

class Point
	{
public:
	void Externalize(ostream& out);
public:
	int32 iX;
	int32 iY;
	};

#endif
	 
