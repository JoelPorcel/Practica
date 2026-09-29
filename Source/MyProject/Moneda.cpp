// Fill out your copyright notice in the Description page of Project Settings.


#include "Moneda.h"
#include "Components/StaticMeshComponent.h"
#include "Nave.h"

// Sets default values
AMoneda::AMoneda()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshMoneda = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshMoneda"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/MyStuff/PlataformaDestruc.PlataformaDestruc'"));
	if (MeshAsset.Succeeded()) MeshMoneda->SetStaticMesh(MeshAsset.Object);
	MeshMoneda->SetCollisionProfileName(TEXT("Trigger"));
	SetRootComponent(MeshMoneda);
}

// Called when the game starts or when spawned
void AMoneda::BeginPlay()
{
	Super::BeginPlay();
	MeshMoneda->OnComponentBeginOverlap.AddDynamic(this, &AMoneda::OnOverlapBegin);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Moneda creada")));
}

// Called every frame
void AMoneda::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMoneda::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OthyerBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherActor->IsA(ANave::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Moneda recogida"));
		this->Destroy();
	}
}