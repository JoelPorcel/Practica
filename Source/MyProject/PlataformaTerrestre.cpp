// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaTerrestre.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlataformaTerrestre::APlataformaTerrestre()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/MyStuff/PlataformaTerreste.PlataformaTerreste'"));
	if (MeshAsset.Succeeded()) MeshPlataforma->SetStaticMesh(MeshAsset.Object);
	MeshPlataforma->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void APlataformaTerrestre::BeginPlay()
{
	Super::BeginPlay();
	MeshPlataforma->OnComponentEndOverlap.AddDynamic(this, &APlataformaTerrestre::OnOverlapEnd);
}

// Called every frame
void APlataformaTerrestre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APlataformaTerrestre::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Un objeto de tipo %s colisiono con End en Trigger"), *OtherActor->GetName()));
}

