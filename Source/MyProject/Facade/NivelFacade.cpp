#include "NivelFacade.h"
#include "SubsistemaConstruccion.h"
#include "SubsistemaEnemigos.h"
#include "SubsistemaRecompensas.h"
#include "Engine/Engine.h"

UNivelFacade::UNivelFacade()
{
	SubsistemaConstruccion = nullptr;
	SubsistemaEnemigos = nullptr;
	SubsistemaRecompensas = nullptr;
}

void UNivelFacade::Inicializar()
{
	SubsistemaConstruccion = NewObject<USubsistemaConstruccion>(this);
	SubsistemaConstruccion->Inicializar();

	SubsistemaEnemigos = NewObject<USubsistemaEnemigos>(this);
	SubsistemaRecompensas = NewObject<USubsistemaRecompensas>(this);
}

void UNivelFacade::ConfigurarZonaBatalla(const FVector& Centro)
{
	if (!SubsistemaConstruccion || !SubsistemaEnemigos || !SubsistemaRecompensas)
	{
		Inicializar();
	}

	SubsistemaConstruccion->ConstruirCampamento(Centro);
	SubsistemaEnemigos->GenerarOleada(Centro + FVector(0.0f, 400.0f, 50.0f), 3);
	SubsistemaRecompensas->DistribuirMonedas(Centro + FVector(0.0f, -300.0f, 50.0f), 4);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Zona de batalla configurada exitosamente por Facade"));
}

void UNivelFacade::ActualizarNivel(float DeltaTime)
{
	if (SubsistemaConstruccion)
	{
		SubsistemaConstruccion->ActualizarEstructuras(DeltaTime);
	}
}

void UNivelFacade::ReiniciarZonaBatalla(const FVector& Centro)
{
	if (SubsistemaEnemigos)
	{
		SubsistemaEnemigos->LimpiarEnemigos();
	}
	if (SubsistemaRecompensas)
	{
		SubsistemaRecompensas->LimpiarMonedas();
	}

	ConfigurarZonaBatalla(Centro);
}
