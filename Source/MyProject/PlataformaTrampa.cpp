// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaTrampa.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlataformaTrampa::APlataformaTrampa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/MyStuff/Plataforma.Plataforma'"));
	if (MeshAsset.Succeeded()) MeshPlataforma->SetStaticMesh(MeshAsset.Object);

}

// Called when the game starts or when spawned
void APlataformaTrampa::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlataformaTrampa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

