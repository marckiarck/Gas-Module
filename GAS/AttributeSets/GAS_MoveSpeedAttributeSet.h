// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/GAS_Macros.h"
#include "GAS_MoveSpeedAttributeSet.generated.h"


UCLASS()
class GAS_API UGAS_MoveSpeedAttributeSet : public UAttributeSet
{

	GENERATED_BODY()

private:
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData maxSpeed = 100000.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData minSpeed = 0.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData baseSpeed = 0.f;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData moveSpeed;

public:
	ATTRIBUTE_ACCESSORS(UGAS_MoveSpeedAttributeSet, maxSpeed)
	ATTRIBUTE_ACCESSORS(UGAS_MoveSpeedAttributeSet, minSpeed)
	ATTRIBUTE_ACCESSORS(UGAS_MoveSpeedAttributeSet, baseSpeed)
	ATTRIBUTE_ACCESSORS(UGAS_MoveSpeedAttributeSet, moveSpeed)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	REPLICATE_ATTRIBUTE(UGAS_MoveSpeedAttributeSet, maxSpeed);
	REPLICATE_ATTRIBUTE(UGAS_MoveSpeedAttributeSet, minSpeed);
	REPLICATE_ATTRIBUTE(UGAS_MoveSpeedAttributeSet, baseSpeed);
	REPLICATE_ATTRIBUTE(UGAS_MoveSpeedAttributeSet, moveSpeed);
};
