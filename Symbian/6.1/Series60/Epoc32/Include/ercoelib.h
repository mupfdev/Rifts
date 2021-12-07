/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Excel Reader (ercolib)
 *
 * Identification   :   Excel Library Class [EXCEL_SDS]
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvCommon/ercoelib.h,v 1.3 2001/12/04 14:06:42 BijalShah Exp $, $Revision: 1.3 $
 *
 * Author           :   Peter Mead
 *
 * History          :   
 *
 * $Log: ercoelib.h,v $
 * Revision 1.3  2001/12/04 14:06:42  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.43  2000/03/29 13:34:13  stefania
 * OR 237, character set conversion
 *
 * Revision 1.42  2000/02/11 15:04:14  stefania
 * OR 223, force strings with leading apostrophe
 *
 * Revision 1.41  2000-02-10 14:33:34+00  stefania
 * OR 222, insert function values
 *
 * Revision 1.40  2000-02-08 14:56:42+00  stefania
 * OR 221, removed redundant EXPORT_Cs
 *
 * Revision 1.39  2000/01/17 17:27:25  stefania
 * OR 200, code changes for performance improvement
 *
 * Revision 1.38  2000/01/11 12:47:26  stefania
 * Fixed OR 163.
 *
 * Revision 1.37  1999/12/16 09:55:45  chrisg
 * OR 301.121.137: Fixed embedded Objects. OLESIZE, and CHART records do not appear
 * in the sheet stream, and EXTERNSHEET are not necessarily associated with embedded
 * objects. Only one warning per worksheet is provided now.
 *
 * Revision 1.36  1999-12-15 16:02:49+00  stefania
 * Added Sheets( ) method to access iSheets.
 *
 * Revision 1.35  1999-12-15 11:43:15+00  stefania
 * Added code for cross references (OR 138)
 *
 * Revision 1.34  1999-11-26 15:08:53+00  peterm
 * Changes for Embedded Object and Currency Number Formats
 *
 * Revision 1.33  1999/11/19 13:56:00  peterm
 * Cell Formating Changes
 *
 * Revision 1.31  1999/10/28 12:57:29  stefania
 * Removed definition of AfcFormulaInfo.
 *
 * Revision 1.30  1999-10-28 13:32:10+01  stefania
 * Merged 1.26.1.2 and 1.29.
 *
 *
 * Revision 1.26.1.2  1999/10/28 12:25:28  stefania
 * Fixed ^Ms.
 *
 * Revision 1.29  1999/10/27 16:09:36  peterm
 * Remove Column Formating
 *
 * Revision 1.28  1999-10-27 16:31:00+01  peterm
 * Add Column Formating
 * Revision 1.27  1999-10-25 20:21:25+01  peterm
 * Add shared formula code not working ye
 *
 * Revision 1.26  1999-10-19 14:11:25+01  peterm
 * Add Number Cell & Column format Afc methods
 *
 * Revision 1.25  1999-10-11 12:18:46+01  peterm
 * Code Review Changes
 *
 * Revision 1.24  1999-10-07 10:13:49+01  stefania
 * Fixed ^Ms.
 *
 * Revision 1.23  1999-09-22 12:22:41+01  peterm
 * add 95 reader
 *
 * Revision 1.22  1999-09-17 14:33:45+01  stefania
 * First complete build of exelcomm.dll
 *
 * Revision 1.21  1999-09-17 09:31:52+01  peterm
 * Changes to constructor
 *
 * Revision 1.20  1999/09/13 16:13:03  peterm
 * More Trace points and re-arrange build order
 *
 * Revision 1.19  1999/09/09 15:48:05  peterm
 * Add AfcCellInfoIEEENumber
 *
 * Revision 1.18  1999/09/07 11:25:10  peterm
 * add AfcCellInfoIEEENumber
 *
 * Revision 1.17  1999-09-06 18:01:46+01  peterm
 * Include file Inter-working bug, fixed
 *
 * Revision 1.16  1999-09-06 09:26:16+01  stefania
 * typos
 *
 * Revision 1.15  1999-09-06 09:20:02+01  stefania
 * Re-arrange include files.
 *
 * Revision 1.14  1999-09-03 15:41:19+01  peterm
 * Make iSharedStringTable public in ExcelLibrary Class
 *
 * Revision 1.13  1999-09-02 09:58:40+01  stefania
 * Few minor changes for first built.
 *
 * Revision 1.12  1999-09-01 15:51:46+01  peterm
 * Modified CBiffLABELSST
 *
 * Revision 1.11  1999-09-01 14:14:55+01  stefania
 * Added include files.
 *
 * Revision 1.10  1999-09-01 12:52:17+01  stefania
 * Added access method to iBiffRecord.
 *
 * Revision 1.9  1999-09-01 11:50:03+01  chrisg
 * Updated to include Trace code, and TEST invariant code, also updated AfcMultipleL to
 * set the full set of cells as necessary (by iteration).
 *
 * Revision 1.8  1999-09-01 09:14:20+01  peterm
 * Review Update
 *
 * Revision 1.7  1999-08-27 13:33:32+01  chrisg
 * Changed the 'orrible TABS into nice spaces :-)
 *
 * Revision 1.6  1999/08/27 08:26:05  peterm
 * AFC & CBiffRecord added
 *
 * Revision 1.5  1999-08-24 17:58:33+01  peterm
 * Changes to BiffRecords
 *
 * Revision 1.4  1999-08-19 17:27:15+01  peterm
 * Changed History
 *
 * Revision 1.3  1999-08-19 17:21:56+01  peterm
 * Added Sheet model Wrapper
 *
 * Revision 1.2  1999-08-17 17:23:45+01  peterm
 * <>
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__ERCOELIB_H__)
#define __ERCOELIB_H__

