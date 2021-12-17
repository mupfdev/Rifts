cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/nokia-ngage-toolchain.cmake)

project(6r49 CXX)

set(NGAGE_DRIVE_LETTER          "E")

# Use CMake or Visual Studio to enable these settings.
option(INSTALL_APP              "Install app on MMC"         OFF)

option(ENABLE_E3_DEMO           "Enable E3 Demo"             OFF)
option(ENABLE_VIBRATION         "Enable Vibration (QD Only)" OFF) # Not yet implemented, but it works!
option(SKIPPABLE_CUTSCENES      "Skippable Cutscenes"        OFF)
option(SKIPPABLE_SPLASH_SCREENS "Skippable Splash Screens"   OFF)
option(SKIP_SPLASH_SCREENS      "Skip Splash Screens"        OFF)
option(UNLOCK_CONCEPT_ART       "Unlock Concept Art"         OFF)
option(UNLOCK_WALLPAPER         "Unlock Wallpaper"           OFF)
option(USE_BLUETOOTH            "Enable Bluetooth"           OFF) # Not supported!

# The line must be drawn here! This far, no further!
set(SRC_ROOT  ${CMAKE_SOURCE_DIR}/src)
set(RIFTS_SRC ${RIFTS_DIR}/Code/src)

set(UID1 0x10000079) # KDynamicLibraryUidValue, e32uid.h
set(UID2 0x100039ce) # KAppUidValue16, apadef.h
set(UID3 0x101FD3F2) # Rifts UID

set(GCC_COMN_DEFS -D__SYMBIAN32__ -D__GCC32__ -D__EPOC32__ -D__MARM__ -D__MARM_ARMI__ -D__DLL__)
set(GCC_MODE_DEFS -DNDEBUG -D_UNICODE)
set(GCC_USER_DEFS -DUID1=${UID1} -DUID2=${UID2} -DUID3=${UID3})
set(GCC_DEFS      ${GCC_COMN_DEFS} ${GCC_MODE_DEFS} ${GCC_USER_DEFS})

if(ENABLE_E3_DEMO)
    add_definitions(-DENABLE_E3_DEMO=1)
endif()

if(ENABLE_VIBRATION)
    add_definitions(-DENABLE_VIBRATION=1)
    set(vibractrl_libs
        "${CMAKE_SOURCE_DIR}/lib/armi/urel/vibractrl.lib")
else()
    set(vibractrl_libs "")
endif()

if(SKIPPABLE_CUTSCENES)
    add_definitions(-DSKIPPABLE_CUTSCENES=1)
endif()

if(SKIPPABLE_SPLASH_SCREENS)
    add_definitions(-DSKIPPABLE_SPLASH_SCREENS=1)
endif()

if(SKIP_SPLASH_SCREENS)
    add_definitions(-DSKIP_SPLASH_SCREENS=1)
endif()

if(UNLOCK_CONCEPT_ART)
    add_definitions(-DUNLOCK_CONCEPT_ART=1)
endif()

if(UNLOCK_WALLPAPER)
    add_definitions(-DUNLOCK_WALLPAPER=1)
endif()

if(USE_BLUETOOTH)
    add_definitions(-DUSE_BLUETOOTH=1)
    set(bluetooth_sources
        "${RIFTS_SRC}/Game/Cores/BTGameMenuCore.cpp"
        "${RIFTS_SRC}/Game/Cores/BTHostMenuCore.cpp"
        "${RIFTS_SRC}/Game/Cores/BluetoothConnectionCore.cpp"
        "${RIFTS_SRC}/Game/Cores/BluetoothCore.cpp"
        "${RIFTS_SRC}/Game/Cores/BluetoothGameCore.cpp"
        "${RIFTS_SRC}/Network/BluetoothPowerSwitch.cpp")
else()
    set(bluetooth_sources "")
endif()

