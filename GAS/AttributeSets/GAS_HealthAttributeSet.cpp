// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/GAS_HealthAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/GAS_TagDefinitions.h"
#include <Net/UnrealNetwork.h>


void UGAS_HealthAttributeSet::InitFromMetaDataTable(const UDataTable* DataTable)
{
	Super::InitFromMetaDataTable(DataTable);
	
	zeroHealthAbilityLaunched = false;
}


void UGAS_HealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute.GetUProperty() == FindFieldChecked<FProperty>(UGAS_HealthAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UGAS_HealthAttributeSet, health)))
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, maxHealth.GetCurrentValue());
	}

}

void UGAS_HealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	PreAttributeChange(Attribute, NewValue);

	UAbilitySystemComponent* owningAbilitySystem = GetOwningAbilitySystemComponent();
	if (NewValue == 0.f && owningAbilitySystem)
	{
		owningAbilitySystem->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(ZERO_HEALTH_TAG));
		LaunchZeroHealthAbility();
	}
	else if (owningAbilitySystem)
	{
		owningAbilitySystem->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(ZERO_HEALTH_TAG));
		zeroHealthAbilityLaunched = false;
	}
}

void UGAS_HealthAttributeSet::LaunchZeroHealthAbility()
{
	if (zeroHealthAbilityLaunched == false)
	{
		FGameplayTag abilityTag = FGameplayTag::RequestGameplayTag(ZERO_HEALTH_ABILITY_TAG, false);

		FGameplayEventData DataEvent;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningActor(), abilityTag, DataEvent);

		zeroHealthAbilityLaunched = true;
	}
}

void UGAS_HealthAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_HealthAttributeSet, maxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_HealthAttributeSet, health, COND_None, REPNOTIFY_Always);
}

