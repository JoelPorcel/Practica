#include "SubsistemaConstruccion.h"
#include "Engine/World.h"
#include "../Builder/Director.h"
#include "../Builder/ContructorBasico.h"
#include "../Builder/ConstructorAvanzado.h"
#include "../Builder/ObjetoComplejo.h"

USubsistemaConstruccion::USubsistemaConstruccion()
{
	Director = nullptr;
	EstructuraBase = nullptr;
	EstructuraDefensa = nullptr;
}

void USubsistemaConstruccion::Inicializar()
{
	Director = NewObject<UDirector>(this);
}

void USubsistemaConstruccion::ConstruirCampamento(const FVector& Ubicacion)
{
	if (!Director)
	{
		Inicializar();
	}

	UContructorBasico* ConstructorBasico = NewObject<UContructorBasico>(this);
	Director->SetBuilder(ConstructorBasico);
	Director->ConstruirBasico(Ubicacion);
	EstructuraBase = Director->ObtenerResultado();

	UConstructorAvanzado* ConstructorAvanzado = NewObject<UConstructorAvanzado>(this);
	Director->SetBuilder(ConstructorAvanzado);
	Director->ConstruirAvanzado(Ubicacion + FVector(0.0f, 600.0f, 0.0f));
	EstructuraDefensa = Director->ObtenerResultado();
}

void USubsistemaConstruccion::ActualizarEstructuras(float DeltaTime)
{
	if (EstructuraBase)
	{
		EstructuraBase->Mover(FVector(0.0f, FMath::Sin(GetWorld()->GetTimeSeconds() * 2.0f) * 120.0f * DeltaTime, 0.0f));
	}
	if (EstructuraDefensa)
	{
		EstructuraDefensa->Rotar(FRotator(0.0f, 35.0f * DeltaTime, 0.0f));
	}
}
