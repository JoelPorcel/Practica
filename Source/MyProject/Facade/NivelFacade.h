#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NivelFacade.generated.h"

class USubsistemaConstruccion;
class USubsistemaEnemigos;
class USubsistemaRecompensas;

UCLASS()
class MYPROJECT_API UNivelFacade : public UObject
{
	GENERATED_BODY()

public:
	UNivelFacade();

	void Inicializar();
	void ConfigurarZonaBatalla(const FVector& Centro);
	void ActualizarNivel(float DeltaTime);
	void ReiniciarZonaBatalla(const FVector& Centro);

private:
	UPROPERTY()
	USubsistemaConstruccion* SubsistemaConstruccion;

	UPROPERTY()
	USubsistemaEnemigos* SubsistemaEnemigos;

	UPROPERTY()
	USubsistemaRecompensas* SubsistemaRecompensas;
};
