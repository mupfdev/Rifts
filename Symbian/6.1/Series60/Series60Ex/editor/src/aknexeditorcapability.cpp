/*
* ============================================================================
*  Name     : CTestEikMfneIntPositive,CTestEikMfneIntNegative,
*             CTestEikMfneIntBoth from CEikMfne
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES

#include "AknExEditorCapability.h" 


//    TCoeInputCapabilities inputCapabilities(TCoeInputCapabilities::ENavigation | TCoeInputCapabilities::EWesternNumericIntegerPositive | TCoeInputCapabilities::EWesternNumericIntegerNegative);
//    TCoeInputCapabilities inputCapabilities(TCoeInputCapabilities::ENavigation | TCoeInputCapabilities::ESecretText); this crashes
//    TCoeInputCapabilities inputCapabilities(TCoeInputCapabilities::ENavigation | TCoeInputCapabilities::EAllText);  this does not bring fep at all 


// Capability is set only with EWesternNumericIntegerPositive flag. 

CTestEikMfneIntPositive::CTestEikMfneIntPositive()
    {
    }

CTestEikMfneIntPositive::~CTestEikMfneIntPositive()
    {
    }

TCoeInputCapabilities CTestEikMfneIntPositive::InputCapabilities() const
    {
    TCoeInputCapabilities inputCapabilities(TCoeInputCapabilities::ENavigation | TCoeInputCapabilities::EWesternNumericIntegerPositive);
    return inputCapabilities;
    }

// Capability is set only with EWesternNumericIntegerNegative flag. 

CTestEikMfneIntNegative::CTestEikMfneIntNegative()
    {
    }

CTestEikMfneIntNegative::~CTestEikMfneIntNegative()
    {
    }

TCoeInputCapabilities CTestEikMfneIntNegative::InputCapabilities() const
    {
    TCoeInputCapabilities inputCapabilities(TCoeInputCapabilities::ENavigation | TCoeInputCapabilities::EWesternNumericIntegerNegative);
    return inputCapabilities;
    }

// Capability is set with both with EWesternNumericIntegerNegative & EWesternNumericIntegerPositive flag

CTestEikMfneIntBoth::CTestEikMfneIntBoth()
    {
    }

CTestEikMfneIntBoth::~CTestEikMfneIntBoth()
    {
    }

TCoeInputCapabilities CTestEikMfneIntBoth::InputCapabilities() const
    {
    TCoeInputCapabilities inputCapabilities(TCoeInputCapabilities::ENavigation | TCoeInputCapabilities::EWesternNumericIntegerPositive | TCoeInputCapabilities::EWesternNumericIntegerNegative);
    return inputCapabilities;
    }



