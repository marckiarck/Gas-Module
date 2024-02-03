// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/GAS_HasteAttributeSet.h"
#include <Net/UnrealNetwork.h>

void UGAS_HasteAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute.GetUProperty() == FindFieldChecked<FProperty>(UGAS_HasteAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UGAS_HasteAttributeSet, hasteCooldown)))
	{
		NewValue = FMath::Clamp(NewValue, minHaste.GetCurrentValue(), maxHaste.GetCurrentValue());
	}
}

void UGAS_HasteAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_HasteAttributeSet, maxHaste, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_HasteAttributeSet, minHaste, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_HasteAttributeSet, baseHaste, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_HasteAttributeSet, hasteCooldown, COND_None, REPNOTIFY_Always);
}