// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Nave.generated.h"

UCLASS()
class MYPROJECT_API ANave : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANave();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* ComponenteMovimiento;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoverAdelante(float Valor);
	void MoverDerecha(float Valor);

	void MoverAtras(float valor);
	void MoverIzquierda(float Valor);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OthyerBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void Disparar();

	void DispararPelota();
};
