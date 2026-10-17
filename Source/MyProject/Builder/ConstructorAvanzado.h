#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Builder.h"
#include "ConstructorAvanzado.generated.h"

class AObjetoComplejo;

UCLASS()
class MYPROJECT_API UConstructorAvanzado : public UObject, public IBuilder
{
	GENERATED_BODY()

public:
	UConstructorAvanzado();

	virtual void Reset() override;
	virtual void DefinirUbicacion(const FVector& InUbicacion) override;
	virtual void ConstruirPiso() override;
	virtual void ConstruirMuros() override;
	virtual void ConstruirTecho() override;
	virtual void ConstruirTorres() override;
	virtual AObjetoComplejo* ObtenerResultado() override;
	virtual AObjetoComplejo* GetResult() override;

private:
	UPROPERTY()
	AObjetoComplejo* Resultado;

	FVector UbicacionBase;
};
