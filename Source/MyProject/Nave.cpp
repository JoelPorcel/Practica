// Fill out your copyright notice in the Description page of Project Settings.


#include "Nave.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ANave::ANave()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPrueba"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Architecture/Wall_500x500.Wall_500x500'"));
	if (MeshAsset.Succeeded()) Mesh->SetStaticMesh(MeshAsset.Object);
	SetRootComponent(Mesh);
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Mesh);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	ComponenteMovimiento = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovimientoNave"));
	ComponenteMovimiento->MaxSpeed = 2000.f;
	
}

// Called when the game starts or when spawned
void ANave::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANave::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoverAdelante", this, &ANave::MoverAdelante);
	PlayerInputComponent->BindAxis("MoverDerecha", this, &ANave::MoverDerecha);
	PlayerInputComponent->BindAxis("MoverAtras", this, &ANave::MoverAtras);
	PlayerInputComponent->BindAxis("MoverIzquierda", this, &ANave::MoverIzquierda);
}

void ANave::MoverAdelante(float Valor)
{
	AddMovementInput(GetActorForwardVector(), Valor);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Valor mover recto: %f"), Valor));
}

void ANave::MoverDerecha(float Valor)
{
	AddMovementInput(GetActorRightVector(), Valor);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Valor mover derecha: %f"), Valor));
}

void ANave::MoverAtras(float valor)
{
	AddMovementInput(GetActorForwardVector(), valor);
}

void ANave::MoverIzquierda(float Valor)
{
	AddMovementInput(GetActorRightVector(), Valor);
}

