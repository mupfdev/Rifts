// FAXSET.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/********************************************************************/

// Contents : for saving/restoring persistent fax settings

/********************************************************************/

#ifndef __FAXSET_H
#define __FAXSET_H

#include <commdb.h>
#include <cdblen.h> 
#include <cdbcols.h>

/********************************************************************/

class TFaxSettings
   {
 public:
   IMPORT_C void ExternalizeL (RWriteStream &) const;
   IMPORT_C void InternalizeL (RReadStream &);
   IMPORT_C TFaxSettings& operator=(const TFaxSettings& aFaxSettings);
   TBuf8 < 20 > iFaxId ;
   TInt iMaxSpeed;
   TInt iMinSpeed;
   TFaxResolution iPreferredResolution;
   TFaxCompression iPreferredCompression;
   TInt iPreferredECM;
   TInt iVerbose;
   TInt iFaxOnDemandDelay ;
   TFaxClass iFaxClass;
   };

/********************************************************************/

// now the CFaxSettings class

class CFaxSettings : public CBase
   {
public:
   static CFaxSettings * NewL ();
   static CFaxSettings * NewLC ();
   ~CFaxSettings ();
   void ValidateAndSetClassL (TFaxSettings *);

protected:
   void ConstructL ();
 protected:
   RFs iFileSession;
   CCommsDatabase* iDatabase;
   };

/********************************************************************/

#endif

