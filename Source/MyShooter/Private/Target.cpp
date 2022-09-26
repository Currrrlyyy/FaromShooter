// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/SphereComponent.h"
#include "ProjectileBulletActor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATarget::ATarget()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(100.0f);
	RootComponent = CollisionComp;
	Mesh->SetupAttachment(CollisionComp);


}

void ATarget::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentHit.AddDynamic(this, &ATarget::OnHit);

}

// Called every frame

