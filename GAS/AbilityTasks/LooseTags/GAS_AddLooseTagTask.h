#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GAS_AddLooseTagTask.generated.h"


UCLASS()
class GAS_API UGAS_AddLooseTagTask : public UAbilityTask
{
	GENERATED_BODY()
	
private:
	FGameplayTagContainer addedTags;

	UPROPERTY(Transient)
		class UAbilitySystemComponent* abilitySystem;

	UPROPERTY()
		bool destroyAtEnd = false;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UGAS_AddLooseTagTask* AddLooseTags(UGameplayAbility* OwningAbility, FGameplayTagContainer looseTags, UAbilitySystemComponent* targetAbilitySystem, bool _destroyAtEnd = false);
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
};