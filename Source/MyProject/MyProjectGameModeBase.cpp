#include "MyProjectGameModeBase.h"
#include "Nave.h"
#include "Plataforma.h"
#include "PlataformaAerea.h"
#include "PlataformaIndestructible.h"
#include "PlataformaLigera.h"
#include "PlataformaTerrestre.h"
#include "PlataformaTrampa.h"
#include "Kismet/GameplayStatics.h"
#include "PlataformaDestructible.h"
#include "Cubo.h"

AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = ANave::StaticClass();
}

void AMyProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//AparecerPlataformas();
	GetWorld()->SpawnActor<APlataformaAerea>(FVector(99,277, 246), FRotator::ZeroRotator);
	GetWorld()->SpawnActor<APlataformaDestructible>(FVector(99, 632, 246), FRotator::ZeroRotator);
	GetWorld()->SpawnActor<APlataformaIndestructible>(FVector(99, 984, 246), FRotator::ZeroRotator);
	GetWorld()->SpawnActor<APlataformaTerrestre>(FVector(99, 1300, 246), FRotator::ZeroRotator);

	ACubo *c = GetWorld()->SpawnActor<ACubo>(FVector(99, 277, 600), FRotator::ZeroRotator);
	c->sumar(1, 2, 3);
	c->sumar(1.5f, 2.5f);
}

void AMyProjectGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyProjectGameModeBase::AparecerPlataformas()
{
	for (int32 i = 0; i < 200; i++)
	{
		float RandX = FMath::RandRange(Limites1.X, Limites2.X);
		float RandY = FMath::RandRange(Limites1.Y, Limites2.Y);
		float RandZ = FMath::RandRange(Limites1.Z, Limites2.Z);
		FVector LocacionRandom(RandX, RandY, RandZ);

		APlataforma* NuevaPlataforma = nullptr;
		int random = FMath::RandRange(0, 4);

		switch (random)
		{
		case 0:
			NuevaPlataforma = GetWorld()->SpawnActor<APlataformaAerea>(LocacionRandom, FRotator::ZeroRotator);
			break;
		case 1:
			NuevaPlataforma = GetWorld()->SpawnActor<APlataformaIndestructible>(LocacionRandom, FRotator::ZeroRotator);
			break;
		case 2:
			NuevaPlataforma = GetWorld()->SpawnActor<APlataformaLigera>(LocacionRandom, FRotator::ZeroRotator);
			break;
		case 3:
			NuevaPlataforma = GetWorld()->SpawnActor<APlataformaTerrestre>(LocacionRandom, FRotator::ZeroRotator);
			break;
		case 4:
			NuevaPlataforma = GetWorld()->SpawnActor<APlataformaTrampa>(LocacionRandom, FRotator::ZeroRotator);
			break;
		}

		if (NuevaPlataforma) plataformas.Add(NuevaPlataforma);
	}

	GetWorldTimerManager().SetTimer(ControlEventos, this, &AMyProjectGameModeBase::IniciarMovimientos, 1.0f, false);
}

void AMyProjectGameModeBase::IniciarMovimientos()
{
	for (int32 i = 0; i < plataformas.Num(); i++)
	{
		APlataforma* Plat = plataformas[i];
		if (!Plat) continue;

		int32 TipoMovimiento = i % 10;
		FVector Direccion;

		switch (TipoMovimiento) {
		case 0: Direccion = FVector(1, 0, 0); break;
		case 1: Direccion = FVector(0, 1, 0); break;
		case 2: Direccion = FVector(0, 0, 1); break;
		case 3: Direccion = FVector(1, 1, 0); break;
		case 4: Direccion = FVector(1, -1, 0); break;
		case 5: Direccion = FVector(1, 0, 1); break;
		case 6: Direccion = FVector(1, 0, -1); break;
		case 7: Direccion = FVector(0, 1, 1); break;
		case 8: Direccion = FVector(0, 1, -1); break;
		case 9: Direccion = FVector(1, 1, 1); break;
		}

		Plat->DistanciaMover = FMath::RandRange(300.f, 1500.f);
		float RapidezAleatoria = FMath::RandRange(150.f, 400.f);
		Plat->VelocidadPlataforma = Direccion.GetSafeNormal() * RapidezAleatoria;
	}

	GetWorldTimerManager().SetTimer(ControlEventos, this, &AMyProjectGameModeBase::DesaparecerPlataformas, 10.0f, false);
}

void AMyProjectGameModeBase::DesaparecerPlataformas()
{
	for (APlataforma* Plat : plataformas)
	{
		if (Plat && Plat->MeshPlataforma)
		{
			Plat->MeshPlataforma->SetVisibility(false);
		}
	}

	GetWorldTimerManager().SetTimer(ControlEventos, this, &AMyProjectGameModeBase::DetenerMovimientos, 5.0f, false);
}

void AMyProjectGameModeBase::DetenerMovimientos()
{
	for (APlataforma* Plat : plataformas)
	{
		if (Plat)
		{
			if (Plat->MeshPlataforma)
			{
				Plat->MeshPlataforma->SetVisibility(true);
			}
			Plat->VelocidadPlataforma = FVector::ZeroVector;
		}
	}
	GetWorldTimerManager().SetTimer(ControlEventos, this, &AMyProjectGameModeBase::ReiniciarMovimiento, 4.0f, false);
}

void AMyProjectGameModeBase::ReiniciarMovimiento()
{
	GetWorldTimerManager().SetTimer(ControlEventos, this, &AMyProjectGameModeBase::IniciarMovimientos, 1.0f, false);
}

void AMyProjectGameModeBase::destruir()
{
	if (plataformas.Num() > 0)
	{
		int32 random = FMath::RandRange(0, plataformas.Num() - 1);
		APlataforma* p = plataformas[random];

		if (p) p->Destroy();

		plataformas.RemoveAt(random);
	}
}