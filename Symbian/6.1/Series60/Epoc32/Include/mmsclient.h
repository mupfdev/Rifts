/*
* ============================================================================
*  Name     : CMmsClientMtm from mmsclient.h
*  Part of  : mmsengine\clientmtm
*
*  Description: 
*     Client Mtm for multimedia messaging.
*     This is the API for accessing multimedia messaging engine.
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

#ifndef MMSCLIENT_H
#define MMSCLIENT_H

//  INCLUDES
#include  <mtclbase.h> // base client mtm
#include  <e32std.h>   // TTimeInterval & TTime
#include  "mmsconst.h" // common constants

// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CMmsSettings;
class CMmsHeaders;
class CMmsMessage;
class CMmsMimeHeaders;
class CMmsAttachmentList;

// CLASS DECLARATION

/**
*  Client Mtm for multimedia messaging subsystem.
*  This class will be the interface to the UI component
*  and other messaging component that might want to handle multimedia messages
*  (For example SendAs interface).
*/
class CMmsClientMtm :public CBaseMtm
    {
    public:  // Constructors and destructor
        // constructor is private!

        /**
        * Factory function.
        * The only function exported by this polymorphic interface dll.<br>
        * This function is not directly called by the application that needs
        * access, it is called by an instance of CClientMtmRegistry class.
        * @param  aRegisteredMtmDll Reference to Mtm Dll registry class
        * @param  aSession Reference to a Message Server session.
        * @return Pointer to CMmsClientMtm class.
        *
        * <PRE>
        * Example of getting access to this class:
        *
        * // Called by a Uikon application that implements
        * // MMsvSessionObserver interface
        *
        * iSession = CMsvSession::OpenSyncL(*this);
        * CleanupStack::PushL(iSession);
        * iClientMtmRegistry = CClientMtmRegistry::NewL(*iSession);
        * CleanupStack::PushL(iClientMtmRegistry);
        * iMmsClient = (CMmsClientMtm *) iClientMtmRegistry->
        *               NewMtmL(KUidMsgTypeMultimedia);
        * CleanupStack::PushL(iMmsClient);
        *
        * // - do other initialization -
        *
        * CleanupStack::Pop(3);    //iSession, iClientMtmRegistry, iMmsClient
        *
        * // - call any public functions in CMmsClientMtm
        *
        * // When the application finishes,
        * // it must delete the objects in reverse order:
        * delete iMmsClient;
        * delete iClientMtmRegistry;
        * delete iSession;
        * </PRE>
        */
        IMPORT_C static CMmsClientMtm* NewL(
            CRegisteredMtmDll& aRegisteredMtmDll,
            CMsvSession& aSession );
        
        /**
        * Destructor.
        */
        ~CMmsClientMtm();

    public:  // New functions

        // ----------------------------------------------------------
        // Functions to create and modify message entries


        /**
        * Create a new message entry
        * @param aDestination target folder
        * @param aCompletionStatus Reference to the status of
        *     an active object.<br>
        *     This status will be set as completed when the operation completes.
        * @return Pointer to a message server operation (active object). <br>
        *     The progress information provides the id of the created message 
        *     when the message has been created in a 8-bit descriptor. 
        *     While the operation is in progress the package will contain a null 
        *     id (KMsvNullIndexEntryId). If there was an error while creating 
        *     the message, then the message will be deleted and the package will 
        *     contain null id.
        */
        virtual CMsvOperation* CreateNewEntryL(
            TMsvId aDestination, 
            TRequestStatus& aCompletionStatus);
    

        
        // ---------------------------------------------------------------------
        // FUNCTIONS TO HANDLE MMSC SETTINGS
        // 
        // There are some settings (for example turning receiving of
        // multimedia messages on and off) that controls the behaviour
        // of server mtm. The MMS service entry contains also template
        // values for new entries created.
        // On the other hand, WAP access point and Internet access point
        // are stored in comms database, not in MMS service entry, and service
        // entry has only a reference to the comms database data.
        // 
        // Currently maximum one MMS service entry is allowed to be created!
        // The possible future requirements to support more then one MMS
        // service entry is considered later.
        // 
        // The Client MTM maintains cached MMS service settings, referred to
        // as current service below. Some of those cached settings are used
        // as template values when a new multimedia message is created.

        /**
        * Create new service entry.
        * Context is set to the new service entry.
        * Currently maximum one service is created, and further requests
        * do not create a new service entry! 
        */
        virtual void CreateServiceL();
        
        /**
        * Restore default MMSC service settings as current service.<br>
        * @return id of the default service if found,
        *     KMsvNullIndexEntryId otherwise.
        */
        virtual TMsvId RestoreDefaultSettingsL();

        /**
        * Selects default MMSC settings. 
        * @param aServiceId entry id of the service to become the default
        * @return ETrue if successful, EFalse, if not
        */
        virtual TBool SetDefaultSettingsL( TMsvId aServiceId );

        /**
        * Returns id of the default MMSC settings. 
        * @return the default service id if found,
        *     KMsvNullIndexEntryId otherwise.
        */
        virtual TMsvId DefaultSettingsL();

        /**
        * Restore factory settings to the default service entry and select it
        * as the current service entry.
        * @param aLevel defines the operations to be done
        */
        virtual void RestoreFactorySettingsL( 
            TMmsFactorySettingsLevel aLevel = EMmsFactorySettingsLevelNormal );

        /**
        * Lists all MMSC service settings available.<br>
        * Caller must delete the array when no longer needed.
        * @return Array of entry IDs of MMS Service settings
        */
        virtual CMsvEntrySelection* ListServicesL();

        /**
        * Select the current service to be used to send the current messages.<br>
        * If no current service is selected, the default is used to 
        *     send any messages.<br>
        * @param aServiceId entry id of the service to be used.
        * @return ETrue if successful, EFalse, if entry not valid
        */
        virtual TBool SelectServiceL( TMsvId aServiceId );
      
        /**
        * Check if specified service really exists and is MMS service.<br>
        * Checks that access points point to valid entries
        *     in comms database.
        * @param aServiceId The id of the service to be checked
        * @return ETrue, if service exists, EFalse if not
        */
        virtual TBool IsServiceLegalL( TMsvId aServiceId );        

        /**
        * Validate service.<br>
        * Checks that access points point to valid entries
        *     in comms database.
        * @return error code (defined in mmserrors.h or e32std.h)
        * KErrNone = service ok. Other error codes in mmserrors.h or e32std.h
        */
        virtual TInt ValidateService( TMsvId aServiceId );

        // ---------------------------------------------------------------------
        // The following methods are mutators and accessors for a service entry.
        // The context must be in a MMS service entry. Otherwise the
        // methods cause a panic!
        // You have to set the context to a service entry and use LoadMessageL()
        // and SaveMessageL() methods in the same way as with message entries, 
        // when you want to modify service settings.
        // NOTE:
        // Those accessors that give values of global settings
        // (those that cannot be changed for each message)
        // can be used without switching context to service entry.
        // If there is any doubt that the settings may have changed,
        // call RestoreDefaultSettingsL() before accessing the settings.
        // The functions that can be used without switching context to
        // service entry are:
        // ServiceName()
        // FirstAccessPoint()
        // SecondAccessPoint()
        // AcceptPersonal()
        // AcceptAdvertisements()
        // AcceptInformational()
        // MessageFetchState()
        // MmsReceivingMode()
        // MaximumSendSize()
        // MaximumReceiveSize()
        // ImageWidth and ImageHeight() give default value from settings,
        // use GetMaximumImage() to access message headers
        // ImageWidth()
        // ImageHeight()
        // SendRetryCount()
        // SendRetryInterval()
        // FetchRetryCount()
        // FetchRetryInterval()
        // MoveToSent()
        // DefaultSpeaker()
        // ---------------------------------------------------------------------

        /**
        * Service Name mutator.
        * Saved in TMsvEntry::iDetails in SaveMessageL()
        * @param aName Service Name
        */
        virtual void SetServiceNameL( const TDesC& aName );

        /**
        * Service name accessor.
        * @return Service Name
        */
        virtual const TPtrC ServiceName() const;

        /**
        * Get most preferred access point (Comms database id).
        * @return access point id from comms database.
        */
        virtual TUint32 FirstAccessPoint();

        /**
        * Set most preferred access point.
        * @param aAccessPoint access point id in comms database
        */
        virtual void SetFirstAccessPoint( TUint32 aAccessPointId );

        /**
        * Get second most preferred access point (Comms database id).
        * @return access point id from comms database.
        */
        virtual TUint32 SecondAccessPoint();

        /**
        * Set second most preferred access point.
        * @param aAccessPoint access point id in comms database
        */
        virtual void SetSecondAccessPoint( TUint32 aAccessPointId );

        /**
        * Get expiration interval.
        * @return message expiration interval in seconds
        */
        virtual TInt32 DefaultExpiryInterval();

        /**
        * Set expiration interval.
        * @param aExpiryInterval message expiration interval in seconds
        */
        virtual void SetDefaultExpiryInterval( TInt32 aExpiryInterval );
        
        /**
        * Get sender visibility.
        * @return sender visibility code
        */
        virtual TInt32 DefaultSenderVisibility();

        /**
        * Set sender visibility.
        * @param aSenderVisibilty sender visibility code
        * possible values: 
        * EMmsSenderVisibilityDefault,
        * EMmsSenderVisibilityHide,
        * EMmsSenderVisibilityShow
        */
        virtual void SetDefaultSenderVisibility( 
            TMmsMessageSenderVisibility aSenderVisibility );

        /**
        * Get delivery report wanted code.
        * @return delivery report code
        */
        virtual TInt32 DeliveryReportWanted();

        /**
        * Set delivery report wanted.
        * @param aDeliveryReport delivery report code
        * Possible values:
        * EMmsDeliveryReportYes, EMmsDeliveryReportNo
        */
        virtual void SetDeliveryReportWanted( 
            TMmsMessageDeliveryReport aDeliveryReport );

        /**
        * Get Delivery report sending allowed.
        * @return delivery report sending allowed code
        */
        virtual TInt32 DeliveryReportSendingAllowed();

        /**
        * Set Delivery report sending allowed.
        * @param aReportAllowed delivery report sending allowed code
        * possible values:
        * EMmsDeliveryReportAllowedYes, EMmsDeliveryReportAllowedNo
        */
        virtual void SetDeliveryReportSendingAllowed( 
            TMmsSettingsDeliveryReportAllowed aReportAllowed );

        /**
        * Get Read reply wanted code.
        * @return read reply wanted code
        */
        virtual TInt32 ReadReplyWanted();

        /**
        * Set Read reply wanted code.
        * @param aReadReplyWanted read reply wanted code
        * Possible values:
        * EMmsReadReplyYes, EMmsReadreplyNo
        */
        virtual void SetReadReplyWanted( TMmsMessageReadReply aReadReplyWanted );

        /**
        * Get read reply sending allowed code.
        * @return read reply allowed code
        */
        virtual TInt32 ReadReplySendingAllowed();

        /**
        * Set read reply sending allowed code.
        * @param aReadReplySendingAllowed read reply sending allowed code.
        * Possible values:
        * EMmsReadReplyAllowedYes, EMmsReadReplyAllowedNo
        */
        virtual void SetReadReplySendingAllowed( 
            TMmsSettingsReadReplyAllowed aReadReplySendingAllowed );

        /**
        * Get message priority.
        * @return message priority code
        */
        virtual TInt32 DefaultMessagePriority();

        /**
        * Set message priority
        * @param aPriority message priority code
        * Possible values:
        * EMmsPriorityLow, EMmsPriorityNormal, EMmsPriorityHigh
        */
        virtual void SetDefaultMessagePriority( TMmsMessagePriority aPriority);

        /**
        * Get default message class.
        * @return message class code
        */
        virtual TInt32 DefaultMessageClass();

        /**
        * Set default message class.
        * @param aMessageClass message class code
        * Possible values:
        * EMmsClassPersonal, EMmsClassAdvertisement, 
        * EMmsClassInformational, KMmsMessageClassAuto
        */
        virtual void SetDefaultMessageClass( TMmsMessageClass aMessageClass );

        // Accepted message classes flags
        // Anonymous message flag in the same list though it
        // is not strictly a message class, but acceptance
        // handling is similar.
        // Anonymous messages mean messages where the from-field
        // is missing. This means that the sender has a secret number,
        // or that the sender has told MMSC to hide his number

        /**
        * Get personal flag.
        * @return ETrue if personal messages accepted
        */
        virtual TBool AcceptPersonal();

        /**
        * Get advertisement flag.
        * @return ETrue if advertisements accepted
        */
        virtual TBool AcceptAdvertisements();

        /**
        * Get informational flag.
        * @return ETrue if informational messages accepted
        */
        virtual TBool AcceptInformational();

        /**
        * Get anonymous flag.
        * @return ETrue if anonymous messages accepted
        */
        virtual TBool AcceptAnonymous();

        /**
        * Set Personal messages accepted.
        * @param aPersonalAllowed boolean value for the flag
        */
        virtual void SetAcceptPersonal( TBool aPersonalAllowed = ETrue );

        /**
        * Set Advertisements allowed.
        * @param aAdvertisementsAllowed boolean value for the flag
        */
        virtual void SetAcceptAdvertisements( TBool aAdvertisementsAllowed = ETrue );

        /**
        * Set Informational messages allowed.
        * @param aInformationalAllowed boolean value for the flag
        */
        virtual void SetAcceptInformational( TBool aInformationalAllowed = ETrue );

        /**
        * Set anonymous messages allowed.
        * @param aAnonymousAllowed boolean value for the flag
        */
        virtual void SetAcceptAnonymous( TBool aAnonymousAllowed = ETrue );

        /**
        * Get message fetching state.<br>
        * Fetching state when MMS receiving is enabled 
        * (either always enabled or enabled at home)
        * @return fetching state (on/off/deferred)
        */
        virtual TInt32 MessageFetchState();

        /**
        * Set message fetching state.
        * Fetching state when MMS receiving is enabled.
        * @param aFetchingState (on/off/deferred)
        * Possible values:
        * EMmsFetchingOn, EMmsFetchingOff, EMmsFetchingDeferred
        * EMmsFetchingOn: fetch message automatically
        * EMmsFetchingOff: Send reject response to MMSC for all messages
        * EMmsFetchingDeferred: Send "deferred" response to MMSC for all messages.
        *     Messages can be fetched later by turning MessageFetchState ON
        */
        virtual void SetMessageFetchState( TMmsSettingsFetchMode aFetchingState );

        /**
        * Get MMS receiving mode.
        * MMS receiving mode controls whether any responses to notifications
        * (acknowledgements or fetch requests) are sent to MMSC
        * EMmsReceivingAlwaysEnabled: Interact with MMSC according to setting
        *     specified in SetMessageFetchState.
        * EMmsReceivingEnabledInHomeNetwork: Like EMmsReceivingAlwaysEnabled
        *     if phome is in Home Network, like EMmsReceivingDisabled, if 
        *     phone is roaming
        * EMmsReceivingDisabled: Do not send any acknowledgements to MMSC
        *     delete all notifications as they arrive
        * EMmsReceivingManual: Do not send any acknowledgements to MMSC.
        *     Message fetching is under user control
        * @return receiving mode (Always Enabled/Enabled in Home Network/Disabled/Manual)
        */
        virtual TInt32 MmsReceivingMode();

        /**
        * Set MmsReceiving mode (Always Enabled/Enabled in Home Network/Disabled/Manual).
        * @param aReceivingMode
        * Possible values:
        * EMmsReceivingAlwaysEnabled, EMmsReceivingEnabledInHomeNetwork, 
        * EMmsReceivingDisabled, EMmsReceivingManual
        * (see detailed explanation of modes above)
        */
        virtual void SetMmsReceivingMode( TMmsReceivingMode aReceivingMode );

        /**
        * Get maximum size of messages that can be sent.
        * @return maximum message size in bytes (0 = any size)
        */
        virtual TUint32 MaximumSendSize();
        
        /**
        * Set maximum size of messages that can be sent.
        * @param aMaxSize in bytes (0 = any size)
        */
        virtual void SetMaximumSendSize( TUint32 aMaxSize );

        /**
        * Get maximum size of messages that can be received.
        * @return maximum message size in bytes (0 = any size)
        */
        virtual TUint32 MaximumReceiveSize();
        
        /**
        * Set maximum size of messages that can be received.
        * @param aMaxSize maximum message size in bytes (0 = any size)
        */
        virtual void SetMaximumReceiveSize( TUint32 aMaxSize );

        // Image width is for UI use only, engine does not care about it.
        /**
        * Get image width.
        * @return image width in pixels
        */
        virtual TInt32 ImageWidth();

        /**
        * Set image width.
        * @param aImageWidth image width in pixels
        */
        virtual void SetImageWidth( TInt32 aImageWidth );

        // Image height is for UI use only, engine does not care about it.
        /**
        * Get image height.
        * @return image height in pixels
        */
        virtual TInt32 ImageHeight();

        /**
        * Set image height.
        * @param aImageHeight image height in pixels
        */
        virtual void SetImageHeight( TInt32 aImageHeight );

        /**
        * Get send retry count.
        * @return number of retries for send attempt
        */
        virtual TUint32 SendRetryCount();

        /**
        * Set send retry count.
        * @param aSendRetries number of retries for send attempt
        */
        virtual void SetSendRetryCount( TUint32 aSendRetries );

        /**
        * Get send retry interval.
        * @return send retry interval in seconds
        */
        virtual TUint32 SendRetryInterval();

        /**
        * Set send retry interval.
        * @param aSendRetryInterval interval between send retries in seconds
        */
        virtual void SetSendRetryInterval( TUint32 aSendRetryInterval );
        
        /**
        * Get fetch retry count.
        * @return number of retries for fetch attempt
        */
        virtual TUint32 FetchRetryCount();

        /**
        * Set fetch retry count.
        * @param aFetchRetries number of retries for send attempt
        */
        virtual void SetFetchRetryCount( TUint32 aFetchRetries );

        /**
        * Get fetch retry interval.
        * @return send retry interval in seconds
        */
        virtual TUint32 FetchRetryInterval();

        /**
        * Set fetch retry interval.
        * @param aSendRetryInterval interval between fetch retries in seconds
        */
        virtual void SetFetchRetryInterval( TUint32 aFetchRetryInterval );

        /**
        * Get option that tells if messages are moved to sent folder
        * after they have been successfully sent, or if they are deleted.
        * @return ETrue, if messages are moved, EFalse, if they are deleted.
        */
        virtual TBool MoveToSent();

        // This function has no effect. The value of MoveToSent
        // is controlled by Shared data. The function remains
        // here in case we have a system where the common MoveToSent
        // setting does not exist.
        /**
        * Set option that tells if messages are moved to sent folder
        * after they have been successfully sent, or if they are deleted.
        * @param aMove (ETrue or EFalse)
        */
        virtual void SetMoveToSent( TBool aMove );

        /**
        * Default speaker accessor.
        * @return default speaker system
        */
        virtual TInt32 DefaultSpeaker();

        /**
        * Default speaker mutator.
        * @param aSpeaker speaker system
        */
        virtual void SetDefaultSpeaker( TMmsSettingsDefaultSpeaker aSpeaker );


        // ---------------------------------------------------------------------
        // FUNCTIONS TO HANDLE MMS HEADERS

        // Accessors and mutators for header fields.
        // Some of these header fields have default values that are assigned
        // from cached service settings when a new header is allocated.
        // Some header fields are needed by protocol only.
        // Those headers don't have accessors and mutators here,
        // as they are used by Server MTM who accesses them directly
        // through functions offered by CMmsHeaders.

        /**
        * Returns recipients that are of specified type (To, Cc, Bcc).
        * @param aType specifies recipient type (types defined in MMSCONST.H)
        * @return array of recipient addresses.
        */
        virtual const CDesCArray& TypedAddresseeList( TMmsRecipients aType );

        /**
        * Adds recipient with specified type (To, Cc, Bcc).<br>
        * This function also adds all recipients into the internal list <br>
        * that contains all addressees regardless of addressee type.<br>
        * @param aRealAddress recipient address.
        * @param aType specifies recipient type (types defined in MMSCONST.H)
        */
        virtual void AddTypedAddresseeL( 
            const TDesC& aRealAddress, 
            TMmsRecipients aType );

        /**
        * Adds recipient with specified type (To, Cc, Bcc).<br>
        * This function also adds all recipients into the internal list <br>
        * that contains all addressees regardless of addressee type.<br>
        * @param aRealAddress recipient address.
        * @param aAlias Reference to a descriptive name (not a real address)
        * @param aType specifies recipient type (types defined in MMSCONST.H)
        */
        virtual void AddTypedAddresseeL( 
            const TDesC& aRealAddress, 
            const TDesC& aAlias, 
            TMmsRecipients aType );

        /**
        * Sender mutator
        * @param aAlias
        */
        virtual void SetSenderL( const TDesC& aAlias );

        /**
        * Sender accessor
        * @return Real address of sender (for example phone number). <br>
        *     Alias can be searched from contacts database.
        */
        virtual const TPtrC Sender() const;

        /**
        * Message class mutator.
        * @param aMessageClass message class code
        */
        virtual void SetMessageClass( TMmsMessageClass aMessageClass );

        /**
        * Message class accessor
        * @return Message class: Personal/Advertisement/Informational. <br>
        *     values defined in MMSCONST.H
        */
        virtual TInt MessageClass() const;

        /**
        * Expiration interval mutator.
        * Both for message and service entries.
        * @param aInterval The length of time after which the message
        *     is discarded by MMSC. Expressed in seconds.
        */
        virtual void SetExpiryInterval( TTimeIntervalSeconds aInterval );

        /**
        * Expiration interval accessor.
        * Both for message and service entries.
        * @return Storage time of the message in MMSC (in seconds).
        */
        virtual TTimeIntervalSeconds ExpiryInterval() const;

        /**
        * Expiration date mutator.
        * @param aDate The date and time the message will expire.
        *     The date must be greater than 1970-01-01, 00:00:00 GMT
        */
        virtual void SetExpiryDate( TTime aDate );

        /**
        * Expiration date accessor.
        * @return The date and time the message will expire.
        */
        virtual TTime ExpiryDate() const;

        /**
        * Delivery time interval mutator.
        * @param aInterval The length of time after which the message will<br>
        *     be delivered to the recipient by the MMSC.<br>
        *     Expressed in seconds.
        */
        virtual void SetDeliveryTimeInterval( TTimeIntervalSeconds aInterval );

        /**
        * Delivery time interval accessor.
        * @return delivery time interval of the message (in seconds).
        */
        virtual TTimeIntervalSeconds DeliveryTimeInterval() const;

        /**
        * Delivery date mutator.
        * @param aDate The date and time the message will be delivered <br>
        *     to the recipient by the MMSC. 
        *     The date must be greater than 1970-01-01, 00:00:00 GMT
        */
        virtual void SetDeliveryDate( TTime aDate );

        /**
        * Delivery date accessor.
        * @return The date and time the message will be delivered to the
        *     recipient by the MMSC.
        */
        virtual TTime DeliveryDate() const;

        /**
        * Message priority mutator (Low/Normal/High). Default: Normal.
        * @param aPriority Message priority, values defined in MMSCONST.H
        */
        virtual void SetMessagePriority( TMmsMessagePriority aPriority );

        /**
        * Message priority accessor.
        * @return Message priority, values defined in MMSCONST.H
        */
        virtual TInt MessagePriority() const;

        /**
        * Sender visibility mutator.
        * @param aVisibility Hide or Show (values defined in MMSCONST.H)
        */
        virtual void SetSenderVisibility( 
            TMmsMessageSenderVisibility aVisibility );

        /**
        * Sender visibility accessor.
        * @return Hide or Show (values defined in MMSCONST.H)
        */
        virtual TInt SenderVisibility() const;

        /**
        * Delivery Report Request mutator.
        * @param aRequest Yes or No (values defined in MMSCONST.H)
        */
        virtual void SetDeliveryReport( 
            TMmsMessageDeliveryReport aRequest );

        /**
        * Delivery Report Request accessor.
        * @return Yes or No (values defined in MMSCONST.H)
        */
        virtual TInt DeliveryReport() const;

        /**
        * Read Reply Request mutator.
        * @param aRequest Yes or No (values defined in MMSCONST.H)
        */
        virtual void SetReadReply( TMmsMessageReadReply aRequest );

        /**
        * Read Reply Request accessor.
        * @return Yes or No (values defined in MMSCONST.H)
        */
        virtual TInt ReadReply() const;

        /**
        * Message root part mutator.
        * Leaves with KErrNotFound if attachment not found.
        * @param aId Attachment Id of the message part which should be 
        * displayed first.<br>
        * Should point to the SMIL part that starts the message display.
        */
        virtual void SetMessageRootL( const TMsvId aId );

        /**
        * Message root part accessor.
        * @return the attachment part that starts the message display.
        * KMsvNullIndexEntryId if not set.
        */
        virtual const TMsvId MessageRoot() const;

        /**
        * Sending date and time accessor.
        * Valid only for mobile terminated messages
        * @return the time when MMSC has received the message from sender.
        */
        virtual TTime SendingDate() const;

        /**
        * Maximum image size mutator.
        * @param aHeight image height
        * @param aWidth image width
        */
        virtual void SetMaximumImage( TInt aWidth, TInt aHeight );

        /**
        * Maximum image size accessor.
        * @param aHeight image height (OUT)
        * @param aWidth image width (OUT)
        */
        virtual void GetMaximumImage( TInt& aWidth, TInt& aHeight ) const;

        // ---------------------------------------------------------------------
        // GENERAL MESSAGE INFORMATION METHODS 

        /**
        * Message size accessor. SaveMessageL and LoadMessageL updates the 
        * value.
        * @return size of all message parts in bytes including both
        * attachments and internal header structures. The actual message
        * size in transmission is smaller due to the header
        * binary encoding.
        */
        virtual TInt32 MessageSize();

        /**
        * Message description accessor. 
        * MMS engine has a very special way to determine
        * the message description in SaveMessageL. <br>
        * Message description determination order: <br>
        *   1 - Subject <br>
        *   2 - Maximum <KMmsMaxDescription> characters from first text/plain 
        *       part. <br>
        *   3 - empty if none of the above match <br>
        * Note that the description is generated automatically by 
        * SaveMessageL. 
        * SetMessageDescriptionL should be used if a message modification 
        * should reflect to the message description. 
        * See also SetMessageDescriptionL.
        * @return message description
        */
        virtual TPtrC MessageDescription();

        /**
        * Message description mutator. 
        * This provides a method to override the default message description.
        * The next SaveMessageL saves the description text in the 
        * TMsvEntry::iDescription.
        * Note that this method does not check the text length, so avoid long 
        * descriptions to minimize memory usage. Zero length description is ignored.
        * @param aText message description
        */
        virtual void SetMessageDescriptionL( const TDesC& aText );

        // ---------------------------------------------------------------------
        // FUNCTIONS TO HANDLE MESSAGE PRESENTATION PARTS
        // A message presentation part is an attachment of the message root from
        // technical point of view. 
        
        /**
        * Create attachment entry and copy specified file to binary file storage.
        * User should call SaveMessageL afterwards to update TMsvEntry of the 
        * message entry. This method tries to solve the attachment's mime
        * content type, but it is not quaranteed that it is successful.
        * @param aAttachmentId returned ID of the new attachment entry
        * @param aFullPath Filename of the attachment to be added
        */
        virtual void CreateAttachment2L(
            TMsvId& aAttachmentId,
            const TDesC& aFullPath );

        /**
        * Create text/plain attachment.
        * @param aAttachmentId returned ID of the new attachment entry
        * @param aText UNICODE text to be added as a text/plain attachment.
        */
        virtual void CreateTextAttachmentL(
            TMsvId& aAttachmentId,
            const TDesC& aText );

        /**
        * Create text/plain attachment. <br>
        * works as previous function, but has option to convert all
        *     unicode paragraph separator marks to line feeds.
        * @param aAttachmentId returned ID of the new attachment entry
        * @param aText UNICODE text to be added as a text/plain attachment.
        * @param aConvertParagraphSeparator flag to tell if the function 
        *     will search for all 0x2029 characters (Unicode paragraph
        *     separator) and replace them with 0x000a (line feed).
        *     aConvertParagraphSeparator == ETrue: convert
        *     aConvertParagraphSeparator == EFalse: do not convert
        */
        virtual void CreateTextAttachmentL(
            TMsvId& aAttachmentId,
            const TDesC& aText,
            TBool aConvertParagraphSeparator);

        /**
        * Create text/plain attachment.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId returned ID of the new attachment entry
        * @param aText UNICODE text to be added as a text/plain attachment.
        * @param aFile attachment text file to be created
        */
        virtual void CreateTextAttachmentL(
            TMsvId& aAttachmentId,
            const TDesC& aText,
            const TDesC& aFile );

        /**
        * Create text/plain attachment.
        * works as previous function, but has option to convert all
        *     unicode paragraph separator marks to line feeds.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId returned ID of the new attachment entry
        * @param aText UNICODE text to be added as a text/plain attachment.
        * @param aFile attachment text file to be created
        * @param aConvertParagraphSeparator flag to tell if the function 
        *     will search for all 0x2029 characters (Unicode paragraph
        *     separator) and replace them with 0x000a (line feed).
        *     aConvertParagraphSeparator == ETrue: convert
        *     aConvertParagraphSeparator == EFalse: do not convert
        */
        virtual void CreateTextAttachmentL(
            TMsvId& aAttachmentId,
            const TDesC& aText,
            const TDesC& aFile,
            TBool aConvertParagraphSeparator);

        // Accessors and mutators for message parts.
        // The base class has attachment and new entry functions.
        // See functions derived from base class.
        
        /**
        * Attachment list accessor.
        * Free the memory of the selection after you do not need it! 
        * Usage of CleanupStack is preferred for this purpose.
        * @return Array of attachment TMsvIds
        *     If there are no attachments, returns a pointer to empty list.
        */
        virtual CMsvEntrySelection* GetAttachmentsL();

        /**
        * Attachment binary file accessor.
        * Leaves with KErrNotFound if attachment not found.        
        * User should free the memory after usage. 
        * @param aAttachmentId TMsvId of the attachment
        * @param aFilePath full path to the binary file of the attachment
        */
        virtual void GetAttachmentPathL( 
            TMsvId aAttachmentId,
            TFileName& aFilePath );

        /**
        * Attachment finding by content-location.
        * User should free the memory after usage.
        * @param aContentLocation Content-Location header for the attachment.
        * @param aFilePath Full path to the binary file of the attachment
        */
        virtual void GetAttachmentPathL( 
            const TDesC& aContentLocation,
            TFileName& aFilePath );

        /**
        * Attachment finding by content-location.
        * User should free the memory after usage.
        * @param aContentLocation Content-Location header for the attachment.
        * @param aFilePath Full path to the binary file of the attachment
        * @param aId TMsvId of the attachment (OUT).
        */
        virtual void GetAttachmentPathAndIdL( 
            const TDesC& aContentLocation,
            TFileName& aFilePath,
            TMsvId& aId );

        /**
        * Attachment finding by content-id.
        * User should free the memory after usage.
        * @param aCid Content-ID header for the attachment.
        * @param aFilePath full path to the binary file of the attachment
        */
        virtual void GetAttachmentPathByCidL( 
            const TDesC8& aCid,
            TFileName& aFilePath );

        /**
        * Attachment finding by content-id.
        * User should free the memory after usage.
        * @param aCid Content-ID header for the attachment.
        * @param aFilePath full path to the binary file of the attachment
        * @param aId TMsvId of the attachment (OUT).
        */
        virtual void GetAttachmentPathAndIdByCidL( 
            const TDesC8& aCid,
            TFileName& aFilePath,
            TMsvId& aId
            );

        /**
        * Content-Location for Attachment
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment
        * @return Content-location (filename without path) of the attachment.
        */
        virtual const TPtrC AttachmentNameL( TMsvId aAttachmentId );

        /**
        * Content-ID for Attachment
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment
        * @return Content-ID (URI) of the attachment.
        */
        virtual const TPtrC8 AttachmentCidL( TMsvId aAttachmentId );

        /**
        * Set Content-Location header for an attachment
        * This is needed, if the presentation part refers to message parts
        *     by content-locations.<br>
        * The location should be a relative URI (filename only). This way it
        *     also functions as a suggestion for the filename for the
        *     recipient.<br>
        * CreateAttachmentL() nor CreateAttachment2L do not set initial value
        *     for this data.<br> 
        * Leaves with KErrAlreadyExists if the content-location value already
        * exists in other attachment of the message.
        * @param aAttachmentId TMsvId of the attachment
        * @param aFilename Content-Location to identify the attachment. 
        *     Suggest a filename for the attachment, if the user wants
        *     to save the attachment in some local folder outside the
        *     messaging system.
        */
        virtual void SetAttachmentNameL( 
            TMsvId aAttachmentId, 
            const TDesC& aFilename );

        /**
        * Set Content-ID header for an attachment
        * This is needed, if the presentation part refers to message parts
        * by cids.<br>
        * Leaves with KErrAlreadyExists if the content-id value already
        * exists in other attachment of the message.<br>
        * Leaves with KErrNotFound if attachment not found.        
        * @param aAttachmentId TMsvId of the attachment
        * @param aCid CID URI to identify the attachment
        */
        virtual void SetAttachmentCidL( 
            TMsvId aAttachmentId, 
            const TDesC8& aCid );

        /**
        * Attachment's MIME content-type accessor. 
        * Leaves with KErrNotFound if attachment not found. 
        * @param aAttachmentId TMsvId of the attachment
        * @return MIME type of the attachment
        */
        virtual const TPtrC8 AttachmentTypeL( TMsvId aAttachmentId );

        /**
        * Attachment MIME content-type mutator.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment
        * @param aMimeType MIME type of the attachment. The method leaves with
        * KErrNotFound if the length is zero.
        */
        virtual void SetAttachmentTypeL( 
            TMsvId aAttachmentId, 
            TDesC8& aMimeType );

        /**
        * Attachment size accessor.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment
        * @return size of the specified attachment in bytes
        */
        virtual TInt32 AttachmentSizeL( TMsvId aAttachmentId ) const;

        /**
        * Attachment character set accessor.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment
        * @return character set as IANA MIBEnum value
        */
        virtual TUint AttachmentCharsetL( TMsvId aAttachmentId ) const;

        /**
        * Attachment character set mutator.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment
        * @param sCharset character set as IANA MIBEnum value
        */
        virtual void SetAttachmentCharsetL( 
            TMsvId aAttachmentId, 
            TUint aCharset );
        /**
        * Content-Disposition mutator.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment        
        * @param aPath Content-Disposition
        */
        virtual void SetAttachmentContentDispositionL(
            TMsvId aAttachmentId,
            const TDesC8& aPath );

        /**
        * Content-Disposition accessor.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment        
        * @return Content-Disposition
        */
        virtual const TPtrC8 AttachmentContentDispositionL(
            TMsvId aAttachmentId );

        /**
        * Content-Description mutator.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment        
        * @param aPath Content-Description
        */
        virtual void SetAttachmentContentDescriptionL(
            TMsvId aAttachmentId,
            const TDesC8& aPath );

        /**
        * Content-Description accessor.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment        
        * @return Content-Description
        */
        virtual const TPtrC8 AttachmentContentDescriptionL(
            TMsvId aAttachmentId );

        /**
        * Content-Base mutator.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment        
        * @param aPath Content-Base
        */
        virtual void SetAttachmentContentBaseL(
            TMsvId aAttachmentId,
            const TDesC8& aPath );

        /**
        * Content-Base accessor.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment.
        * @return Content-Base
        */
        virtual const TPtrC8 AttachmentContentBaseL(
            TMsvId aAttachmentId );

        /**
        * Content-Disposition parameter array accessor.
        * The array includes parameter names and values so that parameter name is
        * even index and value locates in following odd index.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment          
        * @return Array of parameters and values.
        */
        virtual CDesC8Array& AttachmentContentDispositionParamsL(
            TMsvId aAttachmentId );

        /**
        * X-Type parameter array accssor. 
        * Anything else that is in the header, but not recognised
        * The array includes parameter names and values so that parameter name is
        * even index and value locates in following odd index.
        * Leaves with KErrNotFound if attachment not found.
        * @param aAttachmentId TMsvId of the attachment          
        * @return Array of parameters and values.
        */
        virtual CDesC8Array& AttachmentXTypeParamsL(
            TMsvId aAttachmentId );    


        // ---------------------------------------------------------------------
        // MESSAGE NOTIFICATION FUNCTIONS 

        // You can control the message fetch mode through the 
        // SetMessageFetchState method. In the normal EMmsFetchingOn
        // mode you normally do not need to access notifications, but in other
        // modes you might need to list and access notifications.
        // You can fetch messages one by one by using FetchMessage
        // method instead of FetchAll().

        // Set the context to a message notification and call appropriate
        // accessors. Note that part of the accessors are common methods used
        // for regular messages too. You should not call mutators for 
        // notifications.
        // Valid accessors for notifications:
        // - Sender()
        // - Subject()
        // - MessageClass()
        // - MessageTransferSize()
        // - ExpiryDate()
        // - MessageContentLocation()  
        //
        // The deletion of a message notification is done by the special
        // DeleteNotificationL() method.
        
        /**
        * Get number of MMS Notifications for unfetched messages.<br>
        * If the receiving of Multimedia Messages has been turned off,
        * there may be a number of notifications waiting for processing.<br>
        * When the receiving of messages is turned on again, the UI may want
        * to check the number of pending notifications before giving the
        * "FetchAll" command.
        * @return Number of MMS notifications waiting for processing
        */
        virtual TInt NotificationCount();

        /**
        * Lists all MMS Notifications for unfetched messages.<br>
        * Caller must delete the array when no longer needed.<br>
        * The notifications have similar format as messages, but they
        * contain only MMS headers, and no attachments.<br>
        * Individual fields can be queried the same way as for messages.
        * @return Array of entry IDs of MMS Notifications.
        */
        virtual CMsvEntrySelection* ListNotificationsL();

        /**
        * Actual message size in encoded format.
        * This is valid only for a nofification. X-Mms-Message-Size.
        * @return message size in octets.
        */
        virtual TInt MessageTransferSize() const;

        /**
        * Location of the message.
        * This is valid only for a nofification. X-Mms-Content-Location.
        * @return location of the actual message.
        */
        virtual TPtrC8 MessageContentLocation() const;

        /**
        * Notification Deletion.
        * Leaves if notification not found or illegal message type (KErrNotFound).
        * @param aId notification id
        */
        virtual void DeleteNotificationL( TMsvId aId );

        /**
        * Notification Deletion. 
        * Deletes all notifications.
        */
        virtual void DeleteNotificationsL();

        // ---------------------------------------------------------------------
        // MESSAGE HANDLING FUNCTIONS 

        // NOTE: these are asynchronous functions

        /**
        * Send current message using current service settings.
        *     If current service has not been set (== NULL),
        *     default service is used. <br>
        *     If no current service and no default service, aCompletionStatus
        *     will reflect the error. <br>
        *     The message is moved to OUTBOX folder before starting to send it.
        * @param aCompletionStatus iStatus member of an active object.<br>
        *     It will be set as completed when the request has finished.
        * @return pointer to an operation active object.<br>
        *     If successful, this is an asynchronously completing operation.<br>
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        virtual CMsvOperation* SendL( TRequestStatus& aCompletionStatus );

        /**
        * Send selection of message using current service settings.
        *     If current service has not been set (== NULL),
        *     default service is used. <br>
        *     If no current service and no default service, aCompletionStatus
        *     will reflect the error. <br>
        *     The messages are moved to OUTBOX folder before starting to send them.
        *     All messages must be in the same place originally
        *     (all in drafts, or all in outbox).
        * @param aSelection list of messages to be sent. If list is empty,
        *      nothing is sent.
        * @param aCompletionStatus iStatus member of an active object.<br>
        *     It will be set as completed when the request has finished.
        * @param aSendingTime time at which the message selection is to be sent
        *     given as local time. If aSending time is zero or in the past, the
        *     message is scheduled to be sent as soon as possible.
        * @return pointer to an operation active object.<br>
        *     If successful, this is an asynchronously completing operation.<br>
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        virtual CMsvOperation* SendL(
            CMsvEntrySelection& aSelection,
            TRequestStatus& aCompletionStatus,
            TTime aSendingTime );

        /**
        * Send all unsent MMS messages from outbox using current service
        * settings.<br>
        * This can be used to construct several messages and then send them
        * all, Or it can be used to resend messages, whose sending has failed
        * the first time.<br>
        * THIS IS FOR TESTING PURPOSES ONLY. Deprecated.<br>
        * @param aCompletionStatus iStatus member of an active object.<br>
        *     It will be set as completed when the request has finished.
        * @return pointer to an operation active object.<br>
        *     If successful, this is an asynchronously completing operation.<br>
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        virtual CMsvOperation* SendAllL( TRequestStatus& aCompletionStatus );

        /**
        * Fetch all available MMS messages from current MMSC to inbox.<br>
        * This can be used if the phone has been off, and the user wants
        * to fetch pending messages.<br>
        * If there are postponed notifications, they are all fetched.<br>
        * We have hoped that MMS specs would support telling MMSC that 
        * it should send new notifications for all pending messages. 
        * However, for the time being this is not possible.
        * @param aCompletionStatus iStatus member of an active object.<br>
        *     It will be set as completed when the request has finished.
        * @return pointer to an operation active object.<br>
        *     If successful, this is an asynchronously completing operation.<br>
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        virtual CMsvOperation* FetchAllL( TRequestStatus& aCompletionStatus );

        /**
        * Fetch all MMS messages referred by the notification selection 
        * from current MMSC to inbox.<br>
        * This is usefull if manual feching mode is supported and used.<br>
        * @param aSelection selection of notification entries.<br>
        * @param aCompletionStatus iStatus member of an active object.<br>
        *     It will be set as completed when the request has finished.
        * @return pointer to an operation active object.<br>
        *     If successful, this is an asynchronously completing operation.<br>
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        virtual CMsvOperation* FetchL( 
            CMsvEntrySelection aSelection,
            TRequestStatus& aCompletionStatus );

        /**
        * Fetch specified MMS messages from current MMSC to inbox.<br>
        * @param aId Entry ID of a notification that refers to an
        *     unfetched message.
        * @param aCompletionStatus iStatus member of an active object.<br>
        *     It will be set as completed when the request has finished.
        * @return pointer to an operation active object.<br>
        *     If successful, this is an asynchronously completing operation.<br>
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        virtual CMsvOperation* FetchMessageL(
            TMsvId aId,
            TRequestStatus& aCompletionStatus );

        /**
        * Delete expired notifications.<br>
        * Notifications may be in inbox, in documents folder or some 
        * folder that is a child of the documents folder. Document folder 
        * is a child of local service. In automatic mode the notifications 
        * may also be under the service entry. <br>
        * The function schedules the deletion to be done by server mtm 
        * under control of Task Scheduler. This way the control returns to 
        * the caller as fast as possible. <br>
        * This may lead to strange race conditions, it must be very 
        * carefully tested.
        * @param aCompletionStatus iStatus member of an active object.<br>
        *     It will be set as completed when the request has finished.
        * @return pointer to an operation active object.<br>
        *     If successful, this is an asynchronously completing operation.<br>
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        virtual CMsvOperation* DeleteExpiredNotificationsL(
            TRequestStatus& aCompletionStatus );


        
    public:  // FUNCTIONS FROM BASE CLASSES

        /**
        * From CBaseMtm: Return type of this Mtm
        * @return Registered Mtm type
        */
        inline TUid Type() const;

        /**
        * From CBaseMtm: Return session that was set at initialization
        * @return Reference to session object
        */
        inline CMsvSession& Session();
        
        // Context specific functions

        /**
        * From CBaseMtm: Set current context
        * @param aEntry Pointer to entry instance
        */
        inline void SetCurrentEntryL( CMsvEntry* aEntry );        

        /**
        * From CBaseMtm: Switch context to entry defined by aId.
        * @param aId Entry id in message store.
        */
        inline void SwitchCurrentEntryL( TMsvId aId );
        
        /**
        * From CBaseMtm: return reference to current entry
        * @return reference to entry instance
        */
        inline CMsvEntry& Entry() const;
        
        /**
        * From CBaseMtm: Query if entry context has been set
        * @return ETrue, if context has been set, EFalse, if not
        */
        inline TBool HasContext() const;

        
        // Message specific functions

        /**
        * From CBaseMtm: Store current entry data.
        */
        void SaveMessageL(); 

        /**
        * From CBaseMtm: Restore current entry data.
        */
        void LoadMessageL();

        /**
        * From CBaseMtm: Send a reply to current message 
        * @param aDestination Id for the new message entry.
        * @param aPartlist Flags specifying which standard message parts
        *     are to be included in the response.<br>
        * @param aPartlist Flags specifying which standard message parts
        *     are to be included in the response.<br>
        *     (defined in MTMDEF.H) <br>
        *     KMsvMessagePartPartBody is ignored <br>
        *     KMsvMessagePartRecipient causes reply-to-all. 
        *        Otherwise reply-to-sender only. <br> 
        *     KMsvMessagePartOriginator is ignored.<br>
        *     KMsvMessagePartDescription copies Subject field. <br>
        *     KMsvMessagePartDate is ignored. <br>
        *     KMsvMessagePartAttachments is ignored.<br>
        * @param aCompletionStatus Reference to the status of
        *     an active object.<br>
        *     This status will be set as completed when the operation completes.
        * @return Pointer to a message server operation (active object). <br>
        *     The progress information provides the id of the created message 
        *     when the message has been created in a 8-bit descriptor. 
        *     While the operation is in progress the package will contain a null 
        *     id (KMsvNullIndexEntryId). If there was an error while creating 
        *     the message, then the message will be deleted and the package will 
        *     contain null id.
        */
        CMsvOperation* ReplyL(
            TMsvId aDestination,
            TMsvPartList aPartlist,
            TRequestStatus& aCompletionStatus );
        
        /**
        * From CBaseMtm: Forward current message to new recipient
        * @param aDestination Id for the new message entry.
        *     to be included in the response.<br>
        *     (defined in MTMDEF.H) <br>
        * @param aPartlist Flags specifying which standard message parts
        *     are to be included in the response.<br>
        *     KMsvMessagePartPartBody is ignored <br>
        *     KMsvMessagePartRecipient is ignored. <br>
        *     KMsvMessagePartOriginator is ignored.<br>
        *     KMsvMessagePartDescription copies Subject field.<br>
        *     KMsvMessagePartDate is ignored.<br>
        *     KMsvMessagePartAttachments is ignored. <br>
        * @param aCompletionStatus Reference to the status of
        *     an active object.<br>
        *     This status will be set as completed when the operation completes.
        * @return Pointer to message server operation (active object). <br>
        *     The progress information provides the id of the created message 
        *     when the message has been created in a 8-bit descriptor. 
        *     While the operation is in progress the package will contain a null 
        *     id (KMsvNullIndexEntryId). If there was an error while creating 
        *     the message, then the message will be deleted and the package will 
        *     contain null id.
        */
        CMsvOperation* ForwardL(
            TMsvId aDestination,
            TMsvPartList aPartList,
            TRequestStatus& aCompletionStatus );
        
        /**
        * From CBaseMtm: Validates that selected parts of current message are
        *     legal.
        * @param aPartList Flags specifying which parts to validate.<br>
        *     (defined in MTMDEF.H).<br>
        *     KMsvMessagePartPartBody is ignored <br>
        *     KMsvMessagePartRecipient is supported.  <br>
        *     KMsvMessagePartOriginator is supported. <br>
        *     KMsvMessagePartDescription is ignored. <br>
        *     KMsvMessagePartDate is ignored. <br>
        *     KMsvMessagePartAttachments is supported. <br>
        * @return Flags that specify which or the specified parts were valid.
        */
        TMsvPartList ValidateMessage( TMsvPartList aPartList );
        
        /**
        * From CBaseMtm: Searches for specified text in selected parts of
        * current message.
        * @param aPartList Flags specifying which parts to search.<br>
        *     (defined in MTMDEF.H). <br>
        *     KMsvMessagePartPartBody is ignored <br>
        *     KMsvMessagePartRecipient is supported.  <br>
        *     KMsvMessagePartOriginator is supported. <br>
        *     KMsvMessagePartDescription is supported. <br>
        *     KMsvMessagePartDate is ignored. <br>
        *     KMsvMessagePartAttachments is ignored . <br>
        * Following find attributes are supported: <br>
        *     KMsvFindCaseSensitive
        *     KMsvFindWholeWord
        * @return Flags that specify in which of the specified parts the text
        *     was found.
        */
        TMsvPartList Find( const TDesC& aTextToFind, TMsvPartList aPartList );

        /**
        * From CBaseMtm: Returns list of addressees in current entry to
        * callers that do not understand details of Mtm type.<br>
        * Returns all addressees (To, Cc, Bcc).
        * @return Array of addresses (as text strings)
        */
        inline const CDesCArray& AddresseeList();

        /**
        * From CBaseMtm: Adds an addressee. Cannot distiguish To, Cc, and Bcc.
        * New addresses are handled as To type of addresses.
        * @param aRealAddress Reference to an address string
        */
        void AddAddresseeL( const TDesC& aRealAddress );
        
        /**
        * From CBaseMtm: Adds an addressee. Cannot distiguish To, Cc, and Bcc.
        * New addresses are handled as To type of addresses. 
        * @param aRealAddress Reference to an address string
        * @param aAlias Reference to a descriptive name (not a real address)
        */
        void AddAddresseeL( const TDesC& aRealAddress, const TDesC& aAlias );
        
        /**
        * From CBaseMtm: Removes an entry from addressee list.
        *     Cannot distinguish To, Cc and Bcc.
        * @param aIndex Index to the array of addresses.
        */
        void RemoveAddressee( TInt aIndex );

        /**
        * From CBaseMtm: Sets the message subject
        * @param aSubject Subject as text string.
        */
        void SetSubjectL( const TDesC& aSubject );
        
        /**
        * From CBaseMtm: Subject accessor
        * @return Constant pointer descriptor pointing to subject
        */
        const TPtrC SubjectL() const;

        // Note: rich text body not supported in MMS Message encapsulation.
        
        /**
        * From CBaseMtm Rich text body accessor
        * @return reference to the rich text body
        */
        inline CRichText& Body();

        /**
        * From CBaseMtm Rich text body accessor
        * @return reference to the rich text body
        */
        inline const CRichText& Body() const;

        /**
        * From CBaseMtm: Create attachment entry.
        * @param aAttachmentId returned ID of the new attachment entry
        * @param aDirectory Directory where to add a file.
        */
        void CreateAttachmentL(
            TMsvId& aAttachmentId,
            TFileName& aDirectory );

        /**
        * From CBaseMtm: Remove specified attachment from the message<br>
        * The attachment is deleted from the current entry
        * (aMessageId is not used).
        * User should call SaveMessageL afterwards to update TMsvEntry of 
        * the message entry.
        * @param aMessageId Not used by default implementation
        * @param aAttachmentId ID of the attachment to be removed
        */
        void DeleteAttachmentL(
            TMsvId aMessageId,
            TMsvId aAttachmentId );

        /**
        * From CBaseMtm: Create an empty entry in the outbox<br>
        * and set it as current context.<br>
        * The entry will be invisible and under construction.
        * @param aServiceId Service id for the new entry.
        */
        void CreateMessageL( TMsvId aServiceId );


        // General MTM-specific functionality

        /**
        * From CBaseMtm:
        * @param aCapability Uid specifying which capablity is queried
        * @param aResponse reference to an integer that will contain the value
        *     describing the capability at return.
        * @return error code, KErrNone, if specified capability is known
        *     to Mtm,<br>
        *     KErrNotSupported, if capability Uid is unknown
        */
        TInt QueryCapability( TUid aCapability, TInt& aResponse );
        
        /**
        * From CBaseMtm: Pass a function code to Server MTM, wait until the
        *     function returns. This function should be used to
        *     invoke synchronous protocol-specific operations.
        * @param aFunctionId An enumeration constant defining the operation
        *     to be performed.<br>
        *     (available function codes defined in MMSCONST.H)
        * @param aSelection Array of message entry ids to be operated on.<br>
        *     First must be a service id unless a default service for this
        *     MTM type has been defined.
        * @param aParameter Reference to a descriptor that contains any
        *     parameter required by function specified by aFunctionId.
        */
        void InvokeSyncFunctionL(
            TInt aFunctionId,
            const CMsvEntrySelection& aSelection,
            TDes8& aParameter );
        
        /**
        * From CBaseMtm: Pass a function code to Server MTM to invoke an
        *     asychronous function. This function should be used to
        *     invoke asynchronous protocol-specific operations.
        * @param aFunctionId An enumeration constant defining the operation
        *     to be performed<br>
        *     (available function codes defined in MMSCONST.H)
        * @param aSelection Array of message entry id's to be uperated on.<br>
        *     First must be a service id unless a default service for this
        *     MTM type has been defined.
        * @param aParameter Reference to a descriptor that contains any
        *     parameter required by function specified by aFunctionId.
        * @param aCompletionStatus Reference to the status
        *     of an active object.<br>
        *     This status will be set as completed when the operation completes.
        * @return Pointer to a message server operation (active object).<br>
        *     If successful, this is an asynchronously completing
        *     operation.<br>
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        CMsvOperation*  InvokeAsyncFunctionL(
            TInt aFunctionId,
            const CMsvEntrySelection& aSelection,
            TDes8& aParameter,
            TRequestStatus& aCompletionStatus );
        
        
    protected:  // New functions


    protected:  // Functions from base classes
        
        /**
        * From CBaseMtm: Called after the context of this instance
        * has been changed to another entry.
        */
        void ContextEntrySwitched();

        /**
        * From CBaseMtm: React to changes 
        * @param aEvent Code that tells which event has occurred.<br>
        *     Event codes defined in MSVAPI.H
        * @param arg1 Depends on Event
        * @param arg2 Depends on Event
        * @param arg3 Depends on Event
        */
        void HandleEntryEventL(
            TMsvEntryEvent aEvent,
            TAny* arg1,
            TAny* arg2,
            TAny* arg3 );

        /**
        * By default Symbian OS constructor is private.
        * @param aRegisteredMtmDll Reference to Mtm Dll registry class
        * @param aSession Reference to a Message Server session.
        */
        CMmsClientMtm(
            CRegisteredMtmDll& aRegisteredMtmDll,
            CMsvSession& aSession );

        void ConstructL();
        
    private:


        /**
        * Create invisible empty service entry
        * @return Id of the new service entry
        */
        TMsvId DoCreateServiceL();

        
        // This function is needed until service handling is complete.
        // As long as real service has not been defined, this function
        // sets up a fake service in order to allow Server MTM to be loaded.
        // (Server MTM cannot run without a service entry)
        // After a decent service has been defined the function should only
        // check the existence of a service, and if no service exists,
        // the function should inform the caller that a service
        // must be set up before we can proceed.
        /**
        * Check that a service exists.
        * @return ETrue a service exists, false if not
        */
        TBool ServiceExistsL();

        /**
        * This method builds the iAddresseeList from the iMmsHeaders data.
        */
        void BuildAddresseeListL();

        /**
        * This methods adds entries from the the specified array to iAddresseeList.
        * @param aArray recipient array.
        */
        void BuildAddresseeListL(
            const CDesCArray& aArray ); 

        /**
        * Attachments size
        */
        TInt32 AttachmentsSize();

        /**
        * Check that the current entry is service entry
        * @return EFlase if not service entry.
        */
        TBool IsThisService() const;

        /**
        * Check that the current entry is notification entry
        * @return EFlase if not notification.
        */
        TBool IsThisNotification() const;

        /**
        * Validate a single address field.
        * The address must be valid EMail address or MMS global phone number.
        * @param anAddress address to be validated.
        * @return ETrue if valid address
        */
        TBool ValidateAddress( const TPtrC& anAddress ) const;

        /**
        * List notificatins.
        * Now the locates under Service entry, but they may be in INBOX in future.
        * @return selection of notifications
        */
        CMsvEntrySelection* DoListNotificationsL();

        /**
        * Convert date time from UTC to local time.
        * @param aDate UTC date time
        * @return local time
        */
        TInt64 ConvertUTCDateToLocal( TInt64 aDate ) const;

        /**
        * Restore MMSC settings into iMmsSettings cache.<br>
        * The values are used when new entries are created.
        * @param aServiceId id of the service entry wanted.
        * @return ETrue, if service found, EFalse, if not found.
        */
        TBool RestoreSettingsL( TMsvId aServiceId );

        /**
        * Delete all MMS messages from the message server.
        * @param aFolder folder where to delete messages
        */
        void DoDeleteMessagesL( TMsvId aFolder );

        // AddEventTypeL not used, as it causes a stray
        // event if log database does not exist. MMS Server
        // Mtm must take care of adding log event type.
        /**
        * Add MMS event type to Log engine.
        */
        /*
        void AddEventTypeL();
        */

        /**
        * Do the entry selection for fetch operation. 
        * This places the MMS service entry as the first element
        * in the given selection.
        * @param aSelection entry selection where to add service element
        */
        void MakeEntrySelectionL( CMsvEntrySelection& aSelection );

        /**
        * Convert Unicode Paragraph separators (0x2029) to line feeds (0x000a)
        * @param aText text to convert
        * @return pointer to buffer containing the converted text. <br>
        *     caller must delete the buffer.
        */
        HBufC* ConvertParagraphSeparatorsL( const TDesC& aText );

        /**
        * Find the folder where MMS messages are to be stored
        */
        TMsvId FindMMSFolderL();

    public:     // Data

    
    protected:  // Data
        CMmsSettings* iMmsSettings;  // MMSC settings (access point etc.)
        CMmsMessage*  iMmsMessage;   // Msg wrapper to access attachments etc.
        TMsvId        iServiceId;    // last selected service
        HBufC*        iAddressOpen;  // address separator begin characters
        HBufC*        iAddressClose; // address separator close characters 
        TBool         iFetchAll;     // All the messages are fetched when a service
                                     // is saved after certain fetch mode change.                                   // for 
        TBool         iFetchOverride; // if switching from deferred to on, 
                                     // force fetching all messages. If switching from
                                     // Automatic at home to always automatic, send acks to
                                     // MMSC, but fetch only if mode is On (not off or deferred)
        TInt          iMessageDrive; // messages are on C: drive by default,
                                     // may be moved to other drive

    private:    // Data

    public:     // Friend classes

    protected:  // Friend classes

    private:    // Friend classes

    };

// panic function 
GLREF_C void gPanic( TMmsPanic aPanic );

#include "mmsclient.inl"

#endif      // MMSCLIENT_H   
            
// End of File

// End of File
