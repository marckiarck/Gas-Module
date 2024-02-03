
#include "GAS/Notifies/GAS_RemoveTagAnimNotify.h"
#include <AbilitySystemComponent.h>

void UGAS_RemoveTagAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	UWorld* affectedWorld = MeshComp->GetWorld();
	if (affectedWorld && UGameplayStatics::GetGameMode(affectedWorld))
	{
		AActor* meshOwner = MeshComp->GetOwner();
		if (meshOwner)
		{
			if (IAbilitySystemInterface* abilitySytemInterface = Cast<IAbilitySystemInterface>(meshOwner))
			{
				UAbilitySystemComponent* abilitySystemComponent = Cast<UAbilitySystemComponent>(abilitySytemInterface->GetAbilitySystemComponent());

				if (abilitySystemComponent)
				{
					abilitySystemComponent->RemoveLooseGameplayTag(notifiedTag);
				}
			}
		}
	}
}
