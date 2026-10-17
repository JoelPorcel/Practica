#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbstractFactory.h"
#include "FabricaHierro.generated.h"

class APlataforma;

UCLASS()
class MYPROJECT_API UFabricaHierro : public UObject, public IAbstractFactory
{
	GENERATED_BODY()

public:
	UFabricaHierro();

	virtual APlataforma* createA(FVector Location) override;
	virtual APlataforma* createB(FVector Location) override;
};
