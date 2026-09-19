// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaAerea.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlataformaAerea::APlataformaAerea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/MyStuff/PlataformaAe.PlataformaAe'"));
	if (MeshAsset.Succeeded()) MeshPlataforma->SetStaticMesh(MeshAsset.Object);
}

// Called when the game starts or when spawned
void APlataformaAerea::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &APlataformaAerea::OnOverlapBegin);
	
}

// Called every frame
void APlataformaAerea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlataformaAerea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OthyerBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Un objeto de tipo %s colisiono con Begin"), *OtherActor->GetName()));
	}
}

