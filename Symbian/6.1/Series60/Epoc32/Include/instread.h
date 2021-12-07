// INSTREAD.H
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//
// Software installation SIS file reader classes
//

#if !defined(__INSTREAD_H__)
#define __INSTREAD_H__

// ===========================================================================
// INCLUDES
// ===========================================================================

#include <e32std.h>
#include <f32file.h>
#include <e32base.h>

#include <insteng.h>

class CSubjectPublicKeyInfo;

// ===========================================================================
// CLASS DEFINITIONS
// ===========================================================================

class CInstallationFile : public CBase
// CInstallationFile - for reading SIS files (real & stub)
	{
	public: // public exported interface
		// construction & initialisation
		IMPORT_C static CInstallationFile* NewL();
		IMPORT_C ~CInstallationFile();
		IMPORT_C void OpenL(RFs& aFs,const TDesC& aName,TFileMode aFileMode);
		IMPORT_C void Close();
		// file related
		IMPORT_C TFileName FileName() const;
		IMPORT_C TBool FileIsCorruptedL() const;
		IMPORT_C TBool IsPartialInstallation() const;
		// SIS file header attributes
		IMPORT_C TSISType Type() const;
		IMPORT_C TInt Uid(TInt aUidNumber) const;
		IMPORT_C TUint16 Crc() const;
		IMPORT_C TUint16 Flags() const;
		IMPORT_C TInt InstallerVersion() const;
		IMPORT_C TInt AppVersionMajor() const;
		IMPORT_C TInt AppVersionMinor() const;
		IMPORT_C TInt AppVersionBuild() const;
		IMPORT_C TInt NumberOfLanguagesSupported() const;
		IMPORT_C TInt NumberOfPkgLines() const;
		IMPORT_C TInt NumberOfPkgLinesDone() const;
		IMPORT_C TInt NumberOfDependencies() const;
		IMPORT_C TInt NumberOfCapabilities() const;
		IMPORT_C TInt MaximumSpaceToInstall() const;
		IMPORT_C void ReadDriveAndLanguageL();
		IMPORT_C void InstallationDrive(TChar& aChar) const;
		IMPORT_C TLanguage LanguageL(TInt aIndex) const;
		IMPORT_C void GetLanguagesL(CArrayFix<TLanguage>& aLanguages) const;
		IMPORT_C void GetCapabilitiesL(CArrayFix<TInstCapability>& aCapabilites) const;
		IMPORT_C TInt SpaceUsed();
		IMPORT_C TInstPackageLineType PkgLineType(TInt aIndex) const;
		// application name & SIS header allocation
		IMPORT_C HBufC* AllocReadForApplicationNameLC() const;
		IMPORT_C HBufC8* AllocReadForFileSisStubLC();
		// to update header attributes during installation
		IMPORT_C void SetDrive(TChar aChar);
		IMPORT_C void SetLanguage(TLanguage aLanguage);
		IMPORT_C void SetSpaceUsedL(TInt aBytes);
		IMPORT_C void SetSystemFileL(RFile& aFile,TBool aIsPartial);
		IMPORT_C void UpdatePkgLinesDoneL(TInt aNumber);
		IMPORT_C TBool IsDigitallySigned() const;
	public: // public interface available within instread.dll only
		HBufC8* AllocReadForLanguageBlockLC() const;
		HBufC8* AllocReadForCapabilitiesBlockLC() const;
		HBufC8* AllocReadForPkgLineBlockLC(TInt aIndex) const;
		HBufC8* AllocReadForDependencyBlockLC(TInt aIndex) const;
		HBufC8* AllocReadForCertificateBlockLC() const;
		HBufC8* AllocReadForSignatureBlockLC() const;
		void ReadL(TInt aFileOffset,TDes8& aDes) const;
		void WriteL(TInt aFileOffset,TDesC8& aData);
		TLanguage LanguageUsed() const;
		TInt LanguageIndexL() const;
		void TruncatePackageFileL(TInt aLength);
		TInt PkgLineOffsetL(TInt aPkgLineIndex) const;
		HBufC8* ComputeSHA1LC() const;
	private:
		enum 
			{
			EUid				=0,
			ECheckSum			=1,
			ENumLanguages		=2,
			ENumPkgLines		=3,
			ENumDependencies	=4,
			ELanguageUsed		=5,
			ENumPkgLinesDone	=6,
			EInstallDrive		=7,
			ENumCapabilities	=8,
			EInstallerVersion	=9,
			EFlags				=10,
			EType				=11,
			EAppVersion			=12,
			ELanguages			=13,
			EPkgLines			=14,
			EDependencies		=15,
			ECertificates		=16,
			EAppNames			=17,
			ESignature			=18,
			ECapabilities		=19,
			ESpaceUsed			=20,
			EMaximumInstall     =21,
			ESpare2				=22
			};
	private:
		CInstallationFile();
		// SIS file header handling
		HBufC8* AllocReadForHeaderLC() const;
		void ReadHeaderL(TDes8& aDes) const;
		TInt HeaderSizeInBytes() const;
		void WorkOutHeaderOffsets();
		// pointers to internal header block
		const TUint8* MovePtr(TInt aIndex) const;
		const TUint8* HeaderStartPtr() const;
		// offsets into SIS file
		TInt ApplicationNamesBlockOffset() const;
		TInt ApplicationNameStringOffsetL() const;
		TInt LanguagesOffset() const;
		TInt DependenciesOffset() const;
		TInt CertificatesOffset() const;
		TInt CapabilitiesOffset() const;
		TInt PkgLinesOffset() const;
		TInt SignatureOffset() const;
		// application name
		void ApplicationNameL(TDes& aName) const;
		TInt ApplicationNameLengthL() const;
		// SIS file language & drive handling
		void ReadLanguageL();
		void ReadDriveLetterL();
		void WriteLanguageL();
		void WriteDriveLetterL();
		// SIS file block reading
		void ReadInLanguageBlockL(TDes8& aDes) const;
		void ReadDependencyBlockL(TDes8& aDes,TInt aIndex) const;
		void ReadCapabilitiesBlockL(TDes8& aDes) const;
		void ReadPkgLineBlockL(TDes8& aDes,TInt aIndex) const;
		//
		TInt SizeOfOneDependency() const;
		TInt SizeOfPkgLineBlockL(TInt aIndex) const;
		void CachePkgLines() const;
		// checksum handling
		TUint16 CheckSumL(TInt aFileSize) const;
		void CalculatePartialCheckSumL(TUint16& aCrc,TDes8& aDes,TInt& aFilePos,TInt aLength) const;
		//
		TBool FileIsInstallationFile() const;
	private:
		RFile iFile;
		RFile iSystemFile; 
		TBool iSystemFileSet;
		CArrayFixFlat<TInstPackageLineType>* iPkgLineTypes;
		CArrayFixFlat<TInt>* iPkgLineBlockLengths;
		TFileName iFileName;
		HBufC8* iHeaderBuffer;
		TInt iHeader[ESpare2+1];
		TLanguage iLanguage;
		TChar iDrive;
	};

