/*
* ============================================================================
*  Name     : CommonPhoneParser from CommonPhoneParser.h
*  Part of  : ?module_name (e.g. Continuus subproject name)
*
*  Description:
*   Class to parse phone numbers. All methods are static.
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef CommonPhoneParser_H
#define CommonPhoneParser_H

//  INCLUDES
#include    <coemain.h>


// CLASS DECLARATION

/**
*  CommonPhoneParser
*   Phone number parser class. All methods are static.
*   Note!
*        There's two levels on validity. An example will probably
*        square the matter best.
*        Number for SMS (EPlainPhoneNumber) is valid if it contains (only) the
*        following
*        characters: "+1234567890()- " // Space represents all whitespaces
*        But it can be used for SMS sending only after parsing it to containing
*        characters: "+1234567890".
*        I.e.
*        TBuf<50> number = _L("+358 (40) 123 132");
*        TBool validNumber = CommonPhoneParser::ParsePhoneNumber( number,
*        CommonPhoneParser::EPlainPhoneNumber );
*        // validNumber = ETrue;
*        // number = "+35840123132"
*        SendSMS(number) // etc..
*        OR
*        TBuf<50> number = _L("+358 (40) 123p132"); // note 'p'
*        TBool validNumber = CommonPhoneParser::ParsePhoneNumber( number,
*        CommonPhoneParser::EPlainPhoneNumber );
*        // validNumber = EFalse;
*        // number = "+358-40w123p132" // unchanged
*/

class CommonPhoneParser
    {
    public:

        /**
        * Enumeration for phone number types
        */
        enum TPhoneNumberType
            {
            EPlainPhoneNumber,
            EContactCardNumber,
            EPhoneClientNumber,
			ESMSNumber
            };

        /**
        * Parse phone number
        *
        * If given Phone number is valid, method parses it and returns ETrue.
        *   If the number was not valid no parsing will be done, and method
        *   returns EFalse.
        *
        * @param aNumber Number which will be checked and parsed. Contains
        *                   parsed number after returning.
        * @param aType  Phone number type
        *
        * @return Returns ETrue if the number was valid and parsed.
        */
        IMPORT_C static TBool ParsePhoneNumber( TDes& aNumber, 
                                                TPhoneNumberType aType );

        /**
        * Check if string is a valid phone number
        *
        * @param aNumber Number which will be checked
        * @param aType  Phone number type
        *
        * @return ETrue if the number was valid
        */
        IMPORT_C static TBool IsValidPhoneNumber( const TDesC& aNumber,
                                                  TPhoneNumberType aType );
        
        /**
        * Check if string is a valid phone number
        *
        * @param aNumber Number which will be checked
        * @param aValidChars Chars that are valid for the number.
        *           Note! Some chars have special rules. See Find Item
        *           UI spec for more info.
        *
        * @return ETrue if the number was valid
        */
        static TBool IsValidPhoneNumber( const TDesC& aNumber,
                                         const TDesC& aValidChars);
        /**
        * Parses invalid characters from a string
        *
        * @param aNumber Number which will be parsed
        * @param aInvalidChars Characters that are invalid
        */
        static void ParseInvalidChars( TDes& aNumber,
                                       const TDesC& aInvalidChars);
    };

#endif      // CommonPhoneParser.h
            
// End of File
