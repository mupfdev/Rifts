
/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   EXCELCOMM.DLL
 *
 * Identification   :   CExcelLibrary class
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvCommon/Excoelib.h,v 1.3 2001/12/04 14:06:42 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: Excoelib.h,v $
 * Revision 1.3  2001/12/04 14:06:42  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.20  2000/03/29 13:34:14  stefania
 * OR 237, character set conversion
 *
 * Revision 1.19  2000/02/14 10:31:24  stefania
 * OR 228, moved static data from header files to source files (and removed static)
 *
 * Revision 1.18  2000-02-09 16:59:37+00  stefania
 * OR 222
 *
 * Revision 1.17  2000-02-08 14:56:46+00  stefania
 * OR 221, removed redundant EXPORT_Cs
 *
 * Revision 1.16  1999/12/03 12:39:55  stefania
 * Changes for OR 057 (password protection).
 *
 * Revision 1.15  1999-11-29 10:19:37+00  chrisg
 * OR 301.121.115: Updating Conversion UIDs
 *
 * Revision 1.14  1999-10-15 13:18:39+01  stefania
 * Changed return of a few functions from TInt to void.
 *
 * Revision 1.13  1999-10-07 16:34:23+01  peterm
 * WriteBiffFactory parameter in NewL( ) now defaults to NULL.
 *
 * Revision 1.12  1999/10/01 14:36:31  stefania
 * Added BIFF factory class and new constructor.
 *
 * Revision 1.11  1999-09-28 17:33:04+01  stefania
 * Added EndRowL
 *
 * Revision 1.10  1999-09-21 10:35:34+01  stefania
 * Changed return type of End( ) methods from TInt to TBool
 *
 * Revision 1.9  1999-09-21 10:23:45+01  stefania
 * Added EndRowBlockL()
 *
 * Revision 1.8  1999-09-20 17:40:01+01  stefania
 * Added EndSheetL() and EndWorkBookL( ). Removed SaveDocumentL( )
 *
 * Revision 1.7  1999-09-17 14:35:25+01  stefania
 * First complete build of exelcomm.dll
 *
 * Revision 1.6  1999-09-16 18:01:55+01  peterm
 * Changes to constructor methods
 *
 * Revision 1.5  1999/09/15 16:03:19  peterm
 * Change cotrmain.h ollomain.h includes to user libraries
 *
 * Revision 1.4  1999-09-15 14:24:30+01  stefania
 * Fixed ^Ms.
 *
 * Revision 1.3  1999-09-15 14:01:08+01  stefania
 * Merge with basic drop
 *
 * Revision 1.2  1999-09-15 13:51:05+01  stefania
 * Basic drop merge.
 *
 * Revision 1.1  1999-09-08 11:08:48+01  stefania
 * Initial revision
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__EXCO_ELIB_H__)
#define __EXCO_ELIB_H__

//EPOC include files
#include <e32base.h>
#include <e32std.h>   
#include <f32file.h> 
#include <s32file.h> 
#include <e32def.h>    
#include <conarc.h>  
#include <apparc.h>

#include <charconv.h> //OR 237

//OLE 2 library
#include <ollomain.h>

//Trace library
#include <cotrmain.h>

//COMMON TYPES
#include <cosyincs.h>

extern const TUid KUidExelComm;

// Panic Function
void Panic( TInt errcode );

/******************************************************************************
                              class CExcelLibrary
 ******************************************************************************
 */

class CWriteBiffFactory;  //Factory funtion for BIFF records
class MConverterUiObserver; //CONARC converter observer

//ABC for CExcelLibraryR and CExcelLibraryW
//Implements data shared between the two
class CExcelLibrary : public CBase
{ 
public:
    //types
    enum ERequestType
    {
        EExcelRead, //for reading excel docs. imp. in CExcelLibraryR
        EExcelWrite //for writing excel docs., imp. in CExcelLibraryW
    };
    enum EVersion //OR 237
    { 
        EVersion9700 = 0 , 
        EVersion95 
    };                                                  
public:
    //construction, destruction
     IMPORT_C static CExcelLibrary* NewL ( const TFileName& aFileName, 
                                           const COle2StreamPackage* aOleStream, 
                                                 RFs&   aFs, 
                                           const ERequestType& aRequestType, 
                                                 CWriteBiffFactory* aBiffFactory = NULL,
                                           const EVersion& aVersion = EVersion9700 );
     IMPORT_C virtual ~CExcelLibrary();
public:
     //interface methods for writing
    //these are not pure virtual because are not needed by the 
    //CExcelLibraryR class
     virtual void  VerifyDocumentL( MConverterUiObserver * ) { }
     virtual TInt  NumberOfStepsL( ) { return KExcelNotSupported; }
     virtual void  CreateWorkBookL( ){ }
     virtual TBool EndWorkBookL( )   { return EFalse;             }
     virtual TInt  AddSheetL( )      { return KExcelNotSupported; } 
     virtual TBool EndSheetL( )      { return EFalse;             }
     virtual TInt  AddRowBlockL( )   { return KExcelNotSupported; }
     virtual void  EndRowBlockL( )   { }
     virtual void  AddRowL( )        { }
     virtual TInt  EndRowL( )        { return KExcelNotSupported; }
     virtual TInt  AddCellL( )       { return KExcelNotSupported; }

public:
    //interface methods for reading
    //cannot insert them since they expose the CBiff classes
    //for reading

public:
    //OR 237 - we need version information for char set conversion
    EVersion& Version( ) { return iVersion; }
    const EVersion& Version( ) const { return iVersion; }

    CCnvCharacterSetConverter*& 
        CharSetConverter( ) { return iCharSetConverter; }
    CCnvCharacterSetConverter* const & 
        CharSetConverter( ) const { return iCharSetConverter; }

public:
    IMPORT_C void ConvertAsciiToUnicodeL( TDes16& aBuf ); 
    IMPORT_C void ConvertUnicodeToAsciiL( TDes8& aBuf );

protected: 
    //construction
    CExcelLibrary( const TFileName& aFileName, 
                   const COle2StreamPackage* aOleStream, 
                         RFs&   aFs ); 
                  
    CExcelLibrary( const TFileName& aFileName, 
                   const COle2StreamPackage* aOleStream, 
                         RFs&   aFs, 
                   const CWriteBiffFactory* aBiffFactory );
    virtual void ConstructL( ) = 0;

protected:
    //data access to derived classes
    const TFileName& FileName( ) const { return iFileName; }
    const COle2StreamPackage* OleStream( ) const { return iOleStream; }
          RFs& Fs( )  { return iFs; }
    const RFs& Fs( ) const { return iFs; }
private:
    //OR 237, character set conversion
    void  PrepareCharSetConverterL( const EVersion& aVersion );
private: 
    // data
    const TFileName           iFileName;    //FILE NAME:  target in r.lib and source in w.lib
    const COle2StreamPackage* iOleStream;   //OLE STREAM: source in r.lib. and target in w.lib      
          RFs                 iFs;          //FILE SERVER

    //OR 237
    EVersion                    iVersion;
    CCnvCharacterSetConverter*	iCharSetConverter;
};

#endif //__EXCO_ELIB_H__
