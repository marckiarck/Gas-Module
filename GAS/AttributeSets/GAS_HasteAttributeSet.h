// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/GAS_Macros.h"
#include "GAS_HasteAttributeSet.generated.h"


UCLASS()
class GAS_API UGAS_HasteAttributeSet : public UAttributeSet
{

	GENERATED_BODY()

private:
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData maxHaste = 100000.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData minHaste = 0.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData baseHaste = 0.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData hasteCooldown;

public:
	ATTRIBUTE_ACCESSORS(UGAS_HasteAttributeSet, maxHaste)
	ATTRIBUTE_ACCESSORS(UGAS_HasteAttributeSet, minHaste)
	ATTRIBUTE_ACCESSORS(UGAS_HasteAttributeSet, baseHaste)
	ATTRIBUTE_ACCESSORS(UGAS_HasteAttributeSet, hasteCooldown)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	REPLICATE_ATTRIBUTE(UGAS_HasteAttributeSet, maxHaste);
	REPLICATE_ATTRIBUTE(UGAS_HasteAttributeSet, minHaste);
	REPLICATE_ATTRIBUTE(UGAS_HasteAttributeSet, baseHaste);
	REPLICATE_ATTRIBUTE(UGAS_HasteAttributeSet, hasteCooldown);
};
