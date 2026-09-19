// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaLigera.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlataformaLigera::APlataformaLigera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/MyStuff/PlataformaLigera.PlataformaLigera'"));
	if (MeshAsset.Succeeded()) MeshPlataforma->SetStaticMesh(MeshAsset.Object);
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Box->SetActive(false);
	MeshPlataforma->SetCollisionProfileName(TEXT("BlockAll"));

}

// Called when the game starts or when spawned
void APlataformaLigera::BeginPlay()
{
	Super::BeginPlay();
	MeshPlataforma->OnComponentHit.AddDynamic(this, &APlataformaLigera::OnHit);
	
}

// Called every frame
void APlataformaLigera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlataformaLigera::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Un objeto de tipo %s colisiono con hit"), *OtherActor->GetName()));
	}
}

