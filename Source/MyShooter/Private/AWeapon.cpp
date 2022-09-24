// Fill out your copyright notice in the Description page of Project Settings.


#include "AWeapon.h"
#include "Components/BoxComponent.h"
#include "ProjectileBulletActor.h"


// Sets default values
AAWeapon::AAWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("AWeapon constructor"));

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = CollisionComp;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(CollisionComp);
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Game/Geometry/Meshes/1M_Cube"));
	//UStaticMesh* Asset = MeshRef.Object;
	//VisualMesh->SetStaticMesh(Asset);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	MuzzleLocation->SetupAttachment(VisualMesh);
	MuzzleLocation->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));

}

//UBoxComponent* AAWeapon::GetCollisionComp()
//{
//	return CollisionComp;
//}
//
UStaticMeshComponent* AAWeapon::GetVisualMesh()
{
	return VisualMesh;
}

USceneComponent* AAWeapon::GetMuzzleLocation()
{
	return MuzzleLocation;
}

void AAWeapon::SpawnActor(FVector Loc, FRotator Rot)
{
	UWorld* const World = GetWorld();

	FActorSpawnParameters ActorSpawnParams;
	//ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UE_LOG(LogTemp, Warning, TEXT("Spawning a projectile"));

	AProjectileBulletActor* SpawnedActorRef = World->SpawnActor<AProjectileBulletActor>(ProjectileToSpawn, Loc, Rot, ActorSpawnParams);

	UE_LOG(LogTemp, Warning, TEXT("Spawned a projectile"));
}

void AAWeapon::OnFire()
{
	UE_LOG(LogTemp, Warning, TEXT("OnFire started"));

	FRotator Rot((0.0f, 0.0f, 0.0f));
	FVector Loc = GetActorLocation() + (0.0f, 50.0f, 0.0f);
	SpawnActor(Loc, Rot);

	UE_LOG(LogTemp, Warning, TEXT("OnFire end"));
}

// Called when the game starts or when spawned
void AAWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	//OnFire();

}

// Called every frame
void AAWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