#include <cotrmain.h>
#include <cosyincs.h>
#include <ollomain.h>

#include "excoelib.h" //CExcelLibrary

#include "ewcohash.h"

#include "ercoincs.h"
//#include "ercomain.h"

#include "ercobiff.h" //CBiff* classes
#include "er97biff.h"
#include "er95biff.h"
#include "excoepoc.h" //CEpocRecord

/******************************************************************************
                              class CExcelLibraryR 
 ******************************************************************************
 */
/*Note method name ending with an 8 indicate that they the are used by Biff 8/Excel
97 & 00 and there implementation can be found Er97biff. Similarly method names
ending in 7 are used by Biff 7/Excel 95 and implemented in Er95biff.*/

class CExcelLibraryR : public CExcelLibrary
{
public:
    //types
    enum {KGranularity = 4};
public:  //construction, destruction
    //constructor is public as it's only called by CExcelLibrary::NewL
    IMPORT_C CExcelLibraryR(const TFileName& aFileName, 
                            const COle2StreamPackage* aOleStream, 
                            RFs&   aFs );
    IMPORT_C ~CExcelLibraryR();
public: //interface
    IMPORT_C TInt AfcSingleL(CBiffSingle         *aBiffRecord);
    IMPORT_C TInt AfcMultipleL(CBiffMultiple     *aBiffRecord);

    IMPORT_C TInt AfcWorkBookInfo(CBiffBOUNDSHEET* aBiffRecord);

    IMPORT_C TInt AfcDateSystem(CBiff1904* aBiffRecord);

    IMPORT_C TInt AfcSubStreamInfo(CBiffBOF     *aBiffRecord);
    IMPORT_C TInt AfcSubStreamInfo(CBiffEOF     *aBiffRecord);

    IMPORT_C void AfcSave( const TFileName& aTarget, RFs& aFs );

    IMPORT_C TInt AfcColumnFormat(CBiffCOLINFO  *aBiffRecord);

    IMPORT_C TInt AfcNumberFormat(CBiffFORMAT   *aBiffRecord);
    IMPORT_C TInt AfcCellFormat(CBiffXF         *aBiffRecord);
    IMPORT_C TInt AfcCellFormat(CBiffFONT       *aBiffRecord);

    IMPORT_C TInt AfcCellInfoSharedFormula(CBiffSHRFMLA  *aBiffRecord);
    IMPORT_C TInt AfcCellInfoFormula(CBiffFORMULA        *aBiffRecord);
             
