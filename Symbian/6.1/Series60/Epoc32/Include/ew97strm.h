/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Excel writer: EXLW9700.DLL
 *
 * Identification   :   CExcel9700StreamWriter classes
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvV97/ew97strm.h,v 1.3 2001/12/04 14:06:45 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: ew97strm.h,v $
 * Revision 1.3  2001/12/04 14:06:45  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.5  2000/02/08 14:59:44  stefania
 * OR 221, removed redundant EXPORT_Cs
 *
 * Revision 1.4  1999/10/28 08:18:48  stefania
 * Removed const from MConverterUiObserver parameter since conarc has changed.
 *
 * Revision 1.3  1999-10-07 17:42:31+01  stefania
 * Removed const from BiffFactory( ) parameter.
 *
 * Revision 1.2  1999-10-07 17:16:14+01  stefania
 * BiffFactory now using file server.
 *
 * Revision 1.1  1999-10-07 16:20:59+01  stefania
 * Initial revision
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__EWCO_9700_STRM_H__)
#define __EWCO_9700_STRM_H__ 

#include "ewcostrm.h"
#include "ew97bfac.h"

/******************************************************************************
                              class CExcel9700StreamWriter 
 ******************************************************************************
 */
class CExcel9700StreamWriter : public CExcelStreamWriter
{
public:
    CExcel9700StreamWriter( MConverterUiObserver* 
            aObserver ) : CExcelStreamWriter( aObserver ) { }
    virtual ~CExcel9700StreamWriter() { }
public:
  virtual const TPtrC StreamName( ) 
                 { return _L("Workbook"); }
  virtual CWriteBiffFactory* BiffFactory( RFs& aFs ) 
  { return CWriteBiff8Factory::NewL( aFs ); }
};

#endif // __EWCO_STRM_H__