class CInstallationFileInfoReader : public CBase
// reads file info block within SIS file
	{
	public: // public exported interface
		IMPORT_C static CInstallationFileInfoReader* NewLC(
			CInstallationFile& aInstallationFile, TInt aIndex);
		IMPORT_C ~CInstallationFileInfoReader();
		IMPORT_C TBool IsLanguageDependent() const;
		IMPORT_C TInstFileType FileType() const;
		IMPORT_C void FileOption(TInstFileOption& aOption) const;
		IMPORT_C HBufC* AllocReadForSourceLC() const;
		IMPORT_C HBufC* AllocReadForDestinationLC() const;
		IMPORT_C HBufC8* AllocReadForMimeTypeLC() const;
		IMPORT_C HBufC8* AllocReadForFileContentsLC() const;
		IMPORT_C TInt FileLength() const;
		IMPORT_C TInt FileLengthInSisFile() const;
		IMPORT_C void DeleteFileContentsFromInstallationFileL();
	public: // public interface available within instread.dll only
		TInt OffsetToFile(TInt aLanguageIndex = -1) const;
		void ReadInSomeFileContentsFromInstallationFileL(TDes8& aDes, TInt offset) const;
		void ExtractToFileL(RFile &aDestinationFile);
		void SetFileNotInstalled();
	private:
		enum
			{
			ELangDependent		=0,
			EFileType			=1,
			EFileOptions		=2,
			ESource				=3,
			EDestination		=4,
			ELengths			=5,
			EOffsets			=6,
			EUncompressedLengths=7,
			EMimeType			=8,
			};
	private:
		void ConstructL(CInstallationFile& aInstallationFile,TInt aIndex);
		void WorkOutOffsets();
		void WorkOutLanguageIndexL();
		const TUint8* StartPtr() const;
		const TUint8* MovePtr(TInt aIndex) const;
		void SourceL(TDes& aString) const;
		void DestinationL(TDes& aString) const;
		void MimeTypeL(TDes8& aString) const;
		TInt SourceStringLength() const;
		TInt DestinationStringLength() const;
		TInt MimeTypeStringLength() const;
		TInt SourceStringFileOffset() const;
		void ReadInFileContentsFromInstallationFileL(TDes8& aDes) const;
		TInt SumOfFileLengthsForAllLanguages() const;
	private:
		CInstallationFile* iInstallationFile;
		TInt iPkgLineOffset;
		HBufC8* iFileBuf;
		TInt iOffset[9];
		TInt iLanguageIndex;
	};

