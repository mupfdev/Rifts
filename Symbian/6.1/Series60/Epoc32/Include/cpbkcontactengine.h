/*
* ============================================================================
*  Name     : CPbkContactEngine.h from PbkEng.dll
*  Part of  : PbkEng.dll
*
*  Description:
*     Represents a connection to the Phonebook contact database
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
* ============================================================================
*/

#ifndef __CPbkContactEngine_H__
#define __CPbkContactEngine_H__

//  INCLUDES
#include <e32base.h>        // CBase
#include <cntdef.h>         // TContactItemId
#include <cntdbobs.h>       // MContactDbObserver
#include <f32file.h>        // RFs
#include "PbkFields.hrh"    // TPbkFieldId


// FORWARD DECLARATIONS
class CContactDatabase;
class MIdleFindObserver;
class MPbkContactDbObserver;
class CContactGroup;
class CPbkFieldsInfo;
class CPbkContactItem;
class CPbkContactIter;
class CPbkContactChangeNotifier;
class CPbkIdleFinder;
class MPbkCompressUi;
class CPbkConstants;
class MPbkContactNameFormat;
class MPbkFieldDataArray;
class MPbkContactDbEventFilter;
class CContactViewBase;
class CContactItem;
class RSharedDataClient;


// CLASS DECLARATION

/**
 * Phonebook engine.
 * Represents a connection to the Phonebook contact database.
 */
