// APMREC.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline TInt CApaDataRecognizerType::MimeTypesCount() const
	{
	return iCountDataTypes;
	}

inline TUid CApaDataRecognizerType::TypeUid() const
	{
	return iTypeUid;
	}

inline TInt CApaDataRecognizerType::Priority() const
	{
	return iPriority;
	}

inline TInt CApaDataRecognizerType::Confidence() const
	{
	return iConfidence;
	}

inline TInt CApaDataRecognizerType::Locked() const
	{
	return iLock;
	}


	
