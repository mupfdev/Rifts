/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Excel Reader 97 & 00
 *
 * Identification   :   97 & 00 Stream Reader Classes[EXCEL_SDS]
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Workfile$, $Revision: 1.3 $
 *
 * Author           :   Peter Mead
 *
 * History          :   
 *
 * $Log: er97main.h,v $
 * Revision 1.3  2001/12/04 14:06:44  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.15  2000/01/18 10:10:06  stefania
 * OR 200, stream name now defined in er97main.h
 *
 * Revision 1.14  2000-01-17 17:32:19+00  stefania
 * OR 200, code changes for performance improvement.
 *
 * Revision 1.13  1999-10-28 10:02:45+01  stefania
 * Changes for wide build and new epoc sheet API.
 *
 * Revision 1.12  1999/10/20 12:32:31  peterm
 * Made constructore private, and corrected smelling mistake
 *
 * Revision 1.11  1999-10-19 14:30:55+01  peterm
 * Add ValidRecordType & ReturnConvertionStatus
 *
 * Revision 1.10  1999-10-08 12:09:24+01  peterm
 * Code Review Changes
 *
 * Revision 1.9  1999-09-22 12:39:19+01  peterm
 * add 95 reader
 *
 * Revision 1.8  1999/09/07 12:45:18  peterm
 * Changed the useless NewLC into a really nice NewL :-)
 *
 * Revision 1.7  1999-09-06 18:00:01+01  peterm
 * Include file inter-working problem fixed
 *
 * Revision 1.6  1999-09-02 10:00:57+01  stefania
 * Few minor changes for first built.
 *
 * Revision 1.5  1999-09-01 15:43:55+01  chrisg
 * Changed class to include ConverterObserver in its private data
 *
 * Revision 1.4  1999-09-01 09:16:30+01  peterm
 * Review Update
 *
 * Revision 1.3  1999-08-27 13:37:02+01  chrisg
 * Changed horrible TABS into nice SPACES :-)
 *
 * Revision 1.2  1999/08/24 17:00:11  peterm
 * Changes to BiffRecords
 *
 * Revision 1.1  1999-08-19 15:54:04+01  peterm
 * Initial revision
 *
 * Revision 1.1  1999-08-17 17:42:41+01  peterm
 * Initial revision
 *
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__ER97MAIN_H__)
#define __ER97MAIN_H__


#include "ercoelib.h"

/******************************************************************************
                              class CExcel9700StreamReader 
 ******************************************************************************
 */
#define STREAM_NAME_9700 _L16("Workbook")
class CExcel9700StreamReader:public MExcelStreamReader, public CBase
{
public:
    IMPORT_C static CExcel9700StreamReader *NewL(      COle2StreamPackage *aStream,
                                                 const TFileName& aTarget,
                                                       RFs& aFs,
		                                       MConverterUiObserver *aObserver);
    IMPORT_C ~CExcel9700StreamReader();
    IMPORT_C TBool DoConvertL();
    IMPORT_C TInt MaxStepsL();

private: // methods 
    CExcel9700StreamReader( const TFileName&          aTarget,
                                  RFs&                aFs,
		                  MConverterUiObserver *aObserver);
    void ConstructL(      COle2StreamPackage *aStream,
                    const TFileName&          aTarget,
                          RFs&                aFs);
    TInt ValidRecordType(CBiffRecord    *aLocalBiff);
    TInt ReturnConversionStatus(MConverterUiObserver::TResult aStatus);

private: // data
    CExcelLibraryR           *iExcelLibrary;
    COle2StreamPackage       *iExternalStream; //used for Workbook  - OR 200
    COle2StreamPackage       *iInternalStream; //used for Worksheet - OR 200
	MConverterUiObserver       *iConverterObserver;
    TFileName                 iTargetFile;
    RFs                       iFs; 
	TInt                      iMaxSteps;
	TInt                      iCurrentStep;
    
};

#endif // !defined (__ER97MAIN_H__)
