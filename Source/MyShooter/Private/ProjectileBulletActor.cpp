// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBulletActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectileBulletActor::AProjectileBulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	UE_LOG(LogTemp, Warning, TEXT("Projectile Constructor"));

	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.5f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Bullet");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectileBulletActor::OnHit);
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	RootComponent = CollisionComp;
	VisualMesh->SetupAttachment(RootComponent);

	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>
		(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = BulletInitialSpeed;
	ProjectileMovement->MaxSpeed = BulletMaxSpeed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 5.0f;
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("Projectile::Constructor"));

}

void AProjectileBulletActor::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile BeginPlay"));

	Super::BeginPlay();	
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("Projectile::BeginPlay"));
	bHasTickedAlready = false;


	
	
}

void AProjectileBulletActor::Tick(float DeltaTime)
{
	if (bHasTickedAlready == false)
	{
		bHasTickedAlready = true;
		Super::Tick(DeltaTime);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("bHasTickedAlready = true"));

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("Projectile::Tick"));
	}
	FVector GetActorPos = GetActorLocation();
	/*UE_LOG(LogTemp, Warning, TEXT("X: %f"), GetActorPos.X);
	UE_LOG(LogTemp, Warning, TEXT("Y: %f"), GetActorPos.Y);
	UE_LOG(LogTemp, Warning, TEXT("Z: %f"), GetActorPos.Z);*/


}

void AProjectileBulletActor::BeginDestroy()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("Projectile::BeginDestroy"));

	Super::BeginDestroy();

}

void AProjectileBulletActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit start"));
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		OtherComp->AddImpulseAtLocation(( GetVelocity() * -10.0f), GetActorLocation());
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Bullet was destroyed"));
	}
	UE_LOG(LogTemp, Warning, TEXT("OnHit end"));

}

USphereComponent* AProjectileBulletActor::GetCollisionComponent() const
{
	return CollisionComp;
}

UProjectileMovementComponent* AProjectileBulletActor::GetProjectileMovement() const
{
	return ProjectileMovement;
}

