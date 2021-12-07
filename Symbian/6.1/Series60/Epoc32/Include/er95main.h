/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Excel Reader 95
 *
 * Identification   :   95 Stream Reader Classes[EXCEL_SDS]
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Workfile$, $Revision: 1.3 $
 *
 * Author           :   Peter Mead
 *
 * History          :   
 *
 * $Log: er95main.h,v $
 * Revision 1.3  2001/12/04 14:06:44  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.7  2000/01/18 10:20:58  stefania
 * OR 200, stream name now defined in er95main.h
 *
 * Revision 1.6  2000-01-17 17:31:29+00  stefania
 * OR 200, code changes for performance improvement.
 *
 * Revision 1.5  1999-10-28 10:20:01+01  stefania
 *  Changes for wide build and new EPOC sheet API.
 *
 * Revision 1.4  1999/10/20 13:00:28  peterm
 * review comments
 *
 * Revision 1.3  1999-10-19 14:32:03+01  peterm
 * Add ValidRecordType & ReturnConvertionStatus
 *
 * Revision 1.2  1999-10-08 13:47:15+01  peterm
 * Code Review Changes
 *
 * Revision 1.1  1999-09-22 12:43:23+01  peterm
 * Initial revision
 *

 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__ER95MAIN_H__)
#define __ER95MAIN_H__


#include "ercoelib.h"

/******************************************************************************
                              class CExcel95StreamReader 
 ******************************************************************************
 */
#define STREAM_NAME_95 _L16("Book")
class CExcel95StreamReader:public MExcelStreamReader, public CBase
{
public:
    IMPORT_C static CExcel95StreamReader *NewL(      COle2StreamPackage *aStream,
                                               const TFileName& aTarget,
                                                     RFs& aFs,
		                                             MConverterUiObserver *aObserver);
    IMPORT_C ~CExcel95StreamReader();
    IMPORT_C TBool DoConvertL();
    IMPORT_C TInt MaxStepsL();

private: // methods 
    CExcel95StreamReader( const TFileName&          aTarget,
                                RFs&                aFs,
		                MConverterUiObserver *aObserver);
    void ConstructL(      COle2StreamPackage *aStream,
                    const TFileName& aTarget,
                          RFs& aFs);
    TInt ValidRecordType(CBiffRecord    *aLocalBiff);
    TInt ReturnConversionStatus(MConverterUiObserver::TResult aStatus);

private: // data
    CExcelLibraryR           *iExcelLibrary;
    COle2StreamPackage *iExternalStream; //used for Workbook  - OR 200
    COle2StreamPackage *iInternalStream; //used for Worksheet - OR 200
	MConverterUiObserver       *iConverterObserver;
    TFileName                 iTargetFile;
    RFs                       iFs; 
	TInt                      iMaxSteps;
	TInt                      iCurrentStep;
};

#endif // !defined (__ER95MAIN_H__)
