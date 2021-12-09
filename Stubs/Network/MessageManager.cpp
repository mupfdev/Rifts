#include "common.h"
#include "Math/Randomizer.h"
#include "MessageManager.h"
#include "RiftsResourceID.h"

MessageManager::MessageManager()
{
    Reset();
}

MessageManager* MessageManager::NewL()
{
    MessageManager* pManager = BB_NEW(MessageManager);
    CleanupStack::PushL(pManager);
    pManager->ConstructL();
    CleanupStack::Pop();
    return pManager;
}

void MessageManager::ConstructL()
{
    Reset();
}

void MessageManager::Reset(void)
{
    TTime currentTime;
    currentTime.UniversalTime();
    m_InitialRandomSeed = currentTime.Int64().Low();
}

bool MessageManager::CheckDefenderProp(uint32 a_FileID)
{
    return true;
}

int MessageManager::GetDeviceID()
{
    return -1;
}

int MessageManager::GetRandomSeedForTurn(int a_Turn, int a_Action)
{
    GameRandSeed(a_Turn, "MM-GRS1");
    GameRandSeed(m_InitialRandomSeed + GameRand("MM-GRS2"), "MM-GRS3");

    for (int i = 0; i < a_Action; ++i)
    {
        int iMin = GameRand(5, 10, "MM-GRS4");
        for (int j = 0; j < iMin; ++j, GameRand("MM-GRS5"));
        GameRandSeed(GameRand("MM-GRS6"), "MM-GRS7");
    }

    return GameRand("MM-GRS8");
}

bool MessageManager::IsArenaActive()
{
    return false;
}

bool MessageManager::IsBluetoothActive()
{
    return false;
}

bool MessageManager::IsClient()
{
    return false;
}

bool MessageManager::IsDefenderProp(uint32 a_FileID)
{
    switch(a_FileID)
    {
        case ENTY_PROP_CombatPyramid:
        case ENTY_PROP_Pyramid:
        case ENTY_PROP_PyramidTolkeen:
            return true;
        default:
            return false;
    }
}

bool MessageManager::IsHost()
{
    return true;
}

bool MessageManager::IsNetworkActive()
{
    return false;
}

bool MessageManager::IsRemoteEntity(ActorEntity* a_pEntity)
{
    return false;
}

void MessageManager::QueueMessage(MessageBase* a_pMessage, int a_MessageSize)
{
    (void)a_pMessage;
    (void)a_MessageSize;
    return;
}

bool MessageManager::ReadData(ReadStream* /*a_pStream*/)
{
    return false;
}

void MessageManager::SendEndTurnMessage(int iFacingDir = -1, int iDefend = 0, const String& a_Message = "", const String& a_Title = "")
{
    (void)iFacingDir;
    (void)iDefend;
    (void)a_Message;
    (void)a_Title;
    return;
}

void MessageManager::SendMessage(MessageBase* a_pMessage, int a_MessageSize, int a_DeviceID = -1 )
{
    (void)a_pMessage;
    (void)a_MessageSize;
    (void)a_DeviceID;
    return;
}

void MessageManager::SendMessageFlag(eMESSAGE_FLAG a_Flag, bool a_BroadcastFlag)
{
    (void)a_Flag;
    (void)a_BroadcastFlag;
    return;
}

void MessageManager::SendQuitGameMessage()
{
    return;
}
