// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/GAS_Macros.h"
#include "GAS_BaseAttributeSet.generated.h"


UCLASS()
class GAS_API UGAS_BaseAttributeSet : public UAttributeSet
{

	GENERATED_BODY()

private:
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData maxValue = 100000.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData minValue = 0.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData baseValue = 0.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData currentValue = 0.f;

public:
	ATTRIBUTE_ACCESSORS(UGAS_BaseAttributeSet, maxValue)
	ATTRIBUTE_ACCESSORS(UGAS_BaseAttributeSet, minValue)
	ATTRIBUTE_ACCESSORS(UGAS_BaseAttributeSet, baseValue)
	ATTRIBUTE_ACCESSORS(UGAS_BaseAttributeSet, currentValue)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	REPLICATE_ATTRIBUTE(UGAS_BaseAttributeSet, maxValue);
	REPLICATE_ATTRIBUTE(UGAS_BaseAttributeSet, minValue);
	REPLICATE_ATTRIBUTE(UGAS_BaseAttributeSet, baseValue);
	REPLICATE_ATTRIBUTE(UGAS_BaseAttributeSet, currentValue);
};
