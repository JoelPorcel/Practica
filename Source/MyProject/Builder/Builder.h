#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Builder.generated.h"

class AObjetoComplejo;

UINTERFACE(MinimalAPI)
class UBuilder : public UInterface
{
	GENERATED_BODY()
};

class MYPROJECT_API IBuilder
{
	GENERATED_BODY()

public:
	virtual void Reset() = 0;
	virtual void DefinirUbicacion(const FVector& InUbicacion) = 0;
	virtual void ConstruirPiso() = 0;
	virtual void ConstruirMuros() = 0;
	virtual void ConstruirTecho() = 0;
	virtual void ConstruirTorres() = 0;
	virtual AObjetoComplejo* ObtenerResultado() = 0;
	virtual AObjetoComplejo* GetResult() = 0;
};
