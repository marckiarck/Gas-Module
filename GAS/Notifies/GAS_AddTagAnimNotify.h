

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include <GameplayTagContainer.h>
#include "GAS_AddTagAnimNotify.generated.h"


UCLASS()
class GAS_API UGAS_AddTagAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "GameplayTag"))
	FGameplayTag notifiedTag;

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
