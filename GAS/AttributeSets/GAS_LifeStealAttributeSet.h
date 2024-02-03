// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/GAS_Macros.h"
#include "GAS_LifeStealAttributeSet.generated.h"


UCLASS()
class GAS_API UGAS_LifeStealAttributeSet : public UAttributeSet
{

	GENERATED_BODY()

private:
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData maxLifeSteal = 1.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData minLifeSteal = 0.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData baseLifeSteal = 0.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData lifeStealChance = 0.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData lifeStealHealing = 0.f;

public:
	ATTRIBUTE_ACCESSORS(UGAS_LifeStealAttributeSet, maxLifeSteal)
	ATTRIBUTE_ACCESSORS(UGAS_LifeStealAttributeSet, minLifeSteal)
	ATTRIBUTE_ACCESSORS(UGAS_LifeStealAttributeSet, baseLifeSteal)
	ATTRIBUTE_ACCESSORS(UGAS_LifeStealAttributeSet, lifeStealChance)
	ATTRIBUTE_ACCESSORS(UGAS_LifeStealAttributeSet, lifeStealHealing)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	REPLICATE_ATTRIBUTE(UGAS_LifeStealAttributeSet, maxLifeSteal);
	REPLICATE_ATTRIBUTE(UGAS_LifeStealAttributeSet, minLifeSteal);
	REPLICATE_ATTRIBUTE(UGAS_LifeStealAttributeSet, baseLifeSteal);
	REPLICATE_ATTRIBUTE(UGAS_LifeStealAttributeSet, lifeStealChance);
	REPLICATE_ATTRIBUTE(UGAS_LifeStealAttributeSet, lifeStealHealing);
};