class CResult;

class CInstallationConditionInfoReader : public CBase
// reads condition info block within SIS
	{
	public: // public exported interface
		IMPORT_C static CInstallationConditionInfoReader* NewLC(
			CInstallationFile& aInstallationFile, TInt aIndex,
			MInstallCondVariableSupplier& aVariableSupplier);
		IMPORT_C ~CInstallationConditionInfoReader();
		IMPORT_C TInstPackageLineType Type();
		IMPORT_C TBool Evaluate();
	private:
		void ConstructL(CInstallationFile& aInstallationFile,TInt aIndex,
			MInstallCondVariableSupplier& aVariableSupplier);
		CResult* EvaluateExprLC(TText8*& ptr);
		CResult* EvaluatePrimExprLC(TText8*& ptr);
	private:
		CInstallationFile* iInstallationFile;
		MInstallCondVariableSupplier* iVariableSupplier;
		TInstPackageLineType iType;
		HBufC8* iConditionBuf;
	};

class CInstallationOptionsInfoReader : public CBase
// reads options info block within SIS
	{
	public: // public exported interface
		IMPORT_C static CInstallationOptionsInfoReader* NewLC(
			CInstallationFile& aInstallationFile, TInt aIndex);
		IMPORT_C ~CInstallationOptionsInfoReader();
		IMPORT_C CDesCArray* AllocReadForOptionsNamesLC() const;
		IMPORT_C void SetOption(TInt aOptionIndex, TBool aValue);
		IMPORT_C TBool Option(TInt aOptionIndex) const;
		IMPORT_C TInt NumberOfOptions() const;
	private:
		void ConstructL(CInstallationFile& aInstallationFile,TInt aIndex);
		void ReadInNameL(TInt aOptionIndex, TDes& aDes) const;
	private:
		CInstallationFile* iInstallationFile;
		TInt iPkgLineOffset;
		HBufC8* iOptionsBuf;
	};

class CInstallationDependencyInfoReader : public CBase
// reads dependency info block within SIS
	{
	public: // public exported interface
		IMPORT_C static CInstallationDependencyInfoReader* NewLC(
			CInstallationFile& aInstallationFile, TInt aIndex);
		IMPORT_C ~CInstallationDependencyInfoReader();
		IMPORT_C TInt Uid() const;
		IMPORT_C TInt MajorVersion() const; 
		IMPORT_C TInt MinorVersion() const;
		IMPORT_C TInt BuildVersion() const;
		IMPORT_C HBufC* AllocReadForDependencyNameLC() const;
	private:
		enum
			{
			EUid			=0,
			EVersion		=1,
			ENameLengths	=2,
			ENameStrings	=3,
			};
	private:
		void ConstructL(CInstallationFile& aInstallationFile,TInt aIndex);
		void WorkOutOffsets();
		const TUint8* StartPtr() const;
		const TUint8* MovePtr(TInt aIndex) const;
		void ReadInNameL(TDes& aDes) const;
	private:
		CInstallationFile* iInstallationFile;
		TInt iDependencyIndex;
		HBufC8* iDependencyBuf;
		TInt iOffset[4];
	};


class CInstallationSignatureInfoReader : public CBase
	{
	public: 
		IMPORT_C static CInstallationSignatureInfoReader* NewLC(
			CInstallationFile& aInstallationFile);
		IMPORT_C static CInstallationSignatureInfoReader* NewL(
			CInstallationFile& aInstallationFile);
		IMPORT_C ~CInstallationSignatureInfoReader();
		IMPORT_C TSignatureValidationResult SignatureIsValidL() const;
		IMPORT_C TDateTime SignatureDate() const;
		IMPORT_C CPKIXCertChain* CertChain() const;
		IMPORT_C CPKIXValidationResult* CertValidationL() const;

	private:
		CInstallationSignatureInfoReader(CInstallationFile& aInstallationFile);
		void ConstructL();
		TSignatureValidationResult ValidateRSASignatureL(const TDesC8 &aSignature,
			const CSubjectPublicKeyInfo& aPki) const;
		TSignatureValidationResult ValidateDSASignatureL(const TDesC8 &aSignature,
			const CSubjectPublicKeyInfo& aPki) const;
	private:
		CInstallationFile* iInstallationFile;
		CPKIXCertChain* iCertificate;
		HBufC8* iCertificateBuf;
		TDateTime iSignatureDate;
		TInt iNumCerts;
	};

#endif
