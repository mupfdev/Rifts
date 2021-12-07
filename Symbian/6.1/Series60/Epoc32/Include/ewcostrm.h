/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Excel writer: EXELWRIT.DLL
 *
 * Identification   :   MExcelStreamWriter and CExcelStreamWriter classes
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvCommon/ewcostrm.h,v 1.3 2001/12/04 14:06:44 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: ewcostrm.h,v $
 * Revision 1.3  2001/12/04 14:06:44  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.9  2000/02/08 14:56:46  stefania
 * OR 221, removed redundant EXPORT_Cs
 *
 * Revision 1.8  1999/10/28 08:22:50  stefania
 * Changes for new sheet API and new conarc API.
 *
 * Revision 1.7  1999-10-19 15:55:44+01  stefania
 * Fixed bug with TFileName.
 *
 * Revision 1.6  1999-10-19 15:26:45+01  stefania
 * Changes for code review.
 *
 * Revision 1.5  1999/10/07 16:42:18  stefania
 * Removed const from BiffFactory( ) parameter.
 *
 * Revision 1.4  1999-10-07 17:16:19+01  stefania
 * BiffFactory now using file server.
 *
 * Revision 1.3  1999/10/01 14:36:04  stefania
 * Added OLE stream package and biff factory class.
 *
 * Revision 1.2  1999-10-01 09:34:08+01  stefania
 * Added NewL( ) method.
 *
 * Revision 1.1  1999-09-15 13:59:23+01  stefania
 * Merge with basic drop
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__EWCO_STRM_H__)
#define __EWCO_STRM_H__ 

//EPOC include files
#include <e32base.h>
#include <e32std.h>   // CBase class
#include <f32file.h>  // RFile class
#include <e32def.h>   
#include <conarc.h>   //MConverterUiObserver class

#include <cosyincs.h> //System Error codes

#include "excoelib.h" //CExcelLibrary

/******************************************************************************
                              class MExcelStreamWriter 
 ******************************************************************************
 */
class CWriteBiffFactory;

//Interface class for CExcelStreamWriter derived classes
//and derived classes
class MExcelStreamWriter 
{
public:
    virtual TBool   DoConvertL()                = 0; //imp. in CExcelStreamWriter
    virtual TInt    MaxSteps()                  = 0; //imp. in CExcelStreamWriter
    virtual const TPtrC StreamName( )           = 0; //imp. in derived version classes
    virtual CWriteBiffFactory* BiffFactory( RFs& aFs )   
                                                = 0; //imp. in derived version classes 
};

/******************************************************************************
                              class CExcelStreamWriter 
 ******************************************************************************
 */
class CExcelStreamWriter : public CBase, public MExcelStreamWriter
{
public:
     CExcelStreamWriter( MConverterUiObserver* aObserver );
     ~CExcelStreamWriter( );
public:
    //implementation of MExcelStreamWriter methods
     TBool DoConvertL();
     TInt MaxSteps();
public:
    CExcelLibrary*&        Library( ) { return iExcelLibrary; }
    CExcelLibrary* const & Library( ) const { return iExcelLibrary; }
    COle2StreamPackage*&        OleStream( ) { return iOleStream; }
    COle2StreamPackage* const & OleStream( ) const { return iOleStream; }
    COle2File*&        OleFile( ) { return iOleFile; }
    COle2File* const & OleFile( ) const { return iOleFile; }
    RFs&         Fs( ) { return iFs; }
    RFs const &  Fs( ) const { return iFs; }
    const TFileName*& TargetFile( ) { return iTargetFile; }
    const TFileName* const & TargetFile( ) const { return iTargetFile; }
private: 
    // data
    CExcelLibrary            * iExcelLibrary;
    COle2StreamPackage       * iOleStream;
    MConverterUiObserver       * iConverterObserver;
    COle2File                * iOleFile;
    const TFileName*           iTargetFile;
    RFs                        iFs;
	TInt                       iMaxSteps;
	TInt                       iCurrentStep;
};

#endif // __EWCO_STRM_H__
