/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Word Writer(wwcomain)
 *
 * Identification   :   Classes as identified in [ADS]
 *
 * SDS Ref          :   [ADS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/WordcnvCommon/wwcomain.h,v 1.3 2001/12/04 14:06:48 BijalShah Exp $
 *
 * Author           :   Ed Simons
 *
 * History          :   
 *
 * $Log: wwcomain.h,v $
 * Revision 1.3  2001/12/04 14:06:48  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.4  2000/02/14 16:26:21  stefania
 * OR 221, removed EXPORT_Cs from exelwrit.cnv
 *  and exelread.cnv
 *
 * Revision 1.3  1999-11-18 16:44:42+00  conorm
 * Put though wide compiler
 *
 * Revision 1.2  1999-10-27 09:34:19+01  conorm
 * Word Writer common library now handles both 95 and 97 cvonversions: OR61
 *
 * Revision 1.1  1999-09-30 14:37:07+01  eds
 * Initial revision
 *
 *
 *
 *
 * ---------------------------------------------------------------------------
 */

// NB. This file is extremely similar to "wrcomain.h"
 
#ifndef __WWCOMAIN_H__
#define __WWCOMAIN_H__

#include <e32base.h>
#include <f32file.h>
#include <e32def.h>
#include <Conarc.h>
#include <e32std.h>

#include "ollomain.h"
#include "wccoliby.h"  // For CWconLibrary


/******************************************************************************
*                             class CWconWriterConv
*******************************************************************************
*/
class CWconWriterConv:public CConverterLibrary
{
public:
    CConverterBase* Converter(TUid aUid);
};

/******************************************************************************
                              class CWconWriter 
 ******************************************************************************
 */

class CWconWriter : public CConverterBase
{

public:
    
     CWconWriter(TWconWordVersion aVersion) {iWordVersion=aVersion;}
     ~CWconWriter();

     void ConvertL(
                const TFileName& aSourceFile,
                const TFileName& aTargetFile,
                      MConverterUiObserver *aObserver=NULL);
     void ConvertAL(
                const TFileName& aSourceFile,
                const TFileName& aTargetFile,
                      MConverterUiObserver *aObserver=NULL);
     void ConvertObjectL(
                RReadStream& aReadStream,
                RWriteStream& aWriteStream,
                MConverterUiObserver* aObserver=NULL);
     void ConvertObjectAL(
                RReadStream& aReadStream,
                RWriteStream& aWriteStream,
                MConverterUiObserver* aObserver=NULL); 
    
     TBool  DoConvertL();
     TUid   Uid();
     TInt   Capabilities();
     void   CancelConvert();

private:    // methods

private:    // data

    RFs                 iFs;
    MConverterUiObserver* iConverterObserver;
    
    CWconLibrary        *iLibrary;
    TWconWordVersion    iWordVersion;

    void __DbgTestInvariant() const; 
};

#endif
