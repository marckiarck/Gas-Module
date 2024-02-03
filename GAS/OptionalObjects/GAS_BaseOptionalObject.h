

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GAS_BaseOptionalObject.generated.h"


UCLASS()
class GAS_API UGAS_BaseOptionalObject : public UObject
{
	GENERATED_BODY()
	
public:
	bool IsSupportedForNetworking() const override;
};
