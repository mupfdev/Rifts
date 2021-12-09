#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "Main/ActorEntity.h"
#include "Network/Message.h"
#include "Network/MessageBase.h"
#include "Network/NetworkGameTypes.h"

struct MessageQueueEntry
{
    int   m_iMessageSize;
    byte* m_pMessageData;
};

typedef List<MessageQueueEntry> MessageQueue;

class MessageManager
{
public:
    MessageManager();
    ~MessageManager();
    static MessageManager* NewL();
    static MessageBase*    CopyMessage(void* a_pRaw, int a_Len);

    void ConstructL();
    void Reset();

    MessageQueue& GetMessageQueue();

    bool     CheckDefenderProp(uint32 a_FileID);
    String   GameName();
    int      GetAveragePlayerLevel();
    int64_t  GetBattleID();
    int      GetDeviceID();
    const int GetGameType();
    int      GetRandomSeedForTurn(int a_Turn, int a_Action);
    bool     IsArenaActive();
    bool     IsBluetoothActive();
    bool     IsClient();
    bool     IsDefenderProp(uint32 a_FileID);
    bool     IsHost();
    bool     IsNetworkActive();
    bool     IsRemoteEntity(ActorEntity* a_pEntity);
    int      MaxCharacters();
    int      MaxPlayers();
    int      MaxPointsToWin();
    int      MaxRounds();
    int      MaxTeams();
    void     QueueMessage(MessageBase* a_pMessage, int a_MessageSize);
    bool     ReadData(ReadStream* /*a_pStream*/);
    void     SendEndTurnMessage(int iFacingDir = -1, int iDefend = 0, const String& a_Message = "", const String& a_Title = "");
    void     SendMessage(MessageBase* a_pMessage, int a_MessageSize, int a_DeviceID = -1 );
    void     SendMessageFlag(eMESSAGE_FLAG a_Flag, bool a_BroadcastFlag);
    void     SendSaveGameMessage();
    void     SendQuitGameMessage();
    bool     WriteData(IWriteStream* /*a_pStream*/);

    int m_CurrentSaveSlot;

private:
    int          m_InitialRandomSeed;
    MessageQueue m_MessageQueue;
};

#endif // __MESSAGEMANAGER_H__