    TInt AfcSheetInfomation(CBiffDIMENSIONS    *aBiffRecord)
        {return aBiffRecord->GetLastRow(iLastRow);};

    IMPORT_C TInt AfcEmbeddedL(CBiffEmbedded     *aBiffRecord);

    TInt AfcTextBox(CBiffTXO                    *aBiffRecord)
        {return AfcEmbeddedL(aBiffRecord);};
    TInt AfcGraphic(CBiffIMDATA                 *aBiffRecord)
        {return AfcEmbeddedL(aBiffRecord);};
    TInt AfcSound(CBiffSOUND                    *aBiffRecord)
        {return AfcEmbeddedL(aBiffRecord);};
    TInt AfcObj(CBiffOBJ                        *aBiffRecord)
        {return AfcEmbeddedL(aBiffRecord);};
    
    //Changed by SA - Or 138
    IMPORT_C TInt AfcExternSheet(CBiffEXTERNSHEET*     aBiffRecord);
    IMPORT_C TInt AfcSupportingWorkBook(CBiffSUPBOOK * aBiffRecord);

    TInt AfcCellInfoLabel(CBiffSTRING           *aBiffRecord)
        {return AfcSingleL(aBiffRecord);}
    TInt AfcCellInfoRichString(CBiffSTRING      *aBiffRecord)
        {return AfcSingleL(aBiffRecord);}
    TInt AfcCellInfoEmpty(CBiffBLANK            *aBiffRecord)
        {return AfcSingleL(aBiffRecord);}
    TInt AfcCellInfoBoolError(CBiffBOOLERR      *aBiffRecord)
        {return AfcSingleL(aBiffRecord);}

    TInt AfcCellInfoNumber(CBiffRK              *aBiffRecord)
        {return AfcSingleL(aBiffRecord);}
    TInt AfcSharedString(CBiffLABELSST8         *aBiffRecord)
        {return AfcSingleL(aBiffRecord);}
    TInt AfcCellInfoIEEENumber(CBiffNUMBER      *aBiffRecord)
        {return AfcSingleL(aBiffRecord);}

    TInt AfcCellInfoEmpty(CBiffMULTBLANK        *aBiffRecord)
        {return AfcMultipleL(aBiffRecord);}
    TInt AfcCellInfoNumber(CBiffMULTRK          *aBiffRecord)
        {return AfcMultipleL(aBiffRecord);}

    IMPORT_C TInt AfcSharedString(CBiffSST8     *aBiffRecord);
    CBiffSST8    *iSharedStringTable;

public:
    CHashTable<HBufC*,TInt32>*& Sheets( ) { return iSheets; }
    CHashTable<HBufC*,TInt32>* const & Sheets( ) const { return iSheets; }

protected: // methods
    void ConstructL( );
    
private: //Methods
    TInt SetCellFormat(TInt16 &aXfIndex, TCellRef &aRef);
    TInt SetCellContentL(CBiffRecord* aBiffRecord, const TCellRef& aCellRef); //OR 223
    TInt AfcCellInsertEvaluatedFormula( CBiffFORMULA* aBiffRecord ); //OR 222
    TBool IsStringInterpreted( ); //OR 223

        
private: // data
    CEpocRecord *iEpocRecord;
    CBiffXF     *iXfList;
    CBiffXF     *iXfListEnd;
    CBiffFORMAT *iFormatList;
    CBiffFONT   *iFontList;
    CBiffFONT   *iFontListEnd;
    CHashTable<HBufC*,TInt32>* iSheets;
    CBiffSHRFMLA *iSharedFormulaList;
    CBiffEXTERNSHEET* iExternSheetRecord; //OR 138 - sheet cross references
    CBiffSUPBOOK*     iSupBookRecord;     //OR 138 - sheet cross references
    TInt        iLastRow;
    TBool       i1904DateSystem;
    TInt        iCellFormat;

    TBuf<MAXSTRINGLENGTH> iBuf; //OR 163, to avoid having a large buffer on the stack

	__DECLARE_TEST;

};

#endif // !defined (__ERCOELIB_H__)

