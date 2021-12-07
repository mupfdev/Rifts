/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   EXLW95.DLL
 *
 * Identification   :   WriteBiffRecords Classes relative to version BIFF7
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvV95/ew95biff.h,v 1.3 2001/12/04 14:06:44 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: ew95biff.h,v $
 * Revision 1.3  2001/12/04 14:06:44  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.8  2000/03/29 13:42:35  stefania
 * OR 237
 *
 * Revision 1.7  1999-12-13 15:29:32+00  stefania
 * Added code for cross references, OR 138
 *
 * Revision 1.6  1999/12/03 12:34:07  stefania
 * Changes for OR 104 (nothing to print)
 *
 * Revision 1.5  1999-10-18 14:16:11+01  stefania
 * Added Compare to CString7. Changes to CWriteBiffFONt7 for support of font names.
 *
 * Revision 1.4  1999-10-15 16:11:56+01  stefania
 * Added  CWriteBIFFFormat7::WriteStringLengthL( ).
 *
 * Revision 1.3  1999/10/15 12:19:15  stefania
 * Changed return of Write functions from TInt to void.
 *
 * Revision 1.2  1999/10/07 14:18:33  stefania
 * Added Compress( ) and UnCompress( ) methods to CBiff7.
 *
 * Revision 1.1  1999-10-05 16:25:38+01  stefania
 * Initial revision
 *
 *
 * -------------------------------------------------------------------------------
 */

#if !defined (__EW95_BIFF_H__)
#define __EW95_BIFF_H__

#include "ewcobiff.h"

/* ==============================================
 *               STRING Class 
 * ----------------------------------------------
 */
class CExcelLibraryW;
class CString7 : public CBase, public MString
{
public:
    static CString7* NewL( );
    static CString7* NewL( const TDesC& aDes );
    static CString7* NewLC( );
    static CString7* NewLC( const TDesC& aDes );
    virtual ~CString7( ) { delete iDes; }
public:
          void WriteL( const COle2StreamPackage* aStream );
          void SetL( const TDesC& aDes );
    const TInt16 StringSize( ) const;
    const TInt16 StringLength( ) const;
          void Compress( ) { }
          void UnCompress( ) { }
          void ConvertUnicodeToAsciiL( const CExcelLibraryW* const aLibrary ) const; //OR 237  
protected:
    virtual TBool Compare(const MString*) const;
private:
    CString7( const TDesC& ) { }
    CString7(  ) { }
    void ConstructL( const TDesC& aDes );
private:
    HBufC8* iDes;
};

/* ==============================================
 *           BIFF record clsses
 * ----------------------------------------------
 */

////////////////////
//     BOF       //
//////////////////
class CWriteBiffBOF7 : public CWriteBiffBOF
{
public:
    CWriteBiffBOF7( const ESubStreamType& aType ) : CWriteBiffBOF( aType ) { }
protected:
    IMPORT_C virtual void SetDefaultValues( );
};

/////
//// NOTE: Cannot avoid repeating following code because
////       cannot use multiple inheritance
////


//////////////////////////////
//VERTICAL PAGE BREAK      //
////////////////////////////
class CWriteBiffVERTICALPAGEBREAKS7 : public CWriteBiffVERTICALPAGEBREAKS
{ 
public:
    enum { KSizeOfRgBrk = 2 }; //size of variable length structs for page breaks
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,
        const CWriteBiffRecord* = NULL);
protected:
    IMPORT_C virtual TInt SizeOfRgBrk( ) { return KSizeOfRgBrk; }
};

//////////////////////////////
//HORIZONTAL PAGE BREAK      //
////////////////////////////
class CWriteBiffHORIZONTALPAGEBREAKS7 : public CWriteBiffHORIZONTALPAGEBREAKS
{ 
public:
    enum { KSizeOfRgBrk = 2 }; //size of variable length structs for page breaks
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,
        const CWriteBiffRecord* = NULL) ; 
protected:
    IMPORT_C virtual TInt SizeOfRgBrk( ) { return KSizeOfRgBrk; }
};

class CWriteBiffSTRING7 : public CWriteBiffSTRING
{ 
public:
    friend class CWriteBiffFORMULA7;
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,
        const CWriteBiffRecord* = NULL); 
};

class CWriteBiffLABEL7 : public CWriteBiffLABEL
{ 
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,
        const CWriteBiffRecord* = NULL); 
};

/////////////////////
//   FORMULA      //
///////////////////
class CWriteBiffFORMULA7 : public CWriteBiffFORMULA
{ 
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
    IMPORT_C virtual void InitFormulaTable( ) const;
};

//////////////////
//  INDEX      //
////////////////
class CWriteBiffINDEX7 : public CWriteBiffINDEX
{
public:
    IMPORT_C virtual void WriteRows ( const TInt aFirstRow, const TInt aLastRow ); 
};

//////////////////////
// BOUNDSHEET      //
////////////////////
class CWriteBiffBOUNDSHEET7 : public CWriteBiffBOUNDSHEET
{
protected:
    IMPORT_C virtual MString* SheetNameLC( ) const;
};

//////////////
// XF      //
////////////
class CWriteBiffXF7 : public CWriteBiffXF
{
public:
    //consts
    static const TInt KRecordLength;
public:
    IMPORT_C CWriteBiffXF7(const EXFType& aType) : CWriteBiffXF( aType ) { }
public:
  IMPORT_C virtual void WriteFixedStyleL( ) const;
  IMPORT_C virtual void WriteFixedCellL( ) const;
protected:
  IMPORT_C virtual TInt RecordLength( );
};

//////////////
//  FONT   //
////////////
class CWriteBiffFONT7 : public CWriteBiffFONT
{
public:
    IMPORT_C virtual void NameL(const TDesC& ) ;
};

////////////////////////
//  NUMBER FORMAT    //
//////////////////////
class CWriteBiffFORMAT7 : public CWriteBiffFORMAT
{ 
protected:
  IMPORT_C virtual TInt RecordLength( );
  IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
  IMPORT_C virtual void WriteStringLengthL( );
};

////////////////////////
//  WINDOW2 - OR 104 //
//////////////////////
class CWriteBiffWINDOW27 : public CWriteBiffWINDOW2
{ 
};

//////////////////////////////
// EXTERNCOUNT  -  OR 138  //
// sheet cross references //
///////////////////////////
class CWriteBiffEXTERNCOUNT7 : public CWriteBiffRecord
{
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
};

//////////////////////////////
// EXTERNSHEET  -  OR 138  //
// sheet cross references //
///////////////////////////
class CWriteBiffEXTERNSHEET7 : public CWriteBiffRecord
{
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
    IMPORT_C virtual ~CWriteBiffEXTERNSHEET7( ) { DELETE( iName ); }
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
private:
    CString7* iName;
};
#endif //__EW95_BIFF_H__
