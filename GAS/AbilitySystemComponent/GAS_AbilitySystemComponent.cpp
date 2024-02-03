#include "GAS/AbilitySystemComponent/GAS_AbilitySystemComponent.h"

// Called when the game starts
void UGAS_AbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

const FString UGAS_AbilitySystemComponent::GetAttributeSetKey(TSubclassOf<UAttributeSet> attributeSetClass)
{
	return attributeSetClass->GetName();
}

void UGAS_AbilitySystemComponent::InitializeAbilitySystem()
{
	for (TSubclassOf<UGameplayAbility> ability : addedAbilities)
	{
		if (ability)
		{
			GiveAbility(FGameplayAbilitySpec(ability.GetDefaultObject(), 1, 0));
		}
	}

	for (TSubclassOf<UAttributeSet> attributeClassIt : addedAtributeSets)
	{
		if (attributeClassIt)
		{
			const FString attributesSetHash = GetAttributeSetKey(attributeClassIt);
			if (attributesMap.Contains(attributesSetHash) == false)
			{
				const UAttributeSet* instancedAttributes = NewObject<UAttributeSet>(attributeClassIt);
				instancedAttributes = InitStats(attributeClassIt, attributtesDatatable);

				attributesMap.Add(attributesSetHash, instancedAttributes);
			}
			else
			{
				InitStats(attributeClassIt, attributtesDatatable);
			}
		}
	}
}
