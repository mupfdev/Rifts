#ifndef SYSTEMAPP_H
#define SYSTEMAPP_H

#include <coeccntx.h>

#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikmenup.h>

#include <eikon.hrh>

class CSystemApp : public CEikApplication
{
public:
    ~CSystemApp();

private:
    // Inherited from class CApaApplication
    CApaDocument* CreateDocumentL();
    TUid AppDllUid() const;
};

class CSystemAppView : public CCoeControl
{
public:
    static CSystemAppView* NewL(const TRect& aRect);
    CSystemAppView();
    ~CSystemAppView();
    void ConstructL(const TRect& aRect);

private:
    // Inherited from CCoeControl
    void Draw(const TRect& /*aRect*/) const;

private:
    HBufC*  iSystemText;
};


class CSystemAppUi : public CEikAppUi
{
public:
    void ConstructL();
    ~CSystemAppUi();

private:
    // Inherirted from class CEikAppUi
    void HandleCommandL(TInt aCommand);

private:
    CCoeControl* iAppView;
};

class CSystemDocument : public CEikDocument
{
public:
    static CSystemDocument* NewL(CEikApplication& aApp);
    CSystemDocument(CEikApplication& aApp);
    void ConstructL();
private:
    // Inherited from CEikDocument
    CEikAppUi* CreateAppUiL();
};

#endif /* SYSTEMAPP_H */
