/*
* ============================================================================
*  Name     : CPbkViewState from CPbkViewState.h
*  Part of  : PbkView.dll
*
*  Description:
*     View states.
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

#ifndef __CPbkViewState_H__
#define __CPbkViewState_H__

//  INCLUDES
#include <e32base.h>    // CBase
#include <cntdef.h>     // TContactItemId, CContactIdArray

// FORWARD DECLARATIONS
class RReadStream;
class RWriteStream;
class CPbkFieldDataArray;

// CLASS DECLARATION

/**
 * Generic Phonebook view state.
 */
class CPbkViewState : public CBase
    {
    public:  // Types
        enum TDataType
            {
            EEnd = 0,
            EFocusedContactId,
            ETopContactId,
            EMarkedContactIds,
            EFocusedFieldIndex,
            ETopFieldIndex,
            EFieldDataArray
            };

    public:  // Constructors and destructor
        /**
         * Creates and returns a new instace of this class.
         */
        IMPORT_C static CPbkViewState* NewL();

        /**
         * Like NewL(), but leaves the object on the cleanup stack
         * @see NewL
         */
        IMPORT_C static CPbkViewState* NewLC();
        
        /**
         * Creates and returns a new instace of this class intialized
         * from aStream.
         */
        IMPORT_C static CPbkViewState* NewL(RReadStream& aStream);
        
        /**
         * Like NewL(RReadStream& aStream) but leaves the object on
         * the cleanup stack.
         * @see NewL(RReadStream& aStream)
         */
        IMPORT_C static CPbkViewState* NewLC(RReadStream& aStream);
        
        /**
         * Creates and returns a new instace of this class intialized
         * from aBuf.
         */
        IMPORT_C static CPbkViewState* NewL(const TDesC8& aBuf);
        
        /**
         * Like NewL(const TDesC8& aBuf) but leaves the object on
         * the cleanup stack.
         * @see NewL(const TDesC8& aBuf)
         */
        IMPORT_C static CPbkViewState* NewLC(const TDesC8& aBuf);

        /**
         * Destructor.
         */
        ~CPbkViewState();

    public:  // Getters
        /**
         * Returns the message Uid for use with view server messages.
         */
        IMPORT_C static TUid Uid();

        /**
         * Returns id of the focused contact.
         */
        IMPORT_C TContactItemId FocusedContactId() const;

        /**
         * Returns id of the topmost contact.
         */
        IMPORT_C TContactItemId TopContactId() const;

        /**
         * Returns const array of marked contacts, NULL if not set.
         */
        IMPORT_C const CContactIdArray* MarkedContactIds() const;

        /**
         * Returns array of marked contacts, NULL if not set.
         */
        IMPORT_C CContactIdArray* MarkedContactIds();

        /**
         * Returns index of the focused field (field is from FocusedContactId()), 
         * -1 = no field focused.
         */
        IMPORT_C TInt FocusedFieldIndex() const;

        /**
         * Returns index of the topmost field (field is from FocusedContactId()), 
         * -1 = no topmost field.
         */
        IMPORT_C TInt TopFieldIndex() const;

        /**
         * Returns field data array, NULL if not set.
         */
        IMPORT_C CPbkFieldDataArray* FieldDataArray() const;

    public:  // Setters
        /**
         * Sets id of the focused contact to aId.
         */
        IMPORT_C void SetFocusedContactId(TContactItemId aId);

        /**
         * Sets id of the topmost contact to aId.
         */
        IMPORT_C void SetTopContactId(TContactItemId aId);

        /**
         * Sets the array of marked contact ids to aArray. Destroys previous
		 * array and takes ownership of aArray.
         */
        IMPORT_C void SetMarkedContactIds(CContactIdArray* aArray);

        /**
         * Sets index of the focused field to aIndex (field from
		 * FocusedContactId()), -1 = no field focused.
         */
        IMPORT_C void SetFocusedFieldIndex(TInt aIndex);

        /**
         * Sets index of the topmost field to aIndex (field from
		 * FocusedContactId()), -1 = no topmost field.
         */
        IMPORT_C void SetTopFieldIndex(TInt aIndex);

        /**
         * Sets field data array to aArray. Destroys previous array
         * and takes ownership of aArray.
         */
        IMPORT_C void SetFieldDataArray(CPbkFieldDataArray* aFieldDataArray);

        /**
         * Reset this state to empty.
         */
        IMPORT_C void Reset();

        /**
         * Merges another view state to this view state.
         *
         * @param aOtherState   the state to merge to this state. The 
         *                      properties which have a value in aOtherState
         *                      override properties in this object. aOtherState
         *                      may be modified by this function.
         */
        /*IMPORT_C*/ void MergeViewState(CPbkViewState& aOtherState);

    public:  // Stream support
        /**
         * Packages and returns this object in a buffer. Caller is responsible
         * of deleting the buffer.
         */
        IMPORT_C HBufC8* PackL() const;

        /**
         * Like PackL, but leaves the buffer on the cleanup stack.
         * @see PackL
         */
        IMPORT_C HBufC8* PackLC() const;

        /**
         * Sets this state from aPack previously created with PackL.
         * @see PackL
         * @see PackLC
         */
        IMPORT_C void UnpackL(const TDesC8& aPack);

        /**
         * Externalizes this object to aStream.
         * @see InternalizeL
         */
        IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

        /**
         * Internalizes this object from aStream.
         * @see ExternalizeL
         */
        IMPORT_C void InternalizeL(RReadStream& aStream);

    public: // Support functions
        IMPORT_C TBool operator==(const CPbkViewState& aRhs) const; 

    private:  // Implementation
        CPbkViewState();

    private:  // data
        /// Own: Id of the focused contact
        TContactItemId iFocusedContactId;
        /// Own: Id of the topmost contact
        TContactItemId iTopContactId;
        /// Own: Index of the focused field
        TInt iFocusedFieldIndex;
        /// Own: Index of the top field
        TInt iTopFieldIndex;
        /// Own: Array of marked contacts
        CContactIdArray* iMarkedContactIds;
        /// Own: Field data array
        CPbkFieldDataArray* iFieldDataArray;

    private:  // const static data
        static const TUid KUid;
    };


