/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __MACROS_H__
#define __MACROS_H__

//MACROS - similar to the TRAP/TRAPD Epoc defined macros

/*!
  @function CHECK_NO_PANIC

  @discussion Executes a statement within a trap harness, and then
  checks that it didn't panic - by checking for the special leave code
  produced by the reimplementation of User::Panic.
  @param sStatement the statement to execute
  */
#define CHECK_NO_PANIC(aStatement)		    \
	{									    \
	TInt error_code;						\
		{								    \
		TTrap __t;						    \
		if (__t.Trap(error_code) == 0)		\
			{						    	\
			aStatement;						\
			TTrap::UnTrap();		    	\
			}					    		\
		}					    			\
	if (error_code == KErrNone)				\
		{	    							\
		NoPanicPass();	    				\
		}								    \
	else if (error_code == KPanicTrapped)	\
		{								    \
		NoPanicFail();					    \
		}								    \
	else								    \
		{								    \
		User::Leave(error_code);		    \
		}								    \
	}


/*!
  @function CHECK_PANIC

  @discussion Executes a statement within a trap harness, and then
  checks that it did panic - by checking for the special leave code
  produced by the reimplementation of User::Panic.
  @param sStatement the statement to execute
  */
#define CHECK_PANIC(aStatement)			\
	{									\
	TInt error_code;					\
		{								\
		TTrap __t;						\
		if (__t.Trap(error_code) == 0)	\
			{							\
			aStatement;					\
			TTrap::UnTrap();			\
			}							\
		}								\
	if (error_code == KPanicTrapped)	\
		{								\
		PanicPass();					\
		}								\
	else if (error_code == KErrNone)	\
		{								\
		PanicFail();					\
		}								\
	else								\
		{								\
		User::Leave(error_code);		\
		}								\
	}


/*!
  @function CHECK_PANIC

  @discussion Executes a statement within a trap harness, and then
  checks that it didn't leave.
  @param sStatement the statement to execute
  */
#define CHECK_NO_LEAVE(aStatement)		\
	{									\
	TInt error_code;					\
		{								\
		TTrap __t;						\
		if (__t.Trap(error_code) == 0)	\
			{							\
			aStatement;					\
			TTrap::UnTrap();			\
			}							\
		}								\
	if (error_code == KErrNone)			\
		{								\
		NoLeavePass();					\
		}								\
	else								\
		{								\
		NoLeaveFail(error_code);		\
		}								\
	}


/*!
  @function CHECK_PANIC

  @discussion Executes a statement within a trap harness, and then
  checks that it did leave.
  @param sStatement the statement to execute
  */
#define CHECK_LEAVE(aStatement,aExpectedLeveCode)	\
	{									            \
	TInt error_code;						        \
		{								            \
		TTrap __t;						            \
		if (__t.Trap(error_code) == 0)		        \
			{							            \
			aStatement;						        \
			TTrap::UnTrap();			            \
			}							            \
		}								            \
	if (error_code == aExpectedLeveCode)	        \
		{								            \
		LeavePass();					            \
		}								            \
	else								            \
		{								            \
		LeaveFail(error_code);  		    	    \
		}						        		    \
	}


/*!
  @function CHECK_INVARIANTS_OK

  @discussion Executes a statement within a trap harness, and then
  checks that it didn't leave with the special value KInvariantTrapped
  produced by the reimplementation of User::Invariant.
  @param sStatement the statement to execute
  */
#define CHECK_INVARIANTS_OK(aStatement)	        \
	{									        \
	TInt error_code;					        \
		{								        \
		TTrap __t;						        \
		if (__t.Trap(error_code) == 0)	        \
			{							        \
			aStatement;                         \
            TTrap::UnTrap();			        \
			}							        \
		}								        \
	if (error_code == KErrNone)			        \
		{								        \
		OkInvariantPass();				        \
		}								        \
	else if (error_code == KInvariantTrapped)	\
		{								        \
		OkInvariantFail();				        \
		}								        \
	else								        \
		{								        \
		User::Leave(error_code);				\
		}								        \
	}


/*!
  @function CHECK_INVARIANTS_OK

  @discussion Executes a statement within a trap harness, and then
  checks that it did leave with the special value KInvariantTrapped
  produced by the reimplementation of User::Invariant.
  @param sStatement the statement to execute
  */
#define CHECK_INVARIANTS_BAD(aStatement)	\
	{									    \
	TInt error_code;						\
		{								    \
		TTrap __t;						    \
		if (__t.Trap(error_code) == 0)		\
			{							    \
			aStatement;                     \
            TTrap::UnTrap();			    \
			}							    \
		}								    \
	if (error_code == KInvariantTrapped)	\
		{								    \
		BadInvariantPass();				    \
		}								    \
	else if (error_code == KErrNone)		\
		{								    \
		BadInvariantFail();				    \
		}								    \
	else								    \
		{								    \
		User::Leave(error_code);			\
		}								    \
	}


#endif //__MACROS_H__
