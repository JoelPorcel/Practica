#include "PlataformaDestructible.h"
#include "Components/StaticMeshComponent.h"
#include "ProjectileRebote.h"
#include "Components/BoxComponent.h"
#include "Nave.h"

APlataformaDestructible::APlataformaDestructible()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/MyStuff/PlataformaDestruc.PlataformaDestruc'"));
	if (MeshAsset.Succeeded()) MeshPlataforma->SetStaticMesh(MeshAsset.Object);
	MeshPlataforma->SetCollisionProfileName(TEXT("BlockAll"));
}

void APlataformaDestructible::BeginPlay()
{
	Super::BeginPlay();
	MeshPlataforma->OnComponentHit.AddDynamic(this, &APlataformaDestructible::OnHit);
}

void APlataformaDestructible::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Un objeto de tipo %s colisiono con la plataforma destructible"), *OtherActor->GetName()));
	if (OtherActor && OtherActor->IsA(AProjectileRebote::StaticClass()))
	{
		this->Destroy();
	}

	/*if (OtherActor && OtherActor->IsA(ANave::StaticClass())) {
		OtherActor->Destroy();
	}*/
}