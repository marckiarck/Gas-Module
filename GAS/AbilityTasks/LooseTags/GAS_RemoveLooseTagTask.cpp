#include "GAS/AbilityTasks/LooseTags/GAS_RemoveLooseTagTask.h"
#include <AbilitySystemInterface.h>
#include <AbilitySystemComponent.h>

UGAS_RemoveLooseTagTask* UGAS_RemoveLooseTagTask::RemoveLooseTags(UGameplayAbility* OwningAbility, FGameplayTagContainer looseTags, UAbilitySystemComponent* affectedAbilitySystem)
{
	UGAS_RemoveLooseTagTask* returnedTask = NewAbilityTask<UGAS_RemoveLooseTagTask>(OwningAbility);
	returnedTask->removeTags = looseTags;
	returnedTask->abilitySystem = affectedAbilitySystem;

	return returnedTask;
}

void UGAS_RemoveLooseTagTask::Activate()
{
	if (abilitySystem == nullptr)
	{
		abilitySystem = Cast<UAbilitySystemComponent>(Cast<IAbilitySystemInterface>(GetAvatarActor())->GetAbilitySystemComponent());
	}

	abilitySystem->RemoveLooseGameplayTags(removeTags);
}