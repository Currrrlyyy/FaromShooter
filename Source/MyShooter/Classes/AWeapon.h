// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AWeapon.generated.h"

class UBoxComponent;
class AProjectileBulletActor;

UCLASS()
class MYSHOOTER_API AAWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAWeapon();

	//UBoxComponent* GetCollisionComp();

	UStaticMeshComponent* GetVisualMesh();

	USceneComponent* GetMuzzleLocation();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<AProjectileBulletActor> ProjectileToSpawn; 

private:

	UPROPERTY(VisibleDefaultsOnly, Category = "Gun")
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleDefaultsOnly, Category="Gun")
		UBoxComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Gun")
		USceneComponent* MuzzleLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnFire();

	void SpawnActor(FVector Loc, FRotator Rot);

};
