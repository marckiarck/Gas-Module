


#include "GAS/AbilityTasks/CastTasks/GAS_ShapeCastAbilityTask.h"
#include "GAS/GAS_Macros.h"
#include <AbilitySystemGlobals.h>

UGAS_ShapeCastAbilityTask::UGAS_ShapeCastAbilityTask()
{
	bTickingTask = true;
}

UGAS_ShapeCastAbilityTask* UGAS_ShapeCastAbilityTask::CastBoxShapeTask(UGameplayAbility* OwningAbility, FGAS_ShapeCastSpawnParams castParams, FVector boxCenter, FVector boxSize, FQuat boxRotation)
{
	UGAS_ShapeCastAbilityTask* returnedTask = UGAS_ShapeCastAbilityTask::CreateShapeTask<UGAS_ShapeCastAbilityTask>(OwningAbility, castParams);

	returnedTask->CreateBoxShape(boxSize);
	returnedTask->sweepStart = boxCenter;
	returnedTask->sweepEnd = boxCenter;
	returnedTask->sweepRotation = boxRotation;

	return returnedTask;
}

UGAS_ShapeCastAbilityTask* UGAS_ShapeCastAbilityTask::CastSphereShapeTask(UGameplayAbility* OwningAbility, FGAS_ShapeCastSpawnParams castParams, FVector sphereCenter, float sphereRadious)
{
	UGAS_ShapeCastAbilityTask* returnedTask = UGAS_ShapeCastAbilityTask::CreateShapeTask<UGAS_ShapeCastAbilityTask>(OwningAbility, castParams);

	returnedTask->CreateSphereShape(sphereRadious);
	returnedTask->sweepStart = sphereCenter;
	returnedTask->sweepEnd = sphereCenter;
	returnedTask->sweepRotation = FQuat::Identity;

	return returnedTask;
}

UGAS_ShapeCastAbilityTask* UGAS_ShapeCastAbilityTask::CastCapsuleShapeTask(UGameplayAbility* OwningAbility, FGAS_ShapeCastSpawnParams castParams, FVector capsuleCenter, float capsuleRadius, float capsuleHalfHeight, FQuat capsuleRotation)
{
	UGAS_ShapeCastAbilityTask* returnedTask = UGAS_ShapeCastAbilityTask::CreateShapeTask<UGAS_ShapeCastAbilityTask>(OwningAbility, castParams);

	returnedTask->CreateCapsuleShape(capsuleRadius, capsuleHalfHeight);
	returnedTask->sweepStart = capsuleCenter;
	returnedTask->sweepEnd = capsuleCenter;
	returnedTask->sweepRotation = capsuleRotation;

	return returnedTask;
}

const TArray<AActor*> UGAS_ShapeCastAbilityTask::GetHittedActors()
{
	return hittedActors;
}

const FVector UGAS_ShapeCastAbilityTask::GetSweepStart()
{
	return sweepStart;
}

const FVector UGAS_ShapeCastAbilityTask::GetSweepEnd()
{
	return sweepEnd;
}

const FQuat UGAS_ShapeCastAbilityTask::GetSweepRotation()
{
	return sweepRotation;
}

void UGAS_ShapeCastAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (castStarted == false)
	{
		return;
	}

	sweepStart = UpdateSweepStart();
	sweepEnd = UpdateSweepEnd();
	sweepRotation = UpdateSweepRotation();

	TArray<FHitResult> hitResults;
	if (CastShapeSweep(hitResults))
	{
		TArray<FHitResult> unregiteredHitResults;
		for (FHitResult hitResultIt : hitResults)
		{
			AActor* hittedActor = hitResultIt.GetActor();
			if (hittedActors.Contains(hittedActor) == false)
			{
				unregiteredHitResults.Add(hitResultIt);
				hittedActors.Add(hittedActor);
			}

		}
		onActorHitted.Broadcast(unregiteredHitResults, hittedActors);
	}

