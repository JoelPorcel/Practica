// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cubo.generated.h"

UCLASS()
class MYPROJECT_API ACubo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class USceneComponent* SceneComponent;

	FVector posicionInicialY;
	FVector posicionActualY;
	FVector posicionFinalY;
	bool y;
	float incremento;
	bool moverse;
	//void movimientoY();
	FORCEINLINE bool GetMoverseY() { return y; }
	FORCEINLINE void SetMoverseY(bool m = false) { y = m; }

	void mensaje();

	int sumar(int a, int b, int c);
	float sumar(float a, float b);
};
