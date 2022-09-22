// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBulletActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectileBulletActor::AProjectileBulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.5f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Bullet");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectileBulletActor::OnHit);
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_Yes;

	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>
		(TEXT("ProjectileComp"));

	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = BulletInitialSpeed;
	ProjectileMovement->MaxSpeed = BulletMaxSpeed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 5.0f;
}

void AProjectileBulletActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}

USphereComponent* AProjectileBulletActor::GetCollisionComponent() const
{
	return CollisionComp;
}

UProjectileMovementComponent* AProjectileBulletActor::GetProjectileMovement() const
{
	return ProjectileMovement;
}

