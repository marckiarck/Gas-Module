
#include "GAS/Notifies/GAS_AddTagAnimNotifyState.h"
#include "GameplayEffect.h"
#include <GameplayEffectComponents/TargetTagsGameplayEffectComponent.h>

UGAS_NotifyAddTagGameplayEffect::UGAS_NotifyAddTagGameplayEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	
}

void UGAS_NotifyAddTagGameplayEffect::SetTagAdded(FGameplayTag notifiedTag)
{
	FInheritedTagContainer grantedTagsContainer;
	grantedTagsContainer.Added = FGameplayTagContainer(notifiedTag);
	UTargetTagsGameplayEffectComponent& tagAddComponent = FindOrAddComponent<UTargetTagsGameplayEffectComponent>();
	tagAddComponent.SetAndApplyTargetTagChanges(grantedTagsContainer);
}

UGAS_AddTagAnimNotifyState::UGAS_AddTagAnimNotifyState()
{

}

void UGAS_AddTagAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	AddTag(MeshComp);
}

void UGAS_AddTagAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	RemoveTag(MeshComp);
}

bool UGAS_AddTagAnimNotifyState::ShouldFireInEditor()
{
	return false;
}

void UGAS_AddTagAnimNotifyState::AddTag(USkeletalMeshComponent* MeshComp)
{
	UWorld* affectedWorld = MeshComp->GetWorld();
	if (affectedWorld && UGameplayStatics::GetGameMode(affectedWorld))
	{
		AActor* meshOwner = MeshComp->GetOwner();
		if (meshOwner)
		{
			if (IAbilitySystemInterface* abilitySytemInterface = Cast<IAbilitySystemInterface>(meshOwner))
			{
				abilitySystemComponent = Cast<UAbilitySystemComponent>(abilitySytemInterface->GetAbilitySystemComponent());

				if (abilitySystemComponent) 
				{
					UGameplayEffect* tagAddedGameplayEffect = CreateAddTagGameplayEffect();

					FGameplayEffectContextHandle tagAddedGameplayEffectHandle;
					activeTagAddedHandle = abilitySystemComponent->ApplyGameplayEffectToSelf(tagAddedGameplayEffect, 0.f, tagAddedGameplayEffectHandle);
				}
			}
		}
	}
}

void UGAS_AddTagAnimNotifyState::RemoveTag(USkeletalMeshComponent* MeshComp)
{
	UWorld* affectedWorld = MeshComp->GetWorld();
	if (affectedWorld && UGameplayStatics::GetGameMode(affectedWorld))
	{
		AActor* meshOwner = MeshComp->GetOwner();
		if (meshOwner && abilitySystemComponent)
		{
			abilitySystemComponent->RemoveActiveGameplayEffect(activeTagAddedHandle);
		}
	}
}

UGameplayEffect* UGAS_AddTagAnimNotifyState::CreateAddTagGameplayEffect()
{
	UGAS_NotifyAddTagGameplayEffect* tagAddedGameplayEffect = NewObject<UGAS_NotifyAddTagGameplayEffect>();
	tagAddedGameplayEffect->SetTagAdded(notifiedTag);

	return tagAddedGameplayEffect;
}

