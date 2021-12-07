/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Word Library Class (wccoliby)
 *
 * Identification   :   Word Common Library Classes as identified in [WORD_SDS]
 *
 * SDS Ref          :   [WORD_SDS]
 *
 * Filename         :   $Revision: 1.3 $
 *
 * Author           :   Ed Simons
 *
 * History          :   
 *
 * $Log: wccoliby.h,v $
 * Revision 1.3  2001/12/04 14:06:47  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.23  2000/02/14 16:26:20  stefania
 * OR 221, removed EXPORT_Cs from exelwrit.cnv
 *  and exelread.cnv
 *
 * Revision 1.22  1999-12-14 17:49:51+00  ghousk
 * Implemented support for Password protected EPOC Word docs
 *
 * Revision 1.21  1999-11-10 11:48:42+00  conorm
 * [OR110] InitialiseL() method removed
 *
 * Revision 1.20  1999-10-28 11:24:49+01  eds
 * WPI : 301.033.029 : Preparing for Unicode build.
 *
 * Revision 1.19  1999-10-26 16:22:50+01  conorm
 * wccoliby changed to allow specification of Word version
 *
 * Revision 1.18  1999-10-13 12:43:22+01  eds
 * Fixed bug with NumStepsL and DoStepL.
 *
 * Revision 1.17  1999-10-13 10:20:25+01  conorm
 * CM_REVIEW_002 fixes
 *
 * Revision 1.16  1999-10-09 16:02:20+01  eds
 * Added endnote handling.
 *
 * Revision 1.15  1999-10-08 14:33:37+01  conorm
 * Changes to library architecture
 *
 * Revision 1.14  1999-10-08 11:32:25+01  conorm
 * Prelimary changes to MWconDoc design
 *
 * Revision 1.13  1999-10-04 11:28:52+01  eds
 * Character counting moved from library to document classes.
 *
 * Revision 1.12  1999-09-30 11:16:24+01  conorm
 * InitialiseL() added.
 *
 * Revision 1.11  1999/09/29 15:34:58  conorm
 * Changed for [WORD_SDS] Issue 2
 *
 * Revision 1.10  1999-09-27 18:35:12+01  eds
 * Top-level re-work for Final Drop.
 *
 * Revision 1.9  1999/09/27 16:14:37  eds
 * Changes required for Final Drop - Converter/Library interface issues.
 *
 * Revision 1.8  1999-09-13 17:03:17+01  ghousk
 * Removed class data member iFs
 *
 * Revision 1.7  1999/09/07 13:19:45  ghousk
 * Added Trace Initialisation
 *
 * Revision 1.6  1999/09/07 10:51:58  ghousk
 * Destructor definition moved to wccoliby.cpp
 *
 * Revision 1.5  1999/09/06 10:20:03  ghousk
 * exported method ProcessTextSegmentL()
 *
 * Revision 1.4  1999-09-06 10:33:13+01  eds
 * Made COle2StreamPackages const.
 *
 * Revision 1.3  1999-09-03 18:13:43+01  eds
 * Made functions exportable.
 *
 * Revision 1.2  1999-09-03 17:14:59+01  eds
 * Ready for code review.
 *
 * Revision 1.1  1999-09-01 16:36:27+01  eds
 * Initial revision
 *
 *
 *
 *
 * ---------------------------------------------------------------------------
 */

#ifndef __WCCOLIBY_H__
#define __WCCOLIBY_H__

#include <e32std.h>

#include "ollomain.h"
#include "wccoincs.h"
#include "wccomdoc.h"
#include "wccoedoc.h"

//extern GLDEF_C void Panic(TInt);


class CWconLibrary : public CBase
{
public:
                                    ~CWconLibrary();
    IMPORT_C static CWconLibrary*   NewL(const TFileName&       aSourceFilename,
                                         TWconWordVersion       aSourceVersion,   
                                         const TFileName&       aDestinationFilename,
                                         TWconWordVersion       aDestinationVersion,
                                         RFs&                   aFs,
                                         const TPassword*       aPassword = NULL
                                         );
   
                    TInt            NumStepsL() { return iSourceDoc->NumStepsL( ); }
                    TInt            DoStepL() { return iSourceDoc->DoStepL( ); }
    IMPORT_C        TInt            SaveConversionL();


protected:
    void            ConstructL(  const TFileName&       aSourceFilename,
                                 TWconWordVersion       aSourceVersion,   
                                 const TFileName&       aDestinationFilename,
                                 TWconWordVersion       aDestinationVersion,
                                 RFs&                   aFs,
                                 const TPassword*       aPassword = NULL
                                 );

private: // methods.
                    CWconLibrary() {};

private: // data.
    MWconSourceDoc*             iSourceDoc;
    MWconDestinationDoc*        iDestinationDoc;

    __DECLARE_TEST;
};


#endif
