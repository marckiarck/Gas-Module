// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GAS_DelegateTickTask.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTickDelegate, float, elapsedTime, float, DeltaTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartDelegateTickTask);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndDelegateTickTask);

UCLASS()
class GAS_API UGAS_DelegateTickTask : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UGAS_DelegateTickTask();

private:
	float delegateDuration;
	float elapsedDelegateTime;
	float delegateCallFrecuency;
	float delegateFrecuencyElapsed;

	UPROPERTY(BlueprintAssignable)
		FTickDelegate tickFunctionality;

	UPROPERTY(BlueprintAssignable)
		FStartDelegateTickTask onStart;

	UPROPERTY(BlueprintAssignable)
		FEndDelegateTickTask onEnd;

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UGAS_DelegateTickTask* DelegateTickTask(UGameplayAbility* OwningAbility, float _delegateDuration, float _delegateCallFrecuency = 0.f /*@pamam _delegateCallFrecuency: time passed beetween delegateFunctionality execution*/);

private:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
};
