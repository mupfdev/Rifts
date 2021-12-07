/*
* ============================================================================
*  Name     : Intconninit.h
*  Part of  : Intconninit
*
*  Description:
*     Declaration of the CIntConnectionInitiator class
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __INTCONNINIT_H
#define __INTCONNINIT_H

//  INCLUDES
#include <e32base.h>        //CActive
#include <cdbpreftable.h>   //CCommsDbConnectionPrefTableView
#include <agentclient.h>    //RGenericAgent

// CONSTANTS

// Statuses for ConnectL functions
/**
* Connection exists and matches to aPref1 then status is 
* KConnectionPref1Exists.
*/
const TInt KConnectionPref1Exists = 0x0001; 

/**
* Connection exists and matches to aPref2 then status is 
* KConnectionPref2Exists
*/
const TInt KConnectionPref2Exists = 0x0002;

/**
* Connection exists but it is neither of preferences then status is 
* KConnectionExists.
*/
const TInt KConnectionExists      = 0x0003;

/**
* Connection created with aPref1 then status is KConnectionPref1Created
*/  
const TInt KConnectionPref1Created = 0x0004; 

/**
* Connection created with aPref2 then status is KConnectionPref2Created
*/
const TInt KConnectionPref2Created = 0x0005; 

/**
* Connection created but it is neither of preferences then status is 
* KConnectionCreated.
*/
const TInt KConnectionCreated = 0x0006; 

/**
* Something wrong in preference(s) specified by the user. 
*/ 
const TInt KErrWrongValueInPrefs = 0x0007;

/**
* Connection has been successfully terminated
*/ 
const TInt KConnectionTerminated = 0x0008;

/**
* There is an outstanding request
*/ 
const TInt KErrOutstandingRequest = 0x0009;


// MACROS
// DATA TYPES
// FUNCTION PROTOTYPES
// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
*   This class provides an interface for clients wishing to initiate an 
* Internet connection over CSD and GPRS data bearers.
* It gives a possibility to check if there is an active connection and returns
* the value of IAP ID if one is existing. 
* User can also terminate an active connection.
*
*   User must carefully fill in the preference(s) fields: rank, direction,
* bearer set, dialog and IAPid. If the fields of rank, direction, bearer set
* and dialog are different from the following:
*   - in case of one preference the rank must be 1,
*   - in case of two preferences first rank is 1 and second is 2.
*   - direction must be ECommDbConnectionDirectionOutgoing or
*     ECommDbConnectionDirectionIncoming or ECommDbConnectionDirectionUnknown.
*   - bearer set must be one from the following: ECommDbBearerCSD, 
*     ECommDbBearerGPRS, ECommDbBearerUnknown,  ECommDbBearerCSD | 
*     ECommDbBearerGPRS or KMaxTUint32 (special case).
*   - dialog must be one from the following: ECommDbDialogPrefDoNotPrompt,
*     ECommDbDialogPrefPrompt, ECommDbDialogPrefWarn or 
*     ECommDbDialogPrefUnknown.
* then we will complete the user status with KErrWrongValueInPrefs.
*
*   If ConnectL( TRequestStatus& aStatus ) is used then user does not wish 
* to override anything. Connection attempts will be initiated using preferences
* from CommDb.
*
*   If ConnectL(
*           const CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref& 
*           aPref1, TRequestStatus& aStatus ) is used then only one connection
* attempt will be made and preference with rank=1 will be overridden.
* Note: the rank value in aPref1 must be = 1, otherwise an error 
* KErrWrongValueInPrefs will be returned.
*
*   If ConnectL(
*           const CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref& 
*           aPref1,
*           const CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref& 
*           aPref2,
*           TRequestStatus& aStatus ) is used then two connection attempts will
* be made: first with rank=1 second with rank=2. Both connection preferences
* will be overridden.
* Note: the rank value in aPref1 must be = 1 and in aPref2 must be = 2, 
* otherwise an error KErrWrongValueInPrefs will be returned.
*
*   If bearer set field has value 1000 in user preference(s) (this is a special
* case when user knows IAP ID but does not know the bearer set associated with
* this IAP ID) then our module will try to find out the corresponding bearer 
* and fill in the field before it starts overriding. In case of failure it 
* reports the KErrWrongValueInPrefs to client.
*
*   It is recommended to fill in the fields carefully in order to avoid errors
* and failure of connection trial.
*
*   Note: a preference with ranking 1 is always attempted first by 
* GenConn Agent.
*   
*   Note: the ranking information essentially determines the behaviour of
* our module.
*
*   Note: if connection/termination attempt is started while there is an
* outstanding request then KErrOutstandingRequest error is returned.
*   
*   The following code fragment is an easy example of how to start with 
* ConnectL:
*
*******************************************************************
*   CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref pref;
*   CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref pref2;
*
*   --- First preference ----
*   pref.iRanking = 1;
*   pref.iDirection = ECommDbConnectionDirectionOutgoing;
*   pref.iDialogPref = ECommDbDialogPrefDoNotPrompt;    
*   CCommsDbConnectionPrefTableView::TCommDbIapBearer bearer;
*       bearer.iBearerSet = ECommDbBearerGPRS;              
*       bearer.iIapId = 0x01;               
*   pref.iBearer = bearer;
*
*   ---Second preference ---
*   pref2.iRanking = 2;
*   pref2.iDirection = ECommDbConnectionDirectionOutgoing;
*   pref2.iDialogPref = ECommDbDialogPrefDoNotPrompt; 
*   CCommsDbConnectionPrefTableView::TCommDbIapBearer bearer2;
*       bearer2.iBearerSet = ECommDbBearerCSD; 
*       bearer2.iIapId = 0x04;              
*   pref2.iBearer = bearer2;
*
*   ---call Iniatator---
*   TRequestStatus stat(KRequestPending);
*
*   CIntConnectionInitiator* initConn = CIntConnectionInitiator::NewL();
*   CleanupStack::PushL( initConn );
*
*   initConn->ConnectL(pref, pref2, stat);
*
*******************************************************************
*
*   Status of the operation received by client shows a result of the
* connection/termination trial with corresponding error code or status.
*
*   In case of success the statuses are present above (see CONSTANTS):
* If a connection exists and matches to aPref1 then status is 
* KConnectionPref1Exists.
* If a connection exists and matches to aPref2 then status is 
* KConnectionPref2Exists.
* If a connection exists but it is neither of preferences then status is 
* KConnectionExists.
*
* If a connection created with aPref1 then status is KConnectionPref1Created.
* If a connection created with aPref2 then status is KConnectionPref2Created.
* If a connection created but it is neither of preferences then status is 
* KConnectionCreated.
*
* If a connection terminated successfully then status is KConnectionTerminated.
*
*   In case of failure corresponding error code passed from GenConn Agent
* to client. Exceptions are KErrWrongValueInPrefs and KErrOutstandingRequest.
*/

