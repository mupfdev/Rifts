// ETOOLS.H
//
// version 1.01
//

#if !defined(__ETOOLS_H__)
#define __ETOOLS_H__

#include <e32std.h>
#include <e32panic.h>
#include <e32svr.h>


// Tool for putting a name to the class
// when a memory leak occurs, you can trace it back
// by looking at the memory space!
// the for(;;) is a bit awkward
//#if defined(_DEBUG)
//#define CLASSNAMEDECL(a) char __iName[sizeof(#a)];
/*#define CLASSNAMEINIT(a) \
	char tmp[] = #a; \
	for(TUint _i_##a=0;_i_##a<sizeof(tmp);_i_##a++) __iName[_i_##a] = tmp[_i_##a]; 
	*/
//#define CLASSNAME this->__iName
//#else
#define CLASSNAMEDECL(a)
#define CLASSNAMEINIT(a)
#define CLASSNAME "?"
//#endif



//
// put this in your constructor/destructor to see the memory usage
//
//#if defined(_DEBUG)
/*#define CTOR(a)	\
	LOGTEXT4(_L8("+++ object at 0x%08x (%d bytes) %s "), this, sizeof(a) - __Align8(sizeof(__iName)), #a );
//
#define DTOR(a)	\
	LOGTEXT4(_L8("--- object at 0x%08x (%d bytes) %s"), this, sizeof(a) - (4+(sizeof(__iName) & ~0x03)), #a );
*/
//#else
#define CTOR(a)
#define DTOR(a)
//#endif




//
// Use this macro in the beginning of functions to check that some ptrs are != NULL
//

#ifndef __PANIC
#define __PANIC { char tmp[] = __FILE__; \
        TInt i;\
		for(i=sizeof(tmp)-1;i>=0;i--) \
			if( (tmp[i] == 0x5c /* '\' */) || (tmp[i] == '/') ) \
				break; \
		TBuf8<32> txt8((const TUint8*)&tmp[++i]); \
		TBuf16<32> txt16; \
  		txt16.Copy(txt8); \
  		User::Panic( txt16 , __LINE__ ); }
#endif

#if defined(__WINS__) || defined(_DEBUG)
#define __CHECK_NULL(p) if(p == NULL) __PANIC
#else
#define __CHECK_NULL(p)	if(p == NULL) return EReqNull; // 48
#endif





//
// size of arrays
//

#ifndef ELEM_SIZE
#define ELEM_SIZE(t) (sizeof(t)/sizeof(t[0]))
#endif

//
//	Check var against mask, return bool type
//
#define BOOL_BIT(var,msk) ( (var & msk)==(msk) )

#if _DEBUG
#define _DBG(p)	p
#else
#define _DBG(p)
#endif

#if defined(_DEBUG) && !defined(__WINS__)
//#define DBGARM(a)	RDebug::Print(_L(a));
#define DBGARM(a)
#else
#define DBGARM(a)
#endif

//
// small macro for bit fickling
//

#ifndef BIT
#define BIT(a) (1 << a)
#else
#pragma message ("warning: BIT already defined")
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Version history
//
////////////////////////////////////////////////////////////////////////////////
//
// 1.00 - initial version
//
// 1.01 - added BIT macro
//
////////////////////////////////////////////////////////////////////////////////



#endif // ETOOLS_H
