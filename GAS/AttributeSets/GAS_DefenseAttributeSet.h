// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/GAS_Macros.h"
#include "GAS_DefenseAttributeSet.generated.h"


UCLASS()
class GAS_API UGAS_DefenseAttributeSet : public UAttributeSet
{

	GENERATED_BODY()

private:
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData maxDefense = 100000.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData minDefense = 0.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData baseDefense = 1.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData currentDefense = 1.f;

public:
	ATTRIBUTE_ACCESSORS(UGAS_DefenseAttributeSet, maxDefense)
	ATTRIBUTE_ACCESSORS(UGAS_DefenseAttributeSet, minDefense)
	ATTRIBUTE_ACCESSORS(UGAS_DefenseAttributeSet, baseDefense)
	ATTRIBUTE_ACCESSORS(UGAS_DefenseAttributeSet, currentDefense)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	REPLICATE_ATTRIBUTE(UGAS_DefenseAttributeSet, maxDefense);
	REPLICATE_ATTRIBUTE(UGAS_DefenseAttributeSet, minDefense);
	REPLICATE_ATTRIBUTE(UGAS_DefenseAttributeSet, baseDefense);
	REPLICATE_ATTRIBUTE(UGAS_DefenseAttributeSet, currentDefense);
};
