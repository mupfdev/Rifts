/*
* ============================================================================
*  Name     : ApSelect.h
*  Part of  : Access Point Engine
*
*  Description: Declaration of the CApSelect class.
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

#ifndef CAPSELECT_H
#define CAPSELECT_H

//  INCLUDES
#include <bldvariant.hrh>

#include <commdb.h>
#include <ApEngineVer.h>
#include <ApEngineConsts.h>

#include <bldvariant.hrh>

// FORWARD DECLARATIONS
class CApListItem;
class CApListItemList;
class CApUtils;


// CLASS DECLARATION

/**
*  This class is used to help client's access point selection.
*  Selection can be tailored with specific filters, rules and sort order.
*  Provides methods for setting and getting filters and sort order.
*
*/
class CApSelect :public CBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor. Leaves on failure, places instance
        * on cleanup stack.
        * @param aDb a pointer to a CCommsDataBase.
        * @param aIspTypeFilter Filtering criteria on ISP type
        * Possible values are:
        * KEApIspTypeInternetOnly, KEApIspTypeWAPOnly,
        * KEApIspTypeInternetAndWAP, KEApIspTypeWAPMandatory
        * KEApIspTypeAll and their combinations.
        * @param aBearerFilter Filtering criteria on bearer type
        * Possible values are the TApBearer enums and
        * their combinations (or-ed).
        * @param aSortType Specifies the sort order to use.
        * Possible values are:
        * KEApSortUidAscending, KEApSortUidDescending,
        * KEApSortNameAscending, KEApSortNameDescending
        * @return The constructed CApSelect.
        */
        IMPORT_C static CApSelect* NewLC(
                                        CCommsDatabase& aDb,
                                        TInt aIspFilter,
                                        TInt aBearerFilter,
                                        TInt aSortType
                                        );


        /**
        * Destructor.
        */
        IMPORT_C virtual ~CApSelect();


    protected:      // Constructors

        /**
        * C++ default constructor.
        */
        IMPORT_C CApSelect();

        /**
        * Second-phase constructor.
        */
        IMPORT_C void ConstructL(
                                CCommsDatabase& aDb,
                                TInt aIspFilter,
                                TInt aBearerFilter,
                                TInt aSortType
                                );




    public: // New functions
        /**
        * Sets filters and sorting order for the list of available
        * access points
        * @param aIspTypeFilter Filtering criteria on ISP type
        * Possible values are:
        * KEApIspTypeInternetOnly, KEApIspTypeWAPOnly,
        * KEApIspTypeInternetAndWAP,
        * KEApIspTypeWAPMandatory, KEApIspTypeAll and their combinations.
        * @param aBearerFilter Filtering criteria on bearer type
        * Possible values are the TApBearer enums and
        * their combinations (or-ed).
        * @param aSortType Specifies the sort order to use.
        * Possible values are:
        * KEApSortUidAscending, KEApSortUidDescending,
        * KEApSortNameAscending, KEApSortNameDescending
        */
        IMPORT_C void SetFiltersL(
                                 TInt aIspFilter,
                                 TInt aBearerFilter,
                                 TInt aSortType
                                 );



        /**
        * Gets the current ISP-type filter
        * @return The current ISP-type filter
        */
        IMPORT_C TInt IspTypeFilter();


        /**
        * Gets the current bearer-type filter
        * @return The current bearer-type filter
        */
        IMPORT_C TInt BearerFilter();


        /**
        * Gets the current sorting order
        * @return The current sorting order
        */
        IMPORT_C TInt SortOrder();


        /**
        * Navigates to the first access point in the list.
        * @return Boolean indicating the success of the operation.
        */
        IMPORT_C TBool  MoveToFirst();


        /**
        * Navigates to the next access point in the list.
        * @return Boolean indicating the success of the operation.
        */
        IMPORT_C TBool  MoveNext();


        /**
        * Navigates to the last access point in the list.
        * @return Boolean indicating the success of the operation.
        */
        IMPORT_C TBool  MoveLast();


        /**
        * Navigates to the previous access point in the list.
        * @return Boolean indicating the success of the operation.
        */
        IMPORT_C TBool  MovePrev();


        /**
        * Counts the items in the list
        * @return The number of items in the list.
        */
        IMPORT_C const TUint32 Count();


        /**
        * Gets the name of the 'current' access point
        * Ownership of the returned text is not passed.
        * @return The name of the current access point
        */
        IMPORT_C const TDesC& Name();


        /**
        * Gets the UID of the current access point
        * @return The UID of the current access point
        */
        IMPORT_C const TUint32 Uid();


        /**
        * Gets the ISP-type of the current access point
        * @return The ISP-type of the current access point.
        */
        IMPORT_C const TCommsDbIspType Type();


        /**
        * Gets the bearer-type of the current access point
        * @return The bearer-type of the current access point.
        */
        IMPORT_C const TApBearerType BearerType();


        /**
        * Provides all data in a CApListItemList array.
        * @param aList A reference to a CApListItemList object
        * to hold the values.
        * @return The number of items in the list.
        * All elements in the aList array and their memory
        * will be freed inside the routine.
        * The routine expands or shrinks the array as necessary
        * to minimize memory consumption.
        */
        IMPORT_C TInt AllListItemDataL( CApListItemList& aList );

        /**
        * Returns whether the current item is read-only or not.
        * @return Returns whether the current item is read-only or not.
        */
        IMPORT_C const TBool IsReadOnly() const;

    private:
        /**
        * This function updates the member data according to the
        * current filter settings.
        * @return Error code.
        */
        TInt DoUpdateL();


        /**
        * Gets the filtered and sorted wap table
        * and places it on the Cleanupstack
        */
        CCommsDbTableView* GetFilteredSortedWapTableViewLC();


        /**
        * Gets the filtered and sorted IP bearer table
        * and places it on the Cleanupstack
        */
        CCommsDbTableView* GetFilteredSortedIpBearerTableViewLC();

