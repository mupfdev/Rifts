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
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvCommon/ewcobfac.h,v 1.3 2001/12/04 14:06:43 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: ewcobfac.h,v $
 * Revision 1.3  2001/12/04 14:06:43  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.7  2000/03/29 13:34:13  stefania
 * OR 237, character set conversion
 *
 * Revision 1.6  2000-02-09 16:59:33+00  stefania
 * OR 222
 *
 * Revision 1.5  2000-02-08 14:56:44+00  stefania
 * OR 221, removed redundant EXPORT_Cs
 *
 * Revision 1.4  1999/12/13 15:32:17  stefania
 * Added code for cross references, OR 138
 *
 * Revision 1.3  1999-10-07 14:23:19+01  stefania
 * Replaced Lookup with LookupL.
 *
 * Revision 1.2  1999-10-05 16:22:24+01  stefania
 * Added pre-declaration of COle2StreamPackage.
 *
 * Revision 1.1  1999-10-01 15:34:51+01  stefania
 * Initial revision
 *
 *
 * -----------------------------------------------------------------------------
 */

#if !defined (__EWCO_BIFF_FACTORY_H__)
#define __EWCO_BIFF_FACTORY_H__

#include <e32base.h>
#include <e32std.h>   

class CWriteBiffRecord;
class COle2StreamPackage;
class CEpocRecord;
class CExcelLibraryW;
#include "ewcobift.h"

//Factory class for BIFF record classes
class CWriteBiffFactory : public CBase
{
public:
    enum BiffVersion { EBiff8, EBiff7 };
public:
     virtual CWriteBiffRecord* NewBiffL(const COle2StreamPackage *aStream, 
        const EBiffType aType) const = 0;
     virtual CWriteBiffRecord* NewBiffL(const COle2StreamPackage *aStream,
        const CEpocRecord* aEpocRecord ) const = 0;                    
     virtual CWriteBiffRecord* NewBiffLC(const COle2StreamPackage *aStream,
        const EBiffType aType) const = 0;
     virtual CWriteBiffRecord* NewBiffLC(const COle2StreamPackage *aStream,
        const CEpocRecord* aEpocRecord ) const = 0;
public:
     virtual BiffVersion Version ( ) const = 0;
     TBool& NoFormula( ) { return iNoFormula; }
     const TBool& NoFormula( ) const { return iNoFormula; }
public:
    //OR 237
    CExcelLibraryW*& Library( ) { return iLibrary; }
    CExcelLibraryW* const & Library( ) const { return iLibrary; }
protected:
    IMPORT_C void InitialiseRecord( CWriteBiffRecord* aBiffRecord ) const;
protected:
    IMPORT_C virtual  CWriteBiffRecord* LookupL(const EBiffType aType) const;
    IMPORT_C virtual  CWriteBiffRecord* LookupL
        (const CEpocRecord* aEpocRecord, EBiffType& aBiffType) const;
private:
    TBool            iNoFormula; //true if we don't want to use formulae, OR 222
    CExcelLibraryW * iLibrary;   //OR 237
};
#endif