/*
* ============================================================================
*  Name     : ApDataHandler.h
*  Part of  : Access Point Engine 
*
*  Description: Declaration of class CApDataHandler
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

#ifndef APDATAHANDLER_H
#define APDATAHANDLER_H

//  INCLUDES
#include <bldvariant.hrh>

#include <commdb.h>
#include <etelbgsm.h>
#include <ApEngineVer.h>
#include <ApEngineConsts.h>



// FORWARD DECLARATIONS
class CApAccessPointItem;


// CLASS DECLARATION

/**
*  Representation of the access point handler.
*  Encapsulates a session with the CommsDB
*  Provides a way to access the database and manipulate its data.
*/
class CApDataHandler :public CBase
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor. Leaves on failure, places instance
        * on cleanup stack.
        * @param aDb a reference to a CCommsDataBase object.
        * @return The constructed CApDataHandler.
        */
        IMPORT_C static CApDataHandler* NewLC( CCommsDatabase& aDb );


        /**
        * Destructor.
        */
        IMPORT_C virtual ~CApDataHandler();


protected:      // Constructors

        /**
        * C++ default constructor.
        */
        IMPORT_C CApDataHandler();

        /**
        * Second-phase constructor.
        */
        IMPORT_C void ConstructL( CCommsDatabase& aDb );


    private:


    public: // New functions
        // query
        /**
        * Reads up one access point's data from the database.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, function leaves with error code.
        * <br>Error conditions:
        *   - Insufficient memory,
        *   - AP does not exists,
        *   - Server connection failure.
        *
        * @param aUid The Uid of the access point to be read
        * @param aApItem A reference to a CApAccessPointItem to hold the data.
        * @return no return value.
        */
        IMPORT_C void AccessPointDataL( TUint32 aUid,
                                      CApAccessPointItem& aApItem );


        // update
        /**
        * Updates data stored in an existing access point.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, no data is stored.
        * <br>Error conditions:
        *   - Insufficient memory
        *   - Server connection failure
        *   - Lock already present by other task
        *   - Uid does not exists.
        *   - Attempting to update read-only records will result
        *     in KErrAccessDenied
        *
        * @param aApItem A reference to a CApAccessPointItem holding the data
        * @param aNameChanged a reference to a TBool that will indicate
        * whether the name has changed or not.
        * @return No return value.
        */
        IMPORT_C void UpdateAccessPointDataL( CApAccessPointItem& aApItem,
                                              TBool& aNameChanged );


        // Creating new AP
        /**
        * Creates a copy of a previously existing access point.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, no access point will be created.
        * <br>Error conditions:
        *   - Insufficient memory
        *   - Server connection failure.
        *   - Lock already present by other task.
        *   - Access point does not exist.
        *   - Attempting to create new in protected tables will results
        *     in KErrAccessDenied
        *
        * @param aBaseId The UID of the existing access point to copy from.
        * @return The Uid of the newly constructed and saved access point.
        */
        IMPORT_C TUint32 CreateCopyFromL( TUint32 aBaseId );


        /**
        * Create a new access point from supplied data
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * The name of the AP will be corrected to be unique if necessary and
        * returned in the passed aApItem.
        * In case of error, no access point will be created and the passed
        * one will remain intact.
        * <br>Error conditions:
        *   - Insufficient memory
        *   - Server connection failure.
        *   - Lock already present by other task.
        *   - Attempting to create new in protected tables will result
        * in KErrAccessDenied
        *
        * @param aApItem Reference to a CApAccessPointItem holding the data
        * @return The UID of the newly created and saved access point.
        */
        IMPORT_C TUint32 CreateFromDataL( CApAccessPointItem& aApItem );


        // Remove
        /**
        * Removes the given access point from the database.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, access point will not be removed.
        * <br>Error conditions:
        *   - Insufficient memory,
        *   - Server connection failure.
        *   - Lock already present by other task.
        *   - Access point does not exist.
        *   - Attempting to remove read-only records will result
        * in KErrAccessDenied
        *
        * @param aUid The UID of the access point to remove.
        * @return no return value.
        */
        IMPORT_C void RemoveAPL( TUint32 aUid );


        // Getting default access point
        /**
        * Reads the UID of the default access point.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, leaves with CommsDb or system error codes.
        * <br>Error conditions:
        *   - Insufficient memory;
        *   - Server connection failure;
        *   - Lock already present;
        *   - Access point does not exists.
        *
        * @param aIsWAP A boolean indicating whether to read the default
        * WAP or the default IAP/ISP (dep. on the database type) access point.
        * @return The UID of the default access point.
        */
        IMPORT_C const TUint32 DefaultL( TBool aIsWap ) const;


        // Setting as default
        /**
        * Sets the default access point.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, leaves with CommsDb or system error codes.
        * <br>Error conditions:
        *   - Insufficient memory;
        *   - Server connection failure;
        *   - Lock already present;
        *   - Access point does not exists.
        *   - Given Access Point is not of the desired type.
        *
        * @param aUid The UID of the access point to be set as default.
        * @param aIntendedType The default type ( IAP, WAP, Both).
        */
        IMPORT_C void SetAsDefaultL(TUint32 aUid,
                                    TCommsDbIspType aIntendedType );



        // Setting preferences
        /**
        * Sets the access point preference. Can be used only if the
        * database type is IAP.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, leaves with CommsDb or system error codes.
        * <br>Error conditions:
        *   - Insufficient memory;
        *   - Server connection failure;
        *   - Lock already present;
        * Can also leave with KErrAlreadyExists (if aOverWrite is EFalse ).
        * @param aRank The ranking of the connection preference.
        * @param aDircetion Specifies the direction of this connection
        * preference
        * @param aBearers The bearer set being valid for this connection
        * preference
        * @param aPrompt Enum value indicating whether or not the user
        * should be prompted or warned on connection
        * @param aIAP The identifier of the preferred IAP for this connection.
        * @param aOverwrite Boolean value indicating that if a same record
        * present, overwrite it or not.
        */
        IMPORT_C void SetPreferredIfDbIapTypeL
                                    (
                                    TUint32 aRank,
                                    TCommDbConnectionDirection aDirection,
                                    TUint32 aBearers,
                                    TCommDbDialogPref aPrompt,
                                    TUint32 aIAP,
                                    TBool aOverwrite
                                    );

        /**
        * Sets the access point preference. Can be used only if the
        * database type is ISP.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, leaves with CommsDb or system error codes.
        * <br>Error conditions:
        *   - Insufficient memory;
        *   - Server connection failure;
        *   - Lock already present;
        * Can also leave with KErrAlreadyExists (if aOverWrite is EFalse ).
        * @param aRank The ranking of the connection preference.
        * @param aDircetion Specifies the direction of this connection
        * preference
        * @param aBearers The bearer set beeing valid for this connection
        * preference
        * @param aPrompt Enum value indicating whether or not the user
        * should be prompted or warned on connection
        * @param aISP The identifier of the preferred ISP for this connection.
        * @param aChargeCard Identifier of the preferred chargecard for
        * this connection.
        * @param aServiceType The type of the service.
        * @param aOverwrite Boolean value indicating that if a same record is
        * present, overwrite it or not.
        */
        IMPORT_C void SetPreferredIfDbIspTypeL
                                    (
                                    TUint32 aRank,
                                    TCommDbConnectionDirection aDirection,
                                    TUint32 aBearers,
                                    TCommDbDialogPref aPrompt,
                                    TUint32 aISP,
                                    TUint32 aChargeCard,
                                    const TDesC& aServiceType,
                                    TBool aOverwrite
                                    );



        /**
        * Gets the access point preference. Can be used only if the
        * database type is IAP.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, leaves with CommsDb or system error codes.
        * <br>Error conditions:
        *   - Insufficient memory;
        *   - Server connection failure;
        *   - Lock already present;
        * @param aRank The ranking of the desired connection preference.
        * @param aDircetion Specifies the direction of the desired connection
        * preference
        * @param aBearers The bearer set beeing valid for this connection
        * preference
        * @param aPrompt Enum value indicating whether or not the user
        * should be prompted or warned on connection
        * @param aIAP The identifier of the preferred IAP for this
        * connection preference.
        */
        IMPORT_C void GetPreferredIfDbIapTypeL
                                    (
                                    TUint32 aRank,
                                    TCommDbConnectionDirection aDirection,
                                    TUint32& aBearers,
                                    TUint32& aPrompt,
                                    TUint32& aIAP
                                    );

        /**
        * Gets the access point preference. Can be used only if the
        * database type is ISP.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, leaves with CommsDb or system error codes.
        * <br>Error conditions:
        *   - Insufficient memory;
        *   - Server connection failure;
        *   - Lock already present;
        * @param aRank The ranking of the desired connection preference.
        * @param aDircetion Specifies the direction of the desired connection
        * preference
        * @param aBearers The bearer set beeing valid for this connection
        * preference
        * @param aPrompt Enum value indicating whether or not the user
        * should be prompted or warned on connection
        * @param aISP The identifier of the preferred ISP for this
        * connection preference.
        * @param aChargeCard Identifier of the preferred chargecard for
        * this connection preference.
        * @return The type of the service.
        */
        IMPORT_C const TDesC& GetPreferredIfDbIspTypeL
                                    (
                                    TUint32 aRank,
                                    TCommDbConnectionDirection aDirection,
                                    TUint32& aBearers,
                                    TUint32& aPrompt,
                                    TUint32& aISP,
                                    TUint32& aChargeCard
                                    );


        // Getting default access point
        /**
        * Reads the UID of the default access point.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, leaves with CommsDb or system error codes.
        * <br>Error conditions:
        *   - Insufficient memory;
        *   - Server connection failure;
        *   - Lock already present;
        *   - Access point does not exists.
        *
        * @param aIsWAP A boolean indicating whether to read the default
        * WAP or the default IAP/ISP (dep. on the database type) access point.
        * @param aReadOnly A TBool passed by reference to hold whether the
        * the default access point record is read-only or not.
        * @return The UID of the default access point.
        */
        IMPORT_C const TUint32 DefaultL( TBool aIsWap, TBool& aReadOnly )const;





    protected:  // New functions
        /**
        * Reads the WAP part of the data from the database.
        * In case of error, leaves with CommDb error codes.
        * @param aWapId The UID of the Access Point to read the data from.
        * @param aApItem A reference to a CApAccessPointItem to hold the data
        * @return No return value.
        */
        void ReadWapDataL( TUint32 aWapId, CApAccessPointItem& aApItem );


        /**
        * Reads the IAP part of the data from the database.
        * In case of error, leaves with CommDb error codes.
        * @param aIapId The UID of the record in the IAP table to read
        * the data.
        * @param aApItem A reference to a CApAccessPointItem to hold the data
        * @return No return value.
        */
        void ReadIapDataL( TUint32 aIapId, CApAccessPointItem& aApItem );


        /**
        * Reads the ISP part of the data from the database.
        * In case of error, leaves with CommDb error codes.
        * @param aIspId The UID of the record in the ISP table to
        * read the data.
        * @param aApItem A reference to a CApAccessPointItem to hold the data
        * @return No return value.
        */
        void ReadIspDataL( TUint32 aIspId, CApAccessPointItem& aApItem );


        /**
        * Reads the GPRS data from the database.
        * In case of error, leaves with CommDb error codes.
        * @param aIspId The UID of the record in the GPRS table to
        * read the data from.
        * @param aApItem A reference to a CApAccessPointItem to hold the data
        * @return No return value.
        */
        void ReadGprsDataL( TUint32 aIspId, CApAccessPointItem& aApItem );


        /**
        * Writes the WAP bearer part of the data to the database.
        * In case of error, leaves with CommDb error codes.
        * @param aIsNew A Boolean indicating whether it is a new record or it
        * is an update operation.
        * @param aWapId The UID of the WAP Access Point record to update.
        * Used only if aIsNew EFalse.
        * @param aApItem Reference to a CApAccessPointItem which holds the data
        * @return No return value.
        */
        void WriteWapBearerDataL
                        (
                        TBool aIsNew,
                        TUint32 aWapId,
                        CApAccessPointItem& aApItem
                        );


        /**
        * Writes the WAP AP part of the data to the database.
        * In case of error, leaves with CommDb error codes.
        * @param aIsNew A Boolean indicating whether it is a new record or it
        * is an update operation.
        * @param aWapId The UID of the WAP Access Point record to update.
        * Used only if aIsNew EFalse.
        * @param aApItem Reference to a CApAccessPointItem which holds the data
        * @return No return value.
        */
        void WriteWapApDataL
                        (
                        TBool aIsNew,
                        TUint32 aWapId,
                        CApAccessPointItem& aApItem
                        );



        /**
        * Writes the IAP part of the data to the database.
        * In case of error, leaves with CommDb error codes.
        * @param aIsNew A Boolean indicating whether it is a new record or it
        * is an update operation.
        * @param aIapId The UID of the IAP Access Point record to update.
        * Used only if aIsNew EFalse.
        * @param aApItem Reference to a CApAccessPointItem which holds the data
        * @return No return value.
        */
        void WriteIapDataL
                        (
                        TBool aIsNew,
                        TUint32 aIapId,
                        CApAccessPointItem& aApItem
                        );

        /**
        * Writes the ISP part of the data to the database.
        * In case of error, leaves with CommDb error codes.
        * @param aIsNew A Boolean indicating whether it is a new record or it
        * is an update operation.
        * @param aIspId The UID of the ISP Access Point record to update.
        * Used only if aIsNew EFalse.
        * @param aApItem Reference to a CApAccessPointItem which holds the data
        * @return No return value.
        */
        void WriteIspDataL( TBool aIsNew, TUint32 aIspId,
                            CApAccessPointItem& aApItem );


        /**
        * Writes the Gprs data to the database.
        * In case of error, leaves with CommDb error codes.
        * @param aIsNew A Boolean indicating whether it is a new record or it
        * is an update operation.
        * @param aApItem Reference to a CApAccessPointItem which holds the data
        * @return No return value.
        */
        void WriteGprsDataL( TBool aIsNew,
                            CApAccessPointItem& aApItem );



        /**
        * Writes the data to the database.
        * In case of error, leaves with CommDb error codes.
        * @param aApItem Reference to a CApAccessPointItem which holds the data
        * @param aIsNew A Boolean indicating whether it is a new record or it
        * is an update operation.
        * @return No return value.
        */
        TUint32 DoUpdateAccessPointDataL( CApAccessPointItem& aApItem,
                                       TBool aIsNew, TBool& aNameChanged );


        /**
        * Sets the default IAP & ISP records in Global Settings.
        * In case of error, leaves with CommDb error codes.
        * @param aApItem A UID to the WAP Access Point record to
        * be used as a default.
        * @return No return value.
        */
        void SetDefaultIapIspL( TUint32 aUid );

        // Remove
