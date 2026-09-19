// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaIndestructible.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlataformaIndestructible::APlataformaIndestructible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/MyStuff/Plataformaindestruc.Plataformaindestruc'"));
	if (MeshAsset.Succeeded()) MeshPlataforma->SetStaticMesh(MeshAsset.Object);
}

// Called when the game starts or when spawned
void APlataformaIndestructible::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentEndOverlap.AddDynamic(this, &APlataformaIndestructible::OnOverlapEnd);
	
}

// Called every frame
void APlataformaIndestructible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlataformaIndestructible::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Un objeto de tipo %s colisiono con End"), *OtherActor->GetName()));
	}
}

