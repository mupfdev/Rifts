/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Excel Writer: EXELWRIT.DLL
 *
 * Identification   :   CExcelWriter and CMyConvLibrary classes
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvCommon/ewcomain.h,v 1.3 2001/12/04 14:06:43 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: ewcomain.h,v $
 * Revision 1.3  2001/12/04 14:06:43  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.12  2000/02/14 10:31:23  stefania
 * OR 228, moved static data from header files to source files (and removed static)
 *
 * Revision 1.11  2000-02-08 14:56:46+00  stefania
 * OR 221, removed redundant EXPORT_Cs
 *
 * Revision 1.10  1999/12/03 12:39:54  stefania
 * Changes for OR 057 (password protection).
 *
 * Revision 1.9  1999-11-29 10:19:36+00  chrisg
 * OR 301.121.115: Updating Conversion UIDs
 *
 * Revision 1.8  1999-10-29 13:32:10+01  stefania
 * Added uids. Removed include of exelwrit.h
 *
 * Revision 1.7  1999/10/28 08:22:49  stefania
 * Changes for new sheet API and new conarc API.
 *
 * Revision 1.6  1999-10-19 15:55:51+01  stefania
 * Fixed bug with TFileName.
 *
 * Revision 1.5  1999-10-19 15:26:38+01  stefania
 * Changes for code review.
 *
 * Revision 1.4  1999/10/01 14:35:24  stefania
 * Added Excel version differentation.
 *
 * Revision 1.3  1999-10-01 09:33:10+01  stefania
 * Added CExcelWriter destructor
 *
 * Revision 1.2  1999-09-17 14:35:04+01  stefania
 * First complete build of exelcomm.dll
 *
 * Revision 1.1  1999-09-15 13:59:23+01  stefania
 * Merge with basic drop
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__EWCO_WRIT_H__)
#define __EWCO_WRIT_H__

#include <e32base.h>
#include <e32std.h>   // CBase class
#include <f32file.h>  // RFile class
#include <e32def.h>
#include <conarc.h>   // Converter api

#include <cotrmain.h>
#include <cosyincs.h>
#include <ollomain.h>

//DLL AND CONVERSION UIDS FROM [EXEL_SDS] DOCUMENT
extern const TUid KUidExcelWriter;
extern const TUid KUidExcelWriter95;
extern const TUid KUidExcelWriter9700;

//PANIC FUNTION
void Panic ( const TInt errcode );

class CExcelStreamWriter;

/******************************************************************************
*                             class CMyConvLibrary
*******************************************************************************
*/
class CMyConvLibrary:public CConverterLibrary
{
public:
    CConverterBase* Converter(TUid aUid);
};


/******************************************************************************
                              class CExcelWriter
 ******************************************************************************
 */

class CExcelWriter : public CConverterBase
{
public:
    enum EVersion
    {
        E9700,  //Excel 97 and 2000, i.e. BIFF 8
        E95     //Excel 95, i.e. BIFF 7
    };
public:
     CExcelWriter(EVersion aVers) { iVersion = aVers; }
     ~CExcelWriter( );
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
private:
    RFs                  iFs; 
    TInt                 iMaxSteps;
    CExcelStreamWriter * iStreamWriter;
    const TFileName    * iTargetFile; 
    COle2File          * iOleFile;
    EVersion             iVersion;
};
    
    
#endif //  __EWCO_WRIT_H__
