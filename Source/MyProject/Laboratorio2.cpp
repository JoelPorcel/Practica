#include "Laboratorio2.h"
#include "PlataformaDestructible.h"
#include "PlataformaIndestructible.h"
#include "Nave.h"

ALaboratorio2::ALaboratorio2()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = ANave::StaticClass();
}

void ALaboratorio2::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerSpawneo, this, &ALaboratorio2::SpawnPlataformasAreas, 5.0f, true);
}

void ALaboratorio2::SpawnPlataformasAreas()
{
	float LimitesAreasX[4] = { -2191.0f, -722.0f, 746.0f, 2215.0f };

	for (int32 i = 0; i < 3; i++)
	{
		float RandX = FMath::RandRange(LimitesAreasX[i], LimitesAreasX[i + 1]);
		float RandY = FMath::RandRange(-532.0f, 568.0f);
		float RandZ = FMath::RandRange(4, 78);
		FVector LocacionRandom(RandX, RandY, 49.0f);
		FRotator Rotacion = FRotator(90, 0, 0);

		int32 randomTipo = FMath::RandRange(0, 1);
		APlataforma* NuevaPlataforma;

		if (randomTipo == 0) NuevaPlataforma = GetWorld()->SpawnActor<APlataformaDestructible>(LocacionRandom, Rotacion);
		else NuevaPlataforma = GetWorld()->SpawnActor<APlataformaIndestructible>(LocacionRandom, Rotacion);

		if (NuevaPlataforma) PlataformasEscenario.Add(NuevaPlataforma);
	}
}