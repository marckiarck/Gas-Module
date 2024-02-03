// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/GAS_Macros.h"
#include "GAS_HealthAttributeSet.generated.h"


UCLASS()
class GAS_API UGAS_HealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData maxHealth;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, Replicated)
		FGameplayAttributeData health;

	bool zeroHealthAbilityLaunched = false;

public:
	ATTRIBUTE_ACCESSORS(UGAS_HealthAttributeSet, maxHealth)
	ATTRIBUTE_ACCESSORS(UGAS_HealthAttributeSet, health)

	void InitFromMetaDataTable(const UDataTable* DataTable) override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	REPLICATE_ATTRIBUTE(UGAS_HealthAttributeSet, maxHealth);
	REPLICATE_ATTRIBUTE(UGAS_HealthAttributeSet, health);

private:
	void LaunchZeroHealthAbility();
};
