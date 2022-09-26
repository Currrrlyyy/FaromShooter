// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UBoxComponent;
class AProjectileBulletActor;

// Weapon class

UCLASS()
class MYSHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	AWeapon();

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun")
		int MagazineCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun")
		int AmmoReserve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun")
		int AmmoLoaded;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* ReloadSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* EmptyMagSound;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<AProjectileBulletActor> ProjectileToSpawn;

	UPROPERTY(EditAnywhere, Category = "Gun")
		class USkeletalMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere, Category = "Gun")
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Gun")
		class USceneComponent* MuzzleLocation;

	UFUNCTION()
		void SpawnActor(FVector Loc, FRotator Rot);

};
