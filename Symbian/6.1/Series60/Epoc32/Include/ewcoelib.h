/* ===========================================================================

 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   EXCELCOMM.DLL
 *
 * Identification   :   CExcelLibraryW class
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvCommon/Ewcoelib.h,v 1.3 2001/12/04 14:06:42 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: Ewcoelib.h,v $
 * Revision 1.3  2001/12/04 14:06:42  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.12  2000/03/29 13:34:14  stefania
 * OR 237, character set conversion
 *
 * Revision 1.11  2000-02-09 16:59:36+00  stefania
 * OR 222
 *
 * Revision 1.10  1999/12/03 12:39:55  stefania
 * Changes for OR 057 (password protection).
 *
 * Revision 1.9  1999-10-18 14:14:47+01  stefania
 * Added VerifyDocumentL
 *
 * Revision 1.8  1999/10/15 12:17:48  stefania
 * Changed return of Write functions from TInt to void.
 *
 * Revision 1.7  1999/10/11 10:22:10  stefania
 * Added iFormula.
 *
 * Revision 1.6  1999/10/01 14:38:23  stefania
 * Added BIFF factory class.
 *
 * Revision 1.5  1999-09-30 16:14:11+01  stefania
 * Fixed memory leak bugs and added page breaks. Changed number of steps.
 *
 * Revision 1.4  1999-09-22 13:00:51+01  stefania
 * Added iRowRecord
 *
 * Revision 1.3  1999-09-17 14:34:34+01  stefania
 * First complete build of exelcomm.dll
 *
 * Revision 1.2  1999-09-15 14:01:08+01  stefania
 * Merge with basic drop
 *
 * Revision 1.1  1999-09-08 11:08:44+01  stefania
 * Initial revision
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__ERCOELIBW_H__)
#define __ERCOELIBW_H__

#include "ewcobfac.h" //BIFF records factory
#include "excoelib.h" //CExcelLibrary 
#include "ewcoform.h" //RFormula

class CEpocRecord;
class CFormat;
/******************************************************************************
                              class CExcelLibraryW 
 ******************************************************************************
 */

class CExcelLibraryW : public CExcelLibrary
{
public:
    //Constants
    const static TInt KNumberOfRowsPerBlock;

public:  
    //Construction, Destruction
    //constructor is public as it's only called by CExcelLibrary::NewL
    CExcelLibraryW( 
            const TFileName&          aFileName,           //SOURCE
            const COle2StreamPackage* aOleStream,          //TARGET
                  RFs                 aFs,                 //FILE SERVER
                  CWriteBiffFactory* aBiffFactory );       //FACTORY CLASS FOR BIFF RECORDS

    EXPORT_C virtual ~CExcelLibraryW();

public:
    //interface from CExelLibrary
    IMPORT_C virtual void  VerifyDocumentL( MConverterUiObserver* );
    IMPORT_C virtual TInt  NumberOfStepsL( );
    IMPORT_C virtual void  CreateWorkBookL( );
    IMPORT_C virtual TBool EndWorkBookL( );
    IMPORT_C virtual TInt  AddSheetL( );
    IMPORT_C virtual TBool EndSheetL( );
    IMPORT_C virtual TInt  AddRowBlockL( );
    IMPORT_C virtual void  EndRowBlockL( );
    IMPORT_C virtual void  AddRowL( );
    IMPORT_C virtual TInt  EndRowL( );
    IMPORT_C virtual TInt  AddCellL( );

public:
    CFormat*& Format( )  { return iFormat;  }
    RFormula& Formula( ) { return iFormula; }
    CFormat* const & Format( )  const { return iFormat;  }
    const RFormula&        Formula( ) const { return iFormula; }

private:
    //Real Construction
    void ConstructL( );

private:
    //Implementation methods
    void WriteRecordL ( const EBiffType& aType, 
        const TInt aPosition = -1, const CWriteBiffRecord* aBiffRecord = NULL);
    void WriteFixedPartL( const TUint8* aBuf, const TInt aSize );

private:
    //Data

    //Current position in OLE stream
    TInt iCurrentPosition;

    //Position of row records
    TInt iRowRecordPointer;

    //EPOC Record
    CEpocRecord* iEpocRecord;

    //FORMATTING
    CFormat*           iFormat;

    //FORMULAE
    RFormula           iFormula;

    //BIFF Records Factory
    CWriteBiffFactory* iBiffFactory;

    //PERSISTENT BIFF Records
    CWriteBiffRecord*  iRowRecord;
    CWriteBiffRecord*  iIndexRecord;
    CWriteBiffRecord*  iDbCellRecord;
    CWriteBiffRecord*  iBoundSheetRecord; 
};

#endif // !defined (__ERCOELIBW_H__)