/*
   ** View state binary stream format **
   
    - View parameter UID is 0x101f4ccf

    - Format of the stream in (slightly freeform) BNF:

    stream ::= { command }
    command ::= Int8(opcode) parameters
    opcode ::= EEnd | EFocusedContactId | ETopContactId | EMarkedContactIds |
              EFocusedFieldIndex | ETopFieldIndex | EFieldDataArray
    command ::= EEnd  // no further commands are read after EEnd. EEnd is not mandatory in a stream.
    command ::= EFocusedContactId Int32(TContactItemId)
    command ::= ETopContactId Int32(TContactItemId)
    command ::= EMarkedContactIds (Int32(count) { Int32(TContactItemId) })  // count is count TContactItemIds
    command ::= EFocusedFieldIndex Int32(index)
    command ::= ETopFieldIndex Int32(index)
    command ::= EFieldDataArray contactdata

    contactdata ::= Int32(count) { fielddata }  // count is count of fieldatas
    fielddata ::= fieldtype data
    fieldtype ::= ETypeText | ETypeTime
    fielddata ::= ETypeText (Int32(length) text)  // length is length of text in chars, text is unicode
    fielddata ::= ETypeTime (Int32(high) Int32(low))  // high and low words of a TTime's internal Int64

    Constants:
        EEnd = 0,
        EFocusedContactId = 1,
        ETopContactId = 2,
        EMarkedContactIds = 3,
        EFocusedFieldIndex = 4,
        ETopFieldIndex = 5,
        EFieldDataArray = 6


    - Example:
    Activate Phonebook's contact info view to show contact with id 5 and field 
    at index 3 focused:

    // Write parameters in a buffer
    TBuf8<16> param;
    RDesWriteStream stream(param);
    stream.PushL();
    param.WriteInt8L(1);  // opcode EFocusedContactId
    param.WriteInt32L(5);  // Contact id 5
    param.WriteInt8L(4);  // opcode EFocusedFieldIndex
    param.WriteInt32L(3);  // field index 3
    stream.CommitL();
    CleanupStack::PopAndDestroy();  // stream

    // Make view id with Phonebook's app UID3 and Contact Info View's id
    const TVwsViewId viewId(0x101f4cce, 4);

    // Activate the view
    AppUi()->ActivateViewL(viewId, TUid::Uid(0x101f4ccf), param);


    - Same example as above, now using CPbkViewState:

    #include <CPbkViewState.h>  // need also to add PbkView.lib into projects .mmp
    #include <PbkUID.h> // Phonebook UIDs

    CPbkViewState* pbkViewParam = CPbkViewState::NewLC();
    pbkViewParam->SetFocusedContactId(5);
    pbkViewParam->SetFocusedFieldIndex(3);
    HBufC8* paramBuf = pbkViewParam->PackLC();
    
    // Make view id with Phonebook's app UID3 and Contact Info View's id
    const TVwsViewId viewId(KPbkUID3, 4);

    // Activate the view
    AppUi()->ActivateViewL(viewId, CPbkViewState::Uid(), *paramBuf);

    // Cleanup
    CleanupStack::PopAndDestroy(2);  // paramBuf, pbkViewParam

    - The latter example is cleaner, but using CPbkViewState from your 
    application means that your application will have a dependency to 
    CPbkViewState.h and PbkView.lib at compile time and to PbkView.dll at
    run time.

*/

#endif // __CPbkViewState_H__
            
// End of File
