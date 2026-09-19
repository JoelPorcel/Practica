#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MYPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* ColisionEsfera;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshProyectil;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* MovimientoProyectil;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};