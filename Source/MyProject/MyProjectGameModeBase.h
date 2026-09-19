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
};