// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AMyProjectGameModeBase();

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	int vida = 5;

	FString nombre = TEXT("Juan");

	float altura = 5.75327f;

	class ANave* nave;
	
};
