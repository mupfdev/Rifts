// BIF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// BIO-message Information File (BIF) Reader and Writer Classes
// 

#if !defined(__BIF_H__)
#define __BIF_H__

#if !defined(__APMREC_H__)
#include <apmrec.h>				// for TRecognitionConfidence
#endif 

// Classes defined
class CBioInfoFileReader;
class CBioInfoFileWriter;

// Classes referenced:
class CFileStore;
class CFbsBitmap;

#include <f32file.h>


//
// Constants
const TUid KUidBioInfoFile={0x10005233};		// unicode Uid, used as 2nd Uid of file store
const TUid KUidBioUseNoApp={0x00000000};			
const TUid KUidBioUseDefaultApp={0x100052b2};		
const TInt KMaxBioDescription=128;
const TInt KMaxBioIdText=128;
const TInt KMaxBioCommandLine=256;
const TInt KMaxBioFileExtension=10;


//
// Data types
typedef TBuf<KMaxBioIdText> TBioMsgIdText;
typedef TBuf<KMaxBioCommandLine> TBioCommand;

enum TBioMsgIdType 
	{
	EBioMsgIdUnknown,
	EBioMsgIdIana,
	EBioMsgIdNbs,

	//Receive over WDP
	EBioMsgIdWap,
	EBioMsgIdWapSecure,

	//Receive over WSP
	EBioMsgIdWsp,
	EBioMsgIdWspSecure
	};

class TBioMsgId 
	{
public:
	TBioMsgIdType iType;
	CApaDataRecognizerType::TRecognitionConfidence iConfidence;			// from APMREC.H
	TBioMsgIdText iText;
	TUint16 iPort;
	TUid iCharacterSet;
	TInt16 iGeneralIdData;
	};

#if !defined(__BIFBASE_H__)
#include "bifbase.h"				// for CBioInfoFile
#endif 

//////////////////////////////////////////////////////////////////////////////////////////
// BIF Reader Class
//
// Allows reading (all but the icons) from an existing BIF file.
//////////////////////////////////////////////////////////////////////////////////////////
class CBioInfoFileReader : public CBioInfoFile
	{
public:
	//
	// Construction/destruction
	IMPORT_C static CBioInfoFileReader* NewLC(RFs& aFs,const TDesC& aFileName,TUid aMsgTypeUid=KNullUid);
	IMPORT_C static CBioInfoFileReader* NewL(RFs& aFs,const TDesC& aFileName,TUid aMsgTypeUid=KNullUid);
	IMPORT_C ~CBioInfoFileReader();

	//
	// Data getters
	IMPORT_C TUid MessageTypeUid() const;
	IMPORT_C TUid MessageParserUid() const;
	IMPORT_C TUid MessageAppUid() const;
	IMPORT_C TUid MessageAppCtrlUid() const;
	IMPORT_C TInt16 GeneralData1() const;
	IMPORT_C TInt16 GeneralData2() const;
	IMPORT_C TInt16 GeneralData3() const;
	IMPORT_C const TPtrC Description() const;			
	IMPORT_C const TPtrC FileExtension() const;			

	IMPORT_C const TPtrC IconsFilename() const;			
	IMPORT_C const CArrayFixFlat<TInt16>* ZoomLevelsLC() const;
	IMPORT_C const TInt ZoomLevelsCount() const;			

	IMPORT_C const CArrayFixFlat<TBioMsgId>* IdsLC() const;
	
	inline const TEntry& FileEntry() const;

protected:
	//
	// Construction/destruction
	CBioInfoFileReader(RFs& aFs);
	void ConstructL(const TDesC& aFileName,TUid aMsgTypeUid);

private:
	void InternalizeL(RReadStream& aStream);
	void LoadResourceL(TUid aMsgTypeUid);
	void LoadDataL(TUid aMsgTypeUid);
	TBool IsResFileL() const;
	TBool IsDatFile() const;
	//
	TEntry iEntry;
	HBufC* iFileName;
	};


//////////////////////////////////////////////////////////////////////////////////////////
// BIF Writer Class
//
// Allows writing of all data to a new BIF file. On construction a new BIF file is always
// created. If on construction the BIF file already exists then it is deleted and a new 
// one created. BIF files are intended to be Write-Once-Read-Many in nature.
//////////////////////////////////////////////////////////////////////////////////////////
class CBioInfoFileWriter : public CBioInfoFile
	{
public:
	//
	// Construction/destruction
	IMPORT_C static CBioInfoFileWriter* NewLC(RFs& aFs,const TDesC& aFileName,TUid aMsgTypeUid);
	IMPORT_C ~CBioInfoFileWriter();

	IMPORT_C void StoreL();

	//
	// Data setters
	IMPORT_C void SetMessageTypeUid(TUid aValue);
	IMPORT_C void SetMessageParserUid(TUid aValue);
	IMPORT_C void SetMessageAppUid(TUid aValue);
	IMPORT_C void SetMessageAppCtrlUid(TUid aValue);
	IMPORT_C void SetGeneralData1(TInt16 aValue);
	IMPORT_C void SetGeneralData2(TInt16 aValue);
	IMPORT_C void SetGeneralData3(TInt16 aValue);
	IMPORT_C void SetDescription(const TPtrC& aValue);
	IMPORT_C void SetFileExtension(const TPtrC& aValue);
	IMPORT_C void SetIconsFilename(const TFileName& aValue);
	IMPORT_C void SetZoomLevelsL(const CArrayFix<TInt16>& aZoomLevelArray);
	IMPORT_C void AddIdL(const TBioMsgId& aValue);	
	
private:
	//
	// Construction/destruction
	CBioInfoFileWriter(RFs& aFs);
	void ConstructL(const TDesC& aFileName,TUid aMsgTypeUid);

	void ExternalizeL(RWriteStream& aStream) const;

private:
	CStoreMap* iMap;	
	CFileStore* iStore;
	};

#include "bif.inl"

#endif

