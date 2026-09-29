// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubo.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACubo::ACubo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPrueba"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MeshAsset.Succeeded()) Mesh->SetStaticMesh(MeshAsset.Object);
	Mesh->SetupAttachment(SceneComponent);
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -50.f));

}

// Called when the game starts or when spawned
void ACubo::BeginPlay()
{
	Super::BeginPlay();
	posicionInicialY = GetActorLocation() + FVector(0.0f, 220.0f, 0.0f);
	posicionActualY = posicionInicialY;
	posicionFinalY = GetActorLocation() + FVector(0.0f, -480.0f, 0.0f);
	incremento = 2.0f;
	moverse = true;
}

// Called every frame
void ACubo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubo::mensaje()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Cubo llamandose")));
}

int ACubo::sumar(int a, int b, int c)
{
	return a+b+c;
}

float ACubo::sumar(float a, float b)
{
	return a+b;
}

void ACubo::movimientoY()
{
	if (GetMoverseY()) {
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