#ifdef USE_SMS
        /**
        * Removes the WAP_BEARER table part of the access point from
        * the database.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, access point will not be removed.
        * @param aUid The UID of the access point to remove.
        * @param aIsIsp Indicates whether the bearer is IP based or SMS based.
        * @return No return value.
        */
        void RemoveWapBearerApL( TUint32 aUid, TBool aIsIp );
#else
        /**
        * Removes the WAP_BEARER table part of the access point from
        * the database.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, access point will not be removed.
        * @param aUid The UID of the access point to remove.
        * @return No return value.
        */
        void RemoveWapBearerApL( TUint32 aUid );
#endif // USE_SMS


        /**
        * Removes the WAP_ACCESS_POINT table part of the access point from
        * the database.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, access point will not be removed.
        * @param aUid The UID of the access point to remove.
        * @return No return value.
        */
        void RemoveWapApL( TUint32 aUid );


        /**
        * Removes the IAP part of the access point from the database.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, access point will not be removed.
        * @param aUid The UID of the IAP part of the access point to remove.
        * @return No return value.
        */
        void RemoveIapL( TUint32 aUid );


        /**
        * Removes the ISP part of the access point from the database.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, access point will not be removed.
        * @param aUid The UID of the ISP part of the access point to remove.
        * @param aOut TBool indicating whether Dial out or dial in ISP.
        * @return No return value.
        */
        void RemoveIspL( TUint32 aUid, TBool aOut );


        /**
        * Removes the GPRS part of the access point from the database.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, access point will not be removed.
        * @param aUid The UID of the GPRS part of the access point to remove.
        * @return No return value.
        */
        void RemoveGprsL( TUint32 aUid, TBool aOut );


        /**
        * Handles the bearer change related things (deleting old links,
        * inserting new ones if needed in the database).
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, access point data will not be changed.
        * @param aApItem A reference to a CApAccessPointItem holding the
        * CHANGED data.
        * @return Boolean indicating whether bearer has changed or not.
        */
        TBool HandleBearerChangeIfNeededL( CApAccessPointItem& aApItem );



        /**
        * Reads up one access point's data from the database.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, function leaves with error code.
        * <br>Error conditions:
        *   - Insufficient memory,
        *   - AP does not exists,
        *   - Server connection failure.
        *
        * @param aUid The Uid of the access point to be read
        * @param aApItem A reference to a CApAccessPointItem to hold the data.
        * @return no return value.
        */
        void DoAccessPointDataL( TUint32 aUid, CApAccessPointItem& aApItem );


        /**
        * Removes the given access point from the database.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, access point will not be removed.
        * <br>Error conditions:
        *   - Insufficient memory,
        *   - Server connection failure.
        *   - Lock already present by other task.
        *   - Access point does not exist.
        *   - Attempting to remove read-only records will result
        * in KErrAccessDenied
        *
        * @param aUid The UID of the access point to remove.
        * @return no return value.
        */
        void DoRemoveAPL( TUint32 aUid );


        /**
        * Sets the default access point.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, leaves with CommsDb or system error codes.
        * <br>Error conditions:
        *   - Insufficient memory;
        *   - Server connection failure;
        *   - Lock already present;
        *   - Access point does not exists.
        *   - Given Access Point is not of the desired type.
        *
        * @param aUid The UID of the access point to be set as default.
        * @param aIntendedType The default type ( IAP, WAP, Both).
        */
        void DoSetAsDefaultL(TUint32 aUid, TCommsDbIspType aIntendedType );


        /**
        * Sets the access point preference. Can be used only if the
        * database type is IAP.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, leaves with CommsDb or system error codes.
        * <br>Error conditions:
        *   - Insufficient memory;
        *   - Server connection failure;
        *   - Lock already present;
        * Can also leave with KErrAlreadyExists (if aOverWrite is EFalse ).
        * @param aRank The ranking of the connection preference.
        * @param aDircetion Specifies the direction of this connection
        * preference
        * @param aBearers The bearer set beeing valid for this connection
        * preference
        * @param aPrompt Enum value indicating whether or not the user
        * should be prompted or warned on connection
        * @param aIAP The identifier of the preferred IAP for this connection.
        * @param aOverwrite Boolean value indicating that if a same record
        * present, overwrite it or not.
        */
        void DoSetPreferredIfDbIapTypeL
                                    (
                                    TUint32 aRank,
                                    TCommDbConnectionDirection aDirection,
                                    TUint32 aBearers,
                                    TCommDbDialogPref aPrompt,
                                    TUint32 aIAP,
                                    TBool aOverwrite
                                    );


        /**
        * Sets the access point preference. Can be used only if the
        * database type is ISP.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, leaves with CommsDb or system error codes.
        * <br>Error conditions:
        *   - Insufficient memory;
        *   - Server connection failure;
        *   - Lock already present;
        * Can also leave with KErrAlreadyExists (if aOverWrite is EFalse ).
        * @param aRank The ranking of the connection preference.
        * @param aDircetion Specifies the direction of this connection
        * preference
        * @param aBearers The bearer set beeing valid for this connection
        * preference
        * @param aPrompt Enum value indicating whether or not the user
        * should be prompted or warned on connection
        * @param aISP The identifier of the preferred ISP for this connection.
        * @param aChargeCard Identifier of the preferred chargecard for
        * this connection.
        * @param aServiceType The type of the service.
        * @param aOverwrite Boolean value indicating that if a same record
        * present, overwrite it or not.
        */
        void DoSetPreferredIfDbIspTypeL
                                    (
                                    TUint32 aRank,
                                    TCommDbConnectionDirection aDirection,
                                    TUint32 aBearers,
                                    TCommDbDialogPref aPrompt,
                                    TUint32 aISP,
                                    TUint32 aChargeCard,
                                    const TDesC& aServiceType,
                                    TBool aOverwrite
                                    );


        /**
        * Converts AP speed from TApCallSpeed to RBasicGsmCall::TBearerSpeed
        * @param The speed to convert
        * @param The current value of the Anal./ISDNv110/ISDNv120
        * @return The converted speed
        */
		/*****************************************************
		*	Series 60 Customer / ETel
		*	Series 60  ETel API
		*****************************************************/
        RBasicGsmCall::TBearerSpeed ApSpeed2Etel( TApCallSpeed aSpeed,
                                                  TUint32 aIsdn );

        /**
        * Converts AP speed from RBasicGsmCall::TBearerSpeed to TApCallSpeed
        * @param The holder for the converted speed
        * @param The current value of the Anal./ISDNv110/ISDNv120
        * @param The speed to convert
        * @return no return value
        */
		/*****************************************************
		*	Series 60 Customer / ETel
		*	Series 60  ETel API
		*****************************************************/
        void EtelSpeed2Ap( TApCallSpeed& aSpeed, TUint32& aIsdn,
                           RBasicGsmCall::TBearerSpeed aEtelSpeed );

        // Getting default access point
        /**
        * Reads the UID of the default access point.
        * Expects that CApDataHandler has been created and the database had
        * been opened.
        * In case of error, leaves with CommsDb or system error codes.
        * <br>Error conditions:
        *   - Insufficient memory;
        *   - Server connection failure;
        *   - Lock already present;
        *   - Access point does not exists.
        *
        * @param aIsWAP A boolean indicating whether to read the default
        * WAP or the default IAP/ISP (dep. on the database type) access point.
        * @param TBool*: if not NULL, a holder for the read-only flag of
        * the default access point. Prepared for future products but also used
        * here through passing NULL ptr.
        * @return The UID of the default access point.
        */
        const TUint32 DoGetDefaultL( TBool aIsWap, TBool* aReadOnly ) const;

#ifdef __PROXY_SETTINGS
        /**
        * 
        */
        void WriteProxyDataL( TBool aIsNew, const CApAccessPointItem& aApItem );


        /**
        * 
        */
        void ReadProxyDataL( CApAccessPointItem& aApItem );


        /**
        * 
        */
        void RemoveProxyDataL( HBufC* aServiceType, TUint32 aIspId );
#endif // __PROXY_SETTINGS

    private:    // Data
        CCommsDatabase* iDb;
        TCommDbDatabaseType iDbType;

    };

#endif      // APDATAHANDLER_H

// End of File
