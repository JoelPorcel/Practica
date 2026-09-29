#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameModeBase.generated.h"

UCLASS()
class MYPROJECT_API AMyProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProjectGameModeBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	class ANave* nave;

	FVector Limites1 = FVector((4045, 6433, 1128));
	FVector Limites2 = FVector((-9083, -3200, 10277));

	TArray<class APlataforma*> plataformas;

	FTimerHandle ControlEventos;
	FTimerHandle TimerDesaparicion;
	FTimerHandle TimerDestroy;

	void AparecerPlataformas();
	void IniciarMovimientos();
	void DesaparecerPlataformas();
	void DetenerMovimientos();
	void ReiniciarMovimiento();
	void destruir();

	FVector lim1 = FVector(1952.000000,-87.000000, 74.000000);
	FVector lim2 = FVector(261.000000,192.000000, 74.000000);
	FVector lim3 = FVector(-3550.000000, -2175.000000, 71.000000);
};