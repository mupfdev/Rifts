// APGICNFL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__APGICNFL_H__)
#define __APGICNFL_H__

#if !defined (__APADEF_H__)
#include <apadef.h>
#endif
#if !defined (__APAID_H__)
#include <apaid.h>
#endif
#if !defined (__BITDEV_H__)
#include <bitdev.h>
#endif
#if !defined (__APMSTD_H__)
#include <apmstd.h>
#endif
#if !defined (__BADESCA_H__)
#include <badesca.h>
#endif

// classes defined:
class CApaMaskedBitmap;
class CApaAppInfoFile;
class CApaAppInfoFileReader;
class CApaAppInfoFileWriter;
//
// classes referenced:
class CPersistentStore;
//

#ifdef _UNICODE
#define KUidAppInfoFile KUidAppInfoFile16
#else
#define KUidAppInfoFile KUidAppInfoFile8
#endif

const TUid KUidAppInfoFile8={268435562};
const TUid KUidAppInfoFile16={0x10003A38};

class CApaMaskedBitmap : public CFbsBitmap
	{
public:
	IMPORT_C static CApaMaskedBitmap* NewLC();
	IMPORT_C static CApaMaskedBitmap* NewL(CApaMaskedBitmap* aSourceIcon);
	//
	IMPORT_C CFbsBitmap* Mask() const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	//
	IMPORT_C ~CApaMaskedBitmap();
	void SetRomBitmapL(TUint8* aRomPointer);
private:
	CApaMaskedBitmap();
	void ConstructL();
private:
	CFbsBitmap* iMask;
	};

enum TAifVersion
// The order here is important, only ever APPEND to the list
	{
	EAifVersionOriginal,
	EAifVersionAddsDataType,
	EAifVersionAddsViewData,
	EAifVersionAddsFileOwnershipInfo
	};

/**
 * The CApaAIFCaption represents a caption in an AIF during reading and writing of the file.
 *
 * @since App-Framework_6.1
 * @internal
 */
class CApaAIFCaption : public CBase
	{
public:
	~CApaAIFCaption();
	CApaAIFCaption();
	void ConstructL(TLanguage aLanguage,const TDesC& aCaption);
	static CApaAIFCaption* NewLC(TLanguage aLanguage,const TDesC& aCaption);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	TLanguage Language() const;
	TApaAppCaption Caption() const;
public:
	HBufC* iCaption;
	TLanguage iLanguage;
	};


/**
 * The CApaAIFViewData represents a the data associated with an application view described in an AIF
 * during reading and writing of the file.
 *
 * @since App-Framework_6.1
 * @internal
 */
class CApaAIFViewData : public CBase
// implementation class
	{
public:
	IMPORT_C TApaAppCaption CaptionL(TLanguage aLanguage) const;
	IMPORT_C CApaMaskedBitmap* IconByIndexL(TInt aIndex) const;
	IMPORT_C TInt NumberOfIcons() const;
	IMPORT_C TUid ViewUid() const;
	IMPORT_C TInt ScreenMode() const;
public:
	~CApaAIFViewData();
	CApaAIFViewData();
	void ConstructL();
	static CApaAIFViewData* NewLC();
	void InternalizeL(RReadStream& aStream);		
	void ExternalizeL(RWriteStream& aStream) const;
	void SetScreenMode(TInt aScreenMode);
	void AddCaptionL(TLanguage aLanguage,const TDesC& aCaption);
	void AddIconL(CApaMaskedBitmap& aIcon);
	void SetViewUid(TUid aUid);
public:
	TInt iScreenMode;
	CArrayPtr<CApaMaskedBitmap>* iIconArray;
	CArrayPtr<CApaAIFCaption>* iCaptionArray;
	TUid iViewUid;
	};


class CApaAppInfoFile : public CBase
// implementation class
	{
public:
	~CApaAppInfoFile();
	//
protected:
	CApaAppInfoFile(RFs& aFs);
	void ConstructL();
private:
	class TCaptionHeader
		{
	public:
		void InternalizeL(RReadStream& aStream);			// internalizes the header info only
		void ExternalizeL(RWriteStream& aStream) const;		// externalizes the header info only
	public:
		TSwizzle<HBufC> iCaption;
		TLanguage iLanguage;
		};
private:
	class TIconHeader
		{
	public:
		void InternalizeL(RReadStream& aStream);			// internalizes the header info only
		void ExternalizeL(RWriteStream& aStream) const;		// externalizes the header info only
	public:
		TSwizzle<CApaMaskedBitmap> iIcon;
		TInt iIconSideInPixels;
		};
	class TDataTypeHeader
		{
	public:
		// header info only
		void InternalizeL(RReadStream& aStream); 			// internalizes the header info only
		void ExternalizeL(RWriteStream& aStream) const;		// externalizes the header info only
	public:
		TSwizzle<TDataType> iDataType;
		TDataTypePriority iPriority;
		};
	class TViewDataHeader
		{
	public:
		void InternalizeL(RReadStream& aStream);			// internalizes the header info only
		void ExternalizeL(RWriteStream& aStream) const;		// externalizes the header info only
	public:
		TSwizzle<CApaAIFViewData> iViewData;
		};
	class TFileOwnershipInfoHeader
		{
	public:
		void InternalizeL(RReadStream& aStream);			// internalizes the header info only
		void ExternalizeL(RWriteStream& aStream) const;		// externalizes the header info only
	public:
		TSwizzle<HBufC> iOwnedFileName;
		};
protected:
	RFs& iFs;
	CPersistentStore* iStore;
	CArrayFix<TCaptionHeader>* iCaptionHeaderArray;
	CArrayFix<TIconHeader>* iIconHeaderArray;
	CArrayFix<TDataTypeHeader>* iDataTypeHeaderArray;
	CArrayFix<TViewDataHeader>* iViewDataHeaderArray;
	CArrayFix<TFileOwnershipInfoHeader>* iFileOwnershipInfoHeaderArray;
	TApaAppCapability iCapability;
	};

