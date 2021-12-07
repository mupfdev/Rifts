/* Copyright (c) 2002, Nokia. All rights reserved */

#include <avkon.hrh>
#include <aknnotewrappers.h> 
#include <aknlists.h>
#include <s32file.h>
#include <s32crypt.h>

#include <Cipher.rsg>

#include "Cipher.pan"
#include "CipherAppUi.h"
#include "CipherAppView.h"
#include "Cipher.hrh"

// Maximum length of the password
const TInt KAknExQueryTextBufLength = 24;

// Maximum length of the key data
const TInt KMaxKeyDataLength = 2024;

// Maximum length of the message
const TInt KMaxPlainTextDataLength = 1012;

// Location of the encrypted file
_LIT(KCipherFilePath,"\\system\\apps\\cipher\\cipher.enc");
_LIT(KCipherDir,"\\system\\apps\\cipher\\");

// ConstructL is called by the application framework
void CCipherAppUi::ConstructL()
    {
    BaseConstructL();
    iAppView = CCipherAppView::NewL(ClientRect());
    iAppView->SetMopParent(this);
    AddToStackL(iAppView);
    }

CCipherAppUi::CCipherAppUi()                              
    {
    // no implementation required
    }

CCipherAppUi::~CCipherAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

// handle any menu commands
void CCipherAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        case ECipherEncrypt:
            EncryptL();
            break;

        case ECipherDecrypt:
            DecryptL();
            break;

        default:
            Panic(ECipherBasicUi);
            break;
        }
    }


void CCipherAppUi::EncryptL()
    {
    // Query the user for the password and text
    TBuf<KAknExQueryTextBufLength> textToEncrypt;
    TBuf<KAknExQueryTextBufLength> password;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(textToEncrypt, password);
    if (! dlg->ExecuteLD(R_DIALOG_TEXT_PASSWORD_QUERY))
    {
        return;
    }

    // Create a file to write the cipher text to
    RFs fileSession;
    User::LeaveIfError(fileSession.Connect());
    CleanupClosePushL(fileSession);
    fileSession.MkDir(KCipherDir); // Ignore return value
    RFile file;
    if (file.Replace(fileSession, KCipherFilePath, EFileWrite) != KErrNone)
        {
        CAknInformationNote* informationNote = new (ELeave)CAknInformationNote;
        informationNote->ExecuteLD(_L("Failed to create cipher.enc"));
        CleanupStack::PopAndDestroy(); // close fileSession
        return;
        }
    CleanupClosePushL(file);

    // Set up the encryption engine with the user supplied password
    CBoundedSecurityBase* encrypter = Security::NewL();
    CleanupStack::PushL(encrypter);
    encrypter->SetL(KNullDesC, password);

    // Write the security data, used in the decryption process to
    // verify the password
    RFileWriteStream outputFileStream(file);
    CleanupClosePushL(outputFileStream);
    outputFileStream << encrypter->SecurityData(); // must use streaming api not WriteL

    // Write the encrypted data
    REncryptStream encryptedFileStream;
    encryptedFileStream.AttachLC(outputFileStream, *encrypter, KNullDesC8); 
    encryptedFileStream << textToEncrypt;
    encryptedFileStream.Close();
    encryptedFileStream.Pop();

    // Clean up
    CleanupStack::PopAndDestroy(); // close outputFileStream
    CleanupStack::PopAndDestroy(encrypter); 
    CleanupStack::PopAndDestroy(); // close file 
    CleanupStack::PopAndDestroy(); // close fileSession
    
    iAppView->PrintLineL(_L("Encrypted text:"));
    iAppView->PrintLineL(textToEncrypt);
    iAppView->PrintLineL(_L("to file cipher.enc"));
    }

void CCipherAppUi::DecryptL()
    {
    // Query the user for the password
    TBuf<KAknExQueryTextBufLength> password;
    CAknTextQueryDialog* dlg = 
        new (ELeave) CAknTextQueryDialog(password, CAknQueryDialog::ENoTone);
    if (! dlg->ExecuteLD(R_DIALOG_PASSWORD_QUERY))
    {
        return;
    }

    // open file containing encrypted data
    RFs fileSession;
    User::LeaveIfError(fileSession.Connect());
    CleanupClosePushL(fileSession);
    RFile file;
    User::LeaveIfError(file.Open(fileSession, KCipherFilePath, EFileRead));
    CleanupClosePushL(file);

    RFileReadStream inputFileStream(file);
    CleanupClosePushL(inputFileStream);

    // read the security data 
    HBufC8* securityData = HBufC8::NewLC(inputFileStream, KMaxKeyDataLength);

    // create security object, using the read security data
    CBoundedSecurityBase* decrypter = Security::NewL(*securityData); 
    CleanupStack::PushL(decrypter);

    // authenticate password
    TRAPD(err, decrypter->PrepareL(password));
    if (err != KErrNone)
        {
        CAknInformationNote* informationNote = new (ELeave)CAknInformationNote;
        informationNote->ExecuteLD(_L("Failed To Verify Password!"));
        }
    else 
        {
        // Read the encrypted data
        RDecryptStream decryptedFileStream;
        decryptedFileStream.AttachLC(inputFileStream, *decrypter, KNullDesC8); 
        CleanupClosePushL(decryptedFileStream);
        HBufC* decryptedData = HBufC::NewLC(decryptedFileStream, KMaxPlainTextDataLength);

        iAppView->PrintLineL(_L("Decrypted cipher.enc"));
        iAppView->PrintLineL(_L("Contents:"));
        iAppView->PrintLineL(*decryptedData);

        CleanupStack::PopAndDestroy(decryptedData);
        CleanupStack::PopAndDestroy(); // close decryptedFileStream
        decryptedFileStream.Pop(); // removes item placed on cleanup stack by AttachLC
        }

    CleanupStack::PopAndDestroy(decrypter);
    CleanupStack::PopAndDestroy(securityData);

    CleanupStack::PopAndDestroy(); // close inputFileStream 
    CleanupStack::PopAndDestroy(); // close file 
    CleanupStack::PopAndDestroy(); // close fileSession
    }
