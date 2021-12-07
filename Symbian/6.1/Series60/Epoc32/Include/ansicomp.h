// 
// ANSIComp.h
// Copyright (C) 1997-1999 Symbian Ltd. All rights reserved.
//

// 
// Created at: 27-Jul-99 11:47:56 AM
// Comments: Enforce ANSI compliance on Microsoft compilers in 'For loop' behaviour
// 


#if !defined(__ANSICOMP_H__)
#define __ANSICOMP_H__

#if defined(__VC32__) && _MSC_VER>=1100
#pragma warning(disable : 4127)		// warning C4127 : conditional expression is constant

#define for if(false);else for		// Enforce the definition of a loop variable to local scope

#endif

#endif    // __ANSICOMP_H__
