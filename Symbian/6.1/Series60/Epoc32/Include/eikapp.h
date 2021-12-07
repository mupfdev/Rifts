// EIKAPP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKAPP_H__)
#define __EIKAPP_H__

#if !defined(__APPARC_H__)
#include <apparc.h>
#endif

#if !defined(__APAFLREC_H__)
#include <apaflrec.h>
#endif

class CCoeEnv;

class CEikApplication : public CApaApplication
	{
public:
	IMPORT_C ~CEikApplication();
	inline TInt ResourceFileOffset() const;
	inline CApaProcess* Process() const;
	inline const TApaAppCaption& AppCaption() const;
	IMPORT_C virtual void GetDefaultDocumentFileName(TFileName& aDocumentName) const;
	IMPORT_C virtual TFileName BitmapStoreName() const;
	// from CApaApplication
	IMPORT_C CApaAppInfoFileReader* OpenAppInfoFileLC() const;
	IMPORT_C CDictionaryStore* OpenIniFileLC(RFs& aFs) const;
	IMPORT_C void Capability(TDes8& aInfo) const;
	IMPORT_C void SetToIniFileNameL(TParse& aParser) const;
protected: // from CApaApplication
	IMPORT_C void PreDocConstructL();
	IMPORT_C CApaDocument* CreateDocumentL(CApaProcess* aProcess);
private:
	// reserved virtual function from CApaApplication
	IMPORT_C virtual void Reserved_1();
protected: // new function
	IMPORT_C CEikApplication();
public: // new function
	IMPORT_C virtual TFileName ResourceFileName() const;
private: // new function
	virtual CApaDocument* CreateDocumentL()=0;
private: // internal use
	void ParseWithAppName(TParse& aParse,const TDesC& aFileName) const;
	void ReadCaptionNameL();
protected:
	CCoeEnv* iCoeEnv;
	TInt iResourceFileOffset;
private:
	CApaProcess* iProcess;
	TApaAppCaption iCaption;
	TApaAppCapabilityBuf* iCapabilityBuf;
	TUint iAppFlags;
	TInt iSpare;
	};

inline TInt CEikApplication::ResourceFileOffset() const
	{ return(iResourceFileOffset); }

inline CApaProcess* CEikApplication::Process() const
	{ return(iProcess); }

inline const TApaAppCaption& CEikApplication::AppCaption() const
	{ return(iCaption);	}

#endif
