/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   EXELCOMM.DLL
 *
 * Identification   :   BiffRecords Classes relative to Excel writer
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvCommon/Ewcobiff.h,v 1.3 2001/12/04 14:06:41 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: Ewcobiff.h,v $
 * Revision 1.3  2001/12/04 14:06:41  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.32  2000/03/29 15:33:01  stefania
 * OR 235, added trailing L to SetValues( ) as it calls a function that leaves.
 *
 * Revision 1.31  2000-03-20 16:27:08+00  stefania
 * OR 235: Now font names are processed by fontconv.dll
 *
 * Revision 1.30  2000-02-09 16:59:35+00  stefania
 * OR 222
 *
 * Revision 1.29  2000-02-08 14:56:44+00  stefania
 * OR 221, removed redundant EXPORT_Cs
 *
 * Revision 1.28  2000/01/07 16:03:21  stefania
 * Fixed bug in CWriteBiffFormula::WriteErrorL(). Discovered while investigating COR 015.
 *
 * Revision 1.27  1999/12/03 12:08:08  stefania
 * Fixed OR 104 (nothing to print)
 *
 * Revision 1.26  1999/10/25 13:51:59  stefania
 * Code fixes for urel arm build.
 *
 * Revision 1.25  1999-10-22 09:59:46+01  stefania
 * Added CWriteBiffFORMAT::operator !=
 *
 * Revision 1.24  1999-10-20 13:31:05+01  stefania
 * Added __DECLARE_TEST to CWriteBiffRecord.
 *
 * Revision 1.23  1999-10-20 10:32:13+01  stefania
 * Replaced delete with macro DELETE and inserted a couple of comments.
 *
 * Revision 1.22  1999-10-18 14:14:36+01  stefania
 * Added != operator to MString. Added SkipRecordL and Set to CWriteBiffRow. Added
 * FontName( ) to CWriteBiffFont.
 *
 * Revision 1.21  1999-10-15 16:11:31+01  stefania
 * Added  CWriteBIFFFormat::WriteStringLengthL( ).
 *
 * Revision 1.20  1999/10/15 12:17:41  stefania
 * Changed return of Write functions from TInt to void.
 *
 * Revision 1.19  1999-10-15 09:26:29+01  stefania
 * WriteL functions return void rather than TInt.
 *
 * Revision 1.18  1999-10-14 17:57:04+01  stefania
 * Changes for code review.
 *
 * Revision 1.17  1999-10-14 17:07:35+01  stefania
 * Comment format.
 *
 * Revision 1.16  1999-10-14 15:04:21+01  stefania
 * Removed operator != from CWriteBiffXF class.
 *
 * Revision 1.15  1999/10/14 10:25:05  stefania
 * Added alignment enums to CWriteBiffXF. Added != operators to CWriteBiffXF and CWriteBiffFONT.
 *
 * Revision 1.14  1999/10/11 10:22:01  stefania
 * Added Set(RFormula&) method.
 *
 * Revision 1.13  1999/10/07 14:19:53  stefania
 * Few minor changes.
 *
 * Revision 1.12  1999-10-05 16:23:06+01  stefania
 * Added a few IMPORT_Cs. Added FONT and FORMAT records. Moved
 * MString at the beginning.
 *
 * Revision 1.11  1999-10-01 15:37:54+01  stefania
 * Moved include of ewcobift.h
 *
 * Revision 1.10  1999-10-01 15:37:02+01  stefania
 * Added factory class.
 *
 * Revision 1.9  1999-10-01 09:31:50+01  stefania
 * Added CWriteBIFFXF::ResetToDefault( )
 *
 * Revision 1.8  1999-09-30 16:13:08+01  stefania
 * Added COLINFO and PAGEBREAKS records. Moved BOF8 record.
 *
 * Revision 1.7  1999-09-22 12:58:11+01  stefania
 * Added SetOlePosition( )
 *
 * Revision 1.6  1999-09-20 11:47:00+01  stefania
 * Removed everything from excobiff.h to here
 *
 * Revision 1.4  1999-09-15 17:50:25+01  stefania
 * Added BOUNDSHEET and XF records
 *
 * Revision 1.3  1999-09-15 14:01:08+01  stefania
 * Merge with basic drop
 *
 * Revision 1.1  1999-09-08 11:08:31+01  stefania
 * Initial revision
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__EWCO_BIFF_H__)
#define __EWCO_BIFF_H__

//EPOC include files
#include <e32base.h>
#include <e32std.h>   
#include <f32file.h> 
#include <s32file.h> 
#include <e32def.h>    
#include <conarc.h>  
#include <shgapi.h> 
#include <apparc.h>

