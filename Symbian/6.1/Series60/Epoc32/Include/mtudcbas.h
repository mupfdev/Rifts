// MTUDCBAS.H
//
// Copyright (C) Symbian Ltd 1998
//

#if !defined(__MTUDBAS_H__)
#define __MTUDBAS_H__

#if !defined(__MSVSTD_H__)
#include <MSVSTD.H>
#endif

#if !defined(__MSVREG_H__)
#include <MSVreg.H>
#endif

#if !defined(__MTCLREG_H__)
#include <mtclreg.H>
#endif

#if !defined(__BARSREAD_H__)
#include <BARSREAD.H>
#endif

// Forward references
class CFbsBitmap;
class CCoeEnv;

///////////////////////////////////////////////////
// CBaseMtmUiData - MTM Ui data layer base API   //
///////////////////////////////////////////////////
class CBaseMtmUiData : public CBase
	{
public:
	// --- Types ---
	typedef CArrayPtr<CFbsBitmap> CBitmapArray;
	//
	// --- Inline class ---
	class TMtmUiFunction
	///////////////////////////////////
	// In-line class TMtmUiFunction  //
	///////////////////////////////////
	// Provides the interface for    //
	// clients to access MTM-specific//
	// functions, and present these  //
	// functions to the user.	     //
	///////////////////////////////////
		{
		friend class CBaseMtmUiData;// For access to constructor
	public:
		// --- Constants ---
		enum {ECaptionMaxLen=40};

	public:
		// --- Construction ---
		IMPORT_C TMtmUiFunction(TResourceReader& aResourceReader);		
		IMPORT_C TMtmUiFunction(const TMtmUiFunction& aFunc);		

	private:
		// --- Private functions ---
		void SetModifiersFromResourceDefinition(TInt aResourceFileModifiers);		

	public:
		// --- Data ---
		TBuf<ECaptionMaxLen>		iCaption;
		TInt						iPreferredHotKeyKeyCode;
		TInt						iPreferredHotKeyModifiers;
		TInt						iFunctionId;
		TUint8						iFunctionType;	// see MTUD.HRH
		TInt						iFlags;			// see MTUD.HRH
		};
	//
	// --- Destruction ---
	IMPORT_C virtual ~CBaseMtmUiData();
	//
	// --- Accessor functions ---
	inline TUid Type() const;
	//
	// --- Context icons ---
	virtual const CBitmapArray& ContextIcon(const TMsvEntry& aContext, TInt aStateFlags) const = 0;
	//
	// --- MTM-Specific function information (e.g. for dynamically-added menu items) ---
	inline const CArrayFix<TMtmUiFunction>& MtmSpecificFunctions() const;
	IMPORT_C TBool FunctionRecognised(TInt aFunctionId) const;
	//
	// --- Provide context-specific function information ---
	virtual TBool CanCreateEntryL(const TMsvEntry& aParent, TMsvEntry& aNewEntry, TInt& aReasonResourceId) const = 0;
	virtual TBool CanDeleteFromEntryL(const TMsvEntry& aContext, TInt& aReasonResourceId) const = 0;
	IMPORT_C virtual TBool CanUnDeleteFromEntryL(const TMsvEntry& aContext, TInt& aReasonResourceId) const;
	virtual TBool CanDeleteServiceL(const TMsvEntry& aService, TInt& aReasonResourceId) const = 0;
	virtual TBool CanReplyToEntryL(const TMsvEntry& aContext, TInt& aReasonResourceId) const = 0;
	virtual TBool CanForwardEntryL(const TMsvEntry& aContext, TInt& aReasonResourceId) const = 0;
	virtual TBool CanEditEntryL(const TMsvEntry& aContext, TInt& aReasonResourceId) const = 0;
	virtual TBool CanViewEntryL(const TMsvEntry& aContext, TInt& aReasonResourceId) const = 0;
	virtual TBool CanOpenEntryL(const TMsvEntry& aContext, TInt& aReasonResourceId) const = 0;
	virtual TBool CanCloseEntryL(const TMsvEntry& aContext, TInt& aReasonResourceId) const = 0;
	virtual TBool CanCopyMoveToEntryL(const TMsvEntry& aContext, TInt& aReasonResourceId) const = 0;
	virtual TBool CanCopyMoveFromEntryL(const TMsvEntry& aContext, TInt& aReasonResourceId) const = 0;
	virtual TBool CanCancelL(const TMsvEntry& aContext, TInt& aReasonResourceId) const = 0;
	//
	// --- RTTI ---
	virtual TInt OperationSupportedL(TInt aOperationId, const TMsvEntry& aContext) const = 0; // returns 0 if operation *IS* supported, otherwise a resource ID for the reason text
	virtual TInt QueryCapability(TUid aFunctionId, TInt& aResponse) const = 0;
	virtual HBufC* StatusTextL(const TMsvEntry& aContext) const = 0;

protected:
	// --- Construction ---
	IMPORT_C CBaseMtmUiData(CRegisteredMtmDll& aRegisteredMtmDll);
	IMPORT_C void ConstructL();
	virtual void PopulateArraysL() = 0; // Should populate iCapabilities, iMtmSpecificFunctions and iIconArrays
	virtual void GetResourceFileName(TFileName& aFileName) const = 0;
	//
	// --- Utility ---
	IMPORT_C void ReadFunctionsFromResourceFileL(TInt aResourceId);// Up to clients to call this if necessary
	IMPORT_C void CreateBitmapsL(TInt aNumZoomStates, const TDesC& aBitmapFile, TInt aStartBitmap, TInt aEndBitmap);
	CFbsBitmap* CreateBitmapL(const TDesC& aFileName, TInt aId) const;

protected:
	// --- Data ---
	CCoeEnv*									iCoeEnv;
	CArrayPtr<CBitmapArray>*					iIconArrays;
	CArrayFix<TMtmUiFunction>*					iMtmSpecificFunctions;

private:
	// --- Data ---
	TInt										iResourceFileOffset;
	CRegisteredMtmDll&							iRegisteredMtmDll;  // Required in order to call ReleaseLibrary()
	};

#include "Mtudcbas.inl"

#endif // __MTUDBAS_H__