#ifdef USE_SMS
        /**
        * Gets the filtered and sorted SMS bearer table
        * and places it on the Cleanupstack
        */
        CCommsDbTableView* GetFilteredSortedSmsBearerTableViewLC();
#endif

        /**
        * Gets the filtered and sorted ISP table
        * and places it on the Cleanupstack
        */
        CCommsDbTableView* GetFilteredSortedIspTableViewLC( TBool aIn );


        /**
        * Gets the filtered and sorted GPRS table
        * and places it on the Cleanupstack
        */
        CCommsDbTableView* GetFilteredSortedGprsTableViewLC( TBool aIn );


        /**
        * Reads up the specified columns TUint32 values stored
        * in the table and returns it in the passed array
        */
        void GetUintValuesL
                (
                CCommsDbTableView* aTable,
                const TDesC& aField,
                CArrayFixFlat<TUint32>& aArray
                );


        /**
        * Reads up the protection values stored
        * in the table and returns it in the passed array
        */
        void GetProtValuesL( CCommsDbTableView* aTable,
                             CArrayFixFlat<TUint32>& aArray );

        /**
        * Reads up the specified columns text values stored
        * in the table and returns it in the passed array
        */
        void GetTextValuesL
                (
                CCommsDbTableView* aTable,
                const TDesC& aField,
                CArrayPtrFlat<HBufC>& aArray
                );


        /**
        * Reads up the specified columns long text values stored
        * in the table and returns it in the passed array
        */
        void GetLongTextValuesL
                (
                CCommsDbTableView* aTable,
                const TDesC& aField,
                CArrayPtrFlat<HBufC>& aArray
                );


        /**
        * Returns whether a given value is in the given array or not
        */
        TBool IsInArray( CArrayFixFlat<TUint32>* aArray, TUint32 aValue );


        /**
        * Returns the position of a given value in the given array.
        */
        TInt PosInArray( CArrayFixFlat<TUint32>* aArray, TUint32 aValue );


        /**
        * Returns the position of an item with a given UID in the given list.
        */
        TInt GetItemPos( CApListItemList* aTmpApList, TUint32 aId );


        /**
        * Opens a view on the given table with the given SQL query
        * @return the opened view on the table
        */
        CCommsDbTableView* OpenSqlL
                                (
                                const TDesC& aTableName,
                                const TDesC& aSqlQuery
                                );


        /**
        * Opens a view on the given table where a given text coloumn has
        * a given value
        * @return the opened view on the table
        */
        CCommsDbTableView* OpenViewMatchingTextL
                                (
                                const TDesC& aTableName,
                                const TDesC& aColumnToMatch,
                                const TDesC16& aValueToMatch
                                );

        /**
        * Gets the ISP values (ISP UID, ISP type, ISP bearer type)
        * from a given table
        * @param aTable the table to go through (already filtered & ordered)
        * @param aArray An array to hold the readed values
        * @param aIsCsd Defines whether the table is the ISP or the GPRS
        * because they have different fields for the same value.
        */
        void GetIspValuesL
                (
                CCommsDbTableView* aTable,
                CArrayFixFlat<TUint32[3]>* aArray,
                TBool aIsCsd
                );

        /**
        * Gets the position of an element with a given IAP UID
        */
        TInt GetIapPos
                (
                CArrayFixFlat<TUint32[3]>* aArray,
                TUint32 aValue
                );

        /**
        * Sorts the data according to localised sorting, using CompareC
        */
        void SortLocalisedL( TBool aAscending = ETrue );


    private:    // Data
        CCommsDatabase*             iDb;    // Does not own it!
        TInt                        iIsp;
        TInt                        iBearer;
        TInt                        iSort;
        CApListItemList*            iApList;
        TInt                        iCursor;
        TInt                        iCount;
        TInt                        iMaxIndex;

    };

#endif      // CAPSELECT_H

// End of File
