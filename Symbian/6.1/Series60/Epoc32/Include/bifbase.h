// BifBase.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// Base classes for BIO-message Information File (BIF) Reader and Writer
// 

#if !defined(__BIFBASE_H__)
#define __BIFBASE_H__

#if !defined(__S32STD_H__)
#include <s32std.h>				// for TSwizzle
#endif 


//////////////////////////////////////////////////////////////////////////////////////////
// Base Class for Reader and Writer classes
//////////////////////////////////////////////////////////////////////////////////////////
class CBioInfoFile : public CBase
	{
public:
	//
	// Destruction
	~CBioInfoFile();

protected:
	//
	// Construction
	CBioInfoFile(RFs& aFs);
	void ConstructL();

private:
	
	//
	// Classes for complex data structures within BIF file
	class CIdHeader : public CBase
		{
	public:
		CIdHeader();
		~CIdHeader();

		void InternalizeL(RReadStream& aStream);			
		void ExternalizeL(RWriteStream& aStream) const;		

	public:
		TBioMsgIdType iType;
		CApaDataRecognizerType::TRecognitionConfidence iConfidence;			// from APMREC.H
		TSwizzle<HBufC> iText;
		TUint16 iPort;
		TUid iCharacterSet;
		TInt16 iGeneralIdData;
		};

	class TIconZoomLevel
		{
	public:
		void InternalizeL(RReadStream& aStream);			
		void ExternalizeL(RWriteStream& aStream) const;		

	public:
		TInt16 iZoomLevel;
		};
	// End of complex data structure classes
	//


protected:
	RFs& iFs;

	//
	// Simple data to be read/write to/from BIF file
	TUid iMessageTypeUid;
	TUid iMessageParserUid;
	TUid iMessageAppUid;
	TUid iMessageAppCtrlUid;
	TBuf<KMaxBioDescription> iDescription;
	TInt16 iGeneralData1;
	TInt16 iGeneralData2;
	TInt16 iGeneralData3;
	TBuf<KMaxBioFileExtension> iFileExtension;
	
	TBuf<KMaxFileName> iIconsFilename;
		
	//
	// Complex data to be read/write to/from BIF file
	CArrayPtrFlat<CIdHeader>* iIdHeaderArray;
	CArrayFix<TIconZoomLevel>* iIconZoomLevelArray;
	};

#endif
