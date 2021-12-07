/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Excel Reader: EXELCOMM.DLL
 *
 * Identification   :   Header file for CExcelRecord class
 *                      Encapsulate EPOC Sheet API.
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Workfile: $, $Revision: 1.3 $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: Excoepoc.h,v $
 * Revision 1.3  2001/12/04 14:06:42  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.16  1999/10/29 15:26:55  stefania
 * Code changes for OR number 80.
 *
 * Revision 1.15  1999/10/28 08:25:22  stefania
 * Changes for new EPOC sheet API, multiple spreadsheets support.
 *
 * Revision 1.14  1999-10-19 14:17:44+01  stefania
 * Changed LoadL. Added WorkBook() and NameSet( )
 *
 * Revision 1.13  1999-10-19 11:21:48+01  peterm
 * Added SetFormat methods
 *
 * Revision 1.12  1999-10-04 10:46:35+01  stefania
 * Added a few IMPORT_C
 *
 * Revision 1.11  1999-09-30 15:40:27+01  stefania
 * Added CurrentWorkSheet( ) and removed CurrentSheet( ) and CurrentSheetName( )
 *
 * Revision 1.10  1999-09-29 12:32:08+01  stefania
 * Added GridLay( )
 *
 * Revision 1.9  1999-09-29 12:14:04+01  stefania
 * Removed CurrentCell( ) method
 *
 * Revision 1.8  1999-09-28 13:37:10+01  stefania
 * Added *Format( ) methods.
 *
 * Revision 1.7  1999-09-17 14:35:32+01  stefania
 * First complete build of exelcomm.dll
 *
 * Revision 1.6  1999-09-15 14:01:08+01  stefania
 * Merge with basic drop
 *
 * Revision 1.5  1999-09-15 13:51:06+01  stefania
 * Basic drop merge.
 *
 * Revision 1.4  1999-09-14 14:10:10+01  stefania
 * Removed part of Set*( ) functions.
 *
 * Revision 1.3  1999-09-14 14:08:05+01  stefania
 * Removed Cell* functions and some of the construction functions
 *
 * Revision 1.2  1999-09-14 14:00:57+01  stefania
 * Few changes to return values.
 *
 * Revision 1.1  1999-09-08 11:08:50+01  stefania
 * Initial revision
 *
 * Revision 1.3  1999-09-03 16:16:45+01  stefania
 * Added methods for reading EPOC documents.
 *
 * Revision 1.2  1999-09-01 12:15:26+01  stefania
 * Changed return value from TCellError to TInt and removed range functions.
 *
 * Revision 1.1  1999/08/31 13:03:24  stefania
 * Initial revision
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__ERCOEREC_H__)
#define __ERCOEREC_H__

#include "excoelib.h"

#include <shgapi.h>    //CSheetEngine and other sheet classes
#include <shgpanic.h>  
#include <grdstd.h>    //CGridLay


/******************************************************************************
                              class CEpocRecord 
 ******************************************************************************
 */

typedef enum TShgCell::TType       TCellType;
typedef enum TShgCell::TErrorType  TCellErrorType;

//Class used to encapsulate EPOC Sheet API
//Hide API details to the rest of the code
class CEpocRecord : public CBase
{
 public:
    //DATA TYPES
    enum TType
    {
        ECell,
        ECellFormat,
        ERowFormat,
        EColumnFormat,
        ESheetFormat,
        EWorkBookFormat
    };

 public:
   //Construction, Destruction
    IMPORT_C static CEpocRecord* NewL( CSheetEngine* aEngine = NULL );
    IMPORT_C static CEpocRecord* NewLC( CSheetEngine* aEngine = NULL );
 
 private:
    //Private constructors
    CEpocRecord( CSheetEngine* aEngine );

 private:
    void ConstructL( );

 private:
    //COPY PROTECTION
    CEpocRecord( const CEpocRecord& ); //not allowed
    CEpocRecord& operator=(const CEpocRecord&); //not allowed

 public:
    //Class Destructor
    IMPORT_C virtual ~CEpocRecord( ); 

 public:
    //Read current cell data
    IMPORT_C TShgCell* const& Cell( ) const;

    //Read sheet grid lay (doc. in EPOC SDK)
    IMPORT_C CGridLay* GridLay( ) const;
   
 public:
	//record type
    IMPORT_C const TType& Type( ) const ;
	IMPORT_C void SetType ( const TType& aType ) ;

 public:
	 //Set internal co-ordinates
    IMPORT_C void SetCellCoord ( const TCellRef& aCoord ) ;

 public:
	//CELL FORMAT
	IMPORT_C const CParaFormatLayer *  ParagraphFormat( ) const ;
	IMPORT_C const CCharFormatLayer *  CharFormat( ) const ;
	IMPORT_C const TShgNumberFormat    NumberFormat( ) const ;

 public:
    IMPORT_C TShgError SetFormat( CParaFormatLayer * aFormat,   const TCellRef& aRef );
    IMPORT_C TShgError SetFormat( CCharFormatLayer * aFormat,   const TCellRef& aRef );
    IMPORT_C TShgError SetFormat( TShgNumberFormat * aFormat,   const TCellRef& aRef );
    IMPORT_C TShgError SetFormat( const TCellRef& aRef, CParaFormatLayer * aParaFormat,
                         CCharFormatLayer * aCharFormat, TShgNumberFormat * aNumFormat);
	 
 public:
	//READ A CELL 
	IMPORT_C TShgCell*& ReadCell( );
	IMPORT_C TShgCell*& ReadCell( const TCellRef& aRef );

  public:
    IMPORT_C TInt SetCellText ( const TCellRef& aRef, const TDesC& aTxt ) ;
    IMPORT_C TInt SetCellText ( const TDesC& aTxt   ) ;
    IMPORT_C void SetSheetL   ( const TInt   aIndex ) ;
    IMPORT_C TInt SetSheetL   ( const TDesC& aName  );

  public:
    IMPORT_C TInt NextCell( ); 
    IMPORT_C TInt NextRow( ); 
    IMPORT_C TInt NextSheet( );

    IMPORT_C TInt NumberOfCells( ) const;
    IMPORT_C TInt NumberOfRows( ) const;
    IMPORT_C TInt NumberOfSheets( ) const;

    IMPORT_C TInt                 CurrentRow( ) const;
    IMPORT_C TInt                 CurrentCol( ) const;
    IMPORT_C const CShgWorkSheet* CurrentWorkSheet( ) const;
    IMPORT_C const CShgWorkBook*  WorkBook( ) const;
    IMPORT_C const CShgNameSet*   NameSet( ) const;

    IMPORT_C TInt FirstRow( )    const;  
    IMPORT_C TInt FirstColumn( ) const;

    IMPORT_C TInt LastRow( )   const;
    IMPORT_C TInt LastColumn( )   const;

  public:
	//From MEpocRecord
	IMPORT_C void SaveL( const TDesC& aTargetFile, RFs& aFs );
    IMPORT_C void LoadL( CStreamStore* aStore, const CStreamDictionary* aDict );

  private:
	//Data
	TType                    iType;
	CSheetEngine           * iEngine;
	TBool                    iWeOwnEngine;
    TBool                    iFirstSheet;
    TShgCell               * iCell;
	TCellRef                 iCoord; 
   
};
	
#endif //__ERCOEREC_H__
 
