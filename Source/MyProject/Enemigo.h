// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo.generated.h"

UCLASS()
class MYPROJECT_API AEnemigo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemigo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UStaticMeshComponent* Mesh;

	UPROPERTY()
	class UCameraComponent* cam;

	FVector posicionInicialY;
	FVector posicionActualY;
	FVector posicionFinalY;
	bool y;
	int n = 0;
	float incremento;
	bool moverse;
	FORCEINLINE bool GetMoverseY() { return y; }
	FORCEINLINE void SetMoverseY(bool m = false) { y = m; }

	void moverY();
};
