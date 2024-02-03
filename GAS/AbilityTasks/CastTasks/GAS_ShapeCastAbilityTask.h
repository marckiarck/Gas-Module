

#pragma once

#include "CoreMinimal.h"
#include <Containers/EnumAsByte.h>
#include <Abilities/Tasks/AbilityTask_WaitGameplayTagBase.h>
#include "GAS_ShapeCastAbilityTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FShapeCastOnHit, const TArray<FHitResult>&, unregisteredHittedActors, const TArray<AActor*>&, totalHittedActors);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShapeCastOnCastEnds);

static TAutoConsoleVariable<int32> castDebugVariable(TEXT("GAS.EnableCastDebug"), 0, TEXT("Enables and disables GAS shapes debug mode"));

USTRUCT(BlueprintType)
struct GAS_API FGAS_ShapeCastSpawnParams
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "One Time Cast")
	bool oneTimeCast = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Hitting Actor")
	AActor* hitActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Shape Duration", meta = (EditCondition = "oneTimeCast==false", EditConditionHides))
	float shapeDuration = -1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Collision Channel")
	TEnumAsByte<ECollisionChannel> collisionChanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Activation Tag")
	FGameplayTag activationTag;
};

UCLASS()
class GAS_API UGAS_ShapeCastAbilityTask : public UAbilityTask_WaitGameplayTag
{
	GENERATED_BODY()

public:
	UGAS_ShapeCastAbilityTask();

protected:
	FCollisionShape castShape;
	TEnumAsByte<ECollisionChannel> shapeCollisionChannel;
	FCollisionQueryParams collisionParams;

private:
	float taskDuration;
	float elapsedDuration;
	bool oneCastTask;
	bool castStarted = true;

	FVector sweepStart;
	FVector sweepEnd;
	FQuat sweepRotation;

	UPROPERTY(Transient)
	AActor* hitActor = nullptr;

	UPROPERTY(Transient)
	TArray<AActor*> hittedActors;

	UPROPERTY(BlueprintAssignable)
	FShapeCastOnHit onActorHitted;

	UPROPERTY(BlueprintAssignable)
	FShapeCastOnCastEnds onCastEnds;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks | ShapeCast", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UGAS_ShapeCastAbilityTask* CastBoxShapeTask(UGameplayAbility* OwningAbility, FGAS_ShapeCastSpawnParams castParams, FVector boxCenter, FVector boxSize, FQuat boxRotation);

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks | ShapeCast", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UGAS_ShapeCastAbilityTask* CastSphereShapeTask(UGameplayAbility* OwningAbility, FGAS_ShapeCastSpawnParams castParams, FVector sphereCenter, float sphereRadious);

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks | ShapeCast", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UGAS_ShapeCastAbilityTask* CastCapsuleShapeTask(UGameplayAbility* OwningAbility, FGAS_ShapeCastSpawnParams castParams, FVector capsuleCenter, float capsuleRadius, float capsuleHalfHeight, FQuat capsuleRotation);

	const TArray<AActor*> GetHittedActors();
	const FVector GetSweepStart();
	const FVector GetSweepEnd();
	const FQuat GetSweepRotation();

protected:
	template<typename T>
	static T* CreateShapeTask(UGameplayAbility* OwningAbility, FGAS_ShapeCastSpawnParams castParams);

	virtual void TickTask(float DeltaTime) override;
	void GameplayTagCallback(const FGameplayTag abilitySystemTag, int32 NewCount) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	virtual FVector UpdateSweepStart();
	virtual FVector UpdateSweepEnd();
	virtual FQuat UpdateSweepRotation();
	virtual bool CastShapeSweep(TArray<FHitResult>& hittedResults);
	virtual bool ShouldEndTask();

	virtual void DrawDebugShapeCast(FColor shapeColor);

	void CreateBoxShape(FVector halfExtent);
	void CreateSphereShape(float sphereRadious);
	void CreateCapsuleShape(float capsuleRadius, float capsuleHalfHeight);

private:
	UFUNCTION()
	void OnActivationTagAdded();

	UFUNCTION()
	void OnActivationTagRemoved();
};

template<typename T>
T* UGAS_ShapeCastAbilityTask::CreateShapeTask(UGameplayAbility* OwningAbility, FGAS_ShapeCastSpawnParams castParams)
{
	T* returnedTask = NewAbilityTask<T>(OwningAbility);
	returnedTask->taskDuration = castParams.shapeDuration;
	returnedTask->shapeCollisionChannel = castParams.collisionChanel;
	returnedTask->oneCastTask = castParams.oneTimeCast;
	returnedTask->hitActor = castParams.hitActor;

	returnedTask->collisionParams.bTraceComplex = true;
	returnedTask->collisionParams.AddIgnoredActor(OwningAbility->GetAvatarActorFromActorInfo());

	if (castParams.activationTag.IsValid())
	{
		returnedTask->Tag = castParams.activationTag;

		returnedTask->castStarted = false;
	}

	return returnedTask;
}
