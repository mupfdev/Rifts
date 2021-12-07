/*
* ============================================================================
*  Name     : RConeResourceLoader from RConeResLoder.h
*  Part of  : CommonEngine
*
*  Description:
*   Utility class for loading resources to the CONE environment.
*
*  Version:
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

#ifndef CONERESLOADER_H
#define CONERESLOADER_H

// forward declarations
class CCoeEnv;

/** 
* This class encapsulates adding and removing a localised resource file
* in the CONE environment. 
* Only one resource at a time may be open by one RConeResourceLoaderClass
* instance. You can use several RConeResourceLoaderClass instances for accessing
* several resources simultaneously or use one instance and close the previous
* resource before opening a new one.
*
* The implementation uses BaflUtils::NearestLanguageFile to search for
* a localised resource in proper search order.
* 
* Usage example:  
*
* #include <ConeResLoader.h>  
*
* RConeResourceLoader resourceLoader(iCoeEnv);
*
* _LIT(KMyResourcesWithFullPath,"z:\\System\\Data\\MyResources.rSC");
* TFileName fileName(KMyResourcesWithFullPath); 
* TInt err = resourceLoader.Open(fileName);
* if ( !err ) 
*
* // OR just (if Leaves are allowed) 
* resourceLoader.OpenL(fileName);
*
*  // read from the resources
* 
* resourceLoader.Close();
* // After closing another resource may be opened with same instance.
*
*/
class RConeResourceLoader
    {
    public:
        /**
         * Constructor. 
         * @param aEnv Control environment in which resource is loaded.
         */
        IMPORT_C RConeResourceLoader(CCoeEnv& aEnv);

        /**
         * Opens resource for use, only one resource may be open at a time,
         * panics if already opened.
         * 
         * @param aFileName Reference for resource file name. Please
         *                  note that drive letter is required ! 
         * @return Symbian OS error code.
         */
        IMPORT_C TInt Open(TFileName& aFileName);

        /**
         * Opens resource for use, only one resource may be open at a time,
         * Leaves if already opened.
         * 
         * @param aFileName Reference for resource file name. Please
         *                  note that drive letter is required ! 
         */
        IMPORT_C void OpenL(TFileName& aFileName);


        /**
         * Closes the resource file, new resource may be opened
         * after the previous has been closed.
         * You must always remember to close the resource when finished using
         * it.
         */
        IMPORT_C void Close();

    private:
                
        // Prohibit copy constructor and assigment operator because not deriving from CBase.
        RConeResourceLoader(const RConeResourceLoader&);
        RConeResourceLoader& operator= ( const RConeResourceLoader& );
    
        // Needed for closing
        CCoeEnv& iEnv; 
        TInt iResourceFileOffset;
    };


#endif

// End of File
