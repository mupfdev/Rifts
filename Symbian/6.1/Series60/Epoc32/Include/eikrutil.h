// EIKRUTIL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKRUTIL_H__)
#define __EIKRUTIL_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__GULUTIL_H__)
#include <gulutil.h>
#endif
class CFbsFont;
class CEikonEnv;
class CWsScreenDevice;
class TResourceReader;

class EikResourceUtils
	{
public:
	inline static CFbsFont* CreateScreenFontL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CFbsFont* CreateScreenFontL(TInt aResourceId,CEikonEnv* aEnv=NULL);
	inline static TInt8 ReadTInt8L(TInt aResourceId,CEikonEnv* aEnv=NULL);
	inline static TInt16 ReadTInt16L(TInt aResourceId,CEikonEnv* aEnv=NULL);
	inline static TInt32 ReadTInt32L(TInt aResourceId,CEikonEnv* aEnv=NULL);
	IMPORT_C static CColorArray* CreateColorArrayL(TInt aResourceId,CEikonEnv* aEnv=NULL);
	IMPORT_C static CColorArray* CreateColorArrayLC(TInt aResourceId,CEikonEnv* aEnv=NULL);
	//
private:
	enum TResourceTypeInt { EResourceInt8,EResourceInt16,EResourceInt32 };
private:
	IMPORT_C static TInt32 ReadResourceIntL(TInt aResourceId,CEikonEnv* aEnv,TResourceTypeInt aSize);
	};

//	class EikResourceUtils
inline CFbsFont* EikResourceUtils::CreateScreenFontL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice)
	{
	return(ResourceUtils::CreateScreenFontL(aResourceReader,aScreenDevice));
	}
inline TInt8 EikResourceUtils::ReadTInt8L(TInt aResourceId,CEikonEnv* aEnv)
	{
	return((TInt8)ReadResourceIntL(aResourceId,aEnv,EResourceInt8));
	}
inline TInt16 EikResourceUtils::ReadTInt16L(TInt aResourceId,CEikonEnv* aEnv)
	{
	return((TInt16)ReadResourceIntL(aResourceId,aEnv,EResourceInt16));
	}
inline TInt32 EikResourceUtils::ReadTInt32L(TInt aResourceId,CEikonEnv* aEnv)
	{
	return((TInt32)ReadResourceIntL(aResourceId,aEnv,EResourceInt32));
	}
#endif
