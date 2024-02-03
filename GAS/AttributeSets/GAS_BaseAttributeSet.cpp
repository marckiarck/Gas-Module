// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/GAS_BaseAttributeSet.h"
#include <Net/UnrealNetwork.h>

void UGAS_BaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute.GetUProperty() == FindFieldChecked<FProperty>(UGAS_BaseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UGAS_BaseAttributeSet, currentValue)))
	{
		NewValue = FMath::Clamp(NewValue, minValue.GetCurrentValue(), maxValue.GetCurrentValue());
	}
}

void UGAS_BaseAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_BaseAttributeSet, maxValue, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_BaseAttributeSet, minValue, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_BaseAttributeSet, baseValue, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_BaseAttributeSet, currentValue, COND_None, REPNOTIFY_Always);
}