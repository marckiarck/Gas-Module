

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GAS/AbilitySystemComponent/GAS_AbilitySystemComponent.h"
#include "GAS_PlayerState.generated.h"


UCLASS()
class GAS_API AGAS_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AGAS_PlayerState();
	
public:
	UPROPERTY(EditAnywhere)
		UGAS_AbilitySystemComponent* playerAbilitySystem = nullptr;
};
