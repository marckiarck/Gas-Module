


#include "GAS/PlayerState/GAS_PlayerState.h"

AGAS_PlayerState::AGAS_PlayerState()
{
	playerAbilitySystem = CreateDefaultSubobject<UGAS_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	playerAbilitySystem->SetIsReplicated(true);
	playerAbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	NetUpdateFrequency = 30.f;
}
