#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Builder.h"
#include "Director.generated.h"

class AObjetoComplejo;

UCLASS()
class MYPROJECT_API UDirector : public UObject
{
	GENERATED_BODY()

public:
	UDirector();

	void SetBuilder(IBuilder* InBuilder);
	void Construir(const FVector& Ubicacion);
	void ConstruirBasico(const FVector& Ubicacion);
	void ConstruirAvanzado(const FVector& Ubicacion);
	void ConstruirBasicoCon(IBuilder* InBuilder, const FVector& Ubicacion);
	void ConstruirAvanzadoCon(IBuilder* InBuilder, const FVector& Ubicacion);
	AObjetoComplejo* ObtenerResultado();
	AObjetoComplejo* GetResultado();

private:
	IBuilder* BuilderActual;
};
