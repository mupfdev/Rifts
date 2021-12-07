// Header PDRRECRD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__PDRRECRD_H__)
#define __PDRRECRD_H__
#if !defined(__LEXICAL_H__)
#include "lexical.h"
#endif
#if !defined(__RECORD_H__)
#include "record.h"
#endif
#if !defined(__UID_H__)
#include "uid.h"
#endif

enum StyleIndex 
	{
	Normal,
	Bold,
	Italic,
	BoldItalic
	};

class PdrResource
	{
public:
	IMPORT_C static PdrResource* New();
	IMPORT_C void Delete();
	void Externalize(ostream& out);
public:
	int32 iId;
	String iString;
	};

class PdrResources : public Record
	{
public:
	IMPORT_C static PdrResources* New();
	IMPORT_C void Delete();
	void Externalize(ostream& out);
	IMPORT_C void AddResource(PdrResource* aResource);
private:
	~PdrResources();
private:
	ObjectList<PdrResource*> iPdrResourceList;
	};

class PdrTranslation
	{
public:
	IMPORT_C static PdrTranslation* New();
	IMPORT_C void Delete();
	void Externalize(ostream& out);
public:
	uint16 iFrom;
	String iTo;  //  !! Think about Unicode version
	};

class PdrTranslates : public Record
	{
public:
	IMPORT_C static PdrTranslates* New();
	IMPORT_C void Delete();
	void Externalize(ostream& out);
	IMPORT_C void AddTranslation(PdrTranslation* aTranslation);
private:
	~PdrTranslates();
private:
	ObjectList<PdrTranslation*> iPdrTranslationList;
	};

class Width
	{
public:
	IMPORT_C static Width* New();
	IMPORT_C void Delete();
	void Externalize(ostream& out);
public:
	uint16 iWidthInPixels;
	};

class WidthsCodeSection
	{
private:
	WidthsCodeSection();
public:
	IMPORT_C static WidthsCodeSection* New();
	IMPORT_C void Delete();
	void Externalize(ostream& out);
	IMPORT_C void AddWidth(Width* aWidth);
	IMPORT_C Width* WidthList(int i);
	IMPORT_C int NumWidths();
	~WidthsCodeSection();
public:
	uint16 iStart;
	uint16 iEnd;
private:
	ObjectList<Width*> iWidthList;
	};	

class FontInfo : public Record
	{
public:
	IMPORT_C static FontInfo* New();
	IMPORT_C void Delete();
	void Externalize(ostream& out);
	IMPORT_C void AddCodeSection(WidthsCodeSection* aCodeSection);
	IMPORT_C WidthsCodeSection* CodeSectionList(int i);
	IMPORT_C int NumCodeSections();
private:
	~FontInfo();	
public:
	uint16 iAscentInPixels;
	uint16 iMaxCharWidthInPixels;
	uint16 iMaxNormalCharWidthInPixels;
private:
	ObjectList<WidthsCodeSection*> iCodeSectionList;
	};
 
class PdrStyle
	{
public:
	IMPORT_C static PdrStyle* New();
	IMPORT_C void Delete();
	void Externalize(ostream& out);
	PdrStyle();
public:
	boolean iIsAvailable;
	Record *iFontInfo;
	};
   
class PdrFontHeight
	{
public:
	IMPORT_C static PdrFontHeight* New();
	IMPORT_C void Delete();
	void Externalize(ostream& out);
	PdrFontHeight();
public:
	String iCommandString;
	int32 iHeightInTwips;
	int32 iWidthScale;
	PdrStyle iStyle[BoldItalic+1];	// Array for four styles
	};

class PdrScalableFontHeight
	{
public:
	PdrScalableFontHeight();
	void Externalize(ostream& out);
public:
	String iCommandString;
	int32 iHeightMinInTwips;
	int32 iHeightMaxInTwips;
	int32 iHeightDeltaInTwips;
	PdrStyle iStyle[BoldItalic+1];	// Array for four styles
	};

class TypefaceFonts : public Record
	{
public:
	IMPORT_C static TypefaceFonts* New();
	IMPORT_C void Delete();
	void Externalize(ostream& out);
	IMPORT_C void AddFontHeight(PdrFontHeight* aFontHeight);
	IMPORT_C int NumFontHeights();
	PdrFontHeight* FontHeightList(int i);
private:
	TypefaceFonts();
	~TypefaceFonts();
public:
	Typeface iTypeface;
	boolean iIsScalable;
private:
	ObjectList<PdrFontHeight*> iFontHeightList;
public:
	PdrScalableFontHeight iScalableFontHeight;
	Record *iTranslates;
	};

