#include "Plataforma.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

APlataforma::APlataforma()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	MeshPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPlataforma"));
	MeshPlataforma->SetupAttachment(Root);
	MeshPlataforma->SetRelativeLocation(FVector(-40.0f, -110.0f, 0.0f));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Root);
	Box->SetRelativeLocation(FVector(1.0f, 0.0f, -7.0f));
	Box->SetRelativeScale3D(FVector(1.3625f, 3.86f, 0.2775f));

}

void APlataforma::BeginPlay()
{
	Super::BeginPlay();

	LocacionInicial = GetActorLocation();
}

// Llamado en cada frame
void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoverPlataforma(DeltaTime);
	RotarPlataforma(DeltaTime);
}

void APlataforma::MoverPlataforma(float DeltaTime)
{
	DistanciaMovida = GetDistanciaMovida();

	if (DistanciaMovida >= DistanciaMover)
	{
		float Exceso = DistanciaMovida - DistanciaMover;
		FString NombrePlataforma = GetName();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s se paso por %f"), *NombrePlataforma, Exceso));

		FVector DireccionMovimiento = VelocidadPlataforma.GetSafeNormal();
		FVector NuevaLocacionInicial = LocacionInicial + DireccionMovimiento * DistanciaMover;
		SetActorLocation(NuevaLocacionInicial);
		LocacionInicial = NuevaLocacionInicial;

		VelocidadPlataforma = -VelocidadPlataforma;
	}
	else
	{
		FVector LocacionActual = GetActorLocation();

		LocacionActual = LocacionActual + (VelocidadPlataforma * DeltaTime);

		SetActorLocation(LocacionActual);
	}
}

void APlataforma::RotarPlataforma(float DeltaTime)
{
	FRotator RotacionAAgregar = VelocidadRotacion * DeltaTime;
	AddActorLocalRotation(RotacionAAgregar);
}

void APlataforma::mensaje()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("clase base APlataforma haciendo su movimiento"));
}
