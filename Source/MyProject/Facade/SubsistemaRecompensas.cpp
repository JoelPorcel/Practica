#include "SubsistemaRecompensas.h"
#include "Engine/World.h"
#include "../Moneda.h"

USubsistemaRecompensas::USubsistemaRecompensas()
{
}

void USubsistemaRecompensas::DistribuirMonedas(const FVector& Ubicacion, int32 Cantidad)
{
	FVector Posicion = Ubicacion;
	for (int32 i = 0; i < Cantidad; i++)
	{
		if (AMoneda* Moneda = GetWorld()->SpawnActor<AMoneda>(Posicion, FRotator::ZeroRotator))
		{
			MonedasActivas.Add(Moneda);
		}
		Posicion.Y += 150.0f;
	}
}

void USubsistemaRecompensas::LimpiarMonedas()
{
	for (int32 i = 0; i < MonedasActivas.Num(); i++)
	{
		if (MonedasActivas[i])
		{
			MonedasActivas[i]->Destroy();
		}
	}
	MonedasActivas.Empty();
}
