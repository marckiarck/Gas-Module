// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAS.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
#include "GAS/DebugCategories/GAS_PlayerAttriutesDebugCategory.h"

#if WITH_GAMEPLAY_DEBUGGER

#include "GameplayDebugger.h"

#endif // WITH_GAMEPLAY_DEBUGGER

IMPLEMENT_GAME_MODULE(FGASModule, GAS);

DEFINE_LOG_CATEGORY(GAS)

#define LOCTEXT_NAMESPACE "GAS"

void FGASModule::StartupModule()
{
#if WITH_GAMEPLAY_DEBUGGER
	IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();

	GameplayDebuggerModule.RegisterCategory(TEXT("PlayerAttributes"), IGameplayDebugger::FOnGetCategory::CreateStatic(&FGAS_PlayerAttriutesDebugCategory::MakeInstance),
		EGameplayDebuggerCategoryState::EnabledInGameAndSimulate);
	GameplayDebuggerModule.NotifyCategoriesChanged();
#endif
}

void FGASModule::ShutdownModule()
{
#if WITH_GAMEPLAY_DEBUGGER
	IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
	GameplayDebuggerModule.UnregisterCategory(TEXT("PlayerAttributes"));
#endif
}

#undef LOCTEXT_NAMESPACE