/**
 * Do not use
 * @internal
 */
class CApaAppInfoFileReader : public CApaAppInfoFile
	{
public:
	IMPORT_C static CApaAppInfoFileReader* NewLC(RFs& aFs, const TDesC& aFileName,TUid aApplicationUid=KNullUid);
	IMPORT_C static CApaAppInfoFileReader* NewL(RFs& aFs, const TDesC& aFileName,TUid aApplicationUid=KNullUid);
	//
	IMPORT_C void Capability(TDes8& aInfo)const;
	IMPORT_C TApaAppCaption CaptionL(TLanguage aLanguage);
	
	IMPORT_C CApaMaskedBitmap* CreateMaskedBitmapL(TInt aIconSideInPixels); // If there are no bitmaps in the file this method leaves with KErrNotFound
	// Not available until ER6
	CApaMaskedBitmap* CreateMaskedBitmapByIndexL(TInt aIndex); // If there are no bitmaps in the file this method leaves with KErrNotFound
	TInt NumberOfBitmaps() const;

	// Not available till ER5
	IMPORT_C void DataTypesSupportedL(CArrayFix<TDataTypeWithPriority>& aTypeList) const;
	//

	// Not available till ER6.1
	IMPORT_C void GetViewsL(CArrayPtr<CApaAIFViewData>& aViewList) const;
	IMPORT_C void GetOwnedFilesL(CDesCArray& aOwnedFilesList) const;
	//	

	// utility function
	IMPORT_C static void StretchDrawL(CFbsBitmap* aSource,CFbsBitmap* aTarget,TSize aSizeInPixels);
	//
	IMPORT_C ~CApaAppInfoFileReader();
public:
	static void GetAifFileNameL(const TDesC& aFullName,TDes& aAifName);
private:
	CApaAppInfoFileReader(RFs& aFs);
	void InternalizeL(RReadStream& aStream);
	void ConstructL(const TDesC& aFileName,TUid aUid);
private:
	HBufC* iDefaultCaption;
	TUint8* iRomPointer;
	};


/**
 * Do not use
 * @internal
 */
class CApaAppInfoFileWriter : public CApaAppInfoFile
	{
public:
	IMPORT_C static CApaAppInfoFileWriter* NewLC(RFs& aFs, const TDesC& aFileName,TUid aApplicationUid);
	//
	IMPORT_C TInt SetCapability(const TDesC8& aInfo);
	IMPORT_C void AddCaptionL(TLanguage aLanguage,const TDesC& aCaption);
	IMPORT_C void AddIconL(const TDesC& aIconFileName);
	IMPORT_C void AddIconL(CApaMaskedBitmap& aIcon);
	
	// Not available till ER5
	IMPORT_C void AddDataTypeL(const TDataTypeWithPriority& aTypePriority);
	//

	// Not available till ER6.1
	IMPORT_C void AddViewL(TUid aViewUid);
	IMPORT_C void AddViewL(TUid aViewUid,TInt aScreenMode);
	IMPORT_C void AddViewCaptionL(TLanguage aLanguage,const TDesC& aCaption,TUid aViewUid);
	IMPORT_C void AddViewIconL(CApaMaskedBitmap& aIcon,TUid aViewUid);
	IMPORT_C void StoreViewL(TUid aViewId);
	IMPORT_C void AddOwnedFileL(const TDesC& aOwnedFileName);
	//
	
	IMPORT_C void StoreL();
	//
	IMPORT_C ~CApaAppInfoFileWriter();
private:
	CApaAppInfoFileWriter(RFs& aFs);
	void ExternalizeL(RWriteStream& aStream) const;
	void ConstructL(const TDesC& aFileName,TUid aUid);
private:
	CStoreMap* iMap;
	};

class CApaAppCaptionFileReader : public CBase
	{
public:
	CApaAppCaptionFileReader(RFs& aFs,const TDesC& iAppFileName);
	void GetCaptionsL(TApaAppCaption& aCaption,TApaAppCaption& aShortCaption);
private:	
	RFs& iFs;
	TFileName iCaptionFileName;
	};

/**
 * Internal utilities providing helper functions for non-ROM localisation
 */
class AppInfoFileUtils
	{
public: // For internal use only
	IMPORT_C static void GetAifFileName(const RFs& aFs,TDes& aAifName);
public:
	static void GetAifFileNameL(const RFs& aFs,const TDesC& aFullName,TDes& aAifName);
	};

#endif

