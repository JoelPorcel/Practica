#include "Director.h"
#include "ObjetoComplejo.h"
#include "ContructorBasico.h"
#include "ConstructorAvanzado.h"

UDirector::UDirector()
{
	BuilderActual = nullptr;
}

void UDirector::SetBuilder(IBuilder* InBuilder)
{
	BuilderActual = InBuilder;
}

void UDirector::Construir(const FVector& Ubicacion)
{
	if (BuilderActual)
	{
		BuilderActual->DefinirUbicacion(Ubicacion);
		BuilderActual->Reset();
		BuilderActual->ConstruirPiso();
		BuilderActual->ConstruirMuros();
		BuilderActual->ConstruirTecho();
	}

}

void UDirector::ConstruirBasico(const FVector& Ubicacion)
{
	if (!BuilderActual)
	{
		BuilderActual = NewObject<UContructorBasico>(this);
	}
	if (BuilderActual)
	{
		BuilderActual->DefinirUbicacion(Ubicacion);
		BuilderActual->Reset();
		BuilderActual->ConstruirPiso();
		BuilderActual->ConstruirMuros();
		BuilderActual->ConstruirTecho();
	}
}

void UDirector::ConstruirAvanzado(const FVector& Ubicacion)
{
	if (!BuilderActual)
	{
		BuilderActual = NewObject<UConstructorAvanzado>(this);
	}
	if (BuilderActual)
	{
		BuilderActual->DefinirUbicacion(Ubicacion);
		BuilderActual->Reset();
		BuilderActual->ConstruirPiso();
		BuilderActual->ConstruirMuros();
		BuilderActual->ConstruirTecho();
		BuilderActual->ConstruirTorres();
	}
}

void UDirector::ConstruirBasicoCon(IBuilder* InBuilder, const FVector& Ubicacion)
{
	SetBuilder(InBuilder);
	ConstruirBasico(Ubicacion);
}

void UDirector::ConstruirAvanzadoCon(IBuilder* InBuilder, const FVector& Ubicacion)
{
	SetBuilder(InBuilder);
	ConstruirAvanzado(Ubicacion);
}

AObjetoComplejo* UDirector::ObtenerResultado()
{
	if (BuilderActual)
	{
		return BuilderActual->ObtenerResultado();
	}
	return nullptr;
}
