/*
* ============================================================================
*  Name     : ApListItem.h
*  Part of  : Access Point Engine
*
*  Description:
*     Declaration of the CApSelect class.
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

#ifndef CAPLISTITEM_H
#define CAPLISTITEM_H

//  INCLUDES
#include <bldvariant.hrh>

#include <commdb.h>
#include <ApEngineVer.h>
#include <ApEngineConsts.h>

// CLASS DECLARATION
/**
*  Representation of a list item.
*/
class CApListItem :public CBase          ///< This class is used to hold
                                         ///< the main information of an
                                         ///< access point.
                                         ///< It is used in CApSelect.
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor. Leaves on failure, places instance
        * on cleanup stack.
        * @return The constructed CApListItem.
        */
        IMPORT_C static CApListItem* NewLC();


        /**
        * NOTE: This function is deprecated, use the one with the additional
        * aStartPage parameter below.
        * Two-phased constructor. Leaves on failure, places instance
        * on cleanup stack.
        * @param aIspType The type of the access point
        * (Internet only, Wap only, Internet AND Wap)
        * @param aUid The ID of the access point
        * @param aName The name of the access point
        * @param aBearerType The bearer type of the access point
        * @return The constructed CApListItem.
        */
        IMPORT_C static CApListItem* NewLC( TCommsDbIspType aIspType,
                                            TUint32 aUid,
                                            const TDesC& aName,
                                            TApBearerType aBearerType );


        /**
        * Two-phased constructor. Leaves on failure, places instance
        * on cleanup stack.
        * @param aIspType The type of the access point
        * (Internet only, Wap only, Internet AND Wap)
        * @param aUid The ID of the access point
        * @param aName The name of the access point
        * @param aBearerType The bearer type of the access point
        * @param aStartpage The starting page of the access point
        * @param aReadOnly Whether the given item is read-only or not
        * @return The constructed CApListItem.
        */
        IMPORT_C static CApListItem* NewLC( TCommsDbIspType aIspType,
                                            TUint32 aUid,
                                            const TDesC& aName,
                                            TApBearerType aBearerType,
                                            const TDesC& aStartPage,
                                            TBool aReadOnly = ETrue
                                            );

        /**
        * Two-phased constructor. Leaves on failure, places instance
        * on cleanup stack.
        * @param aItem a pointer to a CApListItem.
        * @return The constructed CApListItem.
        */
        IMPORT_C static CApListItem* NewLC( CApListItem* aItem );


        /**
        * Destructor.
        */
        IMPORT_C virtual ~CApListItem();


        /**
        * Copies the data from another CApListItem
        * Substitutes the "Assignment operator."
        * @return No return value.
        */
        IMPORT_C void CopyFromL( const CApListItem& aCopyFrom );



    protected:      // Constructors
        /**
        * C++ default constructor.
        */
        IMPORT_C CApListItem();

        /**
        * NOTE: This function is deprecated, use the one with the additional
        * aStartPage parameter below.
        * Second-phase constructor.
        */
        IMPORT_C void ConstructL( TCommsDbIspType aIspType,
                                  TUint32 aUid,
                                  const TDesC& aName,
                                  TApBearerType aBearerType );

        /**
        * Second-phase constructor.
        */
        IMPORT_C void ConstructL( TCommsDbIspType aIspType,
                                  TUint32 aUid,
                                  const TDesC& aName,
                                  TApBearerType aBearerType,
                                  const TDesC& aStartPage
                                  );


        /**
        * Second-phase constructor.
        */
        IMPORT_C void ConstructL();


    public: // New functions

        /**
        * NOTE: This function is deprecated, use the one with the additional
        * aStartPage parameter below.
        * Sets item values of the access point. Leaves on failure.
        * @param aIspType The type of the access point
        * (Internet only, Wap only, Internet AND Wap)
        * @param aUid The ID of the access point
        * @param aName The name of the access point
        * @param aBearerType The bearer type of the access point
        */
        IMPORT_C void SetItemL( TCommsDbIspType aIspType,
                                TUint32 aUid,
                                const TDesC& aName,
                                TApBearerType aBearerType );

        /**
        * Sets item values of the access point. Leaves on failure.
        * @param aIspType The type of the access point
        * (Internet only, Wap only, Internet AND Wap)
        * @param aUid The ID of the access point
        * @param aName The name of the access point
        * @param aBearerType The bearer type of the access point
        * @param aStartpage The starting page of the access point
        */
        IMPORT_C void SetItemL( TCommsDbIspType aIspType,
                                TUint32 aUid,
                                const TDesC& aName,
                                TApBearerType aBearerType,
                                const TDesC& aStartpage
                                );


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
        * Returns the startpage of the current access point if any,
        * otherwise, an empty string is returned.
        * Ownership of the returned text is not passed.
        * @return The startpage of the current access point.
        */
        IMPORT_C const TDesC& StartPage() const;


        /**
        * Returns whether the access point is read-only or not.
        * @return Whether the access point is read-only or not.
        */
        IMPORT_C const TBool IsReadOnly() const;



    private:    // Data
        TCommsDbIspType iIspType;       ///< The type of the access point
                                        ///< (Internet only, Wap only,
                                        ///< Internet AND Wap)
        TUint32         iUid;           ///< The ID of the access point
        HBufC*          iName;          ///< The name of the access point
        HBufC*          iStartPage;     ///< The startpage of the access point

        TApBearerType   iBearerType;    ///< Bearer type of the access point
        TBool           iReadOnly;      ///< Is the AP protected or not


    protected:  // Friend classes
        friend class CApSelect;

    };



#endif      // CAPLISTITEM_H

// End of File
