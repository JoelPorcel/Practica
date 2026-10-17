#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SubsistemaRecompensas.generated.h"

class AMoneda;

UCLASS()
class MYPROJECT_API USubsistemaRecompensas : public UObject
{
	GENERATED_BODY()

public:
	USubsistemaRecompensas();

	void DistribuirMonedas(const FVector& Ubicacion, int32 Cantidad);
	void LimpiarMonedas();

private:
	UPROPERTY()
	TArray<AMoneda*> MonedasActivas;
};
