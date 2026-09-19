#include "ProjectileRebote.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectileRebote::AProjectileRebote()
{
	PrimaryActorTick.bCanEverTick = false;

	ColisionEsfera = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionEsfera"));
	ColisionEsfera->InitSphereRadius(15.0f);
	ColisionEsfera->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	SetRootComponent(ColisionEsfera);

	MeshProyectil = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshProyectil"));
	MeshProyectil->SetupAttachment(ColisionEsfera);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile'"));
	if (MeshAsset.Succeeded())
	{
		MeshProyectil->SetStaticMesh(MeshAsset.Object);
		MeshProyectil->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	}

	MovimientoProyectil = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovimientoProyectil"));
	MovimientoProyectil->UpdatedComponent = ColisionEsfera;
	MovimientoProyectil->InitialSpeed = 1500.f;
	MovimientoProyectil->MaxSpeed = 1500.f;
	MovimientoProyectil->bRotationFollowsVelocity = true;
	MovimientoProyectil->bShouldBounce = true;
	MovimientoProyectil->Bounciness = 1.0f;
	MovimientoProyectil->Friction = 0.0f;
	MovimientoProyectil->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 50.0f;
}

void AProjectileRebote::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(cambiar, this, &AProjectileRebote::cambiarMalla, 2.0f, false);
}

void AProjectileRebote::cambiarMalla()
{
	UStaticMesh* Mesh2 = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'"));

	if (Mesh2)
	{
		MeshProyectil->SetStaticMesh(Mesh2);
		MeshProyectil->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	}
}
