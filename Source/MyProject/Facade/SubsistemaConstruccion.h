#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SubsistemaConstruccion.generated.h"

class UDirector;
class AObjetoComplejo;

UCLASS()
class MYPROJECT_API USubsistemaConstruccion : public UObject
{
	GENERATED_BODY()

public:
	USubsistemaConstruccion();

	void Inicializar();
	void ConstruirCampamento(const FVector& Ubicacion);
	void ActualizarEstructuras(float DeltaTime);

private:
	UPROPERTY()
	UDirector* Director;

	UPROPERTY()
	AObjetoComplejo* EstructuraBase;

	UPROPERTY()
	AObjetoComplejo* EstructuraDefensa;
};
