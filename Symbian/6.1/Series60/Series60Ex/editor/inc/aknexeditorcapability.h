/*
* ============================================================================
*  Name     : CTestEikMfneIntPositive,CTestEikMfneIntNegative,
*             CTestEikMfneIntBoth from CEikMfne
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXEDITORCAPABILITY_H
#define AKNEXEDITORCAPABILITY_H

// INCLUDES
#include <eikmfne.h>


class CTestEikMfneIntPositive:public CEikMfne
{
public:
    CTestEikMfneIntPositive();
    ~CTestEikMfneIntPositive();
    virtual TCoeInputCapabilities InputCapabilities() const;
};

class CTestEikMfneIntNegative:public CEikMfne
{
public:
    CTestEikMfneIntNegative();
    ~CTestEikMfneIntNegative();
    virtual TCoeInputCapabilities InputCapabilities() const;
};

class CTestEikMfneIntBoth:public CEikMfne
{
public:
    CTestEikMfneIntBoth();
    ~CTestEikMfneIntBoth();
    virtual TCoeInputCapabilities InputCapabilities() const;
};

#endif

// End of File
