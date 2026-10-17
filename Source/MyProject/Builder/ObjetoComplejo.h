#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjetoComplejo.generated.h"

class ACubo;
class APlataformaTerrestre;
class USceneComponent;

UCLASS()
class MYPROJECT_API AObjetoComplejo : public AActor
{
	GENERATED_BODY()

public:
	AObjetoComplejo();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* EscenaRaiz;

	UPROPERTY(VisibleAnywhere)
	TArray<ACubo*> Cubos;

	UPROPERTY(VisibleAnywhere)
	TArray<APlataformaTerrestre*> Plataformas;

	void AgregarCubo(ACubo* InCubo);
	void AgregarPlataforma(APlataformaTerrestre* InPlataforma);
	void MostrarEstructura();
	void Mover(const FVector& Desplazamiento);
	void Rotar(const FRotator& NuevaRotacion);
};
