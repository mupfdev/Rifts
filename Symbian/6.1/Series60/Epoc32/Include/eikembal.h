// EIKEMBAL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKEMBAL_H__)
#define __EIKEMBAL_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__BAMDESCA_H__)
#include <bamdesca.h>
#endif

#if !defined(__APADEF_H__)
#include <apadef.h>
#endif

#if !defined(__APAID_H__)
#include <apaid.h>
#endif

class CEikDocument;
class CApaProcess;
class RApaLsSession;

class CEikEmbeddableAppList : public CArrayFixFlat<TApaAppInfo>, public MDesCArray
	{
public:
	IMPORT_C CEikEmbeddableAppList();
	IMPORT_C ~CEikEmbeddableAppList();
	IMPORT_C void ConstructL();
	IMPORT_C CEikDocument* CreateEmbeddedDocumentL(TInt aIndex,CApaProcess* aProcess);
private: // from MDesCArray
	IMPORT_C TInt MdcaCount() const;
	IMPORT_C TPtrC MdcaPoint(TInt aIndex) const;
private: // utility methods
	TInt GetAppListL();
	TInt DoGetAppListL(RApaLsSession& aLs);
	void SortAppListL();
	};

#endif
