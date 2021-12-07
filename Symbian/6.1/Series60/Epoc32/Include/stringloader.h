/*
* ============================================================================
*  Name     : StringLoader from StringLoader.h
*  Part of  : CommonEngine
*
*  Description:
*     StringLoader -class provides methods for loading resource strings
*     and formating them. The order of formating is described in .loc -file.
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
* ============================================================================
*/
#ifndef STRINGLOADER_H
#define STRINGLOADER_H

// INCLUDE FILES
#include    <coemain.h>

// CLASS DECLARATION

/**
*  Resource string loader.
*
*  This module provides interface to load and format
*  resource strings which may contain parameter(s) (%U or %N) as defined
*  by localisation file template (resource_localisation_template.loc).
*
*  Using examples:
*
*  One TInt to add:
*
*  (In .loc -file)
*  #define text_example "You have %N undone tasks."
*
*  (In .rss -file)
*  RESOURCE TBUF r_text_example { buf = text_example; }
*
*  (In the .cpp -file)
*  TInt number( 324 );
*
*  //
*  //iEikonEnv is needed for loading the resource string.
*  //
*  HBufC* stringholder = StringLoader::LoadL( R_TEXT_EXAMPLE, number, iEikonEnv );
*
*  //
*  //The TInt in number is added to the resource string. The result is
*  //that stringholder points to a heap descriptor containing string:
*  //"You have 324 undone tasks."
*  //
*
*  Several strings to add:
*
*  (In .loc -file)
*  #define text_example "I'm %2U%1U %3U%0U fine." 
*
*  (In .rss -file)
*  RESOURCE TBUF r_text_example { buf = text_example; }
*
*  (In the .cpp -file)
*  CDesCArrayFlat* strings = new CDesCArrayFlat( 4 );
*  CleanupStack::PushL( strings );
*
*  strings->AppendL( _L("orking") ); //First string
*
*  strings->AppendL( _L("ll") ); //Second string
*
*  strings->AppendL( _L("sti") ); //Third string
*
*  strings->AppendL( _L("w") ); //Fourth string
*
*  //
*  //iEikonEnv is needed for loading the resource string.
*  //
*  HBufC* stringholder = StringLoader::LoadL( R_TEXT_EXAMPLE, *strings, iEikonEnv );
*
*  //
*  //The strings in strings are added to the resource string. The result is
*  //that stringholder points to a heap descriptor containing string:
*  //"I'm still working fine."
*  //
*
*  CleanupStack::PopAndDestroy(); //strings
*
*  Error handling:
*
*  The leave mechanism of Symbian OS environment is used to handle memory 
*  exhaustion. Errors in application programming are handled with the panic
*  mechanism of Symbian OS environment.
*    
*   Error codes:
*   ETooFewArguments, (Unsolved parameters in resource string.)
*   ETooManyArguments, (Already solved all parameters in  resource string.)
*   EKeyStringNotFound, (The key string wasn't found in formating.)
*   EInvalidIndex, (Invalid index in Format-method)
*   EDescriptorTooSmall (Too small destination descriptor)
*
*/
class StringLoader 
    {
    public:

        
        /**
        * Load( TDes&, TInt ) reads a resource string without memory 
        * allocation. The loaded string is stored in the destination TDes&.
        *
        * @param aResourceId The numeric ID of the resource string to be read.
        * @param aDest Reference to the descriptor where the resource string
        *              is loaded.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        *
        * This method doesn't allocate memory. The destination descriptor must
        * be long enough. Otherwise panic occurs.
        */
        IMPORT_C static void Load( TDes& aDest, TInt aResourceId, 
                                   CCoeEnv* aLoaderEnv = NULL );

        /**
        * Format( TDes&, TDesC&, TInt, TInt ) formats a resource string without 
        * memory allocation. The formated string is stored in the destination 
        * TDes&.
        *
        * @param aDest Reference to the descriptor where the resource string
        *              is formated.
        * @param aOriginal Reference to the original string.
        * @param aPosition The index of the key string.
        * @param aSubs the replacing TInt.
        *
        * This method doesn't allocate memory. The destination descriptor must
        * be long enough. Otherwise panic occurs. In aPositon, -1 means that
        * there is no index in the key string.
        */
        IMPORT_C static void Format( TDes& aDest, const TDesC& aSource, 
                                   TInt aPosition, TInt aSubs );

        /**
        * Format( TDes&, TDesC&, TInt, TDesC& ) formats a resource string 
        * without memory allocation. The formated string is stored in the 
        * destination TDes&.
        *
        * @param aDest Reference to the descriptor where the resource string
        *              is formated.
        * @param aOriginal Reference to the original string.
        * @param aPosition The index of the key string.
        * @param aSubs Reference to the replacing string.
        *
        * This method doesn't allocate memory. The destination descriptor must
        * be long enough. Otherwise panic occurs. In aPositon, -1 means that
        * there is no index in the key string.
        */
        IMPORT_C static void Format( TDes& aDest, const TDesC& aSource, 
                                   TInt aPosition, const TDesC& aSubs );

        /**
        * LoadL( TInt ) reads a resource string with memory allocation.
        *
        * @param aResourceId The numeric ID of the resource string to be read.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the resource 
        *         string.
        *
        * The calling program must destroy the heap descriptor when it is no 
        * longer needed.
        */
        IMPORT_C static HBufC* LoadL( TInt aResourceId, 
                                      CCoeEnv* aLoaderEnv = NULL );

        /**
        * LoadL( TInt, TInt ) reads a resource string with memory 
        * allocation and replaces the first %N-string in it with replacement
        * TInt.
        *
        * @param aResourceId The numeric ID of the resource string to be read.
        * @param aInt the replacing TInt.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return pointer to a heap descriptor containing the formated 
        *         resource string.
        *
        * The calling program must destroy the heap descriptor when it is no 
        * longer needed.
        */
        IMPORT_C static HBufC* LoadL( TInt aResourceId, TInt aInt, 
                                      CCoeEnv* aLoaderEnv = NULL);

        /**
        * LoadL( TInt, const TDesC&) reads a resource string with memory 
        * allocation and replaces the first %U-string in it with replacement 
        * string.
        *
        * @param aResourceId The numeric ID of the resource string to be read.
        * @param aString Reference to the replacing string.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the formated 
        *         resource string.
        *
        * The calling program must destroy the heap descriptor when it is no 
        * longer needed.
        */
        IMPORT_C static HBufC* LoadL( TInt aResourceId, 
                                    const TDesC& aString, 
                                    CCoeEnv* aLoaderEnv = NULL );

        /**
        * LoadL( TInt, const TDesC&, TInt ) reads a resource string 
        * with memory allocation, replaces the first %N-string in it with 
        * replacement TInt and the first %U-string in it with replacement 
        * string.
        *
        * @param aResourceId The numeric ID of the resource string to be 
        *                    read.
        * @param aString Reference to the replacing string.
        * @param aInt The replacing TInt.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the formated 
        *         resource string.
        *
        * The calling program must destroy the heap descriptor when it is no 
        * longer needed.
        */
        IMPORT_C static HBufC* LoadL( TInt aResourceId, const TDesC& aString, 
                                    TInt aInt, CCoeEnv* aLoaderEnv = NULL );

        /**
        * LoadL( TInt, const CArrayFix<TInt>& ) reads a resource string with 
        * memory allocation and replaces the %(index)N-strings in it with 
        * replacement TInts from an array.
        *
        * @param aResourceId The numeric ID of the resource string to be 
        *                    read.
        * @param aInts Reference to the array including the replacing TInts.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the formated 
        *         resource string.
        *
        * The calling program must destroy the heap descriptor when it is no 
        * longer needed.
        */
        IMPORT_C static HBufC* LoadL( TInt aResourceId,
                                    const CArrayFix<TInt>& aInts,
                                    CCoeEnv* aLoaderEnv = NULL);

        /**
        * LoadL( TInt, const MDesCArray& ) reads a resource string with 
        * memory allocation and replaces the %(index)U-strings in it with 
        * replacement strings from an array.
        *
        * @param aResourceId The numeric ID of the resource string to be read.
        * @param aStrings Reference to the array  including pointers to the
        *                 replacing strings.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the formated 
        *         resource string.
        *
        * The calling program must destroy the heap descriptor when it is no 
        * longer needed.
        */
        IMPORT_C static HBufC* LoadL( TInt aResourceId,
                                    const MDesCArray& aStrings,
                                    CCoeEnv* aLoaderEnv = NULL);

        /**
        * LoadL( TInt, const MDesCArray&, const CArrayFix<TInt>& ) reads a 
        * resource string with memory allocation and replaces the 
        * %(index)U-strings in it with replacement strings from an array and 
        * the %(index)N-strings in it with replacement TInts from another 
        * array.
        *
        * @param aResourceId The numeric ID of the resource string to be read.
        * @param aStrings Reference to the array including pointers to the 
        *                 replacing strings.
        * @param aInts Reference to the array including the replacing TInts.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the formated 
        *         resource string.
        *
        * The calling program must destroy the heap descriptor when it is no 
        * longer needed.
        */
        IMPORT_C static HBufC* LoadL( TInt aResourceId,
                                    const MDesCArray& aStrings, 
                                    const CArrayFix<TInt>& aInts,
                                    CCoeEnv* aLoaderEnv = NULL);
        /**
        * LoadLC( TInt ) reads a resource string with memory allocation and 
        * pushes the string onto the cleanup stack.
        *
        * @param aResourceId The numeric ID of the resource string to be read.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the resource 
        *         string. This pointer is in the cleanup stack.
        *
        * The calling program should pop and destroy the heap descriptor when
        * it is no longer needed.
        */
        IMPORT_C static HBufC* LoadLC( TInt aResourceId,
                                        CCoeEnv* aLoaderEnv = NULL);

        /**
        * LoadLC( TInt, TInt ) reads a resource string with memory 
        * allocation, replaces the first %N-string in it with replacement
        * TInt and pushes the string onto the cleanup stack.
        *
        * @param aResourceId The numeric ID of the resource string to be read.
        * @param aInt the replacing TInt.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return pointer to a heap descriptor containing the formated 
        *         resource string. This pointer is in the cleanup stack.
        *
        * The calling program should pop and destroy the heap descriptor when
        * it is no longer needed.
        */
        IMPORT_C static HBufC* LoadLC( TInt aResourceId, TInt aInt,
                                        CCoeEnv* aLoaderEnv = NULL);

        /**
        * LoadLC( TInt, const TDesC&) reads a resource string with memory 
        * allocation, replaces the first %U-string in it with replacement 
        * string and pushes the string onto the cleanup stack.
        *
        * @param aResourceId The numeric ID of the resource string to be read.
        * @param aString Reference to the replacing string.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the formated 
        *         resource string. This pointer is in the cleanup stack.
        *
        * The calling program should pop and destroy the heap descriptor when
        * it is no longer needed.
        */
        IMPORT_C static HBufC* LoadLC( TInt aResourceId, 
                                    const TDesC& aString,
                                    CCoeEnv* aLoaderEnv = NULL);

        /**
        * LoadLC( TInt, const TDesC&, TInt ) reads a resource string 
        * with memory allocation, replaces the first %N-string in it with 
        * replacement TInt and the first %U-string in it with replacement 
        * string and pushes the string onto the cleanup stack.
        *
        * @param aResourceId The numeric ID of the resource string to be 
        *                    read.
        * @param aString Reference to the replacing string.
        * @param aInt The replacing TInt.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the formated 
        *         resource string. This pointer is in the cleanup stack.
        *
        * The calling program should pop and destroy the heap descriptor when
        * it is no longer needed.
        */
        IMPORT_C static HBufC* LoadLC( TInt aResourceId, const TDesC& aString, 
                                    TInt aInt, CCoeEnv* aLoaderEnv = NULL );

        /**
        * LoadLC( TInt, const CArrayFix<TInt>& ) reads a resource string with 
        * memory allocation, replaces the %(index)N-strings in it with 
        * replacement TInts from an array and pushes the string onto the 
        * cleanup stack.
        *
        * @param aResourceId The numeric ID of the resource string to be 
        *                    read.
        * @param aInts Reference to the array including the replacing TInts.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the formated 
        *         resource string. This pointer is in the cleanup stack.
        *
        * The calling program should pop and destroy the heap descriptor when
        * it is no longer needed.
        */
        IMPORT_C static HBufC* LoadLC( TInt aResourceId,
                                    const CArrayFix<TInt>& aInts,
                                    CCoeEnv* aLoaderEnv = NULL);

        /**
        * LoadLC( TInt, const MDesCArray& ) reads a resource string with 
        * memory allocation, replaces the %(index)U-strings in it with 
        * replacement strings from an array and pushes the string onto the
        * cleanup stack.
        *
        * @param aResourceId The numeric ID of the resource string to be read.
        * @param aStrings Reference to the array  including pointers to the
        *                 replacing strings.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the formated 
        *         resource string. This pointer is in the cleanup stack.
        *
        * The calling program should pop and destroy the heap descriptor when
        * it is no longer needed.
        */
        IMPORT_C static HBufC* LoadLC( TInt aResourceId,
                                    const MDesCArray& aStrings,
                                    CCoeEnv* aLoaderEnv = NULL);

        /**
        * LoadLC( TInt, const MDesCArray&, const CArrayFix<TInt>& ) reads a 
        * resource string with memory allocation, replaces the 
        * %(index)U-strings in it with replacement strings from an array and 
        * the %(index)N-strings in it with replacement TInts from another 
        * array and pushes the string onto the cleanup stack.
        *
        * @param aResourceId The numeric ID of the resource string to be read.
        * @param aStrings Reference to the array including pointers to the 
        *                 replacing strings.
        * @param aInts Reference to the array including the replacing TInts.
        * @param aLoaderEnv Pointer to the control environment. If user doesn't
        *                   give this, CCoeEnv::Static is called to get it.
        * @return Pointer to a heap descriptor containing the formated 
        *         resource string. This pointer is in the cleanup stack.
        *
        * The calling program should pop and destroy the heap descriptor when
        * it is no longer needed.
        */
        IMPORT_C static HBufC* LoadLC( TInt aResourceId,
                                    const MDesCArray& aStrings, 
                                    const CArrayFix<TInt>& aInts,
                                    CCoeEnv* aLoaderEnv = NULL);

    private:

        /**
        * C++ default constructor.
        */
        StringLoader();
        
        // Prohibit copy constructor
        StringLoader( const StringLoader& );
        // Prohibit assigment operator
        StringLoader& operator= ( const StringLoader& );

        /**
		* FormatStringL( const TDesC&, const TDesC&, const TDesC& ) finds the 
        * keystring from the source string and replaces it with the 
        * replacement string.
        *
        * @param aSource Reference to the source string.
        * @param aKey Reference to the keystring.
        * @param aSubs Reference to the replacing string.
        * @return Pointer to a heap descriptor containing the formated string.
        */
        static HBufC* FormatStringL( const TDesC& aSource, const TDesC& aKey, 
                                   const TDesC& aSubs );

        /**
		* FormatStringL( HbufC*, const CArrayFix<TInt>&, TInt ) finds the 
        * %(index)N-keystrings from the source string and replaces it with the 
        * replacement TInts.
        * @param aSource Reference to the source string.
        * @param aInts Reference to the array  containing the replacing TInts.
        * @param aMax Maximum number of key strings in the resource string.
        * @return Pointer to a heap descriptor containing the formated string.
        */
        static HBufC* FormatStringL( TDesC& aSource, 
                                   const CArrayFix<TInt>& aInts, 
                                   TInt aMax );

        /**
		* FormatStringL( HbufC*, const MDesCArray&, TInt ) finds the 
        * %(index)U-keystrings from the source string and replaces it with the 
        * replacement strings.
        *
        * @param aSource Reference to the source string.
        * @param aStrings Reference to the array containing pointers to the
        *                 replacing strings.
        * @param aMax Maximum number of key strings in the resource string.
        * @return Pointer to a heap descriptor containing the formated 
        *         string.
        */
        static HBufC* FormatStringL( TDesC& aSource, 
                                   const MDesCArray& aStrings, 
                                   TInt aMax);
        /**
		* Formater( TDes&, const TDesC&, const TDesC&, const TDesC& ) finds 
        * the keystring from the source string and replaces it with the 
        * replacement string. The formated string is stored in the destination
        * descriptor.
        *
        * @param aDest Reference to the destination descriptor.
        * @param aSource Reference to the source string.
        * @param aKey Reference to the keystring.
        * @param aSubs Reference to the replacing string.
        */
        static void Formater( TDes& aDest, const TDesC& aSource,  
                          const TDesC& aKey, const TDesC& aSubs );

        /**
		* KeyStringFormater( TDes&, const TText&, TInt, const TDesC& ) formats 
        * the keystring from given parameters. 
        *
        * @param aDest Reference to the destination descriptor.
        * @param aKey Reference to the key letter.
        * @param aPosition index of the key string.
        * @param aKeyString Reference to the keystring.
        */
        static void KeyStringFormater( TDes& aDest, const TText& aKey, 
                                        TInt aPosition, const TDesC& aKeyString );

    };

#endif      // STRINGLOADER_H   
            
// End of File
