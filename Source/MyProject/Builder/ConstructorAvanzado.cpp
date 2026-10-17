#include "ConstructorAvanzado.h"
#include "ObjetoComplejo.h"
#include "Engine/World.h"
#include "../Cubo.h"
#include "../PlataformaTerrestre.h"

UConstructorAvanzado::UConstructorAvanzado()
{
	Resultado = nullptr;
	UbicacionBase = FVector::ZeroVector;
}

void UConstructorAvanzado::Reset()
{
	Resultado = GetWorld()->SpawnActor<AObjetoComplejo>(UbicacionBase, FRotator::ZeroRotator);
}

void UConstructorAvanzado::DefinirUbicacion(const FVector& InUbicacion)
{
	UbicacionBase = InUbicacion;
}

void UConstructorAvanzado::ConstruirPiso()
{
	if (!Resultado) return;

	FVector Posicion = UbicacionBase + FVector(-150.0f, 0.0f, 0.0f);
	for (int32 i = 0; i < 2; i++)
	{
		if (APlataformaTerrestre* Plat = GetWorld()->SpawnActor<APlataformaTerrestre>(Posicion, FRotator::ZeroRotator))
		{
			Plat->SetActorTickEnabled(false);
			Resultado->AgregarPlataforma(Plat);
		}
		Posicion.X += 300.0f;
	}
}

void UConstructorAvanzado::ConstruirMuros()
{
	if (!Resultado) return;

	FVector Posicion = UbicacionBase + FVector(-150.0f, -100.0f, 60.0f);
	for (int32 i = 0; i < 2; i++)
	{
		for (int32 j = 0; j < 2; j++)
		{
			if (ACubo* Cubo = GetWorld()->SpawnActor<ACubo>(Posicion, FRotator::ZeroRotator))
			{
				Resultado->AgregarCubo(Cubo);
			}
			Posicion.Y += 200.0f;
		}
		Posicion.Y = UbicacionBase.Y - 100.0f;
		Posicion.X += 300.0f;
	}
}

void UConstructorAvanzado::ConstruirTecho()
{
	if (!Resultado) return;

	FVector Posicion = UbicacionBase + FVector(0.0f, 0.0f, 180.0f);
	if (APlataformaTerrestre* Techo = GetWorld()->SpawnActor<APlataformaTerrestre>(Posicion, FRotator::ZeroRotator))
	{
		Techo->SetActorTickEnabled(false);
		Resultado->AgregarPlataforma(Techo);
	}
}

void UConstructorAvanzado::ConstruirTorres()
{
	if (!Resultado) return;

	FVector Posicion = UbicacionBase + FVector(-150.0f, 0.0f, 260.0f);
	for (int32 i = 0; i < 2; i++)
	{
		if (ACubo* Torre = GetWorld()->SpawnActor<ACubo>(Posicion, FRotator::ZeroRotator))
		{
			Resultado->AgregarCubo(Torre);
		}
		Posicion.X += 300.0f;
	}
}

AObjetoComplejo* UConstructorAvanzado::ObtenerResultado()
{
	return Resultado;
}

AObjetoComplejo* UConstructorAvanzado::GetResult()
{
	return ObtenerResultado();
}