//BIFF RECORD TYPES
#include "ewcobift.h"

//RFORMULA
#include "ewcoform.h"

class CFormat;
class CFontFormat;
class CNumberFormat;
class CEpocRecord;
class CExcelLibrary;
class COle2StreamPackage;
class CWriteBiffFactory;
class CWriteBiff8Factory;
class CWriteBiff7Factory;

/******************************************************************************
                              class MString 
 ******************************************************************************
 */

//Interface class for strings
//BIFF7 records will use CString7, which is a non-unicode string
//BIFF8 records will use CString8, which is a unicode string
//Can't use descriptors directly since UNICODE strings have got
//formatting and compression as well, see MSDN page 264.
class MString
{
public:
    virtual ~MString( ) { }
public:
     virtual void  WriteL( const COle2StreamPackage* aStream ) = 0 ;
     virtual void  SetL( const TDesC& aDes ) = 0;
     virtual const TInt16 StringLength( ) const = 0 ;
     virtual const TInt16 StringSize( ) const = 0 ;
     virtual void  Compress( ) = 0;
     virtual void  UnCompress( ) = 0;
     friend TBool operator!=(const MString& aStr1,const MString& aStr2)
        { return aStr1.Compare( &aStr2 ); }
protected:
     virtual TBool Compare(const MString*) const = 0;
};

/******************************************************************************
                              class CWriteBiffRecord 
 ******************************************************************************
 */
class CWriteBiffRecord : public CBase
{
public:
    friend class CWriteBiff8Factory; //factory class for BIFF 8 version
    friend class CWriteBiff7Factory; //factory class for BIFF 7 version
public:
    enum{ KHeaderLength = 4 };
public:
     virtual ~CWriteBiffRecord( ) { }
public:  
    //common fat interface for all biff records
    //not pure virtual since do not apply to every derived class
    IMPORT_C virtual void SkipRecordL();
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
     virtual void Set( const TInt32    ) { }
     virtual void Set( const TDesC&    ) { }
     virtual void Set( const RFormula& ) { }

     virtual void Set( const CFormat* aFormat ) { iFormat = aFormat; }
     virtual void Set(       CWriteBiffFactory* aFactory ) { iFactory = aFactory; }
     
     virtual TInt Next( ) { return KErrNone; }
public:
    //data access 
     EBiffType& Type( ) { return iType; }
     const EBiffType& Type( ) const { return iType; }

     TInt&   Pos( ) { return iPos; }
     const TInt&   Pos( ) const { return iPos; }
public:
    //utility functions
    IMPORT_C void AdvanceOlePositionL(const TInt aPos );
protected:
    //Data access to derived classes
     const  COle2StreamPackage * & Stream( ) { return iStream; }
     const  COle2StreamPackage * const & Stream( ) const { return iStream; }

     TInt16& Length( ) { return iLength; }
     const TInt16& Length( ) const { return iLength; }
protected:
    //called by WriteL( ) before writing the length, 
    //every class should ovverwrite this with its
    //data length (no header)
     virtual TInt RecordLength( ) { return 0; }
protected:
    //Construction, Destruction
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
protected:
    const CFormat* const & Format( ) const { return iFormat; }
    CWriteBiffFactory*       & Factory( )       { return iFactory; }
    CWriteBiffFactory* const & Factory( ) const { return iFactory; }
private:
    //data
    const  COle2StreamPackage *iStream;
    EBiffType  iType;
    TInt       iPos;
    TInt16     iLength;
    
    const CFormat*           iFormat; //used to obtain xf index
          CWriteBiffFactory* iFactory; 
                    //used to replace a biff record with another one,
                    //for example a formula with its evaluated value
    
    __DECLARE_TEST; 
};

/******************************************************************************
                              class CWriteBiffSingle 
 ******************************************************************************
 */
class CWriteBiffSingle : public CWriteBiffRecord
{
public:
    static const TInt8 KDataSize;
public:
     virtual ~CWriteBiffSingle( ) { }
protected:
    IMPORT_C void WriteL( const CEpocRecord* = NULL, const CWriteBiffRecord* = NULL );
protected:
     CWriteBiffSingle( ) { }
    IMPORT_C virtual TInt RecordLength( );
};


