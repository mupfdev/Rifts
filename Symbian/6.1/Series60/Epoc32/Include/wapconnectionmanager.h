/*
* ============================================================================
*  Name     : CConnectionManager
*  Part of  : Connection Manager
*
*  Description:
*     This class provides connection/session related information.
*	  Both the requested and the stored AP's are here.
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/
#ifndef Wap_Connection_Manager_H
#define Wap_Connection_Manager_H

//FORWARD DECLARATION
class CApUtils;
class CApDataHandler;
class CCommsDatabase;
class CApAccessPointItem;

//INCLUDES
	//System Include
#include <E32Base.h>
#include <agentclient.h>
#include <InternetConnectionManager.h>
#include <apengineconsts.h>
#include <MConnection.h>
#include <IdPair.h>

_LIT( KNullIpAddr, "0.0.0.0" );




//CLASS DECLARATION




// CLASS DECLARATION

//This class handles all higher level connection activity for 
//the wap browser, push
//The following notation is used when talking about access points
//ACTIVE is the one that is present at the time of the inquiry. It may not be
//opened by the browser at all (hopefully it is mostly the same as the current one.
//CURRENT is the one that the browser wants to use and created a connection upon.
//But it is not neccessarily the active one as it is possible that some other app 
//changed the connection
//REQUESTED is the one that was requested by the user/bookmark/other app

class CWapConnectionManager: public CBase, public MConnection
	{

private:
	enum TConnManMatchType { ENoMatch, EWapApIdMatch, EIapMatch };
public:
	
	/**
	*Symbian OS constructor
	*return an initialised instance of the connection manager
	*/
	IMPORT_C static CWapConnectionManager* NewL( TBool aSilentMode = EFalse, TBool aUsedByBrowser = EFalse );

	
	/**
	*Symbian OS constructor
	*return an initialised instance of the connection manager
	*/
	IMPORT_C static CWapConnectionManager* NewL( CCommsDatabase* aCommsDb, TBool aSilentMode = EFalse, TBool aUsedByBrowser = EFalse );

	
	/**
	*Call this for obtaining the AP for the current connection
	*@return the AP for the latest connection
	* NULL if there isn't any
	*/
	IMPORT_C const CApAccessPointItem* AccessPoint() const;

	/**
    * Same as AccessPoint(); it was introduced for technical reasons
    * (Access to this is needed through MConnection; but cannot add
    * to MConnection without breaking the API).
	*Call this for obtaining the AP for the current connection
	*@return the AP for the latest connection
	* NULL if there isn't any
	*/
	IMPORT_C const CApAccessPointItem* CurrentAccessPoint() const;

	
	/**
	*Sets the requested AP later it may not be the one to be used
	*@param aRequestedAPs the requested AP idpair 
	*/
	IMPORT_C void SetRequestedAPs( TIdPair aRequestedAPIds );
	
	
	/**
	*Sets RequestedAP
	*@param aRequestedAP the requested AP id
	*@param aDefault indicates whether the AP set is the default or not
	*/
	IMPORT_C void SetRequestedAP( TUint32 aRequestedAPId, TBool aDefault = EFalse );
	
	
	/**
	*Checks the validity of the requested APs
	*@return an enum value indicating û of the requested aps are available
	*/
	IMPORT_C  TAPValidity RequestedAPValidityL();
	
	
	/**
	*Returns the currently (or the last used) AP id
	*@return the currently (or the last used) AP id
	*/
	IMPORT_C TUint32 CurrentAPId() const;

	
	/**
	*@return ETrue if there is a valid accesspoint stored as the current AP (or last used one)
	*/
	IMPORT_C TBool CurrentApExists() const;

	
	/**
	*It closes the connection and sets the manager to offline mode
	*/
	IMPORT_C void GoOffLine();
	
	/**
    * Same as GoOffLine(); it was introduced for technical reasons
    * (Access to this is needed through MConnection; but cannot add
    * to MConnection without breaking the API).
	*It closes the connection and sets the manager to offline mode
	*/
	IMPORT_C void Disconnect();
	
	/**
	*Call this the get the gateway address to be used
	*@retun the address of the gateway associated with the current AP, space for zero terminator is also allocated
	*/
	IMPORT_C HBufC* CurrentGatewayLC() const;
	
	/**
	*Call this the get the start page to be used
	*@return the address of the start page associated with the current AP, space for zero terminator is also allocated
	*/
	IMPORT_C HBufC* CurrentStartPageLC() const;

	/**
	*Call this function to get the name of the current Wap AP, space for zero terminator is also allocated
	*return 
	**/
	IMPORT_C HBufC* CurrentApNameLC() const;
	
	/**
	*Call this the get the current bearer to be used
	*@return the bearer type associated with the current AP
	*/
	IMPORT_C TApBearerType CurrentBearerTypeL() const;

	/**
	*Call this the find out the session security mode for the current AP
	*@retun the security mode for the current AP
	*/
	IMPORT_C TBool CurrentSessionSecure() const;

	/**
	*Call this the find out the connection type for the current AP
	*@retun the conection type for the current AP
	*/
	IMPORT_C TBool CurrentSessionConnectionOriented() const;

	/**
	*Sets an observer on the AP changes
	*@param aObserver reference to the the AP change observer 
	*/
	IMPORT_C void SetApChangeObserver( MApChangeObserver& aObserver );

	
	/**
	*Removes the AP change observer
	*/
	IMPORT_C void UnsetApChangeObserver();
	/**
	*call this to find out the current connection speed
	*@return a TApCallSpeed value
	*/
	IMPORT_C TApCallSpeed CurrentConnectionSpeed() const;
	
	/**
	*Starts connection
	*Finds out the AP to use and creates a connection with that
	*Pops up error notes as specified
	*Wait note is popped up
	*/
	TInt ConnectL( );


	
	/**
	*Starts connection
	*Finds out the AP to use and creates a connection with that
	*It does not block the active scheduler of the current thread!
	*Pops up error notes as specified
	*Commands are absorbed to prevent misrouted commands since the 
	*top control could get the commands otherwise (because it is a non blocking func.)
	*if destructor is called while in this function the connection creation process is Cancelled
	*Wait note is popped up at some point if needed
	*aParam aDisableConnNeeded		disables the query that is popped up 
	*								when there is no connecction
	*								already
	*/
	IMPORT_C TInt StartConnectionL( TBool aDisableConnNeeded = EFalse, TBool aIgnoreSecureAttribute = EFalse );
	
	
	
	/**
	*A query function to find out whether there is a connection which
	*was matches with the "current" connection parameters
	*@return ETrue if the condition above is satisfied EFalse otherwise.
	*/
	IMPORT_C TBool Connected();


	/**
	*Use this function to find out if the old already existing connection is used
	*or a new connection is established
	*/
	IMPORT_C TBool NewConnectionEstablished(  ) const;

