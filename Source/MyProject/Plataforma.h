// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plataforma.generated.h"
#define ECC_Nave ECC_GameTraceChannel1

UCLASS()
class MYPROJECT_API APlataforma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlataforma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshPlataforma;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	FVector VelocidadPlataforma = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
	float DistanciaMover = 100.0f;

	UPROPERTY(VisibleAnywhere)
	float DistanciaMovida = 0.0f;

	UPROPERTY(EditAnywhere)
	FRotator VelocidadRotacion;

	FVector LocacionInicial;

	void MoverPlataforma(float DeltaTime);
	void RotarPlataforma(float DeltaTime);

	FORCEINLINE float GetDistanciaMovida() const {
		return FVector::Dist(LocacionInicial, GetActorLocation());
	}

	virtual void mensaje();

};
