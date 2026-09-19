#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Laboratorio1.generated.h"

UCLASS()
class MYPROJECT_API ALaboratorio1 : public AGameModeBase
{
	GENERATED_BODY()

public:

	ALaboratorio1();

	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<class APlataforma*> PlataformasEscenario;
};