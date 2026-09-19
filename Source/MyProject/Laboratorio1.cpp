// Fill out your copyright notice in the Description page of Project Settings.


#include "Laboratorio1.h"
#include "PlataformaDestructible.h"
#include "PlataformaIndestructible.h"
#include "Nave.h"

ALaboratorio1::ALaboratorio1()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = ANave::StaticClass();
}

void ALaboratorio1::BeginPlay()
{
	Super::BeginPlay();

	int32 CantidadPlataformas = FMath::RandRange(5, 20);
	for (int32 i = 0; i < CantidadPlataformas; i++)
	{
		float RandX = FMath::RandRange(-2191.0f, 2215.0f);
		float RandY = FMath::RandRange(-532.0f, 568.0f);
		FVector LocacionRandom(RandX, RandY, 49.0f);

		int32 randomTipo = FMath::RandRange(0, 1);
		APlataforma* NuevaPlataforma = nullptr;
		FRotator Rotacion = FRotator(90,0, 0);

		if (randomTipo == 0) NuevaPlataforma = GetWorld()->SpawnActor<APlataformaDestructible>(LocacionRandom, Rotacion);
		else NuevaPlataforma = GetWorld()->SpawnActor<APlataformaIndestructible>(LocacionRandom, Rotacion);

		if (NuevaPlataforma) PlataformasEscenario.Add(NuevaPlataforma);
	}
}