///////////////
//BOF record//
/////////////
class CWriteBiffBOF : public CWriteBiffRecord
{
public:
    //sub stream type
    enum ESubStreamType { EWorkbook = 0x0005, EWorksheet = 0x0010 };
public: 
    IMPORT_C CWriteBiffBOF( const ESubStreamType& aType ); 
     virtual ~CWriteBiffBOF( ) { }
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
     virtual void SetDefaultValues( ) = 0;
protected:
    //Data
    TInt16  iBiffVersion;     //BIFF Version
    TInt16  iDt;              //Substream type
    TUint16 iBuildIdentifier; //Build identifier
    TInt16  iBuildYear;       //Build year
};

///////////////
//EOF record//
/////////////
class CWriteBiffEOF : public CWriteBiffRecord
{
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
};

/////////////////
//INDEX record//
///////////////
class CWriteBiffINDEX : public CWriteBiffRecord
{ 
public:
    static const TInt KOffsetSize;  //size of DBCELL records offset 
    static const TInt KDataLength;  //size of data a part from offsets 
public:
    IMPORT_C virtual ~CWriteBiffINDEX( );
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
    IMPORT_C virtual void Set( const TInt32 aValue );
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
protected:
     virtual void WriteRows ( const TInt aFirstRow, const TInt aLastRow ) = 0; 
private:
    //Data
    TInt iBlocks;                          //Number of ROW blocks following INDEX record
    CArrayFixSeg<TInt32>* iDbCellOffsets;  //variable length vector of dbcell offsets
    TInt                  iStartPosition;  //position at the beginning
    
};

//////////////////
//DBCELL record//
////////////////
class CWriteBiffDBCELL : public CWriteBiffRecord
{ 
public:
    //Constants
    static const TInt KRowOffsetSize; //Size of row offset
    static const TInt KCellOffsetSize; //Size of cell offsets
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL); 
    IMPORT_C virtual void Set( const TInt32 aPos );
public:
    IMPORT_C virtual ~CWriteBiffDBCELL( );
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
private:
    //Data
    CArrayFixSeg<TInt16>* iCellOffsets;   //variable length vector of cell offsets
    TInt                  iStartPosition; //position of first row record
};

//////////////////
//ROW record   //
////////////////
class CWriteBiffROW : public CWriteBiffRecord
{ 
public:
    static const TInt KRecordLength; //record length
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL); 
    IMPORT_C virtual void Set( const TInt32  aInt  ) { iNumberOfRows = aInt; }
    IMPORT_C virtual void SkipRecordL();
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
private:
    TInt  iStartPosition;  //position when we are created
    TInt  iNumberOfRows;   //used by SkipRecord for leaving space
};

/////////////////////
//COLUMN record   //
///////////////////
class CWriteBiffCOLINFO : public CWriteBiffRecord
{ 
public:
    static const TInt KRecordLength; //record length
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL); 
    IMPORT_C virtual void Set(const TInt32 aNum) { iColNumber = STATIC_CAST(TInt16, aNum ); }
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
private:
    TInt16 iColNumber;
};

///////////////////////////
//     PAGE BREAKS      //
/////////////////////////
//Common base class for page breaks
class CWriteBiffPAGEBREAKS : public CWriteBiffRecord
{ 
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
    IMPORT_C virtual void Set(const TInt32 aNum);
     virtual ~CWriteBiffPAGEBREAKS( ) { DELETE (iBreaks); }
protected:
    IMPORT_C virtual TInt RecordLength( );
     virtual TInt SizeOfRgBrk( ) = 0;
     CArrayFixSeg<TInt16>* Breaks( ) const { return iBreaks; }
private:
    CArrayFixSeg<TInt16>* iBreaks;
};

//////////////////////////////
//VERTICAL PAGE BREAK      //
////////////////////////////
class CWriteBiffVERTICALPAGEBREAKS : public CWriteBiffPAGEBREAKS
{ 
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
};

//////////////////////////////
//HORIZONTAL PAGE BREAK    //
////////////////////////////
class CWriteBiffHORIZONTALPAGEBREAKS : public CWriteBiffPAGEBREAKS
{ 
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
};

////////////////////
//    NUMBERS    //
//////////////////
class CWriteBiffNUMBER  : public CWriteBiffSingle
{ 
public:
    static const TInt KIeeeLength; //Length of record in bytes
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL); 
public:
    static void Encode( TReal64 aIntNumber, TDes8& aBuf );
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
};

///////////////////
// LABEL        //
/////////////////
class CWriteBiffLABEL : public CWriteBiffSingle
{ 
public:
     virtual ~CWriteBiffLABEL( ) { DELETE (iString); }
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL) = 0;
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
    MString*& String( ) { return iString; }
    MString * const & String( ) const { return iString; }
private:
    MString* iString;
};

