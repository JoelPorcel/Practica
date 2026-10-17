#include "SubsistemaEnemigos.h"
#include "Engine/World.h"
#include "../Enemigo.h"

USubsistemaEnemigos::USubsistemaEnemigos()
{
}

void USubsistemaEnemigos::GenerarOleada(const FVector& Ubicacion, int32 Cantidad)
{
	FVector Posicion = Ubicacion;
	for (int32 i = 0; i < Cantidad; i++)
	{
		if (AEnemigo* Enemigo = GetWorld()->SpawnActor<AEnemigo>(Posicion, FRotator::ZeroRotator))
		{
			EnemigosActivos.Add(Enemigo);
		}
		Posicion.X += 200.0f;
	}
}

void USubsistemaEnemigos::LimpiarEnemigos()
{
	for (int32 i = 0; i < EnemigosActivos.Num(); i++)
	{
		if (EnemigosActivos[i])
		{
			EnemigosActivos[i]->Destroy();
		}
	}
	EnemigosActivos.Empty();
}
