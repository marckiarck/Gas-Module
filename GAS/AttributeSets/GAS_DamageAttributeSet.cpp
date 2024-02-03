// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/GAS_DamageAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include <Net/UnrealNetwork.h>

void UGAS_DamageAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

}

void UGAS_DamageAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

}

void UGAS_DamageAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_DamageAttributeSet, damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_DamageAttributeSet, criticalChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_DamageAttributeSet, criticalDamage, COND_None, REPNOTIFY_Always);
}
