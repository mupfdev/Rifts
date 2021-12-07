/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   EXCELCOMM.DLL
 *
 * Identification   :   RFormula, CFormula and derived classes
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvCommon/ewcoform.h,v 1.3 2001/12/04 14:06:43 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: ewcoform.h,v $
 * Revision 1.3  2001/12/04 14:06:43  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.14  2000/02/08 11:41:27  stefania
 * OR 206, functions can have different argument types.
 *
 * Revision 1.13  1999/10/21 11:08:24  stefania
 * typo
 *
 * Revision 1.12  1999-10-21 11:47:57+01  stefania
 * Fixes for urel build.
 *
 * Revision 1.11  1999/10/19 13:17:15  stefania
 * Added CFormula::ProcessNameToken.
 *
 * Revision 1.10  1999/10/13 08:44:44  stefania
 * Changes for code review.
 *
 * Revision 1.9  1999/10/11 16:46:27  stefania
 * Removed ptgBoolErr.
 *
 * Revision 1.8  1999-10-11 12:11:58+01  stefania
 * Added initialisation of iOwner to true in CFormula default constructor.
 *
 * Revision 1.7  1999/10/11 10:22:55  stefania
 * Added reference counting to RFormula and CFormula.
 *
 * Revision 1.6  1999/10/07 14:03:28  stefania
 * Added iWriteFunctionVarPtg.
 *
 * Revision 1.5  1999-10-05 17:17:45+01  stefania
 * Added iWriteOperandPtgArea.
 *
 * Revision 1.4  1999-10-05 16:24:34+01  stefania
 * Added a few IMPORT_Cs and InitTable7 and 8.
 *
 * Revision 1.3  1999-09-30 16:17:12+01  stefania
 * Removed a few consts and changed ewcohash include.
 *
 * Revision 1.2  1999-09-17 14:34:49+01  stefania
 * First complete build of exelcomm.dll
 *
 * Revision 1.1  1999-09-15 13:59:23+01  stefania
 * Merge with basic drop
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__EWCOFORM_H__)
#define __EWCOFORM_H__

//EPOC Engine files
#include <shgapi.h>
#include <shgcoord.h>
#include <shgtoken.h>
#include <shgfmlex.h>
#include <shgfmvwr.h>

#include "excoelib.h"

#include "excoepoc.h"

//Stack and Hash table
#include "ewcohash.h"
#include "ewcostck.h"

//forward declarations
class CFormula;

//MFormula class
//---------------
//Interface common to RFormula and CFormula classes
class MFormula
{
public:
    virtual TPtr8   ConvertL ( ) = 0;
    virtual TDesC8& EvaluateL( ) = 0;
};

//RFormula class
//---------------
//Package class, contains an instance of a CFormula derived
//class depending on the type of formula, i.e. numeric, boolean
//string or error. The decision of which formula to instantiate
//is taken in CreateL( )
//Memory is released in Destroy.
class RFormula : public MFormula
{
public:
    IMPORT_C RFormula( );
    IMPORT_C virtual ~RFormula( );
    IMPORT_C RFormula(const RFormula&);  
    IMPORT_C RFormula& operator=(const RFormula& aFormula); 
public:
    //needed by cleanup stack
    IMPORT_C operator TCleanupItem();
    IMPORT_C static void Cleanup(TAny *aPtr);
public:
    IMPORT_C void InitTable7L( ) const ; 
    IMPORT_C void InitTable8L( ) const ; 
public:
    IMPORT_C void CreateL ( const CEpocRecord* aEpocRecord );
    IMPORT_C void Destroy( ); 
public:
    //From MFormula
    IMPORT_C TPtr8   ConvertL( ); 
    IMPORT_C TDesC8& EvaluateL( ); 
private:
    //Real formula + reference counting
    struct Formula
    {
        CFormula* formula;
        TUint8    number;
    };
    Formula* iFormula;
};

//Excel tokens and helper class
#include "ewcoetok.h"

//CFormula class
//--------------
//Abstract base class for real formula classes
//There is a real formula class for every type
//a formula can evaluate to, i.e. string, numeric,
//bool and error
//Parsing of EPOC formula tokens and
//mapping of EPOC tokens to Excel tokens is 
//implemented in this class since it does not
//depend on the evaluation type of a formula
class CFormula : public CBase, public MFormula
{
public:
    virtual ~CFormula( );
    CFormula( ) { iOwner = ETrue; }