class CIntConnectionInitiator : public CActive
    {
    public:  // Constructors and destructor
        
        /**
        * C++ default constructor.
        */
        CIntConnectionInitiator();

        /**
        * Two-phased constructor.
        */
        IMPORT_C static CIntConnectionInitiator* NewL();
        
        /**
        * Destructor.
        */
        virtual ~CIntConnectionInitiator();

    public: // New functions

        /**
        * Starts the connection procedure. Two connection preferences have to
        * be specified.
        * @param aPref1 the first preference.
        * @param aPref2 the second preference.
        * @param aStatus Status of the operation.
        * @return void
        */
        IMPORT_C void ConnectL(
            const CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref& 
            aPref1,
            const CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref&
            aPref2,
            TRequestStatus& aStatus );
        
        /**
        * Starts the connection procedure. One connection preference has to be
        * specified.
        * @param aPref1 the preference.
        * @param aStatus Status of the operation.
        * @return void
        */
        IMPORT_C void ConnectL(
            const CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref& 
            aPref1,
            TRequestStatus& aStatus );
        
        /**
        * Starts the connection procedure without any connection preferences
        * specified by the user.
        * @param aStatus Status of the operation.
        * @return void
        */
        IMPORT_C void ConnectL( TRequestStatus& aStatus );

        /**
        * Checks if there is an active connection and returns the value
        * of IAP ID if one is existing. Othervise it returns an 
        * error.
        * @param aIAPId value of IAP ID if connection is existing.
        * @return TInt error value.
        */
        IMPORT_C TInt GetActiveIap( TUint32& aIAPId );

        /**
        * Starts terminating an active connection
        * @return TInt value, which is KErrNone if operation is started 
        * successfully or an error value if one occurs.
        */
        IMPORT_C TInt TerminateActiveConnection();

        /**
        * Terminates an active connection
        * @param aStatus Status of the operation. In case of success the 
        * status is KConnectionTerminated.
        * @return TInt value, which is KErrNone if operation is started
        * successfully or an error value if one occurs.
        */
        IMPORT_C TInt TerminateActiveConnection( TRequestStatus& aStatus );

    public: // Functions from base classes        
        
    protected:  // New functions

    protected:  // Functions from base classes
        
        /**
        * From CActive class 
        * Handles the event generated when the request completes
        * @return void
        */
        void RunL();

        /**
        * From From CActive class 
        * Cancels any outstanding request
        * @return void
        */
        void DoCancel();

    private:

        /**
        * By default Symbian OS constructor is private.
        * @return void
        */
        void ConstructL();

        /**
        * Checks the values of: rank, direction, bearer set and dialog
        * in preference(s). If they are different from the following:
        *   - in case of one preference the rank must be 1,
        *   - in case of two preferences first rank is 1 and second is 2.
        *   - direction must be ECommDbConnectionDirectionOutgoing or
        *     ECommDbConnectionDirectionIncoming or 
        *     ECommDbConnectionDirectionUnknown.
        *   - bearer set must be one from the following: ECommDbBearerCSD,
        *     ECommDbBearerGPRS, ECommDbBearerUnknown, ECommDbBearerCSD |
        *     ECommDbBearerGPRS or KMaxTUint32 (special case).
        *   - dialog must be one from the following:
        *     ECommDbDialogPrefDoNotPrompt, ECommDbDialogPrefPrompt,
        *     ECommDbDialogPrefWarn or ECommDbDialogPrefUnknown.
        * then returns with KErrWrongValueInPrefs.
        * Otherwise returns with KErrNone.
        * @return TInt
        */      
        TInt CheckFieldsInPrefs();

        /**
        * Starts with checking of a connection. If one exists then returns a 
        * corresponding status. 
        * If there is no existing connection then it checks if the connection
        * has to be made either with or without overrides and starts outgoing.
        * If there is an error occured it returns that error.
        * @return TInt
        */      
        TInt StartConnectL();

        /**
        * Resets iPrefers and completes the client status with corresponding 
        * error.
        * @param aError: error code to be completed with.
        * @return void
        */
        void ResetPrefsAndCompleteWithError( TInt aError );

        /**
        * Checks if existing/created connection matches to aPref1 or aPref2 
        * (see ConnectL), or different.
        * @param aIAPId: IAP ID
        * @param aArg1 first argument
        * @param aArg2 second argument
        * @param aArg3 third argument
        * @return TInt
        */
        TInt CheckConnection(
             TUint32 aIAPId,
             const TInt aArg1, 
             const TInt aArg2,
             const TInt aArg3 );
        
        /**
        * Matches access point details from database 
        * @param aIAPId: IAP ID
        * @param aCount number of access points to match ( 1 or 2 )
        * @param aAp1 first access point
        * @param aAp2 second access point
        * @param aArg1 first argument
        * @param aArg2 second argument
        * @param aArg3 third argument
        * @return TInt
        */
        TInt MatchAccessPoints(
             TUint32 aIAPId,
             const TInt aCount,
             const TInt aAp1,
             const TInt aAp2,
             const TInt aArg1, 
             const TInt aArg2,
             const TInt aArg3 );
        
        /**
        * It checks if bearer set field in aPref1/aPref2 set to KMaxTUint32
        * then it tries to find out corresponding bearer and fill in the field.
        * In case of failure returns KErrWrongValueInPrefs otherwise KErrNone.
        * @return TInt
        */
        TInt CheckConnectPrefBearerSetL();
        
        /**
        * Checks if needed to override connection preferences and
        * starts initiating a connection with overrides.
        * @return TInt
        */
        TInt StartOutgoingWithOverridesL();
        
        /**
        * Delets override pointer and puts it to zero
        * @return void
        */
        void DeleteOverrides();

        /**
        * Starts requesting agent's (GenConn) progress notification.
        * @return void
        */
        void StartProgrNotif();     

        /**
        * Checks if network is available.
        * @return TRUE, if network available, FALSE, if no network
        */
        TBool CheckNetworkL();


#ifdef _INTCONNINIT_LOGGING_
        /**
        * logging
        */
        static void Log(TRefByValue<const TDesC> aFmt,...);
#endif

        /**
        * By default, prohibit copy constructor
        */       
        CIntConnectionInitiator( const CIntConnectionInitiator& );

        /**
        * Prohibit assignment operator
        */        
        CIntConnectionInitiator& operator= ( const CIntConnectionInitiator& );

    public:     // Data
    protected:  // Data

    private:    // Data
        RGenericAgent    iGenericAgent;     // instance of RGenericAgent class
        TRequestStatus*  iClientStatus;     // status of the client
        TRequestStatus*  iCallerStatus;     // status of the client when looping
                                            // through access points individually
        // a pointer of type CStoreableOverrideSettings
        CStoreableOverrideSettings* iOverrides;
        // an array of two pointers of type 
        // CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref
        CArrayFixFlat<CCommsDbConnectionPrefTableView::
            TCommDbIapConnectionPref>* iPrefers;
        CArrayFixFlat<CCommsDbConnectionPrefTableView::
            TCommDbIapConnectionPref>* iUserPreferences;
        // this flag is used to switch between connect and terminate functions
        TBool   iTerminationFlag;
        TNifProgressBuf iProgress;  // instance of TNifProgressBuf
        TInt    iNumberOfPreferences; // number of access points
        TInt    iCurrentAccessPoint; // index of current access point
        CCommsDatabase* iDatabase;   // comms database
    };

#endif      // __INTCONNINIT_H   
            
// End of File
