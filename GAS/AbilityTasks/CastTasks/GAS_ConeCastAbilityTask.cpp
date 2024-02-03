
#include "GAS/AbilityTasks/CastTasks/GAS_ConeCastAbilityTask.h"


UGAS_ConeCastAbilityTask::UGAS_ConeCastAbilityTask()
{

}

UGAS_ConeCastAbilityTask* UGAS_ConeCastAbilityTask::CastConeShapeTask(UGameplayAbility* OwningAbility, FGAS_ShapeCastSpawnParams castParams, float maxConeDistance, float angleAperture)
{
    UGAS_ConeCastAbilityTask* returnedTask = UGAS_ShapeCastAbilityTask::CreateShapeTask<UGAS_ConeCastAbilityTask>(OwningAbility, castParams);
    
    returnedTask->CreateBoxShape(FVector(maxConeDistance)); // Is going to be created a box with maxConeDistance radius to calculate wich actors check if they are inside the cone
    returnedTask->angleAperture = angleAperture;
    returnedTask->maxConeDistance = maxConeDistance;

    return returnedTask;
}

bool UGAS_ConeCastAbilityTask::CastShapeSweep(TArray<FHitResult>& hitResults)
{
    hitResults.Empty();

    //Distance check
    FVector sweepLocation = GetSweepStart();

    collisionParams.AddIgnoredActors(GetHittedActors());
    TArray<FHitResult> boxHitResults;
    if (GetWorld()->SweepMultiByChannel(boxHitResults, sweepLocation, sweepLocation, GetSweepRotation(), shapeCollisionChannel, castShape, collisionParams))
    {
        bool castHitted = false;

        AActor* ownerActor = GetAvatarActor();
        FVector coneDirection = GetSweepRotation().Vector();
        for (const FHitResult boxHitResultIt : boxHitResults)
        {
            //Check angle
            FVector actorToCheckLocation = boxHitResultIt.GetActor()->GetActorLocation();
            FVector distToEmitterVector = actorToCheckLocation - sweepLocation;

            FVector distToEmitterNormalized = distToEmitterVector.GetSafeNormal(0.f);
            float dotProduct = FVector::DotProduct(coneDirection, distToEmitterNormalized);
            float angleToConeDirection = FMath::RadiansToDegrees(FMath::Acos(dotProduct));

            if (angleToConeDirection > angleAperture)
            {
                continue;
            }

            hitResults.Add(boxHitResultIt);
            castHitted = true;
        }

        return castHitted;
    }
    else
    {
        return false;
    }
}

void UGAS_ConeCastAbilityTask::DrawDebugShapeCast(FColor shapeColor)
{
    AActor* ownerActor = GetAvatarActor();
    DrawDebugCone(GetWorld(), ownerActor->GetActorLocation(), ownerActor->GetActorForwardVector(), maxConeDistance, FMath::DegreesToRadians(angleAperture), 0.f, 15, shapeColor, false, 0.01f);
}
