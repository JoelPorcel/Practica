#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbstractFactory.generated.h"

class APlataforma;

UINTERFACE(MinimalAPI)
class UAbstractFactory : public UInterface
{
	GENERATED_BODY()
};

class MYPROJECT_API IAbstractFactory
{
	GENERATED_BODY()

public:
	virtual APlataforma* createA(FVector Location) = 0;
	virtual APlataforma* createB(FVector Location) = 0;
};
