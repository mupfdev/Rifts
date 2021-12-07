// EIKDEBUG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDEBUG_H__)
#define __EIKDEBUG_H__

//
//	class CEikDebugPreferences
//

/**
 * @internal
 */
class CEikDebugPreferences : public CBase
	{
private:
	IMPORT_C static CEikDebugPreferences* NewLC();
	IMPORT_C ~CEikDebugPreferences();
	IMPORT_C void StoreL();
	IMPORT_C void RestoreL();
	inline void SetKeysOn(const TBool& aDebugKeysOn);
	inline TBool KeysOn() const;
	void ConstructL();
private:
	CEikDebugPreferences();
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
private:
	friend class CEikonEnv;
	friend class CDebugKeysDlg;
	friend class CDebugKeysAppUi;
	TBool iDebugKeysOn;
	TInt iVersion;
	};



inline void CEikDebugPreferences::SetKeysOn(const TBool& aDebugKeysOn)
	{
	iDebugKeysOn=aDebugKeysOn;
	}

inline TBool CEikDebugPreferences::KeysOn() const
	{
	return iDebugKeysOn;
	}

#endif
