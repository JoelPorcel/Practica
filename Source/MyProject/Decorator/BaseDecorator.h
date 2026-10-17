#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Decorator.h"
#include "BaseDecorator.generated.h"

UCLASS()
class MYPROJECT_API UBaseDecorator : public UObject, public IDecorator
{
	GENERATED_BODY()

public:
	UBaseDecorator();

	void SetComponente(IDecorator* InComponente);
	virtual IDecorator* GetComponente() override;

	virtual float GetVelocidad() override;
	virtual float GetDano() override;
	virtual float GetEscudo() override;
	virtual FString GetDescripcion() override;

protected:
	IDecorator* Componente;

	UPROPERTY()
	UObject* ComponenteObjeto;
};
