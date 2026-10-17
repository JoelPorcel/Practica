// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AEnemigo::AEnemigo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPrueba"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Architecture/Pillar_50x500.Pillar_50x500'"));
	if (MeshAsset.Succeeded()) Mesh->SetStaticMesh(MeshAsset.Object);
	SetRootComponent(Mesh);
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1"));
	cam->SetupAttachment(Mesh);
	

}

// Called when the game starts or when spawned
void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
	posicionInicialY = GetActorLocation() + FVector(0.0f, 220.0f, 0.0f);
	posicionActualY = posicionInicialY;
	posicionFinalY = GetActorLocation() + FVector(0.0f, -480.0f, 0.0f);
	incremento = 7.0f;
	moverse = true;
	y = true;
	
}

// Called every frame
void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	moverY();

}

void AEnemigo::moverY()
{
	if (GetMoverseY()) {
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("moviendose %i"), n));
		n++;
		if (moverse)
		{
			if (posicionActualY.Y > posicionFinalY.Y) posicionActualY.Y -= incremento;
			else moverse = false;
		}
		else
		{
			if (posicionActualY.Y < posicionInicialY.Y) posicionActualY.Y += incremento;
			else moverse = true;
		}

		SetActorLocation(posicionActualY);
	}
}