public:
	/**
	*Destructor
	*/
	IMPORT_C virtual ~CWapConnectionManager();
	

protected:
	/**
    * Constructor.
    */
	CWapConnectionManager( TBool aSilentMode, TBool aUsedByBrowser );
	
	/**
    * Constructor.
    */
	CWapConnectionManager( CCommsDatabase* aCommsDb, TBool aSilentMode, TBool aUsedByBrowser );	

private:
	/**
	*This will close the genconn agent if a leave happens after opening it.
	*The function pointer is pushed to the cleanup stack wihting a TCleanupItem
	*@param aThis the pointer to the object in which the leave happens
	*/
	static void CloseOnLeave( TAny* aThis );
	
private:	
	/**
    * Second phase constructor. Leaves on failure.
    */
	void ConstructL();
		
	
	/**
	*Starts connection
	*Finds out the AP to use and creates a connection with that
	*It does not block the active scheduler of the current thread!
	*Pops up error notes as specified
	*The only difference from StartConnectionL is that it does not absorb commands
	*if destructor is called in while in this function the connection creation process is Cancelled
	*Wait note is popped up at some point if needed
	*aParam aDisableConnNeeded		disables the query that is popped up 
	*								when there is no connecction
	*								already
	*/
	TInt DoStartConnectionL ( TBool aDisableConnNeeded, TBool aIgnoreSecureAttribute );
	
	
	
	
	/**
	*It is a bitten-off piece of the connection logic. It should be called after we are sure that the existing connection is 
	*based on a different IAP from the requested one (ie. the the IAP part of the existing is not compatible with the active one)
	*@param aRequestedAP should contain the requested AP structure
	*@param aActiveAP contains the active AP structure (or equivalent e.g current AP if they are the same: their IAP UIds are the same)
	*@param aIgnoreSecurity switch this on to avoid security field comparision, it is requested by modules that will not use WTLS security, 
	*																												like Push in some cases
	*@param aConnect on return it will contain whether we should connect or the user requested not to or the current connection is OK (depending on the returned error)
	*@return the error status.
	*/
	TInt ConnectIfExistingDiffFromRequestedL(CApAccessPointItem& aRequestedAP,CApAccessPointItem& aActiveAP,TBool aIgnoreSecurity,TBool& aConnect);

	
	
	/**
	*returns the IAP Id of the current connection
	*@return the IAP Id of the current connection
	*/
	TUint32 CurrentIAPId();

	
	/**
	*Returns the IAP id of the specified connection
	*@return the IAP id
 	*/
	TUint32 IAPId( CApAccessPointItem& aAP );

	
	
	/**
	*Returns an object containing all info about the requested AP
	*@return the AP item belonging to the specified requested AP (i,e one of the 2 
	*/
	CApAccessPointItem* RequestedAPItemLC( TInt prefNo );

	
	/**
	*Returns an object containing all info about the AP specified with its Id
	*@return the AP item belonging to the specified APId
	*/
	CApAccessPointItem* APItemFromAPIdLC( TUint32 aAPId );
	
	
	
	/**
	*Returns an object containing all info about the AP specified with its Id
	*@return the AP item belonging to the specified APId
	*/
	CApAccessPointItem* APItemFromIAPIdLC( TUint32 aIAPId );
	
	
	
	/**
	*It is used for finding out the IAP id of the active connection
	*@param aIAPId the IAP id of the active connection
	*@return EFalse if there is no active connection, ETrue if there is
	*/
	TBool ActiveConnectionIAP( TUint32& aIAPId );

	/**
	*It does the actual connection
	*@param aPrefNo the ordinal of the preference to be used ether the first or the second one
	*/
	TInt ConnectL( TInt aPrefNo );
	

	
	/**
	*It tries to find a match on the active AP among the requested ones . 
	*If a match is found  and it is not a full match a aMatchingAP structure will be filled up
	*to contain the data of the matching AP.
	*@param aActiveAP the AP to find a match to
	*@param aMatchingAP the AP which contains the matching AP on return if not a full match was found otherwise you can use the active AP
	*@return the type of the match
	*/
	TBool WhichReqAPMatchesIAPL( CApAccessPointItem& aBaseAP, CApAccessPointItem& aMatchingAP );
	
	
	
	/**
	*Updates the current AP according to the specified base AP, it is possible to update only the WAP part
	*of the AP, and thus create a mixed AP for the current connection (and the session about to be established)
	*@param aBaseAP the base AP according to which the current AP will be updated
	*@param aOnlyWAPPart if set to ETrue only the WAP part of the current AP will be updated. otherewise the whole AP
	*/
	void UpdateCurrentAPL( CApAccessPointItem& aBaseAP, TBool aOnlyWAPpart);
	
	
	
	/**
	*Shows a query note with the aTextResId resource
	*@param aTextResId the resource id to be used as text
	*@return the id of the button pressed
	*/
	TInt ShowConfQueryNoteL(TInt aTextResId );


	/**
	*Shows a info note with the aTextResId resource
	*@param aTextResId the resource id to be used as text
	*/
	void ShowInformationNoteL( TInt aTextResId );

	/**
	*Notifies the observer if aNewUid is different from the old iCurrentUid
	*caller must store the oldUid and pass it to this function
	*@aParam aOldUid the old Uid that is compared with the new one to 
	*decide whether to notify the registered observer
	*/
	void NotifyObserverIfNeeded( TUint32 aOldUid );

public:

    /**
    *Checks if there is an active (HS)CSD connection in the system
    *@return TRUE if there is
    */
    IMPORT_C TBool IsThereActiveHSCSDConnectionL();

private: //data members

	MApChangeObserver* iApObserver;
	CApUtils* iApUtils;
	CApDataHandler* iApDataHandler;
	CCommsDatabase* iCommsDb;
	CApAccessPointItem* iCurrentAP;
	CInternetConnectionManager* iIntConnMan;

	TIdPair iRequestedAPIds;//< It stores the requested WAP AP ids (two prefs)
					//< after the connection is established
					//< it stores the actual WAP Id in both prefs
					//<this latter functionality is needed e.g by browser for not interrupting when clicking on a link
	
	TBool iNoSecondPreference;
	TBool iSilentMode;
	TBool iUsedByBrowser;	
	TBool iDefault;
	TBool iCommsDbOwned;
	TBool iAlreadyConfirmed;
};


#endif //Connection_Manager_H
// End of File
