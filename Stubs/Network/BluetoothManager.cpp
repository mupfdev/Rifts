#include <es_sock.h>
#include "common.h"
#include "BluetoothManager.h"
#include "Utility/SymbStrings.h"

BluetoothManager* BluetoothManager::NewL()
{
    BluetoothManager* pBluetoothManager = BB_NEW(BluetoothManager);
    CleanupStack::PushL(pBluetoothManager);
    pBluetoothManager->ConstructL();
    CleanupStack::Pop();
    return pBluetoothManager;
}

void BluetoothManager::ConstructL()
{
    return;
}

bool BluetoothManager::SetCurrentName(char* a_pName, bool a_bPreventSave = false)
{
    (void)a_pName;
    (void)a_bPreventSave;
    return true;
}

const THostName BluetoothManager::GetCurrentName()
{
    THostName l_Name;
    StrToDes(l_Name, (char*)"Juicer");
    return l_Name;
}

bool Connect()
{
    return false;
}

void Disconnect(int a_DeviceID = -1, bool a_Permanently = true)
{
    (void)a_DeviceID;
    (void)a_Permanently;
    return;
}

bool BluetoothManager::IsBluetoothEnabled()
{
    return false;
}

bool BluetoothManager::IsClient()
{
    return true;
}

bool BluetoothManager::IsHost()
{
    return false;
}

void BluetoothManager::RegisterCallback(INetworkCallbacks* a_pCallback)
{
    (void)a_pCallback;
    return;
}

bool BluetoothManager::RemoveCallback(INetworkCallbacks* a_pCallback)
{
    (void)a_pCallback;
    return true;
}
