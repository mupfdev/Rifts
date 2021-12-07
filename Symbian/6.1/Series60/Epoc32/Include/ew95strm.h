/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Excel writer: EXLW95.DLL
 *
 * Identification   :   CExcel95StreamWriter classes
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvV95/ew95strm.h,v 1.3 2001/12/04 14:06:44 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: ew95strm.h,v $
 * Revision 1.3  2001/12/04 14:06:44  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.5  2000/02/08 14:58:06  stefania
 * OR 221, removed redundant EXPORT_Cs
 *
 * Revision 1.4  1999/10/28 08:19:25  stefania
 * Removed const from MConverterUiObserver parameter since conarc has changed.
 *
 * Revision 1.3  1999-10-07 17:42:24+01  stefania
 * Removed const from BiffFactory( ) parameter.
 *
 * Revision 1.2  1999-10-07 17:16:08+01  stefania
 * BiffFactory now using file server.
 *
 * Revision 1.1  1999-10-07 16:20:44+01  stefania
 * Initial revision
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__EWCO_95_STRM_H__)
#define __EWCO_95_STRM_H__ 

#include "ewcostrm.h"
#include "ew95bfac.h"

/******************************************************************************
                              class CExcel9700StreamWriter 
 ******************************************************************************
 */
class CExcel95StreamWriter : public CExcelStreamWriter
{
public:
    CExcel95StreamWriter( MConverterUiObserver* 
            aObserver ) : CExcelStreamWriter( aObserver ) { }
    virtual ~CExcel95StreamWriter() { }
public:
  virtual const TPtrC StreamName( ) 
                 { return _L("Book"); }
  virtual CWriteBiffFactory* BiffFactory(  RFs& aFs ) 
  { return  CWriteBiff7Factory::NewL( aFs ); }
};

#endif // __EWCO_95_STRM_H__