    //copy
    CFormula( CFormula& );
    CFormula& operator= (CFormula& aFormula);

public:
    //INTERFACE
    //process formula tokens
    //Return parsed formula
    TPtr8 ConvertL( );

public: //OR 206
    const TFunctionEncoding& ActiveFunctionEncoding( ) 
                const { return iActiveFunctionEncoding; }
    const TInt CurrentParameter( ) const { return iNoArguments - 1; }
public:
    //init formula table 
    void InitTable7L( );
    void InitTable8L( );
    void DestroyTable( );

protected:
    //data access to derived classes
    const TShgCell*   Cell( ) { return iEpocRecord->Cell( ); }
    const CEpocRecord*& Record( ) { return iEpocRecord; }
    TDes8& EvaluatedFormula( ) { return iEvaluatedFormula; }
    friend class RFormula;

private:
    //copy
    void Init(CFormula&);

private:
    //used by ProcessFormula
    //process single formula token
    TInt ProcessTokenL( SLexToken& epocToken );

private:
    //for use of ProcessTokenL function
    //implement reverse-polish algorithm
    TInt ProcessOperatorTokenL(SLexToken& aEpocToken );   
    TInt ProcessControlTokenL(SLexToken& aEpocToken );
    TInt ProcessOperandTokenL(SLexToken& aEpocToken ); 
    TInt ProcessNameTokenL(SLexToken& aEpocToken );
    TInt ProcessFunctionTokenL(SLexToken& aEpocToken );

private:
    //OR 206
    void SetActiveFunction(SLexToken& aEpocToken );
    
    //Convert EPOC tokens to excel tokens
    TInt ConvertTokenL( SLexToken& aEpocToken );
    void ConvertToAbsolute( TShgCellRef&  aShgRef );

private: //OR 206
    TFunctionEncoding iActiveFunctionEncoding;

private:
    //functors to write Excel tokens
    TWriteTypePtg*             iWriteTypePtg;
    TWriteOperandPtgString*    iWriteOperandPtgString;
    TWriteOperandPtgInt*       iWriteOperandPtgInt;
    TWriteOperandPtgNumber*    iWriteOperandPtgNumber;
    TWriteOperandPtgReference* iWriteOperandPtgReference;
    TWriteOperandPtgArea*      iWriteOperandPtgArea;
    TWriteFunctionPtg*         iWriteFunctionPtg;
    CWriteFunctionVarPtg*      iWriteFunctionVarPtg;

    //hash table mapping epoc tokens to excel tokens
    CHashTable<TExcelToken,TFormulaToken>* iExcelToken;
    void InitTableL( ); //cannot be called by clients

    //hash table and functors not copied across
    //following variable used for ownership
    //should be replaced with proper reference counting
    TBool                      iOwner;
    
private:
    //epoc record
    const CEpocRecord* iEpocRecord;

    //intermidiate operators stack
    CWriteStack<SLexToken> iOperators;

    //number of function arguments
    TUint8 iNoArguments;

    //Parsed formula 
    CBufFlat* iParsedFormula;

     //Evaluated formula (8 bytes)
    enum { KEvaluatedFormulaSize=8 };
    TBuf8<KEvaluatedFormulaSize> iEvaluatedFormula;

};


//CNumericFormula class
//---------------------
//Implements formulas that evaluate to a number
class CNumericFormula : public CFormula
{
public:
    TDesC8& EvaluateL( );
};


//CStringFormula class
//---------------------
//Implements formulas that evaluate to a string
class CStringFormula : public CFormula
{
public:
    TDesC8& EvaluateL( );
};


//CBoolFormula class
//---------------------
//Implements formulas that evaluate to a boolean value
class CBoolFormula : public CFormula
{
public:
    TDesC8& EvaluateL( );
};


//CErrorFormula class
//---------------------
//Implements formulas that evaluate to an error
class CErrorFormula : public CFormula
{
public:
    TDesC8& EvaluateL( );
};



#endif // __EWCOFORM_H__
