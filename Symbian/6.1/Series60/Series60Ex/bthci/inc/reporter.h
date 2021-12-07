/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __MREPORTER__
#define __MREPORTER__

/*! 
  @class MReporter
  
  @discussion Implementation of this class provides logging capability
  */

class MReporter 
    {
public:
/*!
  @function Print
  
  @discussion Report text
  @param aText the log text
  */
    virtual void Print(const TDesC& aText) = 0;
/*!
  @function PrintLine
  
  @discussion Report text and appends new line.
  @param aText the log text
  */
    virtual void PrintLine(const TDesC& aText) = 0;
/*!
  @function PrintNewLine

  @discussion Print a new line.
  */
    virtual void PrintNewLine() = 0;
    };

#endif //__MREPORTER__
