#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Decorator.h"
#include "NaveDefault.generated.h"

UCLASS()
class MYPROJECT_API UNaveDefault : public UObject, public IDecorator
{
	GENERATED_BODY()

public:
	UNaveDefault();

	virtual float GetVelocidad() override;
	virtual float GetDano() override;
	virtual float GetEscudo() override;
	virtual FString GetDescripcion() override;
};
