#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Laboratorio2.generated.h"

UCLASS()
class MYPROJECT_API ALaboratorio2 : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALaboratorio2();

	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<class APlataforma*> PlataformasEscenario;

	FTimerHandle TimerSpawneo;

	void SpawnPlataformasAreas();
};