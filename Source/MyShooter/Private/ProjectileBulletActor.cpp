// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBulletActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AProjectileBulletActor::AProjectileBulletActor()
{
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(4.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Bullet");
	//CollisionComp->OnComponentHit.AddDynamic(this, &AProjectileBulletActor::OnHit);
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f));
	CollisionComp->CanCharacterStepUpOn = ECB_Yes;

	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>
		(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = BulletInitialSpeed;
	ProjectileMovement->MaxSpeed = BulletMaxSpeed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	VisualMesh->SetupAttachment(RootComponent);

	InitialLifeSpan = 3.0f;
}

void AProjectileBulletActor::BeginPlay()
{

	Super::BeginPlay();	
	ProjectileMovement->InitialSpeed = BulletInitialSpeed;
	ProjectileMovement->MaxSpeed = BulletMaxSpeed;
}

void AProjectileBulletActor::Tick(float DeltaTime)
{
		Super::Tick(DeltaTime);
}
	
void AProjectileBulletActor::BeginDestroy()
{
	Super::BeginDestroy();
}

USphereComponent* AProjectileBulletActor::GetCollisionComponent() const
{
	return CollisionComp;
}

UProjectileMovementComponent* AProjectileBulletActor::GetProjectileMovement() const
{
	return ProjectileMovement;
}

