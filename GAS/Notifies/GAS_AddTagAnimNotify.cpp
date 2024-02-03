
#include "GAS/Notifies/GAS_AddTagAnimNotify.h"
#include <AbilitySystemComponent.h>

void UGAS_AddTagAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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
					abilitySystemComponent->AddLooseGameplayTag(notifiedTag);
				}
			}
		}
	}
}
