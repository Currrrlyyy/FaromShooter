// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBulletActor.generated.h"

UCLASS()
class MYSHOOTER_API AProjectileBulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBulletActor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
					UPrimitiveComponent* OtherComp, FVector NormalImpulse,
					const FHitResult& Hit);

	class USphereComponent* GetCollisionComponent() const;
	class UProjectileMovementComponent* GetProjectileMovement() const;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

private:

	UPROPERTY(VisibleDefaultsOnly, Category = "Bullet")
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly , Category = "BulletSpeed", meta = (AllowPrivateAccess = true))
		float BulletInitialSpeed = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "BulletSpeed", meta = (AllowPrivateAccess = true))
		float BulletMaxSpeed = 1000.0f;

	bool bHasTickedAlready;

};
