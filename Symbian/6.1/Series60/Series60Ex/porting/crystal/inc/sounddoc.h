// Copyright c 2000, Nokia. All rights reserved.

#ifndef __SOUNDDOC_H__
#define __SOUNDDOC_H__

#include <eikdoc.h>

/** An instance of CSoundDocument is the Eikon framework document object. */

class CSoundDocument : public CEikDocument
    {
public:
/** @semantics Perform the first phase of two phase construction.*/
    CSoundDocument(CEikApplication& aApp);

/** @semantics Create a CSoundAppUi object and return a pointer to the object.*/
    CEikAppUi*  CreateAppUiL();
    };


#endif // __SOUNDDOC_H__

