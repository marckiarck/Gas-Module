
#pragma once

#include "CoreMinimal.h"
#include "GAS/AbilityTasks/CastTasks/GAS_ShapeCastAbilityTask.h"
#include "GAS_ConeCastAbilityTask.generated.h"


UCLASS()
class GAS_API UGAS_ConeCastAbilityTask : public UGAS_ShapeCastAbilityTask
{
	GENERATED_BODY()
	
public:
	UGAS_ConeCastAbilityTask();

private:

	UPROPERTY(Transient)
	TArray<AActor*> actorsToIgnore;

	float angleAperture;
	float maxConeDistance;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks | ShapeCast", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UGAS_ConeCastAbilityTask* CastConeShapeTask(UGameplayAbility* OwningAbility, FGAS_ShapeCastSpawnParams castParams, float maxConeDistance, float angleAperture);

protected:
	virtual bool CastShapeSweep(TArray<FHitResult>& hittedResults);
	virtual void DrawDebugShapeCast(FColor shapeColor) override;

};
