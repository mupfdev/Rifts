// 
// PragmaMessage.h
// Copyright (C) 1997-1999 Symbian Ltd. All rights reserved.
// 
// Created at: 20-Dec-99 10:38:03 AM

//
// Comments: Defines a macro for the file line pragma message
// 


#if !defined __PRAGMAMESSAGE_H__
#define __PRAGMAMESSAGE_H__

#define _QUOTE(x) # x
#define QUOTE(x) _QUOTE(x)

// Use __FILE__LINE__ as a string containing "File.x(line#)" for example:
//     #pragma message( __FILE__LINE__ "Remove this line after testing.")
// The above example will display the file name and line number in the build window
// in such a way as to allow you to double click on it to go to the line.
#define __FILE__LINE__ __FILE__ "(" QUOTE(__LINE__) ") : "

#endif	// __PRAGMAMESSAGE_H__


