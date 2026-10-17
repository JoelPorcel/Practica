#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbstractFactory.h"
#include "FabricaAerea.generated.h"

class APlataforma;

UCLASS()
class MYPROJECT_API UFabricaAerea : public UObject, public IAbstractFactory
{
	GENERATED_BODY()

public:
	UFabricaAerea();

	APlataforma* createA(FVector Location) override;
	APlataforma* createB(FVector Location) override;
};
