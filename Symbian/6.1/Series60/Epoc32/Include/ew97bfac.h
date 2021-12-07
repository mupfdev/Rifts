/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   EXELCOMM.DLL
 *
 * Identification   :   Factory class for BIFF record classes
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvV97/ew97bfac.h,v 1.3 2001/12/04 14:06:45 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: ew97bfac.h,v $
 * Revision 1.3  2001/12/04 14:06:45  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.8  2000/02/08 14:59:45  stefania
 * OR 221, removed redundant EXPORT_Cs
 *
 * Revision 1.7  1999/12/13 15:22:07  stefania
 * Added code for cross references, OR 138
 *
 * Revision 1.6  1999-10-07 17:42:49+01  stefania
 * aFs is not const.
 *
 * Revision 1.5  1999-10-07 17:15:23+01  stefania
 * Added two phase construction for tracing.
 *
 * Revision 1.4  1999/10/07 14:16:35  stefania
 * Added external linkage to Lookup functions.
 *
 * Revision 1.3  1999-10-07 14:16:53+01  stefania
 * Replaced Lookup with LookupL.
 *
 * Revision 1.2  1999-10-05 16:27:23+01  stefania
 * Added new Lookup( ) method.
 *
 * Revision 1.1  1999-10-01 15:33:41+01  stefania
 * Initial revision
 *
 *
 * -----------------------------------------------------------------------------
 */

#if !defined (__EWCO_BIFF_FACTORY_8_H__)
#define __EWCO_BIFF_FACTORY_8_H__

#include <e32base.h>
#include <e32std.h>   

#include "ewcobfac.h"

class CWriteBiffRecord;

//Factory class for BIFF record classes
class CWriteBiff8Factory : public CWriteBiffFactory
{     
public:
    IMPORT_C static CWriteBiff8Factory* NewL( RFs& aFs );
     ~CWriteBiff8Factory( ) { cotrTraceTerminate( ); }
public:
    IMPORT_C virtual CWriteBiffRecord* NewBiffL(const COle2StreamPackage *aStream, 
        const EBiffType aType) const;
    IMPORT_C virtual CWriteBiffRecord* NewBiffL(const COle2StreamPackage *aStream,
        const CEpocRecord* aEpocRecord ) const;                    
    IMPORT_C virtual CWriteBiffRecord* NewBiffLC(const COle2StreamPackage *aStream,
        const EBiffType aType) const;
    IMPORT_C virtual CWriteBiffRecord* NewBiffLC(const COle2StreamPackage *aStream,
        const CEpocRecord* aEpocRecord ) const;
public:
     virtual BiffVersion Version ( ) const { return EBiff8; }
private:
    void ConstructL( RFs& aFs );
private:
    IMPORT_C virtual CWriteBiffRecord* LookupL( const EBiffType aType ) const;
    IMPORT_C virtual CWriteBiffRecord* LookupL( const CEpocRecord* aEpocRecord, 
        EBiffType& aType ) const;
};
#endif //__EWCO_BIFF_FACTORY_8_H__