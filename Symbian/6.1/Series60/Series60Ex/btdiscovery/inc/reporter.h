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
  @function Error

  @discussion reports an error
  @param text the log text
  */
    virtual void Error(const TDesC& aText) = 0;
/*!
  @function Print
  
  @discussion reports text
  @param text the log text
  */
    virtual void Print(const TDesC& aText) = 0;
/*!
  @function PrintLine
  
  @discussion reports text and appends new line.
  @param text the log text
  */
    virtual void PrintLine(const TDesC& aText) = 0;
/*!
  @function PrintNewLine

  @discussion prints a new line.
  */
    virtual void PrintNewLine() = 0;
    };

#endif //__MREPORTER__