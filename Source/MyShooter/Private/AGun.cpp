// Fill out your copyright notice in the Description page of Project Settings.


#include "AGun.h"

// Sets default values for this component's properties
UAGun::UAGun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAGun::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

