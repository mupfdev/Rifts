// CFAX32.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/********************************************************************/

// Contents :  fax s/r header file

/********************************************************************/

#ifndef __cfax32_h
#define __cfax32_h

/********************************************************************/

/********************************************************************/

// These are the other include files used when sending and receiving
// faxes.  The order of inclusion should not be changed.  Unfortunately,
// the design of the engine means that there's a very close coupling
// between the various classes involved, and while each class doesn't
// need to know how the other work, they all need to know what the others
// have to offer.  The fax settings need to be accessible from modem for
// autodetection to work, and since the modem handles the session log
// and progress reporting, the the cfaxtransfersource and
// cfaxmodemdriver classes need to be able know about that.  The inline
// functions at the end of this faxtrans.h file clearly won't compile if
// they don't know about cfaxtransfersource either. Ah well. So much for
// neat modular encapsulation.


#include <f32file.h>

#include <c32comm.h>
#include <s32file.h>
#include <s32mem.h>

#include <commdb.h>
#include <cdblen.h> 
#include <faxstore.h>
#include <faxdefn.h>

#include "etel.h"
#include "faxtsrc.h"
#include "faxset.h"
#include "FaxStd.h"

/********************************************************************/

// now the CFaxTransfer class


//***************************** comment for 2D faxing****************************
// The TFaxCompression parameter required by the AddSourceL() function is an enum type defined as 
// enum TFaxCompression
//		{
//			Prefer1D,Prefer2D
//		}
// this enum is defined in faxtsrc.h

enum TFaxClientProgress
	{
	EProgressConverting,	// Fax Progress Information not yet available
	EProgressRxTx			// Refer to Fax Progress Chunck for more detailed information
	};

class CFaxTransfer : public CBase
   {
	public:
		IMPORT_C static CFaxTransfer * NewL (const TFaxSettings &);
		IMPORT_C static CFaxTransfer * NewLC (const TFaxSettings &);

		IMPORT_C TInt Start (TRequestStatus &);		// starts the Fax Client thread		
		IMPORT_C TInt Progress ();					// Gets the progress of the fax session (updates the global progress chunk
		IMPORT_C void SetPhoneNumberL (TDesC8 &);	// sets the phone number to dial to
		IMPORT_C void Cancel ();					// cancels the fax session
		IMPORT_C void Stop ();						// calls Close() to the thread handle
		~CFaxTransfer ();							// destructor

		IMPORT_C void AddSourceL (const TFileName &,TFaxPreferredCompression=Prefer1D);			// TFaxPreferredCompression can be 
		IMPORT_C void AddSourceL (const TFileName &, TInt, TFaxPreferredCompression=Prefer1D);   // one of Prefer1D or Prefer2D
		IMPORT_C void AddSourceL (const TFileName &, TInt, TInt, TFaxPreferredCompression=Prefer1D);	// use this function to 
																				// indicate the fax document for sending
		IMPORT_C void RemoveAllSources ();						// Remove all fax pages from the sent list
		inline void SetReceiveFileName (const TFileName &);		// Set the name of the filename for fax reception
		inline void SetMode (TFaxMode);
		inline void SetPhoneNumber (TDesC8 &);
		TInt GetPhoneInfoForTsy(const TDes& aTsyName, RTelServer::TPhoneInfo& aPhoneInfo) const;
		void GetPhoneModuleNameL(TDes& aModuleName) const;
		void FaxReceiveL ();		
		void FaxTransmitL ();
		

				
		TFaxClientProgress iFaxClientProgress;
		RTelServer iTelServer;
		RLine iLine ;
		RCall iCall ;
		RPhone iPhone ;
		RFax iFax ;
		TBool iFaxStarted;
		CFaxTransferSource * iSource;
		TFaxMode iMode;
		RFax::TProgress iProgress ;
		RCall::TFaxSessionSettings iFaxSessionSettings;
		
		
	protected:
		RThread iDriverThread;						// fax client thread handle
//		RThread iConverterThread;
		CFaxTransfer();								// CFaxTransfer Constructor
		TBool iConverting;							// flag used when preparing the 2D version of the fax document
		TRequestStatus iTransferStatus ;			// status of the fax data transfer
		TRequestStatus iClientCancel;				// status of the cancel request
		TBuf8 < KMaxFaxBuf > iDataBuf;				// buffer to store 
		TFaxSettings iFaxSettings;
		TFileName iReceiveFileName ;				// only used when receiving
		TBuf<KMaxDialString> iPhoneNumber ; 		// only used when dialling
		void Convert2dL ();		// convert from 1D to 2D
		void Convert1dL ();		// convert from 2D to 1D

		
		TInt StartThread();
		void ConstructL (const TFaxSettings &);
		void CancelFaxServerSession ();
		void SetFaxSettingsL();
	
     
   };

/********************************************************************/

#include "cfax32.inl"

#endif
