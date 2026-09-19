// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plataforma.h"
#include "PlataformaLigera.generated.h"

UCLASS()
class MYPROJECT_API APlataformaLigera : public APlataforma
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlataformaLigera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, 
				AActor* OtherActor, 
				UPrimitiveComponent* OtherComp, 
				FVector NormalImpulse, 
				const FHitResult& Hit);

};
