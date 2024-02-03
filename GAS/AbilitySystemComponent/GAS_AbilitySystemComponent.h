

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Engine/DataTable.h"
#include "GAS_AbilitySystemComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAS_API UGAS_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UGameplayAbility>> addedAbilities;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UAttributeSet>> addedAtributeSets;

	UPROPERTY(Transient)
	TMap<FString,const class UAttributeSet*> attributesMap;

	UPROPERTY(EditAnywhere)//, meta = (RequiredAssetDataTags = "RowStructure=AttributeMetaData"))
	UDataTable* attributtesDatatable;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	const FString GetAttributeSetKey(TSubclassOf<class UAttributeSet> attributeSetClass);

public:
	void InitializeAbilitySystem();

	template <typename T>
	const T* GetAttributes()
	{
		if (attributesMap.Contains(GetAttributeSetKey(T::StaticClass())))
		{
			return static_cast<const T*>(attributesMap[GetAttributeSetKey(T::StaticClass())]);
		}
		else
		{
			ensureMsgf(true, TEXT("Attribute Set class passed as template wasn't added to the AddedAttributeSets"));
			return nullptr;
		}
	}
};
