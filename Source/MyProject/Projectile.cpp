#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile()
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

	// Configurar el Movimiento
	MovimientoProyectil = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovimientoProyectil"));
	MovimientoProyectil->UpdatedComponent = ColisionEsfera;
	MovimientoProyectil->InitialSpeed = 3000.f; 
	MovimientoProyectil->MaxSpeed = 3000.f;
	MovimientoProyectil->bRotationFollowsVelocity = true;
	MovimientoProyectil->bShouldBounce = false; 
	MovimientoProyectil->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 3.0f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ColisionEsfera->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Si choca contra algo que no sea él mismo, se destruye
	if (OtherActor && OtherActor != this)
	{
		Destroy();
	}
}