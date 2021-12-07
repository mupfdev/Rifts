/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Excel Reader 95
 *
 * Identification   :   95 Stream Reader Classes[EXCEL_SDS]
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Workfile$, $Revision: 1.3 $
 *
 * Author           :   Peter Mead
 *
 * History          :   
 *
 * $Log: er95biff.h,v $
 * Revision 1.3  2001/12/04 14:06:44  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.15  2000/02/14 11:08:57  stefania
 * OR 229, replaced TBuf<MAXSTRINGLENGTH>& with TDes& in function parameter declarations.
 *
 * Revision 1.14  2000-02-10 14:34:27+00  stefania
 * OR 222, insert function values
 *
 * Revision 1.13  2000/01/14 11:14:28  stefania
 * OR 168, Changed code relative to number formatting.
 *
 * Revision 1.12  2000/01/11 12:48:40  stefania
 * Fixed OR 163.
 *
 * Revision 1.11  1999/12/17 18:54:56  stefania
 * Few fixes.
 *
 * Revision 1.10  1999-12-15 11:47:18+00  stefania
 * Added code for cross references, OR 138.
 *
 * Revision 1.9  1999-11-19 13:58:00+00  peterm
 * Cell Formating Changes
 *
 * Revision 1.8  1999/11/01 10:08:20  peterm
 * Changes to BOF code
 *
 * Revision 1.7  1999-10-28 11:38:29+01  chrisg
 * Merged Peter and Stefis changes
 *
 * Revision 1.6  1999/10/27 16:08:57  peterm
 * Remove Column Formating
 *
 * Revision 1.5  1999-10-27 16:25:33+01  peterm
 * Add Column Formating
 *
 * Revision 1.4  1999-10-25 20:20:30+01  peterm
 * Add shared formula code not working ye
 *
 * Revision 1.3.1.1  1999/10/28 09:16:10  stefania
 *  Changes for wide build and new EPOC sheet API.
 *
 * Revision 1.3  1999/10/19 13:05:51  peterm
 * Add Format7 records
 *
 * Revision 1.2  1999-09-30 15:28:34+01  peterm
 * GetCellReference, GetAreaReference and GetString
 *
 * Revision 1.1  1999-09-22 12:42:34+01  peterm
 * Initial revision
 *
 *
 * ---------------------------------------------------------------------------
 */
#if !defined (__ER95BIFF_H__)
#define __ER95BIFF_H__


/******************************************************************************
                              class CBiffBOF7 
 ******************************************************************************
 */
class CBiffBOF7:public CBiffBOF
{
public:
    CBiffBOF7(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };
    TInt ValidSubStream();
};

/******************************************************************************
                              class CBiffBOUNDSHEET7
 ******************************************************************************
 */
class CBiffBOUNDSHEET7:public CBiffBOUNDSHEET
{
public:
    CBiffBOUNDSHEET7(CBiffRecord *aBiffRecord) : CBiffBOUNDSHEET(aBiffRecord) { }
    virtual TInt OffsetRgch( )     const { return 11; }
    virtual TInt OffsetGrBitChr( ) const { return -1; }//not present in BIFF7 
};

/******************************************************************************
                              class CBiffFORMULA7 
 ******************************************************************************
 */
class CBiffFORMULA7:public CBiffFORMULA
{
public:
    CBiffFORMULA7(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };
protected:
    HBufC* GetCellReferenceLC(TInt aIndex, TInt &aCnt, TInt8 aToken);
    HBufC* GetAreaReferenceLC(TInt aIndex, TInt &aCnt, TInt8 aToken);
    TInt Get3dReference(TDes& aBuf,TInt& aIndex);  //OR 138 
    HBufC* GetStringLC(TInt aIndex, TInt &aCnt);
    virtual CBiffSTRING*  GetSTRINGRecordLC( ); //OR 222 
};

/******************************************************************************
                              class CBiffFORMAT7 
 ******************************************************************************
 */
class CBiffFORMAT7:public CBiffFORMAT
{
public:
    CBiffFORMAT7(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };
    IMPORT_C TInt GetFormatString(TDes& aBuf);
};

/******************************************************************************
                              class CBiffDIMENSIONS7 
 ******************************************************************************
 */
class CBiffDIMENSIONS7:public CBiffDIMENSIONS
{
public:
    CBiffDIMENSIONS7(CBiffRecord *aBiffRecord) { Initialise(aBiffRecord); };
    IMPORT_C TInt GetLastRow(TInt &aRow);
};

/******************************************************************************
                              class CBiffSTRING7 
 ******************************************************************************
 */
class CBiffSTRING7:public CBiffSTRING
{
public:
    CBiffSTRING7() { };
    virtual ~CBiffSTRING7( )  { }
    CBiffSTRING7(CBiffRecord *aBiffRecord) : CBiffSTRING( ) { Initialise(aBiffRecord); };
    IMPORT_C TInt GetCellText(TDes& aBuf);
};

/******************************************************************************
                              class CBiffLABEL7 
 ******************************************************************************
 */
class CBiffLABEL7:public CBiffSTRING7
{
public:
    CBiffLABEL7(CBiffRecord *aBiffRecord) : CBiffSTRING7(aBiffRecord) { Initialise(aBiffRecord);};
};

/******************************************************************************
                              class CBiffRSTRING7 
 ******************************************************************************
 */
class CBiffRSTRING7:public CBiffSTRING7
{
public:
    CBiffRSTRING7(CBiffRecord *aBiffRecord) : CBiffSTRING7(aBiffRecord) { Initialise(aBiffRecord);};
};

#endif // !defined (__ER95BIFF_H__)
