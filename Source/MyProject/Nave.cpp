// Fill out your copyright notice in the Description page of Project Settings.


#include "Nave.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Cubo.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "ProjectileRebote.h"

// Sets default values
ANave::ANave()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPrueba"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/MyStuff/ObjetoPrueba.ObjetoPrueba'"));
	if (MeshAsset.Succeeded()) Mesh->SetStaticMesh(MeshAsset.Object);
	SetRootComponent(Mesh);
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Mesh);
	Box->SetCollisionProfileName(TEXT("Trigger"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0, 0, 149));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	ComponenteMovimiento = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovimientoNave"));
	ComponenteMovimiento->MaxSpeed = 2000.f;
}

// Called when the game starts or when spawned
void ANave::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ANave::OnOverlapBegin);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Nave creada")));
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
	PlayerInputComponent->BindAxis("MirarDerecha", this, &APawn::AddControllerYawInput);


	PlayerInputComponent->BindAxis("MirarArriba", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Disparar", IE_Pressed, this, &ANave::Disparar);
	PlayerInputComponent->BindAction("DispararRebote", IE_Pressed, this, &ANave::DispararPelota);
}

void ANave::MoverAdelante(float Valor)
{
	AddMovementInput(GetActorForwardVector(), Valor);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Valor mover recto: %f"), Valor));
}

void ANave::MoverDerecha(float Valor)
{
	AddMovementInput(GetActorRightVector(), Valor);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Valor mover derecha: %f"), Valor));
}

void ANave::MoverAtras(float valor)
{
	AddMovementInput(GetActorForwardVector(), valor);
}

void ANave::MoverIzquierda(float Valor)
{
	AddMovementInput(GetActorRightVector(), Valor);
}

void ANave::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OthyerBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Begin entrando")));
	if (OtherActor) {
		ACubo* cubo = Cast<ACubo>(OtherActor);
		if (cubo) {
			cubo->mensaje();
		}
	}
}

void ANave::Disparar()
{
	if (GetWorld())
	{
		FVector PosicionSpawn = GetActorLocation() + (GetActorForwardVector() * 150.0f);

		FRotator RotacionSpawn = GetActorRotation();

		AProjectile* BalaGenerada = GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), PosicionSpawn, RotacionSpawn);

		if (BalaGenerada)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("¡Pew Pew!"));
		}
	}
}

void ANave::DispararPelota()
{
	if (GetWorld())
	{
		FVector PosicionSpawn = GetActorLocation() + (GetActorForwardVector() * 150.0f);
		FRotator RotacionSpawn = GetActorRotation();

		GetWorld()->SpawnActor<AProjectileRebote>(AProjectileRebote::StaticClass(), PosicionSpawn, RotacionSpawn);
	}
}