//////////////////////////
//  STRING             //
////////////////////////
//strings following formulas or array of formulas
class CWriteBiffSTRING : public CWriteBiffRecord
{ 
public:
     virtual ~CWriteBiffSTRING( ) { DELETE (iString); }
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL) = 0; 
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
     MString*& String( ) { return iString; }
     MString * const & String( ) const { return iString; }
private:
    MString* iString;
};

//////////////////////////
//  BLANK              //
////////////////////////
class CWriteBiffBLANK : public CWriteBiffSingle
{ 
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL); 
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
};

//////////////////////////
//  FORMULA            //
////////////////////////
class CWriteBiffFORMULA : public CWriteBiffSingle
{ 
public:
    //Constants
    static const TInt KDataLength; //length of record data a part from formula
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL); 
     virtual void Set(const RFormula& aFormula) { iFormula = aFormula; }
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
     virtual void InitFormulaTable( ) const = 0;
     RFormula& Formula( ) { return iFormula; }
     const RFormula& Formula( ) const { return iFormula; }
private:
    void WriteErrorL( const CEpocRecord* );
private:
    TInt      iFormulaLength; //formula length
    RFormula  iFormula;
};

//////////////////////////
//  BOOLERR            //
////////////////////////
class CWriteBiffBOOLERR : public CWriteBiffSingle
{
public:
    //a formula which is not supported has to be able to write an error
    friend class CWriteBiffFORMULA;
public:
    //types
    enum EExcelError
    {
        EErrNull = 0,          //#NULL!
        EErrDivByZero = 7,     //#DIV/0!
        EErrValue = 15,        //#VALUE!
        EErrRef = 23,          //#REF!
        EErrName = 29,         //#NAME?
        EErrNum = 36,          //#NUM!
        EErrNotAvailable = 42, //#N/A!
    };
public:
    //constants
    static const TInt KRecordLength;
public:
    //convert from epoc to excel error
    IMPORT_C static EExcelError TranslateError (const TShgCell::TErrorType& aError );
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL); 
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
};

//////////////////////////
//  BOUNDLESHEETT      //
////////////////////////
class CWriteBiffBOUNDSHEET : public CWriteBiffRecord
{ 
public:
    //consts
    static const TInt KRecordLength;
public:
    IMPORT_C virtual ~CWriteBiffBOUNDSHEET( );
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL); 
    IMPORT_C virtual void SkipRecordL( );
    IMPORT_C virtual void Set(const TDesC& aName); 
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
protected:
     virtual MString* SheetNameLC( ) const = 0;
protected:
     HBufC*& SheetName( ) { return iSheetName; }
     HBufC* const & SheetName( ) const { return iSheetName; }
private:
    TInt     iStartPos;
    HBufC*  iSheetName;
    TUint8   iStringLength;
};

///////////////////////////
// Extended Format (XF) //
/////////////////////////
class CWriteBiffXF : public CWriteBiffRecord
{ 
public:
    friend class CFormat;  //class for formatting
public:
    //not used yet
    enum TAlignment
    {
        EGeneral         = 0x00,
        ELeft            = 0x01,
        ECenter          = 0x02,
        ERight           = 0x03,
        EFill            = 0x04,
        EJustify         = 0x05,
        ECenterAcrossSel = 0x06
    };
    //not used yet
    enum TVerticalAlignment
    {
        EVerticalTop     = 0x00,
        EVerticalCenter  = 0x01,
        EVerticalBottom  = 0x02,
        EVerticalJustify = 0x03
    };
public:
    //XF type
    enum EXFType { ECell, EStyle };
public:
     CWriteBiffXF(const EXFType& aType) : CWriteBiffRecord( ), iType(aType) { }
     virtual ~CWriteBiffXF( ) { }
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL); 
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
     virtual TInt RecordLength( ) = 0;
     virtual void WriteFixedStyleL( ) const = 0;
     virtual void WriteFixedCellL( ) const = 0;
private:
    //interface to friend classes, i.e. format classes,
    //even if these could use data directly, I'll avoid it
    void ResetToDefault( );
    TInt16& Fnt( ) { return iFnt;  } 
    const TInt16& Fnt( ) const { return iFnt;  }
    TInt16& Fmt( ) { return iFmt;  }
    const TInt16& Fmt( ) const { return iFmt;  }
private:
    //data
    EXFType            iType;              //XF type
    TInt16             iFnt;               //index to FONT records
    TInt16             iFmt;               //index to FORMAT records or built-in format
    TAlignment         iAlignment;         //horiz. text alignment
    TVerticalAlignment iVerticalAlignment; //vert. text alignment
    TBool              iWrapText;          //true if text wraps around
    TInt16             iForColorIdx;       //color index of forward fill pattern
    TInt16             iBackColorIdx;      //color index of backward fill pattern
};

