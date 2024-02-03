// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/GAS_LifeStealAttributeSet.h"
#include <Net/UnrealNetwork.h>

void UGAS_LifeStealAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute.GetUProperty() == FindFieldChecked<FProperty>(UGAS_LifeStealAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UGAS_LifeStealAttributeSet, lifeStealChance)))
	{
		NewValue = FMath::Clamp(NewValue, minLifeSteal.GetCurrentValue(), maxLifeSteal.GetCurrentValue());
	}
}

void UGAS_LifeStealAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_LifeStealAttributeSet, maxLifeSteal, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_LifeStealAttributeSet, minLifeSteal, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_LifeStealAttributeSet, baseLifeSteal, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_LifeStealAttributeSet, lifeStealChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_LifeStealAttributeSet, lifeStealHealing, COND_None, REPNOTIFY_Always);
}