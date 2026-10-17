#include "ContructorBasico.h"
#include "ObjetoComplejo.h"
#include "Engine/World.h"
#include "../Cubo.h"
#include "../PlataformaTerrestre.h"

UContructorBasico::UContructorBasico()
{
	Resultado = nullptr;
	UbicacionBase = FVector::ZeroVector;
}

void UContructorBasico::Reset()
{
	Resultado = GetWorld()->SpawnActor<AObjetoComplejo>(UbicacionBase, FRotator::ZeroRotator);
}

void UContructorBasico::DefinirUbicacion(const FVector& InUbicacion)
{
	UbicacionBase = InUbicacion;
}

void UContructorBasico::ConstruirPiso()
{
	if (!Resultado) return;

	if (APlataformaTerrestre* Plataforma = GetWorld()->SpawnActor<APlataformaTerrestre>(UbicacionBase, FRotator::ZeroRotator))
	{
		Plataforma->SetActorTickEnabled(false); 
		Resultado->AgregarPlataforma(Plataforma);
	}
}

void UContructorBasico::ConstruirMuros()
{
	if (!Resultado) return;

	FVector Posicion = UbicacionBase + FVector(-100.0f, 0.0f, 60.0f);
	for (int32 i = 0; i < 2; i++)
	{
		if (ACubo* Cubo = GetWorld()->SpawnActor<ACubo>(Posicion, FRotator::ZeroRotator))
		{
			Resultado->AgregarCubo(Cubo);
		}
		Posicion.X += 200.0f;
	}
}

void UContructorBasico::ConstruirTecho()
{
	if (!Resultado) return;

	FVector Posicion = UbicacionBase + FVector(0.0f, 0.0f, 160.0f);
	if (ACubo* CuboTecho = GetWorld()->SpawnActor<ACubo>(Posicion, FRotator::ZeroRotator))
	{
		Resultado->AgregarCubo(CuboTecho);
	}
}

void UContructorBasico::ConstruirTorres()
{
}

AObjetoComplejo* UContructorBasico::ObtenerResultado()
{
	return Resultado;
}

AObjetoComplejo* UContructorBasico::GetResult()
{
	return ObtenerResultado();
}
