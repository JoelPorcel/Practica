// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"
#include "Nave.h"

AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = ANave::StaticClass();
}

void AMyProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Game Started!"));
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("tu vida es %i, y tu altura es %.3f"), vida, altura));

}

void AMyProjectGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("llamada al tick"));
}
