// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/GAS_Macros.h"
#include "GAS_DamageAttributeSet.generated.h"


UCLASS()
class GAS_API UGAS_DamageAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData damage;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData criticalChance;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData criticalDamage;

public:
	ATTRIBUTE_ACCESSORS(UGAS_DamageAttributeSet, damage)
	ATTRIBUTE_ACCESSORS(UGAS_DamageAttributeSet, criticalChance)
	ATTRIBUTE_ACCESSORS(UGAS_DamageAttributeSet, criticalDamage)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	REPLICATE_ATTRIBUTE(UGAS_DamageAttributeSet, damage);
	REPLICATE_ATTRIBUTE(UGAS_DamageAttributeSet, criticalChance);
	REPLICATE_ATTRIBUTE(UGAS_DamageAttributeSet, criticalDamage);

};
