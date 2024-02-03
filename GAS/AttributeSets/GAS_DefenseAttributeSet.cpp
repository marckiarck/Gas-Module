// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/GAS_DefenseAttributeSet.h"
#include <Net/UnrealNetwork.h>

void UGAS_DefenseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute.GetUProperty() == FindFieldChecked<FProperty>(UGAS_DefenseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UGAS_DefenseAttributeSet, currentDefense)))
	{
		NewValue = FMath::Clamp(NewValue, minDefense.GetCurrentValue(), maxDefense.GetCurrentValue());
	}
}

void UGAS_DefenseAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_DefenseAttributeSet, maxDefense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_DefenseAttributeSet, minDefense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_DefenseAttributeSet, baseDefense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_DefenseAttributeSet, currentDefense, COND_None, REPNOTIFY_Always);
}