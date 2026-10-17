#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SubsistemaEnemigos.generated.h"

class AEnemigo;

UCLASS()
class MYPROJECT_API USubsistemaEnemigos : public UObject
{
	GENERATED_BODY()

public:
	USubsistemaEnemigos();

	void GenerarOleada(const FVector& Ubicacion, int32 Cantidad);
	void LimpiarEnemigos();

private:
	UPROPERTY()
	TArray<AEnemigo*> EnemigosActivos;
};
