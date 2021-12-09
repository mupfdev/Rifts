#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <es_sock.h>

class INetworkCallbacks;

typedef List<INetworkCallbacks*> NET_CALLBACK_LIST;
typedef List<INetworkCallbacks*>::iterator NET_CALLBACK_ITERATOR;

#define USE_BT_PREFIX

class BluetoothManager
{
public:
    BluetoothManager();
    ~BluetoothManager();
    static BluetoothManager* NewL();

    void ConstructL();

    bool SetCurrentName(char* a_pName, bool a_bPreventSave = false);
    const THostName GetCurrentName();

    bool Connect();
    void Disconnect(int a_DeviceID = -1, bool a_Permanently = true);
    bool IsBluetoothEnabled();
    bool IsClient();
    bool IsHost();
    void RegisterCallback(INetworkCallbacks* a_pCallback);
    bool RemoveCallback(INetworkCallbacks* a_pCallback);
};

#endif /* BLUETOOTHMANAGER_H */
