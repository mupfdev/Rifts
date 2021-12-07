/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Excel Reader (ercomain)
 *
 * Identification   :   Common Classes as identified in [EXCEL_SDS]
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvCommon/ercomain.h,v 1.3 2001/12/04 14:06:43 BijalShah Exp $
 *
 * Author           :   Peter Mead
 *
 * History          :   
 *
 * $Log: ercomain.h,v $
 * Revision 1.3  2001/12/04 14:06:43  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.18  2000/02/08 14:56:42  stefania
 * OR 221, removed redundant EXPORT_Cs
 *
 * Revision 1.17  2000/01/17 17:27:30  stefania
 * OR 200, code changes for performance improvement
 *
 * Revision 1.16  1999/10/28 08:22:47  stefania
 * Changes for new sheet API and new conarc API.
 *
 * Revision 1.15  1999-10-11 14:55:28+01  peterm
 * Code Review Changes
 *
 * Revision 1.14  1999/09/09 15:27:50  peterm
 * Change CMyConvLibrary to CExcelReaderConv
 *
 * Revision 1.13  1999-09-07 14:11:40+01  peterm
 * Add ExcelReader Distructor
 *
 * Revision 1.12  1999-09-07 13:38:48+01  peterm
 * Added virtual destructor for MExcelStreamReader
 *
 * Revision 1.11  1999-09-02 10:20:22+01  stefania
 * Removed commented out destructor of CExcelReader.
 *
 * Revision 1.10  1999-09-02 09:58:44+01  stefania
 * Few minor changes for first built.
 *
 * Revision 1.9  1999/09/01 14:46:43  chrisg
 * Added ConvertObjetL() and ConvertObjectAL() functions to class,
 * thier implementations should just LEAVE
 *
 * Revision 1.8  1999-09-01 14:33:44+01  chrisg
 * Corrected the const-ness of the Convert.... methods, and MExcelStreamReader is now
 * pure virtual (as it should be)
 *
 * Revision 1.7  1999-09-01 09:15:23+01  peterm
 * Review Update
 *
 * Revision 1.6  1999-08-27 13:33:32+01  chrisg
 * Changed the 'orrible TABS into nice spaces :-)
 *
 * Revision 1.5  1999/08/24 16:58:56  peterm
 * Changes to BiffRecords
 *
 * Revision 1.4  1999-08-19 17:27:59+01  peterm
 * Changed History
 *
 * Revision 1.3  1999-08-19 17:24:07+01  peterm
 * Add MExcelStreamReader
 *
 * Revision 1.2  1999-08-17 17:23:21+01  peterm
 * <>
 *
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__ERCOMAIN_H__)
#define __ERCOMAIN_H__
/******************************************************************************
*                             class CExcelReaderConv
*******************************************************************************
*/
class CExcelReaderConv:public CConverterLibrary
{
public:
    CConverterBase* Converter(TUid aUid);
};

/******************************************************************************
                              class MExcelStreamReader 
 ******************************************************************************
 */
class MExcelStreamReader
{
public:
    virtual ~MExcelStreamReader() {}
    virtual TBool DoConvertL() = 0;
    virtual TInt MaxStepsL()   = 0;
};

/******************************************************************************
                              class CExcelReader 
 ******************************************************************************
 */
class CExcelReader:public CConverterBase
{
public:
     void ConvertL(const TFileName&          aSourceFile,
                           const TFileName&          aTargetFile,
                                 MConverterUiObserver *aObserver = NULL);
     void ConvertAL(const TFileName&          aSourceFile,
                            const TFileName&          aTargetFile,
                                  MConverterUiObserver *aObserver = NULL);
     void ConvertObjectAL(      RReadStream&       aSourceStream,
                                        RWriteStream&      aTargetStream,
                                        MConverterUiObserver *aObserver = NULL);
     void ConvertObjectL(       RReadStream&       aSourceStream,
                                        RWriteStream&      aTargetStream,
                                        MConverterUiObserver *aObserver = NULL);
     TBool DoConvertL();
     TUid Uid();
     TInt Capabilities();
     void CancelConvert();
     ~CExcelReader();

private:
    TFileName           iSourceFile;
    TFileName           iTargetFile;
    TInt                iMaxSteps;
    RFs                 iFs; 
    MExcelStreamReader *iStreamReader;
    COle2File          *iOleFile;
    COle2StreamPackage *iOleStream;

};
    
IMPORT_C TAny* GateFunction();
void Panic(TInt aPanic);

#endif // !defined (__ERCOMAIN_H__)
