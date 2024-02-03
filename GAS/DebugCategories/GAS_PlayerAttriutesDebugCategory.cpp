// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_GAMEPLAY_DEBUGGER

#include "GAS/DebugCategories/GAS_PlayerAttriutesDebugCategory.h"


FGAS_PlayerAttriutesDebugCategory::FGAS_PlayerAttriutesDebugCategory()
{
	bShowOnlyWithDebugActor = false;
}

void FGAS_PlayerAttriutesDebugCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	
	
}

void FGAS_PlayerAttriutesDebugCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	CanvasContext.Printf(TEXT("Message debug"));
}

TSharedRef<FGameplayDebuggerCategory> FGAS_PlayerAttriutesDebugCategory::MakeInstance()
{
	return MakeShareable(new FGAS_PlayerAttriutesDebugCategory());
}

#endif // WITH_GAMEPLAY_DEBUGGER