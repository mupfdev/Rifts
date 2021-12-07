// GsmCompressionBase.h: interface for the CGsmCompressionBase class.
// 
// suggested by Krzysztof Wasilewski :)
// altered by Chris Wilson :(
//
//////////////////////////////////////////////////////////////////////





#if !defined (__GSMUCOMP_H_)
#define __GSMUCOMP_H_

#if !defined (__E32BASE_H_)
#include <e32base.h>
#endif

class CSmsBufferBase;
class CBufSeg;

class CGsmCompressionBase;
class RFs;
class RReadStream;
class RWriteStream;

#if defined(_UNICODE)
const TUid KUidGsmCompressionDll={0x1000089A};
#else
const TUid KUidGsmCompressionDll={0x100008A0};
#endif

typedef CGsmCompressionBase* (*NewGsmCompressionL)(RFs& aFs);
const TInt KGsmLibraryEntryPointOridinalNumber=1;


class TGsmCompressionSettings
	{
public:
	enum TGsmLanguage
		{
		EGerman=0x00,
		EEnglish=0x001,
		EItalian=0x02,
		EFrench=0x03,
		ESpanish=0x04,
		EDutch=0x05,
		ESwedish=0x06,
		EDanish=0x07,
		EPortugese=0x08,
		EFinnish=0x09,
		ENorwegian=0x0A,
		EGreek=0x0B,
		ETurkish=0x0C,
		EHungarian=0x0D,
		EPolish=0x0E,
		EUnspecified=0x0F
		};
		
	enum TGsmCharacterSet
		{
		ENotDefined=0x00,	// for binary data
		EGsm7Bit=0x01,
		ECodePage437=0x02,
		ECodePage850=0x03,

		EUCS2=0x10000  //  This value is not defined in SMS compression specs
		};             //  but forces the first UCS2 row to be defined in the header

public:
	IMPORT_C TGsmCompressionSettings();

	inline TGsmLanguage CurrentLanguageContext() const;
	inline void SetCurrentLanguageContext(TGsmLanguage aLanguage);

	IMPORT_C TBool CharacterSet(TGsmCharacterSet& aCharacterSet) const;
	IMPORT_C void SetCharacterSet(TBool aChange,TGsmCharacterSet aCharacterSet);
	
	IMPORT_C TBool PunctuatorID(TInt& aID) const;
	IMPORT_C void SetPunctuatorID(TBool aChange,TInt aID);
	
	IMPORT_C TBool CharacterGroupID(TInt& aID) const;
	IMPORT_C void SetCharacterGroupID(TBool aChange,TInt aID);

	IMPORT_C TBool KeywordDictionaryID(TInt& aID) const;
	IMPORT_C void SetKeywordDictionaryID(TBool aChange,TInt aID);

	IMPORT_C TBool HuffmanInitializationID(TInt& aID) const;
	IMPORT_C void SetHuffmanInitializationID(TBool aChange,TInt aID);
	
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

private:
	enum TGsmCompressionSettingsFlags
		{
		EChangeCharacterSet=0x01,
		EChangePunctuatorID=0x02,
		EChangeKeywordDictionaryID=0x04,
		EChangeCharacterGroupID=0x08,
		EChangeHuffmanInitializationID=0x10
		};
private:
	TGsmLanguage iCurrentLanguageContext;
	TInt iFlags;  //  Used for enabling punctuation etc and changing defaults from current language context
	TGsmCharacterSet iCharacterSet;
	TInt iPunctuatorID;            
	TInt iKeywordDictionaryID;     
	TInt iCharacterGroupID;        
	TInt iHuffmanInitializationID; 
	};



class CGsmCompressionBase : public CBase  
	{
public:
	virtual void CompressL(const CSmsBufferBase& aSource, CBufSeg& aDestination,const TGsmCompressionSettings& aSettings)=0;  // Uses settings in aSettings
	virtual void DecompressL(const CBufSeg& aSource, CSmsBufferBase& aDestination,TGsmCompressionSettings& aSettings)=0;  // Returns settings in a aSettings
	virtual TBool SettingsSupported(const TGsmCompressionSettings& aSettings)=0;  //  returns whether settings are supported
	virtual TBool CharacterSupportedL(TChar aChar, const TGsmCompressionSettings& aSettings)=0;  //  returns whether character is supported
	virtual IMPORT_C void Reserved();	// BC extensions
protected:
	IMPORT_C CGsmCompressionBase(RFs& aFs);
protected:
	RFs& iFs;
private:
	TAny* iReserved;	// BC extensions
	};

#include "gsmucomp.inl"

#endif// !defined __GSMUCOMP_H__