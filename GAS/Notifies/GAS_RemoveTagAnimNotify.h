

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include <GameplayTagContainer.h>
#include "GAS_RemoveTagAnimNotify.generated.h"


UCLASS()
class GAS_API UGAS_RemoveTagAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "GameplayTag"))
	FGameplayTag notifiedTag;

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
