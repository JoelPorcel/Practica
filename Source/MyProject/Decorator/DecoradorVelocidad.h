#pragma once

#include "CoreMinimal.h"
#include "BaseDecorator.h"
#include "DecoradorVelocidad.generated.h"

UCLASS()
class MYPROJECT_API UDecoradorVelocidad : public UBaseDecorator
{
	GENERATED_BODY()

public:
	UDecoradorVelocidad();

	virtual float GetVelocidad() override;
	virtual FString GetDescripcion() override;
};
