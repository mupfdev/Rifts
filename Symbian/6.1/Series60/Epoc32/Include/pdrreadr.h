// Header PDRREADR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__PDRREADR_H__)
#define __PDRREADR_H__
#if !defined(__LEXICAL_H__)
#include "lexical.h"
#endif
#if !defined(__PDRRECRD_H__)
#include "pdrrecrd.h"
#endif
#if !defined(__READER_H__)
#include "reader.h"
#endif

// Resource identifiers
const String IdentResources("Resources");
const String IdentTranslates("Translates");
const String IdentFontInfo("FontInfo");
const String IdentTypefaceFonts("TypefaceFonts");
const String IdentModel("Model");
const String IdentPdrStoreFile("PdrStoreFile");
//const String IdentExtraInfo("ExtraInfo");

// Resources identifiers
const String IdentEndResources("EndResources");

// Translates identifiers
const String IdentEndTranslates("EndTranslates");

// Codesection identifiers
const String IdentEndCodeSection("EndCodeSection");

// Fontinfo identifiers
const String IdentEndFontInfo("EndFontInfo");
const String IdentAscent("Ascent");
const String IdentMaxNormalCharWidth("MaxNormalCharWidth");
const String IdentCodeSection("CodeSection");

// Fontheight identifiers
const String IdentEndFontHeight("EndFontHeight");
const String IdentHeight("Height");
const String IdentWidthScale("WidthScale");
const String IdentNormal("Normal");
const String IdentBold("Bold");
const String IdentItalic("Italic");
const String IdentBoldItalic("BoldItalic");
const String IdentCommand("Command");

// Scalable fontheight identifiers
const String IdentEndScalableFontHeight("EndScalableFontHeight");
const String IdentHeightMin("HeightMin");
const String IdentHeightMax("HeightMax");
const String IdentHeightDelta("HeightDelta");
    // uses FontHeight IdentNormal etc

// Typefacefonts identifiers
const String IdentEndTypefaceFonts("EndTypefaceFonts");
const String IdentTypefaceTranslates("Translates");
const String IdentTypefaceName("Name");
const String IdentProportional("Proportional");
const String IdentSerif("Serif");
const String IdentSymbol("Symbol");
const String IdentFontHeight("FontHeight");
const String IdentScalableFontHeight("ScalableFontHeight");

// Extra info identifiers
//const String IdentEndExtraInfo("EndExtraInfo");

// Model identifiers
const String IdentEndModel("EndModel");
const String IdentModelName("Name");
const String IdentRequiresPrinterPort("RequiresPrinterPort");
const String IdentModelFlags("Flags");
const String IdentModelUid("Uid");
const String IdentModelResources("Resources");
const String IdentKPixelWidth("KPixelWidth");
const String IdentKPixelHeight("KPixelHeight");
const String IdentPortraitOffset("PortraitOffset");
const String IdentLandscapeOffset("LandscapeOffset");
const String IdentMinMarginLeft("MinMarginLeft");
const String IdentMinMarginRight("MinMarginRight");
const String IdentMinMarginTop("MinMarginTop");
const String IdentMinMarginBottom("MinMarginBottom");
const String IdentDisplayMode("DisplayMode");
const String IdentTypefaceFontss("TypefaceFontss");
const String IdentSpareRecord("SpareRecord");

// Typefacefontsentry identifiers
const String IdentEndTypefaceFontss("EndTypefaceFontss");
const String IdentNotInPortrait("NotInPortrait");
const String IdentNotInLandscape("NotInLandscape");

// Pdrstorefile identifiers
const String IdentEndPdrStoreFile("EndPdrStoreFile");
const String IdentPDLName("PDLName");
const String IdentPDLUid("PDLUid");
const String IdentModels("Models");
const String IdentEndModels("EndModels");

class PdrReader : public Reader
	{
public:
	IMPORT_C PdrReader();
	IMPORT_C boolean Read(const String& aFilename);
	IMPORT_C ~PdrReader();
	boolean ReadResources();
	boolean ReadTranslates();
	boolean ReadCodeSection(int aCode);
	boolean ReadFontInfo();
	boolean ReadStyle();
	boolean ReadFontHeight();
	boolean ReadScalableFontHeight();
	boolean ReadTypefaceFonts();
	boolean ReadModel();
	boolean ReadPdrStoreFile();
	IMPORT_C boolean Store(const String& aFilename);
    boolean Command(String& aCommand);
//	boolean ReadExtraInfo();
protected:
	PdrModelStore iPdrModelStore;
	PdrStoreFile* iPdrStoreFile;
	PdrResources* iResources;
	PdrTranslates* iTranslates;
	WidthsCodeSection* iCodeSection;
	FontInfo* iFontInfo;
	StyleIndex iIndex;
	PdrFontHeight* iFontHeight;
	TypefaceFonts* iTypefaceFonts;
	PrinterModelHeader* iModel;
	};

#endif
