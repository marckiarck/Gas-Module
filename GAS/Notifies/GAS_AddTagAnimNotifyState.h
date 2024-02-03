
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include <GameplayTagContainer.h>
#include <AbilitySystemComponent.h>
#include "GAS_AddTagAnimNotifyState.generated.h"

UCLASS()
class GAS_API UGAS_NotifyAddTagGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UGAS_NotifyAddTagGameplayEffect();

public:
	void SetTagAdded(FGameplayTag notifiedTag);
};

UCLASS()
class GAS_API UGAS_AddTagAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UGAS_AddTagAnimNotifyState();

private:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "GameplayTag"))
	FGameplayTag notifiedTag;

	UPROPERTY(Transient)
	UAbilitySystemComponent* abilitySystemComponent = nullptr;

	UPROPERTY()
	FActiveGameplayEffectHandle activeTagAddedHandle;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	virtual bool ShouldFireInEditor() override;

private:
	void AddTag(USkeletalMeshComponent* MeshComp);
	void RemoveTag(USkeletalMeshComponent* MeshComp);

	UGameplayEffect* CreateAddTagGameplayEffect();
};
