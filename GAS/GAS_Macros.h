#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define GET_GAMEPLAY_TAG(TAG_NAME) \
	FGameplayTag::RequestGameplayTag(FName(TAG_NAME))

#define REMOVE_GAMEPLAY_EFFECT_WITH_TAG(_TAG) \
	FGameplayTagContainer tagContainer = FGameplayTagContainer(); \
	FGameplayTag gameplayTag = FGameplayTag::RequestGameplayTag(_TAG); \
	tagContainer.AddTag(gameplayTag); \
	abilitySystem->RemoveActiveEffectsWithTags(tagContainer)

#define CHECK_HAS_TAG(ABILITY_SYSTEM, TAG_NAME, OUTPUT_BOOLEAN) \
{ \
FGameplayTagContainer abilitySystemTags; \
ABILITY_SYSTEM->GetOwnedGameplayTags(abilitySystemTags); \
if (abilitySystemTags.HasTag(GET_GAMEPLAY_TAG(TAG_NAME))) \
{ \
	OUTPUT_BOOLEAN = true; \
} \
else \
{ \
	OUTPUT_BOOLEAN = false; \
}; \
}

//Debug colors
#define HIT_COLOR FColor::Red
#define NO_HIT_COLOR FColor::Green

//Multiplayer macros
#define REPLICATE_ATTRIBUTE(ATTRIBUTE_CLASS, ATTRIBUTE_NAME) \
	void OnRep_##ATTRIBUTE_NAME(const FGameplayAttributeData old##ATTRIBUTE_NAME) \
	{ \
	GAMEPLAYATTRIBUTE_REPNOTIFY(ATTRIBUTE_CLASS, ATTRIBUTE_NAME, old##ATTRIBUTE_NAME); \
	}; \

