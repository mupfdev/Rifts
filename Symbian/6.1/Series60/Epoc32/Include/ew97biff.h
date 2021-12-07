/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   EXELCOMM.DLL
 *
 * Identification   :   WriteBiffRecords Classes relative to version BIFF8
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvV97/ew97biff.h,v 1.3 2001/12/04 14:06:45 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: ew97biff.h,v $
 * Revision 1.3  2001/12/04 14:06:45  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.9  1999/12/13 15:22:07  stefania
 * Added code for cross references, OR 138
 *
 * Revision 1.8  1999/12/03 12:31:03  stefania
 * Changes for OR 104 (nothing to print)
 *
 * Revision 1.7  1999-10-18 14:16:40+01  stefania
 * Added Compare to CString8. Changes to CWriteBiffFONT8 for support of font names.
 *
 * Revision 1.6  1999-10-15 16:12:27+01  stefania
 * Added  CWriteBIFFFormat8::WriteStringLengthL( ).
 *
 * Revision 1.5  1999/10/15 12:18:58  stefania
 * Changed return of Write functions from TInt to void.
 *
 * Revision 1.4  1999/10/07 14:17:23  stefania
 * Added Compress( ) and UnCompress( ) methods to CString8.
 *
 * Revision 1.3  1999-10-05 16:27:36+01  stefania
 * Added new BIFF records.
 *
 * Revision 1.2  1999-10-01 15:33:58+01  stefania
 * Changed include path
 *
 * Revision 1.1  1999-09-30 16:13:13+01  stefania
 * Initial revision
 *
 *
 * -------------------------------------------------------------------------------
 */

#if !defined (__EW97_BIFF_H__)
#define __EW97_BIFF_H__

#include "ewcobiff.h"

/* ==============================================
 *               STRING Class 
 * ----------------------------------------------
 */
class CString8 :  public CBase, public MString
{
public:
    static CString8* NewL( );
    static CString8* NewL( const TDesC& aDes );
    static CString8* NewLC( );
    static CString8* NewLC( const TDesC& aDes );
    virtual ~CString8( ) { delete iDes; }
public:
    void WriteL(const COle2StreamPackage* aStream);
    void SetL(const TDesC& aDes);
    const TInt16 StringSize( ) const;
    const TInt16 StringLength( ) const;
    virtual void Compress( ) { iCompressed = ETrue; }
    virtual void UnCompress( ) { iCompressed = EFalse; }
protected:
    virtual TBool Compare(const MString*) const;
private:
    CString8( ) { iCompressed = EFalse; }
    CString8( const TDesC&  ) { iCompressed = EFalse; }
    void ConstructL( const TDesC& aDes );
private:
    HBufC16* iDes;
    TBool    iCompressed; 
};

/* ==============================================
 *       BIFF record classes
 * ----------------------------------------------
 */

////////////////////
//     BOF       //
//////////////////
class CWriteBiffBOF8 : public CWriteBiffBOF
{
public:
    CWriteBiffBOF8( const ESubStreamType& aType ) : CWriteBiffBOF( aType ) { }
public:
    //From MBiffRecord
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
    IMPORT_C virtual void SetDefaultValues( );
private:
    //Default values for BIFF8 BOF records
    TInt32 iFileHistory;       //File History flags
    TInt32 iLowestBiffVersion; //lowest BIFF version
};

/////
//// NOTE: Cannot avoid repeating following code because
////       cannot use multiple inheritance
////


//////////////////////////////
//VERTICAL PAGE BREAK      //
////////////////////////////
class CWriteBiffVERTICALPAGEBREAKS8 : public CWriteBiffVERTICALPAGEBREAKS
{ 
public:
    enum { KSizeOfRgBrk = 6 }; //size of variable length structs for page breaks
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,
        const CWriteBiffRecord* = NULL);
protected:
    IMPORT_C virtual TInt SizeOfRgBrk( ) { return KSizeOfRgBrk; }
};

//////////////////////////////
//HORIZONTAL PAGE BREAK      //
////////////////////////////
class CWriteBiffHORIZONTALPAGEBREAKS8 : public CWriteBiffHORIZONTALPAGEBREAKS
{ 
public:
    enum { KSizeOfRgBrk = 6 }; //size of variable length structs for page breaks
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,
        const CWriteBiffRecord* = NULL) ; 
protected:
    IMPORT_C virtual TInt SizeOfRgBrk( ) { return KSizeOfRgBrk; }
};

class CWriteBiffSTRING8 : public CWriteBiffSTRING
{ 
public:
    friend class CWriteBiffFORMULA8;
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,
        const CWriteBiffRecord* = NULL); 
};

class CWriteBiffLABEL8 : public CWriteBiffLABEL
{ 
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,
        const CWriteBiffRecord* = NULL); 
};

/////////////////////
//   FORMULA      //
///////////////////
class CWriteBiffFORMULA8 : public CWriteBiffFORMULA
{ 
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
    IMPORT_C virtual void InitFormulaTable( ) const;
};

//////////////////
//  INDEX      //
////////////////
class CWriteBiffINDEX8 : public CWriteBiffINDEX
{
public:
    IMPORT_C virtual void WriteRows ( const TInt aFirstRow, const TInt aLastRow ); 
};

//////////////////////
// BOUNDSHEET      //
////////////////////
class CWriteBiffBOUNDSHEET8 : public CWriteBiffBOUNDSHEET
{
protected:
    IMPORT_C virtual MString* SheetNameLC( ) const;
};

//////////////
// XF      //
////////////
class CWriteBiffXF8 : public CWriteBiffXF
{
public:
    //consts
    static const TInt KRecordLength;
public:
    IMPORT_C CWriteBiffXF8(const EXFType& aType) : CWriteBiffXF( aType ) { }
public:
  IMPORT_C virtual void WriteFixedStyleL( ) const;
  IMPORT_C virtual void WriteFixedCellL( ) const;
protected:
  IMPORT_C virtual TInt RecordLength( );
};

//////////////
//  FONT   //
////////////
class CWriteBiffFONT8 : public CWriteBiffFONT
{
public:
    IMPORT_C virtual void NameL( const TDesC& ) ;
};

////////////////////////
//  NUMBER FORMAT    //
//////////////////////
class CWriteBiffFORMAT8 : public CWriteBiffFORMAT
{ 
protected: 
  IMPORT_C virtual TInt RecordLength( );
  IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
  IMPORT_C virtual void WriteStringLengthL( );
};

////////////////////////
//  WINDOW2 - OR 104 //
//////////////////////
class CWriteBiffWINDOW28 : public CWriteBiffWINDOW2
{ 
protected: 
  IMPORT_C virtual TInt RecordLength( );
  IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
};


//////////////////////////////
// SUPBOOK  -  OR 138      //
// sheet cross references //
///////////////////////////
class CWriteBiffSUPBOOK8 : public CWriteBiffRecord
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
class CWriteBiffEXTERNSHEET8 : public CWriteBiffRecord
{
public:
    IMPORT_C virtual void WriteL(const CEpocRecord* = NULL,const CWriteBiffRecord* = NULL);
protected:
    IMPORT_C virtual void ConstructL( const COle2StreamPackage *aStream );
    IMPORT_C virtual TInt RecordLength( );
private:
    TInt16 iNXtys; //number of XTY structures, see MSDN
};


#endif //__EW97_BIFF_H__