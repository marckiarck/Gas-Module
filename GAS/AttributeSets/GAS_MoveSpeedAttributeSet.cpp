// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/GAS_MoveSpeedAttributeSet.h"
#include <Net/UnrealNetwork.h>

void UGAS_MoveSpeedAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute.GetUProperty() == FindFieldChecked<FProperty>(UGAS_MoveSpeedAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UGAS_MoveSpeedAttributeSet, moveSpeed)))
	{
		NewValue = FMath::Clamp(NewValue, minSpeed.GetCurrentValue(), maxSpeed.GetCurrentValue());
	}
}

void UGAS_MoveSpeedAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_MoveSpeedAttributeSet, maxSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_MoveSpeedAttributeSet, minSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_MoveSpeedAttributeSet, baseSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_MoveSpeedAttributeSet, moveSpeed, COND_None, REPNOTIFY_Always);
}