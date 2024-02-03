#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GAS_RemoveLooseTagTask.generated.h"


UCLASS()
class GAS_API UGAS_RemoveLooseTagTask : public UAbilityTask
{
	GENERATED_BODY()

private:
	FGameplayTagContainer removeTags;

	UPROPERTY(Transient)
	class UAbilitySystemComponent* abilitySystem;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UGAS_RemoveLooseTagTask* RemoveLooseTags(UGameplayAbility* OwningAbility, FGameplayTagContainer looseTags, UAbilitySystemComponent* affectedAbilitySystem);
	virtual void Activate() override;
};