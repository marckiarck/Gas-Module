// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_GAMEPLAY_DEBUGGER

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"


class GAS_API FGAS_PlayerAttriutesDebugCategory : public FGameplayDebuggerCategory
{
	
public:
	FGAS_PlayerAttriutesDebugCategory();

public:


protected:

private:


public:
	void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();


};

#endif // WITH_GAMEPLAY_DEBUGGER