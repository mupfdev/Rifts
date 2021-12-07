// CRuleMarkedStack.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved. 
//

// A speciales marked stack specifically for PARSE rules.
// Allows a rule stack to merge rules upto a given mark type.

#ifndef __CRULEMARKEDSTACK_H__
#define __CRULEMARKEDSTACK_H__


// includes
#include <e32base.h>
#include <CMarkedStack.h>
#include <CBNFNode.h>

#pragma warning (disable : 4127) // conditional expression is constant

// CRuleMarkedStack
template <TBool StackOwnsEntry>
class CRuleMarkedStack : public CMarkedStack<CBNFNode, StackOwnsEntry>
	{
public:
	void MergeToMarkL(TInt aMarkType);
	};

#include <CRuleMarkedStack.inl>

#pragma warning ( default : 4127 ) // conditional expression is constant

#endif // __CRULEMARKEDSTACK_H__
