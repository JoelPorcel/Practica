#include "ObjetoComplejo.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
#include "../Cubo.h"
#include "../PlataformaTerrestre.h"

AObjetoComplejo::AObjetoComplejo()
{
	PrimaryActorTick.bCanEverTick = false;
	EscenaRaiz = CreateDefaultSubobject<USceneComponent>(TEXT("EscenaRaiz"));
	EscenaRaiz->SetMobility(EComponentMobility::Movable);
	SetRootComponent(EscenaRaiz);
}

void AObjetoComplejo::AgregarCubo(ACubo* InCubo)
{
	Cubos.Add(InCubo);
	InCubo->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

}

void AObjetoComplejo::AgregarPlataforma(APlataformaTerrestre* InPlataforma)
{
	if (InPlataforma)
	{
		Plataformas.Add(InPlataforma);
		InPlataforma->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void AObjetoComplejo::MostrarEstructura()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Objeto Complejo: %d cubos, %d plataformas"), Cubos.Num(), Plataformas.Num()));
}

void AObjetoComplejo::Mover(const FVector& Desplazamiento)
{
	AddActorWorldOffset(Desplazamiento);
}

void AObjetoComplejo::Rotar(const FRotator& NuevaRotacion)
{
	AddActorWorldRotation(NuevaRotacion);
}
