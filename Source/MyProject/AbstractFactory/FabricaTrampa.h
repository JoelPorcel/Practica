#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbstractFactory.h"
#include "FabricaTrampa.generated.h"

class APlataforma;

UCLASS()
class MYPROJECT_API UFabricaTrampa : public UObject, public IAbstractFactory
{
	GENERATED_BODY()

public:
	UFabricaTrampa();

	virtual APlataforma* createA(FVector Location) override;
	virtual APlataforma* createB(FVector Location) override;
};
