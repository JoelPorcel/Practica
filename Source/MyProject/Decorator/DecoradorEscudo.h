#pragma once

#include "CoreMinimal.h"
#include "BaseDecorator.h"
#include "DecoradorEscudo.generated.h"

UCLASS()
class MYPROJECT_API UDecoradorEscudo : public UBaseDecorator
{
	GENERATED_BODY()

public:
	UDecoradorEscudo();

	virtual float GetEscudo() override;
	virtual FString GetDescripcion() override;
};
