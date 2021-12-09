#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "Main/ActorEntity.h"
#include "Network/Message.h"
#include "Network/MessageBase.h"

class MessageManager
{
public:
    MessageManager();
    ~MessageManager();
    static MessageManager* NewL();
    static MessageBase*    CopyMessage(void* a_pRaw, int a_Len);

    void ConstructL();
    void Reset();

    bool CheckDefenderProp(uint32 a_FileID);
    int  GetDeviceID();
    int  GetRandomSeedForTurn(int a_Turn, int a_Action);
    bool IsArenaActive();
    bool IsBluetoothActive();
    bool IsClient();
    bool IsDefenderProp(uint32 a_FileID);
    bool IsHost();
    bool IsNetworkActive();
    bool IsRemoteEntity(ActorEntity* a_pEntity);
    void QueueMessage(MessageBase* a_pMessage, int a_MessageSize);
    bool ReadData(ReadStream* /*a_pStream*/);
    void SendEndTurnMessage(int iFacingDir = -1, int iDefend = 0, const String& a_Message = "", const String& a_Title = "");
    void SendMessage(MessageBase* a_pMessage, int a_MessageSize, int a_DeviceID = -1 );
    void SendMessageFlag(eMESSAGE_FLAG a_Flag, bool a_BroadcastFlag);
    void SendQuitGameMessage();

private:
    int m_InitialRandomSeed;
};

#endif // __MESSAGEMANAGER_H__