class TypefaceFontsEntry
	{
public:
	IMPORT_C static TypefaceFontsEntry* New(Record* aTypefaceFonts);
	IMPORT_C void Delete();
	void Externalize(ostream& out);
private:
	TypefaceFontsEntry(Record* aTypefaceFonts);
public:
	~TypefaceFontsEntry();
public:
	Record* iTypefaceFonts;
	boolean iNotInPortrait;
	boolean iNotInLandscape;
	};

class Margins
	{
public:
	void Externalize(ostream& out);
public:
	int32 iLeft;
	int32 iRight;
	int32 iTop;
	int32 iBottom;
	};
/*
class PdrExtraInfo : public Record
	{
public:
	~PdrExtraInfo();
	void Externalize(ostream& out);
public:
	ObjectList<String*> iInfo;
	};
*/
class PdrModelInfo
	{
public:
	void Externalize(ostream& out);	
	IMPORT_C void AddTypefaceFontsEntry(TypefaceFontsEntry* aTypefaceFontsEntry);
	int NumTypefaceFontsEntries();
	TypefaceFontsEntry* TypefaceFontsEntryList(int i);
	PdrModelInfo();
	~PdrModelInfo();
public:
	streampos iStreamId;
	int32 iFlags;
	int32 iKPixelWidthInTwips;
	int32 iKPixelHeightInTwips;
	Point iPortraitOffsetInPixels;
	Point iLandscapeOffsetInPixels;
	Margins iMinMarginsInPixels;
	int32 iDisplayMode;
private:
	ObjectList<TypefaceFontsEntry*> iTypefaceFontsEntryList;
public:
	Record *iResources;
	Record *iSpareRecord;
	};
 
class PrinterModelEntry
	{
public:
	PrinterModelEntry();
	void Externalize(ostream& out);
public:
	String iName;
	boolean iRequiresPrinterPort;
	uid iUid;
	};

class PrinterModelHeader : public Record
	{
public:
	IMPORT_C static PrinterModelHeader* New();
	IMPORT_C void Delete();
	void Externalize(ostream& out);
	void ExternalizeData(ostream& out);
	boolean IsPdrModel();
public:
	PrinterModelEntry iEntry;
	PdrModelInfo iInfo;
	};

class PdrStoreFile : public Record
	{
public:
	IMPORT_C static PdrStoreFile* New();
	IMPORT_C void Delete();
	IMPORT_C void AddModel(PrinterModelHeader *aModel);
	void Externalize(ostream& out);
private:
	PdrStoreFile();
private:
	void AddTypefaceFonts(TypefaceFonts* aTypefaceFonts);
	void ExternalizeHeader(ostream& out);
	void ExternalizeComponents(ostream& out);
public:
	String iPDLName;
	uid iPDLUid;
private:
	RecordList iModelList;
	RecordList iTypefaceFontsList;
	RecordList iFontInfoList;
	RecordList iResourcesList;
	RecordList iTranslatesList;	   
//	RecordList iExtraInfoList;
	};

class PdrModelStore
	{
public:
	IMPORT_C boolean Store(const String& aFilename);
	IMPORT_C void AddPdrStoreFile(PdrStoreFile* aPdrStoreFile);
	IMPORT_C void AddModel(PrinterModelHeader *aModel);
	IMPORT_C Record* FindModel(String& aLabel);
	IMPORT_C void AddTypefaceFonts(TypefaceFonts *aTypefaceFonts);
	IMPORT_C Record* FindTypefaceFonts(String& aLabel);
	IMPORT_C void AddFontInfo(FontInfo *aFontInfo);
	IMPORT_C Record* FindFontInfo(String& aLabel);
	IMPORT_C void AddResources(PdrResources *aResources);
	IMPORT_C Record* FindResources(String& aLabel);
	IMPORT_C void AddTranslates(PdrTranslates *aTranslates);
	IMPORT_C Record* FindTranslates(String& aLabel);
//	void AddExtraInfo(PdrExtraInfo *aInfo);
//	Record* FindExtraInfo(String& aLabel);
	PdrModelStore();
	~PdrModelStore();
private:
	PdrStoreFile* iPdrStoreFile;
	RecordList iModelList;
	RecordList iTypefaceFontsList;
	RecordList iFontInfoList;
	RecordList iResourcesList;
	RecordList iTranslatesList;	   
//	RecordList iExtraInfoList;
	};

#endif
	 
