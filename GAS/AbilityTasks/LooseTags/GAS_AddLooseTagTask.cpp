#include "GAS/AbilityTasks/LooseTags/GAS_AddLooseTagTask.h"
#include <AbilitySystemInterface.h>
#include <AbilitySystemComponent.h>

UGAS_AddLooseTagTask* UGAS_AddLooseTagTask::AddLooseTags(UGameplayAbility* OwningAbility, FGameplayTagContainer looseTags, UAbilitySystemComponent* affectedAbilitySystem, bool _destroyAtEnd/* = false*/)
{
    UGAS_AddLooseTagTask* returnedTask = NewAbilityTask<UGAS_AddLooseTagTask>(OwningAbility);
    returnedTask->addedTags = looseTags;
    returnedTask->abilitySystem = affectedAbilitySystem;
    returnedTask->destroyAtEnd = _destroyAtEnd;

    return returnedTask;
}

void UGAS_AddLooseTagTask::Activate()
{

    if (abilitySystem == nullptr)
    {
        abilitySystem = Cast<UAbilitySystemComponent>(Cast<IAbilitySystemInterface>(GetAvatarActor())->GetAbilitySystemComponent());
    }

    abilitySystem->AddLooseGameplayTags(addedTags);
}

void UGAS_AddLooseTagTask::OnDestroy(bool bInOwnerFinished)
{

    if (destroyAtEnd)
    {
        abilitySystem->RemoveLooseGameplayTags(addedTags);
    }

    Super::OnDestroy(bInOwnerFinished);

}