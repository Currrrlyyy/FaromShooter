// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBulletActor.generated.h"

// Projectile, which plays a role of bullet

UCLASS()
class MYSHOOTER_API AProjectileBulletActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AProjectileBulletActor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy() override;

public:

	class USphereComponent* GetCollisionComponent() const;
	class UProjectileMovementComponent* GetProjectileMovement() const;

private:

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Bullet")
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly , Category = "BulletSpeed", meta = (AllowPrivateAccess = true))
		float BulletInitialSpeed = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "BulletSpeed", meta = (AllowPrivateAccess = true))
		float BulletMaxSpeed = 1000.0f;

};