class   CPbkContactEngine :
        public CBase, 
        private MContactDbObserver
    {
    public: // Constructors and destructor
        /**
         * Creates a new Phonebook engine object and connects to the default 
         * contact database. If the default database does not exist it is 
         * created.
         *
         * @param aFs   An open file server connection. If !=NULL aFs is used 
         *              instead of a locally created RFs connection. aFs must
         *              remain connect for the lifetime of the returned object.
         * @return a new instance of this class.
         * @exception KErrCorrupt if the database is corrupted.
         */
		IMPORT_C static CPbkContactEngine* NewL(RFs* aFs=NULL);

        /**
         * @internal
         * TESTING ONLY
         * Creates a new engine object and connects it to a specified 
         * database file. If the database file does not exist it is created.
         *
         * @param aFileName the database filename.
         * @param aReplace  if ETrue replaces exisiting file with an empty one.
         *                  PLEASE NOTE: all data in the existing file 
         *                  will be lost!!!
         * @param aFs   An open file server connection. If !=NULL aFs is used 
         *              instead of a locally created RFs connection. aFs must
         *              remain connected for the lifetime of the returned object.
         * @return a new instance of this class.
         * @exception KErrCorrupt if the database is corrupted.
         */
		IMPORT_C static CPbkContactEngine* NewL
            (const TDesC& aFileName, TBool aReplace=EFalse, RFs* aFs=NULL);

        /**
         * Replaces the database file and connect to it.
         *
         * @param aFs   An open file server connection. If !=NULL aFs is used 
         *              instead of a locally created RFs connection. aFs must
         *              remain connect for the lifetime of the returned object.
         * @return a new instance of this class.
         */
        IMPORT_C static CPbkContactEngine* ReplaceL(RFs* aFs=NULL);

        /**
         * Destructor. Destroys this object and closes the contact database
         * connection.
         */
		~CPbkContactEngine();
		
    public: // Accessors
        /**
         * Returns the global Phonebook engine instance, NULL if no instance
         * created yet.
         * Note1: Uses thread local storage (TLS), which is slow. Cache the
         * returned pointer if it is used more than one time!
         * Note2: Only the first engine instance created in calling thread can
         * be accessed with this function.
         */
        IMPORT_C static CPbkContactEngine* Static();

        /**
         * Returns the CContactDatabase object. Use only if this class's API
         * is not enough for your purposes.
         *
         * @see CContactDatabase
         */
        IMPORT_C CContactDatabase& Database();

        /**
         * Returns the field type info array.
         *
         * @see CPbkFieldsInfo
         */
        IMPORT_C const CPbkFieldsInfo& FieldsInfo();

        /**
         * Returns an open file server session.
         */
        IMPORT_C RFs& FsSession() const;
       
    public:  // Creating contacts
        /**
         * Returns a new contact card with default fields.
         */
        IMPORT_C CPbkContactItem* CreateEmptyContactL();

         /**
          * Adds a new contact to the contact database.
          *
          * @param aContact         the new contact item to add.
          * @param aImmediateNotify send notification to observers immediately.
          *                         NOTE: send immediately will result in 
          *                         observers (MPbkContactDbObserver) receiving
          *                         the event twice!
          * @return the id of the new contact item.
          * @see CContactDatabase::AddNewContactL
          */
        IMPORT_C TContactItemId AddNewContactL
            (CPbkContactItem& aContact, TBool aImmediateNotify=EFalse);

        /**
         * Duplicates a contact in the database.
         *
         * @param aId               id of the contact to duplicate.
         * @param aImmediateNotify  send notification to observers immediately.
         *                          NOTE: send immediately will result in 
         *                          observers (MPbkContactDbObserver) receiving
         *                          the event twice!
         * @return  contact id of the new duplicate.
         */
        IMPORT_C TContactItemId DuplicateContactL
            (TContactItemId aId, TBool aImmediateNotify=EFalse);

    public:  // Reading contacts
        /**
         * Reads a contact and returns a phonebook contact item.
         *
         * @param aContactId Contact item id to be read.
         * @param aFieldTypes   array of types of fields to read in, all
         *                      fields are read if NULL (which is default).
         *                      NOTE: when using this parameter ReadContactL
         *                      may return more field than expected; for example
         *                      if aFieldTypes contains any phonenumber the 
         *                      method may return all phone number fields
         *                      of the contact.
         * @return a new Phonebook contact item.
         * @see CContactDatabase::ReadContactL
         */
        IMPORT_C CPbkContactItem* ReadContactL
            (TContactItemId aContactId, const CPbkFieldIdArray* aFieldTypes=NULL);

        /**
         * Sames as ReadContactL, but leaves the returned contact item
         * on the cleanup stack.
         */
        IMPORT_C CPbkContactItem* ReadContactLC
            (TContactItemId aContactId, const CPbkFieldIdArray* aFieldTypes=NULL);

        /**
         * Same as ReadContactLC but reads only minimal information. See 
         * Contact Model documentation for definition of "minimal" in this
         * case.
         *
         * @param aContactId Contact item id to be read.
         * @return a new phonebook contact item. Leaves the item on the cleanup stack.
         * @see CContactDatabase::ReadMinimalContactL
         */
        IMPORT_C CPbkContactItem* ReadMinimalContactLC(TContactItemId aContactId);

        /**
         * Returns a Phonebook contact iterator.
         * @see CPbkContactIter::NewL.
         */
        IMPORT_C CPbkContactIter* CreateContactIteratorLC
            (TBool aUseMinimalRead=EFalse);

    public:  // Modifying contacts
        /**
         * Opens a contact and returns a phonebook contact item.
         * @param aContactId Contact item id to be opened.
         * @return a new Phonebook contact item.
         * @see CContactDatabase::OpenContactL
         */
        IMPORT_C CPbkContactItem* OpenContactL(TContactItemId aContactId);
        
        /**
         * Same as OpenContactL, but leaves a lock record AND the opened
         * contact object on the cleanup stack.
         * Use CleanupStack::PopAndDestroy(2) to close the contact and destroy
         * the returned object. First pop pops the contact object and second
         * the lock object.
         * @see CContactDatabase::OpenContactLX
         */
        IMPORT_C CPbkContactItem* OpenContactLCX(TContactItemId aContactId);

        /**
         * Commit changes to a previously opened contact item into the contact
         * database.
         *
         * @param aContact          contact item to be updated in the database.
         * @param aImmediateNotify  send notification to observers immediately.
         *                          NOTE: send immediately will result in 
         *                          observers (MPbkContactDbObserver) receiving
         *                          the event twice!
         * @see CContactDatabase::CommitContactL
         */
        IMPORT_C void CommitContactL
            (CPbkContactItem& aContact, TBool aImmediateNotify=EFalse);

        /**
         * Closes a previously opened contact item without saving changes.
         * @param aContactId contact item to be closed.
         * @see CContactDatabase::CloseContactL
         */
    	IMPORT_C void CloseContactL(TContactItemId aContactId);

    public:  // Deleting contacts
        /**
         * Deletes a contact item from the database.
         * @param aContactId    contact item to be deleted.
         * @param aImmediateNotify  send notification to observers immediately.
         *                          NOTE: send immediately will result in 
         *                          observers (MPbkContactDbObserver) receiving
         *                          the event twice!
         * @see CContactDatabase::DeleteContactL
         */
    	IMPORT_C void DeleteContactL
            (TContactItemId aContactId, TBool aImmediateNotify=EFalse);

        /**
         * Deletes multiple contact items from the database.
         * @param aContactIds    contact items to be deleted.
         * @param aImmediateNotify  send notification to observers immediately.
         *                          NOTE: send immediately will result in 
         *                          observers (MPbkContactDbObserver) receiving
         *                          the event twice!
         * @see CContactDatabase::DeleteContactsL
         */
    	IMPORT_C void DeleteContactsL
            (const CContactIdArray& aContactIds, TBool aImmediateNotify=EFalse);

        /**
         * Deletes multiple contacts from the database in an active object 
         * -driven asynchronous background process.
         *
         * @param aContactIds   contacts to delete.
         */
        IMPORT_C void DeleteContactsOnBackgroundL
            (const CContactIdArray& aContactIds);

    public:  // Contact groups
        /**
         * Creates a new Contact group.
         *
         * @param aGroupLabel group name.
         * @param aInTransaction see Contact Model documentation.
         * @see CContactDatabase::CreateContactGroupL
         */
        IMPORT_C CContactGroup* CreateContactGroupL
            (const TDesC& aGroupLabel,TBool aInTransaction=EFalse);

        /**
         * Adds a Contact to a group.
         *
         * @param aItemId   Contact to be added to group.
         * @param aGroupId  Group where the contact will be added to.
         * @see CContactDatabase::AddContactToGroupL
         */
    	IMPORT_C void AddContactToGroupL
            (TContactItemId aItemId, TContactItemId aGroupId);

        /**
         * Removes a contact from a group
         *
         * @param aItemId   Contact to be removed from group.
         * @param aGroupId  Group where the contact will be removed from.
         * @see CContactDatabase::RemoveContactFromGroupL
         */
    	IMPORT_C void RemoveContactFromGroupL
            (TContactItemId aItemId, TContactItemId aGroupId);

        /**
         * Reads a Contact group.
         *
         * @param aId group id.
         * @return contact group object.
         * @see CContactDatabase::ReadContactL
         */
        IMPORT_C CContactGroup* ReadContactGroupL(TContactItemId aId);

        /**
         * Opens a Contact group for modification.
         *
         * @param aId groups id
         * @return contact group object.
         * @see CContactDatabase::OpenContactL
         */
        IMPORT_C CContactGroup* OpenContactGroupL(TContactItemId aId);

        /**
         * Opens a Contact group for modification. Pushes the returned 
         * contact group object and a lock item on the cleanup stack.
         *
         * @param aId groups id
         * @return contact group object.
         * @see CContactDatabase::OpenContactLX
         */
        IMPORT_C CContactGroup* OpenContactGroupLCX(TContactItemId aId);

        /**
         * Commits changes to a contact group to the database.
         *
         * @param aId groups id
         * @param aImmediateNotify  send notification to observers immediately.
         *                          NOTE: send immediately will result in 
         *                          observers (MPbkContactDbObserver) receiving
         *                          the event twice!
         * @see CContactDatabase::CommitContactL
         */
        IMPORT_C void CommitContactGroupL(CContactGroup& aGroup, TBool aImmediateNotify=EFalse);

        /**
         * Deletes a contact group from the database.
         * @param aContactId    contact group to be deleted.
         * @param aImmediateNotify  send notification to observers immediately.
         *                          NOTE: send immediately will result in 
         *                          observers (MPbkContactDbObserver) receiving
         *                          the event twice!
         * @see CContactDatabase::DeleteContactL
         */
        IMPORT_C void DeleteContactGroupL
            (TContactItemId aContactId, TBool aImmediateNotify=EFalse);

    public:  // Speed dials
        /**
         * Sets a speed dial to a contact field.
         *
         * @param aItem         contact item to add speed dial to. 
         * @param aFieldIndex   field index to add Speed dial to.
         * @param aSpeedDialPosition    speed dial position number to set to 
         *                              the field.
         * @see CContactDatabase::SetFieldAsSpeedDialL
         */
        IMPORT_C void SetFieldAsSpeedDialL
            (CPbkContactItem& aItem, TInt aFieldIndex, TInt aSpeedDialPosition);

        /**
         * Returns a speed dial contact. 
         *
         * @param   aSpeedDialPosition  speed dial position number.
         * @param   aPhoneNumber        phone number
         * @see CContactDatabase::GetSpeedDialFieldL.
         */
      	IMPORT_C TContactItemId GetSpeedDialFieldL
            (TInt aSpeedDialPosition, TDes& aPhoneNumber) const;

        /**
         * Removes a speed dial from a contact.
         *
         * @param   aContactId  contact item to remove the speed dial from.
         * @param   aSpeedDialPosition  speed dial position number to remove.
         * @see CContactDatabase::RemoveSpeedDialFieldL.
         */
    	IMPORT_C void RemoveSpeedDialFieldL
            (TContactItemId aContactId, TInt aSpeedDialPosition);

        /**
         * Returns true if this field has been assigned a speed dial position.
         *
         * @param aItem contact item to check for speed dial.
         * @param aFieldIndex   index of the field to check. This is an index 
         *                      into aItem.CardFields().
         * @return  ETrue if Speed dial exitst, EFalse if not.
         */
        IMPORT_C TBool IsSpeedDialAssigned
            (const CPbkContactItem& aItem, TInt aFieldIndex) const;

    public:  // Contact views
        /**
         * Returns a contact view object containing all the contacts in the
         * database.
         * 
         * @see CContactViewBase
         */
        IMPORT_C CContactViewBase& AllContactsView();

        /**
         * Returns a contact view object containing all the groups in the
         * database.
         * 
         * @see CContactViewBase
         */
        IMPORT_C CContactViewBase& AllGroupsViewL();

        /**
         * Returns a contact view object containing all the contacts in the 
         * database that match a filter.
         *
         * @param aFilter   use CContactDatabase::TContactViewFilter.
         * @see CContactViewBase
         */
        IMPORT_C CContactViewBase& FilteredContactsViewL(TInt aFilter);
    
    public:  // Events
        /**
         * Creates and returns a new CPbkContactChangeNotifier for the
         * default contact database. The returned object attaches aObserver
         * to this engine instance as long as the object exists. 
         *
         * @param aObserver observer to attach to this object.
         * @return  new CPbkContactChangeNotifier object. Caller is responsible
         *          of the object.
         * @see CPbkContactChangeNotifier
         * @see MPbkContactDbObserver
         */
        IMPORT_C CPbkContactChangeNotifier* CreateContactChangeNotifierL
            (MPbkContactDbObserver* aObserver);

        /**
         * Registers an event filter which is called to decide which events are
         * forwarded to this object's observers. 
         * <b>NOTE:</b> Filtering affects only observers of this object. 
         * Observers attached directly to CContactDatabase (including any other
         * instances of this class) receive events normally.
         *
         * @param aFilter   event filter. Set to NULL to stop filtering.
         * @return  previously registered event filter or NULL if none set.
         */
        MPbkContactDbEventFilter* SetEventFilter
            (MPbkContactDbEventFilter* aFilter);

    public:  // Contact name formatting
        /**
         * Gets a title text for a contact or localised text for unnamed
         * contact if contact contains no title.
         *
         * @param   aItem   contact item for which to make the title.
         * @return  a buffer containing the title or unnamed text if no title
         *          can be generated. Caller is responsible of deleting the 
         *          returned buffer.
         */
        IMPORT_C HBufC* GetContactTitleL(const CPbkContactItem& aItem) const;

        /**
         * Same as GetContactTitleL but returns NULL if contact contains no
         * title.
         *
         * @see CPbkContactEngine::GetContactTitleL
         */
        IMPORT_C HBufC* GetContactTitleOrNullL
            (const MPbkFieldDataArray& aContactData);

        /**
         * Returns ETrue if field is one of the fields used in building the
         * contact title.
         *
         * @param   aFieldId    id of field.
         * @return  ETrue if aFieldId is type of a field used to build contact
         *          titles.
         * @see GetContactTitle
         * @see GetContactTitleOrNullL
         */ 
        IMPORT_C TBool IsTitleField(TPbkFieldId aFieldId) const;

        /**
         * @internal
         * Returns the contact name formatter.
         *
         * @see MPbkContactNameFormat
         */
        IMPORT_C MPbkContactNameFormat& ContactNameFormat() const;

        /**
         * Returns the localised title text to use for unnamed contacts.
         */
        IMPORT_C const TDesC& UnnamedTitle() const;

    public: // Searching
        /**
         * Call-through for new Phone number matching function in 6.2 version
         * of class CContactDatabase. If you don't need any other functionality
         * from CPbkContactEngine than this consider using the CContactDatabase
         * API directly. See Contact Model documentation for how to use.
         *
         * @see CContactDatabase::MatchPhoneNumberL(const TDesC&,const TInt)
         */
        IMPORT_C CContactIdArray* MatchPhoneNumberL
            (const TDesC& aNumber, const TInt aMatchLengthFromRight);

        /**
         * Searches all contacts in the database for aText.
         *
         * @param aText         text to search.
         * @param aFieldTypes   Phonebook fields types to <i>at least</i> 
         *                      include in the search. If NULL searches all 
         *                      fields.<br>
         *                      <b>PLEASE NOTE:</b> The find matches in most 
         *                      cases also other fields than those specified 
         *                      in aFieldTypes. Always loop through the 
         *                      returned contacts to check match in the 
         *                      required fields.
         * @return array of matching contact IDs.
         * @see CContactDatabase::FindLC.
         */
        IMPORT_C CContactIdArray* FindLC
            (const TDesC& aText, const CPbkFieldIdArray* aFieldTypes=NULL);

        /**
         * Searches all contacts in the database for aText asynchronously.
         *
         * @param aText         text to search.
         * @param aFieldTypes   Phonebook fields types to <i>at least</i> 
         *                      include in the search. If NULL searches all 
         *                      fields.<br>
         *                      <b>PLEASE NOTE:</b> The find matches in most 
         *                      cases also other fields than those specified 
         *                      in aFieldTypes. Always loop through the 
         *                      returned contacts to check match in the 
         *                      required fields.
         * @param  aObserver    observer for this operation.
         * @return  CPbkIdleFinder object which is used to access the find
         *          results when complete.
         * @see CContactDatabase::FindAsyncL.
         * @see CPbkIdleFinder
         */
	    IMPORT_C CPbkIdleFinder* FindAsyncL(
            const TDesC& aText,
            const CPbkFieldIdArray* aFieldTypes=NULL, 
            MIdleFindObserver *aObserver=NULL);

    public:  // Phonebook internal API
        /**
         * @internal
         * Sets the compression UI for this engine.
         * To be called by Phonebook only!
         *
         * @see MPbkCompressUi
         * @see CheckCompress
         * @see CancelCompress
         */
        IMPORT_C void SetCompressUi(MPbkCompressUi* aCompressiUi);

        /**
         * @internal
         * Checks if the contact database needs a compression. 
         * To be called by Phonebook only!
         *
         * @see SetCompressUi
         * @see CompressL
         * @see CancelCompress
         */
        IMPORT_C TBool CheckCompress();

        /**
         * @internal
         * Compresses the database if necessary. To be called by Phonebook only.
         *
         * @see SetCompressUi
         * @see CancelCompress
         */
        IMPORT_C void CompressL();

        /**
         * @internal
         * Call to cancel any ongoing database compression started with
         * CheckCompressL(). Calls PbkCompressCanceled() for any registered 
         * compression UI. To be called by Phonebook only.
         *
         * @see SetCompressUi
         * @see CheckCompress
         */
        IMPORT_C void CancelCompress();

        /**
         * @internal
         * Checks current file system space and amount of wasted space in 
         * Phonebook's database. Compresses the database synchronously if 
         * Phonebook's database can be made smaller by compression. If file 
         * system space is still under critical level after compression,
         * leaves with KErrDiskFull.
         *
         * @exception KErrDiskFull if file system is out of space.
         */
        IMPORT_C void CheckFileSystemSpaceAndCompressL();

    private:  // from MContactDbObserver
        void HandleDatabaseEventL(TContactDbObserverEvent aEvent);

    private:  // Interface for CPbkContactChangeNotifier
        friend class CPbkContactChangeNotifier;
        void AddObserverL(MPbkContactDbObserver* aObserver);
        void RemoveObserver(MPbkContactDbObserver* aObserver);
        void SendEventToAllObservers(const TContactDbObserverEvent& aEvent);
        
    private:  // Implementation
		CPbkContactEngine();
		void ConstructL(const TDesC* aFileName, TBool aReplace, RFs* aFs);
        void ConnectFsL(RFs* aRfs);
        void ReadResourcesL();
        void CreateDbConnectionL(const TDesC* aFileName, TBool aReplace);
        void ForwardEventToAllObservers(const TContactDbObserverEvent& aEvent);
        void SendImmidiateEventToAllObservers(TContactDbObserverEventType aEventType, TContactItemId aContactId, TBool aSendEvent);
        void doDeleteContactL(TContactItemId aContactId);
        void RemoveNonDuplicableContactInformationL(CContactItem& aContactItem);
        class CContactDbConnection;
        friend class CContactDbConnection;

    private:  // Data
        /// Ref: file server connection
        RFs iFs;
        /// Own: file server connection
        RFs iOwnFs;
        /// Own: Contact database connection object.
		CContactDbConnection* iDbConnection;
        /// Own: Observer array
        CArrayPtr<MPbkContactDbObserver>* iObservers;
        /// Own: fields info array.
        CPbkFieldsInfo* iPbkFieldsInfo;
        /// Own: Phonebook constants
        CPbkConstants* iPbkConstants;
        /// Own: Phonebook contact name formatter
        MPbkContactNameFormat* iContactNameFormatter;
        /// Ref: event filter
        MPbkContactDbEventFilter* iEventFilter;
        /// Own: shared data client
        RSharedDataClient* iSharedDataClient;
        /// Own: maximum free space required to delete a contact from the DB
        TInt iFreeSpaceRequiredToDelete;
    };


#endif   // __CPbkContactEngine_H__
            
// End of File
