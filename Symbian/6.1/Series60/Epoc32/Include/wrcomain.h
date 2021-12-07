/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Word Reader (wrcomain)
 *
 * Identification   :   Common Classes as identified in [WORD_SDS]
 *
 * SDS Ref          :   [WORD_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/WordcnvCommon/wrcomain.h,v 1.3 2001/12/04 14:06:48 BijalShah Exp $
 *
 * Author           :   Ghous Khan
 *
 * History          :   
 *
 * $Log: wrcomain.h,v $
 * Revision 1.3  2001/12/04 14:06:48  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.17  2000/02/14 16:26:20  stefania
 * OR 221, removed EXPORT_Cs from exelwrit.cnv
 *  and exelread.cnv
 *
 * Revision 1.16  1999-11-18 15:22:48+00  eds
 * Integration with ConArc.
 *
 * Revision 1.15  1999-09-30 11:17:21+01  conorm
 * Word 95 & 97 DLL merged into this.  See [OR24].
 *
 * Revision 1.14  1999/09/29 14:32:25  conorm
 * Changed for [WORD_SDS] Issue 2
 *
 * Revision 1.13  1999-09-14 13:02:12+01  ghousk
 * Created class CWconReaderConv
 *
 * Revision 1.12  1999/09/14 08:56:55  conorm
 * Ran through Linux "expand"
 *
 * 
 *
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#ifndef __WRCOMAIN_H__
#define __WRCOMAIN_H__

#include <e32base.h>
#include <f32file.h>
#include <e32def.h>
#include <Conarc.h>
#include <e32std.h>

#include "ollomain.h"
#include "wccoliby.h"  // For CWconLibrary
#include "wccoedoc.h"  // For CWconEpocDoc

/******************************************************************************
*                             class CWconReaderConv
*******************************************************************************
*/
class CWconReaderConv:public CConverterLibrary
{
public:
    CConverterBase* Converter(TUid aUid);
};

/******************************************************************************
                              class CWconReader 
 ******************************************************************************
 */

class CWconReader : public CConverterBase
{

public:
     ~CWconReader();
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
  
    void __DbgTestInvariant() const; 
};

#endif
