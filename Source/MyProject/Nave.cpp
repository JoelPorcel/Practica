#include "Nave.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Cubo.h"
#include "Projectile.h"
#include "ProjectileRebote.h"
#include "Moneda.h"
#include "Decorator/Decorator.h"
#include "Decorator/NaveDefault.h"
#include "Decorator/BaseDecorator.h"
#include "Decorator/DecoradorVelocidad.h"
#include "Decorator/DecoradorDano.h"
#include "Decorator/DecoradorEscudo.h"

ANave::ANave()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPrueba"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO'"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
	SetRootComponent(Mesh);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Mesh);
	Box->SetCollisionProfileName(TEXT("Trigger"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 149.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	ComponenteMovimiento = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovimientoNave"));
	ComponenteMovimiento->MaxSpeed = 2000.0f;

	Configuracion = nullptr;
	IndiceDecorador = 0;
}

void ANave::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ANave::OnOverlapBegin);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Nave creada")));

	Configuracion = NewObject<UNaveDefault>(this);
	IndiceDecorador = 0;

	GetWorldTimerManager().SetTimer(TimerDecorador, this, &ANave::AplicarDecorador, 10.0f, true);
}

void ANave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

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
	if (Valor != 0.0f)
	{
		const FRotator RotacionYaw(0.0f, GetControlRotation().Yaw, 0.0f);
		AddMovementInput(FRotationMatrix(RotacionYaw).GetUnitAxis(EAxis::X), Valor);
	}
}

void ANave::MoverDerecha(float Valor)
{
	if (Valor != 0.0f)
	{
		const FRotator RotacionYaw(0.0f, GetControlRotation().Yaw, 0.0f);
		AddMovementInput(FRotationMatrix(RotacionYaw).GetUnitAxis(EAxis::Y), Valor);
	}
}

void ANave::MoverAtras(float valor)
{
	MoverAdelante(valor);
}

void ANave::MoverIzquierda(float Valor)
{
	MoverDerecha(Valor);
}

void ANave::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OthyerBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Begin entrando")));
	if (OtherActor)
	{
		if (AMoneda* moneda = Cast<AMoneda>(OtherActor))
		{
			monedas++;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Monedas: %d"), monedas));
		}
	}
}

void ANave::Disparar()
{
	const FVector PosicionSpawn = GetActorLocation() + (GetActorForwardVector() * 150.0f);
	const FRotator RotacionSpawn = GetActorRotation();

	if (AProjectile* BalaGenerada = GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), PosicionSpawn, RotacionSpawn))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Pew Pew!"));
	}
}

void ANave::DispararPelota()
{
	const FVector PosicionSpawn = GetActorLocation() + (GetActorForwardVector() * 150.0f);
	const FRotator RotacionSpawn = GetActorRotation();

	GetWorld()->SpawnActor<AProjectileRebote>(AProjectileRebote::StaticClass(), PosicionSpawn, RotacionSpawn);
}

void ANave::AplicarDecorador()
{
	UBaseDecorator* Nuevo = nullptr;
	if (IndiceDecorador == 0) Nuevo = NewObject<UDecoradorVelocidad>(this);
	else if (IndiceDecorador == 1) Nuevo = NewObject<UDecoradorDano>(this);
	else Nuevo = NewObject<UDecoradorEscudo>(this);
	IndiceDecorador += 1;

	Nuevo->SetComponente(Configuracion);
	Configuracion = Nuevo;

	ComponenteMovimiento->MaxSpeed = Configuracion->GetVelocidad();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Nave: %s"), *Configuracion->GetDescripcion()));

	FTimerHandle TimerExpiracion;
	GetWorldTimerManager().SetTimer(TimerExpiracion, this, &ANave::QuitarDecorador, 15.0f, false);
}

void ANave::QuitarDecorador()
{
	if (Configuracion && Configuracion->GetComponente())
	{
		Configuracion = Configuracion->GetComponente();
		ComponenteMovimiento->MaxSpeed = Configuracion->GetVelocidad();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Nave: %s"), *Configuracion->GetDescripcion()));
	}
}
