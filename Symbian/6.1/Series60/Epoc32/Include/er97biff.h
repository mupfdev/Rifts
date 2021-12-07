/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Excel Reader 97 & 00
 *
 * Identification   :   BiffRecords Classes [EXCEL_SDS]
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvV97/er97biff.h,v 1.3 2001/12/04 14:06:44 BijalShah Exp $
 *
 * Author           :   Peter Mead
 *
 * History          :   
 *
 * $Log: er97biff.h,v $
 * Revision 1.3  2001/12/04 14:06:44  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.31  2000/02/14 11:10:29  stefania
 * OR 229, replaced TBuf<MAXSTRINGLENGTH>& with TDes& in function parameter declarations.
 *
 * Revision 1.30  2000-02-10 14:35:03+00  stefania
 * OR 222, function values
 *
 * Revision 1.29  2000/01/14 11:16:28  stefania
 * OR 168, Changed code relative to number formatting
 *
 * Revision 1.28  2000/01/11 12:49:46  stefania
 * Fixed OR 163.
 *
 * Revision 1.27  1999/12/17 18:54:17  stefania
 * Fixed a few bugs.
 *
 * Revision 1.26  1999-12-15 11:46:14+00  stefania
 * Added code for cross references, OR 138.
 *
 * Revision 1.25  1999/11/19 13:58:51  peterm
 * Cell Formating Changes
 *
 * Revision 1.24  1999/11/01 10:10:13  peterm
 * Changes to BOF code
 *
 * Revision 1.23  1999-10-28 10:34:07+01  chrisg
 * Merging of Peter and Stefis changes
 *
 * Revision 1.22  1999/10/27 15:25:45  peterm
 * Add Column Formating
 *
 * Revision 1.21  1999-10-25 20:20:42+01  peterm
 * Add shared formula code not working ye
 *
 * Revision 1.20.1.1  1999/10/28 09:00:34  stefania
 * Changes for wide build and new epoc sheet API.
 *
 * Revision 1.20  1999/10/20 11:19:38  peterm
 * Test for Shared String error
 *
 * Revision 1.19  1999-10-19 14:06:17+01  peterm
 * Add Format8 records
 *
 * Revision 1.18  1999-10-08 12:06:18+01  peterm
 * Code Review Changes
 *
 * Revision 1.17  1999/09/30 14:30:45  peterm
 * Added GetCellReference GetAreaReference and Get String
 *
 * Revision 1.16  1999-09-28 16:59:20+01  peterm
 * Add getCellReference method to CBiffFORMULA8
 *
 * Revision 1.15  1999-09-22 12:38:23+01  peterm
 * add 95 reader
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__ER97BIFF_H__)
#define __ER97BIFF_H__


/******************************************************************************
                              class CBiffBOF8 
 ******************************************************************************
 */
class CBiffBOF8:public CBiffBOF
{
public:
    CBiffBOF8(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };
    TInt ValidSubStream();
};

/******************************************************************************
                              class CBiffBOUNDSHEET8
 ******************************************************************************
 */
class CBiffBOUNDSHEET8:public CBiffBOUNDSHEET
{
public:
    CBiffBOUNDSHEET8(CBiffRecord *aBiffRecord) : CBiffBOUNDSHEET(aBiffRecord) { }
    virtual TInt OffsetRgch( )     const { return 12; }
    virtual TInt OffsetGrBitChr( ) const { return 11; }
};

/******************************************************************************
                              class CBiffSST8 
 ******************************************************************************
 */
class CBiffSST8:public CBiffRecord
{
public:
    CBiffSST8(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };
    TInt LoadStrings(const TInt32 aIndex, TDes& aBuff);
};

/******************************************************************************
                              class CBiffLABELSST8 
 ******************************************************************************
 */
class CBiffLABELSST8:public CBiffSingle
{
public:
    CBiffLABELSST8(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };
    CBiffSST8 *iBiffSST8;
private:
    TInt GetCellText(TDes &aBuf);

};

/******************************************************************************
                              class CBiffFORMAT8 
 ******************************************************************************
 */
class CBiffFORMAT8:public CBiffFORMAT
{
public:
    CBiffFORMAT8(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };
    IMPORT_C TInt GetFormatString(TDes& aBuf);
};

/******************************************************************************
                              class CBiffFORMULA8 
 ******************************************************************************
 */
class CBiffFORMULA8:public CBiffFORMULA
{
public:
    CBiffFORMULA8(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };

protected:
    HBufC* GetCellReferenceLC(TInt aIndex, TInt &aCnt, TInt8 aToken);
    HBufC* GetAreaReferenceLC(TInt aIndex, TInt &aCnt, TInt8 aToken);
    HBufC* GetStringLC(TInt aIndex, TInt &aCnt);
    virtual CBiffSTRING*  GetSTRINGRecordLC( ); //OR 222 
private:
    //OR 138
    TInt Get3dReference ( TDes& aBuf, TInt& aIndex );
};

/******************************************************************************
                              class CBiffDIMENSIONS8 
 ******************************************************************************
 */
class CBiffDIMENSIONS8:public CBiffDIMENSIONS
{
public:
    CBiffDIMENSIONS8(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };
    IMPORT_C TInt GetLastRow(TInt &aRow);
};

/******************************************************************************
                              class CBiffSTRING8 
 ******************************************************************************
 */
class CBiffSTRING8:public CBiffSTRING
{
public:
    CBiffSTRING8() { };
    virtual ~CBiffSTRING8( )  { }
    IMPORT_C TInt GetCellText(TDes &aBuf);
};

/******************************************************************************
                              class CBiffLABEL8 
 ******************************************************************************
 */
class CBiffLABEL8:public CBiffSTRING8
{
public:
    CBiffLABEL8(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };
};

/******************************************************************************
                              class CBiffRSTRING8 
 ******************************************************************************
 */
class CBiffRSTRING8:public CBiffSTRING8
{
public:
    CBiffRSTRING8(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };
};

/******************************************************************************
                          class CBiffEXTERNSHEET8
                          OR 138 - sheet cross references
 ******************************************************************************
 */

class CBiffEXTERNSHEET8 : public CBiffEXTERNSHEET
{
public:
    struct Xti //see MSDN
    {
        TInt16 first; //index to first sheet
        TInt16 last;  //index to last sheet
    };
public:
    CBiffEXTERNSHEET8( CBiffRecord* aBiffRecord ) : 
      CBiffEXTERNSHEET( aBiffRecord ) { }
public:
    virtual Xti* XtiInfoLC( TInt aIndex ) const;
};

/******************************************************************************
                              class CBiffSUPBOOK8
                              OR 138 - sheet cross references
 ******************************************************************************
 */
class CBiffSUPBOOK8 : public CBiffSUPBOOK
{
public:
    CBiffSUPBOOK8( CBiffRecord* aBiffRecord) :  CBiffSUPBOOK( aBiffRecord ) { }
public:
    //given an index returs true if workbook is self workbook
    TBool IsSelfReferential( TInt aIndex ) const;
};

#endif // !defined (__ER97BIFF_H__)
