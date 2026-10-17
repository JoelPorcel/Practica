#pragma once

#include "CoreMinimal.h"
#include "BaseDecorator.h"
#include "DecoradorDano.generated.h"

UCLASS()
class MYPROJECT_API UDecoradorDano : public UBaseDecorator
{
	GENERATED_BODY()

public:
	UDecoradorDano();

	virtual float GetDano() override;
	virtual FString GetDescripcion() override;
};