set(6r49_libs
    "${EPOC_LIB}/edllstub.lib"
    "${EPOC_LIB}/egcc.lib"
    "${EPOC_LIB}/ws32.lib"
    "${RIFTS_DIR}/Prototype/NokiaRasterizer/App32/LIB/UREL/NRENDERER.LIB"
    "${EPOC_LIB}/bitgdi.lib"
    "${EPOC_LIB}/euser.lib"
    "${EPOC_LIB}/apparc.lib"
    "${EPOC_LIB}/cone.lib"
    "${EPOC_LIB}/eikcore.lib"
    "${EPOC_LIB}/eikcoctl.lib"
    "${EPOC_LIB}/avkon.lib"
    "${EPOC_LIB}/fbscli.lib"
    "${EPOC_LIB}/efsrv.lib"
    "${EPOC_LIB}/estlib.lib"
    "${EPOC_LIB}/mediaclientaudiostream.lib"
    "${EPOC_LIB}/hal.lib"
    #"${EPOC_LIB}/bluetooth.lib"
    #"${EPOC_LIB}/esock.lib"
    "${EPOC_LIB}/flogger.lib"
    "${EPOC_LIB}/sysagt.lib"
    "${EPOC_LIB}/msgs.lib")

set(6r49_sources
    "${RIFTS_SRC}/common.cpp"
    "${RIFTS_SRC}/./BuildVersion.cpp"
    "${RIFTS_SRC}/./common.cpp"
    "${RIFTS_SRC}/./memory.cpp"
    "${RIFTS_SRC}/Ai/AIHelperClasses.cpp"
    "${RIFTS_SRC}/Ai/AIHelpers.cpp"
    "${RIFTS_SRC}/Ai/AIPath.cpp"
    "${RIFTS_SRC}/Ai/CrazyAI.cpp"
    "${RIFTS_SRC}/Ai/FearAI.cpp"
    "${RIFTS_SRC}/Ai/IAIModule.cpp"
    "${RIFTS_SRC}/Ai/IPlayableAI.cpp"
    "${RIFTS_SRC}/Ai/NPCAI.cpp"
    "${RIFTS_SRC}/Ai/NPCCombatAI.cpp"
    "${RIFTS_SRC}/Ai/NPCCombatAITargeter.cpp"
    "${RIFTS_SRC}/Ai/PCAI.cpp"
    "${RIFTS_SRC}/Ai/PCCombatAI.cpp"
    "${RIFTS_SRC}/Ai/PCCombatAISelectionState.cpp"
    "${RIFTS_SRC}/Ai/PropAI.cpp"
    "${RIFTS_SRC}/Ai/RemoteAI.cpp"
    "${RIFTS_SRC}/Ai/RemoteCombatAI.cpp"
    "${RIFTS_SRC}/Ai/ScriptCombatAI.cpp"
    "${RIFTS_SRC}/Ai/WallAI.cpp"
    "${RIFTS_SRC}/Data/DBObjects.cpp"
    "${RIFTS_SRC}/Data/DataID.cpp"
    "${RIFTS_SRC}/Data/DataList.cpp"
    "${RIFTS_SRC}/Data/DatabaseManager.cpp"
    "${RIFTS_SRC}/Data/ElementDataResource.cpp"
    "${RIFTS_SRC}/Data/EntityDataNPC.cpp"
    "${RIFTS_SRC}/Data/EntityDataPC.cpp"
    "${RIFTS_SRC}/Data/EntityDataProp.cpp"
    "${RIFTS_SRC}/Data/EntityDataResource.cpp"
    "${RIFTS_SRC}/Data/IDataObject.cpp"
    "${RIFTS_SRC}/Data/IElementData.cpp"
    "${RIFTS_SRC}/Data/IElementDataItem.cpp"
    "${RIFTS_SRC}/Data/IEntityData.cpp"
    "${RIFTS_SRC}/Data/IEntityDataActor.cpp"
    "${RIFTS_SRC}/Data/ImportParty.cpp"
    "${RIFTS_SRC}/Data/InfoChunk.cpp"
    "${RIFTS_SRC}/Data/InfoGroup.cpp"
    "${RIFTS_SRC}/Data/LootManager.cpp"
    "${RIFTS_SRC}/Data/MapData.cpp"
    "${RIFTS_SRC}/Data/MapDataResource.cpp"
    "${RIFTS_SRC}/Data/StatTracker.cpp"
    "${RIFTS_SRC}/Data/StoreDataResource.cpp"
    "${RIFTS_SRC}/Entities/BossEntity.cpp"
    "${RIFTS_SRC}/Entities/CameraEntity.cpp"
    "${RIFTS_SRC}/Fonts/FontDescriptor.cpp"
    "${RIFTS_SRC}/Fonts/SpriteUnitString.cpp"
    "${RIFTS_SRC}/Fonts/SpriteUnitString2.cpp"
    "${RIFTS_SRC}/Fonts/TextFillBox.cpp"
    "${RIFTS_SRC}/FrontEnd/2DWidget.cpp"
    "${RIFTS_SRC}/FrontEnd/AttributeModCore.cpp"
    "${RIFTS_SRC}/FrontEnd/ClassSelectionCore.cpp"
    "${RIFTS_SRC}/FrontEnd/DialogueWidget.cpp"
    "${RIFTS_SRC}/FrontEnd/EntityInfoBox.cpp"
    "${RIFTS_SRC}/FrontEnd/FrontEndCore.cpp"
    "${RIFTS_SRC}/FrontEnd/HUDManager.cpp"
    "${RIFTS_SRC}/FrontEnd/ItemMenuWidget.cpp"
    "${RIFTS_SRC}/FrontEnd/MenuWidget.cpp"
    "${RIFTS_SRC}/FrontEnd/NameGenCore.cpp"
    "${RIFTS_SRC}/FrontEnd/SkillSelectionCore.cpp"
    "${RIFTS_SRC}/FrontEnd/SpellSelectionCore.cpp"
    "${RIFTS_SRC}/Game/GameManager.cpp"
    "${RIFTS_SRC}/Game/Actions/AOETileEffectAction.cpp"
    "${RIFTS_SRC}/Game/Actions/Action.cpp"
    "${RIFTS_SRC}/Game/Actions/AirRaidAction.cpp"
    "${RIFTS_SRC}/Game/Actions/AnimationAction.cpp"
    "${RIFTS_SRC}/Game/Actions/CameraAction.cpp"
    "${RIFTS_SRC}/Game/Actions/CharacterAction.cpp"
    "${RIFTS_SRC}/Game/Actions/CharacterTextAction.cpp"
    "${RIFTS_SRC}/Game/Actions/CombatTriggerAction.cpp"
    "${RIFTS_SRC}/Game/Actions/CutsceneAction.cpp"
    "${RIFTS_SRC}/Game/Actions/DeathWordAction.cpp"
    "${RIFTS_SRC}/Game/Actions/DialogueAction.cpp"
    "${RIFTS_SRC}/Game/Actions/EnterDoorAction.cpp"
    "${RIFTS_SRC}/Game/Actions/FaceTileAction.cpp"
    "${RIFTS_SRC}/Game/Actions/FallAction.cpp"
    "${RIFTS_SRC}/Game/Actions/FireQuakeAction.cpp"
    "${RIFTS_SRC}/Game/Actions/FireSpongeAction.cpp"
    "${RIFTS_SRC}/Game/Actions/FlyAction.cpp"
    "${RIFTS_SRC}/Game/Actions/FrontEndAction.cpp"
    "${RIFTS_SRC}/Game/Actions/FullScreenAnimationAction.cpp"
    "${RIFTS_SRC}/Game/Actions/JumpAction.cpp"
    "${RIFTS_SRC}/Game/Actions/JumpDownAction.cpp"
    "${RIFTS_SRC}/Game/Actions/KnockbackAction.cpp"
    "${RIFTS_SRC}/Game/Actions/KnockupAction.cpp"
    "${RIFTS_SRC}/Game/Actions/MeteorStrikeAction.cpp"
    "${RIFTS_SRC}/Game/Actions/MoveAction.cpp"
    "${RIFTS_SRC}/Game/Actions/MoveEntityGraphicsAction.cpp"
    "${RIFTS_SRC}/Game/Actions/ParticleAction.cpp"
    "${RIFTS_SRC}/Game/Actions/PhoenixAction.cpp"
    "${RIFTS_SRC}/Game/Actions/PlagueAction.cpp"
    "${RIFTS_SRC}/Game/Actions/PlayAnimationAction.cpp"
    "${RIFTS_SRC}/Game/Actions/PlayEffectAction.cpp"
    "${RIFTS_SRC}/Game/Actions/PossessAction.cpp"
    "${RIFTS_SRC}/Game/Actions/ProjectileAction.cpp"
    "${RIFTS_SRC}/Game/Actions/ProjectileLaserAction.cpp"
    "${RIFTS_SRC}/Game/Actions/ProjectileTailAction.cpp"
    "${RIFTS_SRC}/Game/Actions/ShakeEntityAction.cpp"
    "${RIFTS_SRC}/Game/Actions/SummonAction.cpp"
    "${RIFTS_SRC}/Game/Actions/TelemechanicAction.cpp"
    "${RIFTS_SRC}/Game/Actions/TidalWaveAction.cpp"
    "${RIFTS_SRC}/Game/Actions/TophetAttackAction.cpp"
    "${RIFTS_SRC}/Game/Actions/TophetKnockbackAction.cpp"
    "${RIFTS_SRC}/Game/Actions/TornadoAction.cpp"
    "${RIFTS_SRC}/Game/Actions/WorldColorAction.cpp"
    "${RIFTS_SRC}/Game/CombatManager/CombatCallbacks.cpp"
    "${RIFTS_SRC}/Game/CombatManager/CombatManager.cpp"
    "${RIFTS_SRC}/Game/CombatManager/CombatManagerDamage.cpp"
    "${RIFTS_SRC}/Game/CombatManager/CombatManagerImpl.cpp"
    "${RIFTS_SRC}/Game/CombatManager/CombatManagerStrings.cpp"
    "${RIFTS_SRC}/Game/CombatManager/ElementHelpers.cpp"
    "${RIFTS_SRC}/Game/CombatManager/ElementReference.cpp"
    "${RIFTS_SRC}/Game/Cores/AbilitiesMenuCore.cpp"
    "${RIFTS_SRC}/Game/Cores/ArenaCharacterSelect.cpp"
    "${RIFTS_SRC}/Game/Cores/ArenaCore.cpp"
    "${RIFTS_SRC}/Game/Cores/ArenaGameCore.cpp"
    "${RIFTS_SRC}/Game/Cores/ArenaGameLoader.cpp"
    "${RIFTS_SRC}/Game/Cores/ArenaGameOptions.cpp"
    "${RIFTS_SRC}/Game/Cores/ArenaGameSearch.cpp"
    "${RIFTS_SRC}/Game/Cores/ArenaGameView.cpp"
    "${RIFTS_SRC}/Game/Cores/ArenaMainMenu.cpp"
    "${RIFTS_SRC}/Game/Cores/ArenaNameGenCore.cpp"
    "${RIFTS_SRC}/Game/Cores/ArenaTurnCore.cpp"
#    "${RIFTS_SRC}/Game/Cores/BTGameMenuCore.cpp"
#    "${RIFTS_SRC}/Game/Cores/BTHostMenuCore.cpp"
#    "${RIFTS_SRC}/Game/Cores/BluetoothConnectionCore.cpp"
#    "${RIFTS_SRC}/Game/Cores/BluetoothCore.cpp"
#    "${RIFTS_SRC}/Game/Cores/BluetoothGameCore.cpp"
    "${RIFTS_SRC}/Game/Cores/CheatEnablerCore.cpp"
    "${RIFTS_SRC}/Game/Cores/ChopShopCore.cpp"
    "${RIFTS_SRC}/Game/Cores/CityMapCore.cpp"
    "${RIFTS_SRC}/Game/Cores/CoreManager.cpp"
    "${RIFTS_SRC}/Game/Cores/CutsceneCore.cpp"
    "${RIFTS_SRC}/Game/Cores/DeleteGameCore.cpp"
    "${RIFTS_SRC}/Game/Cores/EquipmentMenuCore.cpp"
    "${RIFTS_SRC}/Game/Cores/FeaturesCore.cpp"
    "${RIFTS_SRC}/Game/Cores/GameCore.cpp"
    "${RIFTS_SRC}/Game/Cores/GameFileCore.cpp"
    "${RIFTS_SRC}/Game/Cores/ImageBrowserCore.cpp"
    "${RIFTS_SRC}/Game/Cores/InnCore.cpp"
    "${RIFTS_SRC}/Game/Cores/KeyMapMenuCore.cpp"
    "${RIFTS_SRC}/Game/Cores/LimitedPauseMenuCore.cpp"
    "${RIFTS_SRC}/Game/Cores/LoadGameCore.cpp"
    "${RIFTS_SRC}/Game/Cores/MapCore.cpp"
    "${RIFTS_SRC}/Game/Cores/MultiplayerGameCore.cpp"
    "${RIFTS_SRC}/Game/Cores/OptionsMenuCore.cpp"
    "${RIFTS_SRC}/Game/Cores/PartyMenuCore.cpp"
    "${RIFTS_SRC}/Game/Cores/PauseMenuCore.cpp"
    "${RIFTS_SRC}/Game/Cores/PickUpMenuCore.cpp"
    "${RIFTS_SRC}/Game/Cores/QuestMenuCore.cpp"
    "${RIFTS_SRC}/Game/Cores/ReconnectionCore.cpp"
    "${RIFTS_SRC}/Game/Cores/RewardScreenCore.cpp"
    "${RIFTS_SRC}/Game/Cores/SaveGameCore.cpp"
    "${RIFTS_SRC}/Game/Cores/ServerActionCore.cpp"
    "${RIFTS_SRC}/Game/Cores/SettingsMenuCore.cpp"
    "${RIFTS_SRC}/Game/Cores/SinglePlayerGameCore.cpp"
    "${RIFTS_SRC}/Game/Cores/SplashCore.cpp"
    "${RIFTS_SRC}/Game/Cores/StoreCore.cpp"
    "${RIFTS_SRC}/Game/Cores/UnlockablesCore.cpp"
    "${RIFTS_SRC}/Game/PersistentEffects/IPersistentEffect.cpp"
    "${RIFTS_SRC}/Game/PersistentEffects/PersistentControl.cpp"
    "${RIFTS_SRC}/Game/PersistentEffects/PersistentCrazy.cpp"
    "${RIFTS_SRC}/Game/PersistentEffects/PersistentHorror.cpp"
    "${RIFTS_SRC}/Game/PersistentEffects/PersistentStats.cpp"
    "${RIFTS_SRC}/Game/PersistentEffects/PersistentSummon.cpp"
    "${RIFTS_SRC}/Game/PersistentEffects/PersistentTrigger.cpp"
    "${RIFTS_SRC}/Game/Quests/Quest.cpp"
    "${RIFTS_SRC}/Game/Quests/QuestControl.cpp"
    "${RIFTS_SRC}/Game/Quests/Quests.cpp"
    "${RIFTS_SRC}/Game/Sector/DynamicTile.cpp"
    "${RIFTS_SRC}/Game/Sector/DynamicTileStrip.cpp"
    "${RIFTS_SRC}/Game/Sector/LeyLineManager.cpp"
    "${RIFTS_SRC}/Game/Sector/RangeMaker.cpp"
    "${RIFTS_SRC}/Game/Sector/SectorData.cpp"
    "${RIFTS_SRC}/Game/Sector/SectorListResource.cpp"
    "${RIFTS_SRC}/Game/Sector/SectorModule.cpp"
    "${RIFTS_SRC}/Game/Sector/SectorModuleLineOfSight.cpp"
    "${RIFTS_SRC}/Game/Sector/SectorModuleMovement.cpp"
    "${RIFTS_SRC}/Game/Sector/SectorRegion.cpp"
    "${RIFTS_SRC}/Game/Sector/SectorResource.cpp"
    "${RIFTS_SRC}/Game/Sector/AStar/PathFinder.cpp"
    "${RIFTS_SRC}/Game/Sequencer/ActionOpCode.cpp"
    "${RIFTS_SRC}/Game/Sequencer/CreateAction.cpp"
    "${RIFTS_SRC}/Game/Sequencer/DebugLink.cpp"
    "${RIFTS_SRC}/Game/Sequencer/DisAsm.cpp"
    "${RIFTS_SRC}/Game/Sequencer/SequenceFunctions.cpp"
    "${RIFTS_SRC}/Game/Sequencer/SequenceHelpers.cpp"
    "${RIFTS_SRC}/Game/Sequencer/SequenceOpCodes.cpp"
    "${RIFTS_SRC}/Game/Sequencer/SequenceResource.cpp"
    "${RIFTS_SRC}/Game/Sequencer/Sequencer.cpp"
    "${RIFTS_SRC}/Game/Sequencer/SequencerAction.cpp"
    "${RIFTS_SRC}/Game/Triggers/CombatTrigger.cpp"
    "${RIFTS_SRC}/Game/Triggers/StaticTrigger.cpp"
    "${RIFTS_SRC}/Game/Triggers/TriggerScript.cpp"
    "${RIFTS_SRC}/Input/CodeRecognizer.cpp"
    "${RIFTS_SRC}/Input/IInputListener.cpp"
    "${RIFTS_SRC}/Input/InputManager.cpp"
    "${RIFTS_SRC}/Main/ActorEntity.cpp"
    "${RIFTS_SRC}/Main/BBLog.cpp"
    "${RIFTS_SRC}/Main/BBLogCommon.cpp"
    "${RIFTS_SRC}/Main/CombatEntity.cpp"
    "${RIFTS_SRC}/Main/GlobalSettings.cpp"
    "${RIFTS_SRC}/Main/Globals.cpp"
    "${RIFTS_SRC}/Main/HashedStringIndex.cpp"
    "${RIFTS_SRC}/Main/IBaseCore.cpp"
    "${RIFTS_SRC}/Main/IMainObject.cpp"
    "${RIFTS_SRC}/Main/Inventory.cpp"
    "${RIFTS_SRC}/Main/MainElement.cpp"
    "${RIFTS_SRC}/Main/MainEntity.cpp"
    "${RIFTS_SRC}/Main/PartyData.cpp"
    "${RIFTS_SRC}/Main/PropEntity.cpp"
    "${RIFTS_SRC}/Main/StarterCore.cpp"
    "${RIFTS_SRC}/Main/Unlockables.cpp"
    "${RIFTS_SRC}/Math/Basis.cpp"
    "${RIFTS_SRC}/Math/Color.cpp"
    "${RIFTS_SRC}/Math/Direction.cpp"
    "${RIFTS_SRC}/Math/Fixed.cpp"
    "${RIFTS_SRC}/Math/Formula.cpp"
    "${RIFTS_SRC}/Math/LookupTable.cpp"
    "${RIFTS_SRC}/Math/Matrix3.cpp"
    "${RIFTS_SRC}/Math/Orientation.cpp"
    "${RIFTS_SRC}/Math/Quaternion.cpp"
    "${RIFTS_SRC}/Math/Randomizer.cpp"
    "${RIFTS_SRC}/Network/ArenaManager_DEMO.cpp"
    "${RIFTS_SRC}/Network/ArenaManagerArena_DEMO.cpp"
    "${RIFTS_SRC}/Network/ArenaManagerStub.cpp"
    "${RIFTS_SRC}/Network/BluetoothManager.cpp"
#    "${RIFTS_SRC}/Network/BluetoothPowerSwitch.cpp"
    "${RIFTS_SRC}/Network/IServerAction.cpp"
    "${RIFTS_SRC}/Network/Message.cpp"
    "${RIFTS_SRC}/Network/MessageBase.cpp"
    "${RIFTS_SRC}/Network/MessageManager.cpp"
    "${RIFTS_SRC}/Network/SocketAPI.cpp"
    "${RIFTS_SRC}/Network/Actions/AcceptChallengeAction.cpp"
    "${RIFTS_SRC}/Network/Actions/ChallengeStatusAction.cpp"
    "${RIFTS_SRC}/Network/Actions/CreateChallengeAction.cpp"
    "${RIFTS_SRC}/Network/Actions/DownloadCharactersAction.cpp"
    "${RIFTS_SRC}/Network/Actions/DownloadTurnsAction.cpp"
    "${RIFTS_SRC}/Network/Actions/EndGameAction.cpp"
    "${RIFTS_SRC}/Network/Actions/FindChallengeAction.cpp"
    "${RIFTS_SRC}/Network/Actions/GameUpkeepAction.cpp"
    "${RIFTS_SRC}/Network/Actions/NameValidationAction.cpp"
    "${RIFTS_SRC}/Network/Actions/ServerConfigAction.cpp"
    "${RIFTS_SRC}/Network/Actions/UpdateFriendsList.cpp"
    "${RIFTS_SRC}/Network/Actions/UploadCharactersAction.cpp"
    "${RIFTS_SRC}/Network/Actions/UploadTurnsAction.cpp"
    "${RIFTS_SRC}/Raster/3dtypes.cpp"
    "${RIFTS_SRC}/Raster/RenderContext.cpp"
    "${RIFTS_SRC}/Render/3DModelModule.cpp"
    "${RIFTS_SRC}/Render/AnimationModule.cpp"
    "${RIFTS_SRC}/Render/AnimationResource.cpp"
    "${RIFTS_SRC}/Render/AnimationSetResource.cpp"
    "${RIFTS_SRC}/Render/Camera.cpp"
    "${RIFTS_SRC}/Render/CustomModule.cpp"
    "${RIFTS_SRC}/Render/DecalModule.cpp"
    "${RIFTS_SRC}/Render/EmitterRule.cpp"
    "${RIFTS_SRC}/Render/GraphicsModule.cpp"
    "${RIFTS_SRC}/Render/ImageResource.cpp"
    "${RIFTS_SRC}/Render/LineDrawing.cpp"
    "${RIFTS_SRC}/Render/ModelResource.cpp"
    "${RIFTS_SRC}/Render/PaletteFilterContainer.cpp"
    "${RIFTS_SRC}/Render/PaletteResource.cpp"
    "${RIFTS_SRC}/Render/ParticleEmitterModule.cpp"
    "${RIFTS_SRC}/Render/ParticleModule.cpp"
    "${RIFTS_SRC}/Render/ParticleModuleBlitting.cpp"
    "${RIFTS_SRC}/Render/RenderEffects.cpp"
    "${RIFTS_SRC}/Render/RenderManager.cpp"
    "${RIFTS_SRC}/Render/SelectionModule.cpp"
    "${RIFTS_SRC}/Render/TerrainModule.cpp"
    "${RIFTS_SRC}/Render/TerrainResource.cpp"
    "${RIFTS_SRC}/Render/TextureResource.cpp"
    "${RIFTS_SRC}/Resource/IResource.cpp"
    "${RIFTS_SRC}/Resource/ResourceList.cpp"
    "${RIFTS_SRC}/Resource/ResourceManager.cpp"
    "${RIFTS_SRC}/SnapStub/SnapPacket.cpp"
    "${RIFTS_SRC}/Sound/CallMonitor.cpp"
    "${RIFTS_SRC}/Sound/MusicStreamBuffer.cpp"
    "${RIFTS_SRC}/Sound/SoundMonitor.cpp"
    "${RIFTS_SRC}/Sound/SoundWrap.cpp"
    "${RIFTS_SRC}/Sound/audiostreamplayer.cpp"
    "${RIFTS_SRC}/Sound/simplemixer.cpp"
    "${RIFTS_SRC}/System/DFile.cpp"
    "${SRC_DIR}/System/SystemApp.cpp"
    "${RIFTS_SRC}/System/SystemAppUi.cpp"
    "${RIFTS_SRC}/System/SystemAppView.cpp"
    "${RIFTS_SRC}/System/SystemDocument.cpp"
    "${RIFTS_SRC}/System/TKMF.cpp"
    "${RIFTS_SRC}/Utility/BB_String.cpp"
    "${RIFTS_SRC}/Utility/BitVector.cpp"
    "${RIFTS_SRC}/Utility/BlockEncryption.cpp"
    "${RIFTS_SRC}/Utility/DebugRef.cpp"
    "${RIFTS_SRC}/Utility/IWriteStream.cpp"
    "${RIFTS_SRC}/Utility/PerfTimer.cpp"
    "${RIFTS_SRC}/Utility/PulseManager.cpp"
    "${RIFTS_SRC}/Utility/PulseUser.cpp"
    "${RIFTS_SRC}/Utility/RandClass.cpp"
    "${RIFTS_SRC}/Utility/ReadStream.cpp"
    "${RIFTS_SRC}/Utility/ReadStreamFile.cpp"
    "${RIFTS_SRC}/Utility/StateMachine.cpp"
    "${RIFTS_SRC}/Utility/SymbianHelpers.cpp"
    "${RIFTS_SRC}/Utility/Timer.cpp"
    "${RIFTS_SRC}/Utility/WriteStreamFile.cpp"
    "${RIFTS_SRC}/Utility/WriteStreamMemory.cpp"
    "${RIFTS_SRC}/Utility/df_vsprintf.cpp"
    "${RIFTS_SRC}/Utility/zlib/adler32.cpp"
    "${RIFTS_SRC}/Utility/zlib/compress.cpp"
    "${RIFTS_SRC}/Utility/zlib/crc32.cpp"
    "${RIFTS_SRC}/Utility/zlib/deflate.cpp"
    "${RIFTS_SRC}/Utility/zlib/infblock.cpp"
    "${RIFTS_SRC}/Utility/zlib/infcodes.cpp"
    "${RIFTS_SRC}/Utility/zlib/inffast.cpp"
    "${RIFTS_SRC}/Utility/zlib/inflate.cpp"
    "${RIFTS_SRC}/Utility/zlib/inftrees.cpp"
    "${RIFTS_SRC}/Utility/zlib/infutil.cpp"
    "${RIFTS_SRC}/Utility/zlib/trees.cpp"
    "${RIFTS_SRC}/Utility/zlib/uncompr.cpp"
    "${RIFTS_SRC}/Utility/zlib/zutil.cpp")

add_library(${PROJECT_NAME} STATIC ${6r49_sources} ${bluetooth_sources})

if(ENABLE_VIBRATION)
    set(6r49_libs
        "${6r49_libs}"
        "${vibractrl_libs}")
endif()

build_dll(arm_interwork ${PROJECT_NAME} app ${UID1} ${UID2} ${UID3} ${6r49_libs})
if(INSTALL_APP)
    install_file(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_NAME}.app ${NGAGE_DRIVE_LETTER})
    if(ENABLE_VIBRATION)
        install_file(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/lib" "vibractrl.dll" ${NGAGE_DRIVE_LETTER})
    endif()
endif()

target_compile_definitions(
    ${PROJECT_NAME}
    PUBLIC
    ${GCC_DEFS})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${SRC_DIR}
    ${SRC_DIR}/vibractrl
    ${RIFTS_SRC}
    ${RIFTS_SRC}/Main)