////////////////////////
//      FONT         //
//////////////////////
class CFontConverter; //forward declarations
class CColorPalette;
class CWriteBiffFONT : public CWriteBiffRecord
{ 
public:
    friend class CFontFormat;  //class for font formatting
public:
    //types
    enum EPosition {ENone,ESuperscript,ESubscript};
public:
     virtual ~CWriteBiffFONT( ) { DELETE( iFontName ); }
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL); 
    IMPORT_C friend TBool operator!=(const CWriteBiffFONT&, const CWriteBiffFONT&);
public:
    //Font name depends on BIFF version since it's unicode for BIFF8 
    //and non-unicode for BIFF7
     virtual void NameL(const TDesC& ) = 0;
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
    
    MString*& FontName( ) { return iFontName; }
    MString* const & FontName( ) const { return iFontName; }

private:
    //Interface to CFontFormat
    void ResetToDefault( );
    void SetValuesL( const CCharFormatLayer* aCharFormatLayer,
        const CFontConverter* aFontConverter, const CColorPalette* aColorPalette );

    TInt16&    Height( )        { return iHeight; }
    const TInt16&    Height( )   const     { return iHeight; }
    TInt16&    Attributes( )    { return iAttributes; }
    const TInt16&    Attributes( )  const  { return iAttributes; }
    TBool&     Bold( )          { return iBold; }
    const TBool&     Bold( )      const    { return iBold; }
    EPosition& Position( )      { return iPosition; }
    const EPosition& Position( )   const   { return iPosition; }
    TBool&     Underline( )     { return iUnderline; }
    const TBool&     Underline( )   const  { return iUnderline; }
    TBool&     StrikeThrough( ) { return iStrikeThrough; }
    const TBool&     StrikeThrough( ) const { return iStrikeThrough; }
    TBool&     Italic( )        { return iItalic; }
    const TBool&     Italic( )   const     { return iItalic; }
    TInt16&    ColorIndex( )    { return iColorIndex; }
    const TInt16&    ColorIndex( )  const  { return iColorIndex; }

private:
          //data
          TInt16          iHeight;
          TInt16          iAttributes;
          TBool           iBold;
          EPosition       iPosition;
          TBool           iUnderline;
          TBool           iStrikeThrough;
          TBool           iItalic;
          TInt16          iColorIndex;
          TInt            iNameLength;
          MString*        iFontName;
};

////////////////////////
//  NUMBER FORMAT    //
//////////////////////
class CWriteBiffFORMAT : public CWriteBiffRecord
{ 
public:
    friend class CNumberFormat;  //class for font formatting
public:
     virtual ~CWriteBiffFORMAT( ) { DELETE (iNumberString); }
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL); 
    IMPORT_C friend TBool operator!=(const CWriteBiffFORMAT&, const CWriteBiffFORMAT&);
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
             virtual TInt RecordLength( ) = 0;
             virtual void WriteStringLengthL( ) = 0;
protected:
    //interface to CNumberFormat and derived classes
    TInt16& Index( ) { return iIndex; }
    const TInt16& Index( ) const { return iIndex; }

    MString*& NumberString( ) { return iNumberString; }
    MString* const & NumberString( ) const { return iNumberString; }
private:
    TInt16   iIndex;          //format index code
    MString* iNumberString;   //number format string 
};

//////////////////////
// COLOR PALETTE   //
////////////////////
class CPalette; //defined in <gdi.h>
class CColorPalette; //defined in "ewcofont.h"
class CWriteBiffPALETTE : public CWriteBiffRecord
{
public:
    friend class CColorPalette;
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
     virtual ~CWriteBiffPALETTE( ) { }
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
private:
    //interface to CFontFormat
    CPalette*& ColorPalette( ) { return iPalette; }
    CPalette* const & ColorPalette( ) const { return iPalette; }
private:
    CPalette* iPalette;
};

/////////////////////////
// WINDOW1  -  OR 104 //
///////////////////////

class CWriteBiffWINDOW1 : public CWriteBiffRecord
{
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
     virtual ~CWriteBiffWINDOW1( ) { }
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
};

/////////////////////////
// WINDOW2  -  OR 104 //
///////////////////////

class CWriteBiffWINDOW2 : public CWriteBiffRecord
{
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
     virtual ~CWriteBiffWINDOW2( ) { }
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
};
#endif //__EWCO_BIFF_H__
