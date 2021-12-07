/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   Common Trace Include File for System
 *
 * Identification   :   Macros for Trace functions
 *
 * SDS Ref          :   [ADS]
 *
 * Filename         :   $Locker:  $ $Revision: 1.3 $
 *
 * Author           :   Ed Simons
 *
 * History          :   
 * $Log: cotrmain.h,v $
 * Revision 1.3  2001/12/04 14:06:41  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.15  1999/09/29 08:30:23  chrisg
 * Updated to make return types void for undefined functions
 *
 * Revision 1.14  1999-09-21 18:05:51+01  chrisg
 * Updates for UNICODE
 *
 * Revision 1.13  1999-09-21 11:54:13+01  chrisg
 * Updated trace to work with TDes16s now!
 *
 * Revision 1.12  1999-09-14 15:01:40+01  chrisg
 * Updated to protect against trying to use NULL pointers
 *
 * Revision 1.11  1999-09-09 16:50:49+01  peterm
 * Add new trace value type to handle DesC&
 *
 * Revision 1.10  1999-09-03 11:30:34+01  eds
 * Header file no longer causes dependencies in other files.
 *
 * Revision 1.9  1999-09-03 09:09:38+01  chrisg
 * ALWAYS declare the Trace Class (even if it isn't used) OTHERWISE the trace library
 * will not build!!!!!!
 *
 * Revision 1.8  1999-09-02 10:33:02+01  eds
 * Only declare trace class if using trace facility.
 *
 * Revision 1.7  1999-08-31 15:24:46+01  chrisg
 * Sorted out the trace stuff #define INFOMATRIX_TRACE if you want to use it
 *
 * Revision 1.6  1999-08-31 14:30:29+01  chrisg
 * Updated TraceInitialise to be an L function rather than an LC function, otherwise
 * this will cause problems with EIKON applicatoins
 *
 * Revision 1.5  1999-08-27 15:23:41+01  eds
 * Completed Ole2 component testing.
 *
 * Revision 1.4  1999-08-25 09:57:32+01  chrisg
 * Added Trace Value, sorted out TAB characters, and added LINE and FILE context
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__COTRMAIN_H__)
#define __COTRMAIN_H__

#include <e32base.h>
#include <f32file.h>
//
// NOTE: THESE MACROS SHOULD BE USED IN THE CODE TO IMPLEMENT THE TRACE
// FACILITIES AND NOT THE ACTUAL CLASS ITSELF.
//

#ifdef INFOMATRIX_TRACE
    #ifdef __VC32__

        #define cotrTraceInitialiseL(aFS, aFileName)                           \
                {                                                              \
                    if ( Dll::Tls() == NULL )                                  \
                    {                                                          \
                        CInfomatrixTrace *trace = CInfomatrixTrace::NewL(aFS, aFileName);    \
                        Dll::SetTls(trace);                                    \
                    }                                                          \
                }
        #define cotrTraceEntry()                                               \
                if ( Dll::Tls() != NULL )                                      \
                {                                                              \
                ((CInfomatrixTrace*)(Dll::Tls()))->Entry(_L(__VC32_FUNCTION__),\
                                                         _L(__FILE__),         \
                                                         __LINE__);            \
                }
        #define cotrTraceExit()                                                \
                if ( Dll::Tls() != NULL )                                      \
                {                                                              \
                ((CInfomatrixTrace*)(Dll::Tls()))->Exit(_L(__VC32_FUNCTION__), \
                                                        _L(__FILE__),          \
                                                        __LINE__);             \
                }
        #define cotrTracePoint(s)                                              \
                if ( Dll::Tls() != NULL )                                      \
                {                                                              \
                ((CInfomatrixTrace*)(Dll::Tls()))->Point(_L((s)),              \
														 _L(__VC32_FUNCTION__),\
                                                         _L(__FILE__),         \
                                                         __LINE__);            \
                }
        #define cotrTraceValue(s,i)                                            \
                if ( Dll::Tls() != NULL )                                      \
                {                                                              \
                ((CInfomatrixTrace*)(Dll::Tls()))->Value(_L((s)), (i),         \
														 _L(__VC32_FUNCTION__),\
                                                         _L(__FILE__),         \
                                                         __LINE__);            \
                }
        #define cotrTraceTerminate()                                           \
                if ( Dll::Tls()!=NULL )                                        \
                { delete Dll::Tls(); Dll::SetTls(NULL); }



    #else
        #define cotrTraceInitialiseL(a,b)
        #define cotrTraceEntry()
        #define cotrTraceExit()
        #define cotrTracePoint(s)
        #define cotrTraceValue(s,i)
        #define cotrTraceTerminate()
    #endif
#else
    #define cotrTraceInitialiseL(a,b)
    #define cotrTraceEntry()
    #define cotrTraceExit()
    #define cotrTracePoint(s)
    #define cotrTraceValue(s,i)
    #define cotrTraceTerminate()
#endif

//
// Heap allocated class to provide trace facilities.
// This is the main interface to the rest of the converters, hence
// all of the public: functions are preceded by an IMPORT_C
//
// NOTE: CODE SHOULD NOT USE THIS CLASS DIRECTLY, BUT SHOULD USE THE
// MACROS DEFINED ABOVE.
//
class CInfomatrixTrace:public CBase
{
public:    // methods
    IMPORT_C ~CInfomatrixTrace(); // destructor
    IMPORT_C static CInfomatrixTrace* NewL(RFs& aFs, TDesC& aFileName);
    IMPORT_C static CInfomatrixTrace* NewLC(RFs& aFs, TDesC& aFileName);

    // Trace utilities
    IMPORT_C void Entry(TPtrC8 aName, TPtrC8  aFile,  TInt aLine);
    IMPORT_C void Exit (TPtrC8 aName, TPtrC8  aFile,  TInt aLine);
    IMPORT_C void Point(TPtrC8 aText, TPtrC8  aName,  TPtrC8 aFile,
                        TInt   aLine);
    IMPORT_C void Value(const TPtrC8 aText, const TInt   aValue,
                        const TPtrC8 aName, const TPtrC8 aFile,
                        const TInt aLine);
    IMPORT_C void Value(const TPtrC8 aText, const TDesC8&  aValue,
                        const TPtrC8 aName, const TPtrC8 aFile,
                        const TInt aLine);
    IMPORT_C void Value(const TPtrC8 aText, const TDesC16& aValue,
                        const TPtrC8 aName, const TPtrC8 aFile,
                        const TInt aLine);

protected: // methods
    void ConstructL(TDesC& aFileName);

private: // methods
    CInfomatrixTrace(RFs& aFs);    // constructor
    void Indent();
    void Info(TPtrC8 aName, TPtrC8 aFile, TInt aLine);

private: // data
    RFile               iFile;
    RFs                 iFs;
    TInt                iIndentLevel;
};

#endif // !defined (__COTRMAIN_H__)
