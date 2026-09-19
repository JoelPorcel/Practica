#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileRebote.generated.h"

UCLASS()
class MYPROJECT_API AProjectileRebote : public AActor
{
	GENERATED_BODY()

public:
	AProjectileRebote();

	virtual void BeginPlay() override;
	FTimerHandle cambiar;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* ColisionEsfera;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshProyectil;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* MovimientoProyectil;

	void cambiarMalla();
};