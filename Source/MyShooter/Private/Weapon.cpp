// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "ProjectileBulletActor.h"
#include "Components/BoxComponent.h"


AWeapon::AWeapon()
{

	VisualMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Comp"));
	RootComponent = VisualMesh;
	CollisionComp->SetupAttachment(RootComponent);
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	MuzzleLocation->SetupAttachment(RootComponent, FName("s_muzzle"));
	MuzzleLocation->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));

	MagazineCapacity = 20;
	AmmoLoaded = MagazineCapacity;
	AmmoReserve = 40;

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::SpawnActor(FVector Loc, FRotator Rot)
{
	UWorld* const World = GetWorld();

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AProjectileBulletActor* SpawnedActorRef = World->SpawnActor<AProjectileBulletActor>(ProjectileToSpawn, Loc, Rot, ActorSpawnParams);
}