#if WITH_GAMEPLAY_DEBUGGER
	if (castDebugVariable.GetValueOnGameThread())
	{
		hittedActors.Num() > 0 ? DrawDebugShapeCast(HIT_COLOR) : DrawDebugShapeCast(NO_HIT_COLOR);
	}
#endif //#if WITH_GAMEPLAY_DEBUGGER

	elapsedDuration += DeltaTime;
	if (ShouldEndTask())
	{
		EndTask();
	}
}

void UGAS_ShapeCastAbilityTask::GameplayTagCallback(const FGameplayTag abilitySystemTag, int32 NewCount)
{
	Super::GameplayTagCallback(abilitySystemTag, NewCount);

	UAbilitySystemComponent* abilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetAvatarActor());
	if (castStarted == false && abilitySystem && abilitySystem->HasMatchingGameplayTag(Tag))
	{
		OnActivationTagAdded();
	}
	else
	{
		OnActivationTagRemoved();
	}
}

void UGAS_ShapeCastAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

	onCastEnds.Broadcast();
}

FVector UGAS_ShapeCastAbilityTask::UpdateSweepStart()
{
	if (hitActor)
	{
		return hitActor->GetActorLocation();
	}
	else 
	{
		return sweepStart;
	}
}

FVector UGAS_ShapeCastAbilityTask::UpdateSweepEnd()
{
	if (hitActor)
	{
		return hitActor->GetActorLocation();
	}
	else
	{
		return sweepEnd;
	}
}

FQuat UGAS_ShapeCastAbilityTask::UpdateSweepRotation()
{
	if (hitActor)
	{
		return hitActor->GetActorRotation().Quaternion();
	}
	else
	{
		return sweepRotation;
	}
}

bool UGAS_ShapeCastAbilityTask::CastShapeSweep(TArray<FHitResult>& hitResults)
{

	return GetWorld()->SweepMultiByChannel(hitResults, sweepStart, sweepEnd, sweepRotation, shapeCollisionChannel, castShape, collisionParams);
}

bool UGAS_ShapeCastAbilityTask::ShouldEndTask()
{
	if (oneCastTask)
	{
		return true;
	}
	else if (taskDuration > 0.f)
	{
		if (elapsedDuration >= taskDuration)
		{
			return true;
		}
	}
	
	return false;
}

void UGAS_ShapeCastAbilityTask::DrawDebugShapeCast(FColor shapeColor)
{
	if (castShape.IsBox())
	{
		DrawDebugBox(GetWorld(), sweepStart, castShape.GetBox(), sweepRotation, shapeColor, false, 0.1f);
	}
	else if (castShape.IsSphere())
	{
		DrawDebugSphere(GetWorld(), sweepStart, castShape.GetSphereRadius(), 12, shapeColor, false, 0.1f);
	}
	else if (castShape.IsCapsule())
	{
		DrawDebugCapsule(GetWorld(), sweepStart, castShape.GetCapsuleHalfHeight(), castShape.GetCapsuleRadius(), sweepRotation, shapeColor, false, 0.1f);
	}
}

void UGAS_ShapeCastAbilityTask::CreateBoxShape(FVector halfExtent)
{
	castShape = FCollisionShape::MakeBox(halfExtent);
}

void UGAS_ShapeCastAbilityTask::CreateSphereShape(float sphereRadious)
{
	castShape = FCollisionShape::MakeSphere(sphereRadious);
}

void UGAS_ShapeCastAbilityTask::CreateCapsuleShape(float capsuleRadius, float capsuleHalfHeight)
{
	castShape = FCollisionShape::MakeCapsule(capsuleRadius, capsuleHalfHeight);
}

void UGAS_ShapeCastAbilityTask::OnActivationTagAdded()
{
	castStarted = true;
}

void UGAS_ShapeCastAbilityTask::OnActivationTagRemoved()
{
	EndTask();
}
