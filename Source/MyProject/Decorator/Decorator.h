#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Decorator.generated.h"

UINTERFACE(MinimalAPI)
class UDecorator : public UInterface
{
	GENERATED_BODY()
};

class MYPROJECT_API IDecorator
{
	GENERATED_BODY()

public:
	virtual float GetVelocidad() = 0;
	virtual float GetDano() = 0;
	virtual float GetEscudo() = 0;
	virtual FString GetDescripcion() = 0;
	virtual IDecorator* GetComponente() { return nullptr; }
};
