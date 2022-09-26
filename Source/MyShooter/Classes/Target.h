// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

class AProjectileBulletActor;

UCLASS()
class MYSHOOTER_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Bullet")
		class USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* HitSound;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
