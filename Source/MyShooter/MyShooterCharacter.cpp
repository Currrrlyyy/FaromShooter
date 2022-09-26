// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyShooterCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ProjectileBulletActor.h"
#include "Weapon.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AMyShooterCharacter 

AMyShooterCharacter::AMyShooterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void AMyShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	bIsAiming = false;
	bPlayerHasWeapon = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyShooterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyShooterCharacter::FireWeapon);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyShooterCharacter::Interact);
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMyShooterCharacter::DropWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyShooterCharacter::ReloadWeapon);



	PlayerInputComponent->BindAxis("MoveForward", this, &AMyShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyShooterCharacter::MoveRight);


	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyShooterCharacter::LookUpAtRate);
}

void AMyShooterCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyShooterCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMyShooterCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyShooterCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMyShooterCharacter::Jump()
{
	if (!bIsAiming)
	{
		Super::Jump();
	}
}


void AMyShooterCharacter::Interact()
{
	FVector Start = GetMesh()->GetSocketLocation(FName("headSocket"));

	FVector End = Start + FollowCamera->GetComponentRotation().Vector() * 2000.0f;
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Pawn, Params))
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (Cast<AWeapon>(HitActor))
			{
				if (bPlayerHasWeapon)
				{
					DropWeapon();
				}
				HitActor->Destroy();
				SpawnWeapon();
			}
		}
	}
}

void AMyShooterCharacter::DropWeapon()
{
	if (bPlayerHasWeapon)
	{
		bIsAiming = false;
		if (Weapon)
		{
			Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Weapon->VisualMesh->SetSimulatePhysics(true);
			Weapon->VisualMesh->SetCollisionProfileName(FName("Pawn"));
			bPlayerHasWeapon = false;
		}
	}
}

void AMyShooterCharacter::SpawnWeapon()
{
	if (WeaponClass)
	{
		FTransform WeaponTransform;
		WeaponTransform.SetLocation(FVector::ZeroVector);
		WeaponTransform.SetRotation(FQuat(FRotator::ZeroRotator));

		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, WeaponTransform, SpawnParams);
		Weapon->VisualMesh->SetSimulatePhysics(false);
		Weapon->VisualMesh->SetCollisionProfileName(FName("NoCollision"));


		if (Weapon)
		{
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("s_hand_r"));

			bPlayerHasWeapon = true;
		}
	}
}

int AMyShooterCharacter::GetAmmoLoaded()
{
	return Weapon->AmmoLoaded;
}

int AMyShooterCharacter::GetAmmoReserve()
{
	return Weapon->AmmoReserve;
}

void AMyShooterCharacter::FireWeapon()
{
	if (bIsAiming && bPlayerHasWeapon)
	{
		if (Weapon->AmmoLoaded < 0)
		{
			Weapon->AmmoLoaded = 0;
		}

		if (Weapon->AmmoReserve < 0)
		{
			Weapon->AmmoReserve = 0;
		}

		if (Weapon->AmmoLoaded == 0)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Weapon->EmptyMagSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
			return;
		}

		FRotator BulletRotation = FollowCamera->GetComponentRotation();
		FVector BulletLocation = (Weapon->MuzzleLocation->GetSocketLocation(FName("s_muzzle")));
		Weapon->SpawnActor(BulletLocation, BulletRotation);
		
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Weapon->FireSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
		--(Weapon->AmmoLoaded);
	}
}

void AMyShooterCharacter::ReloadWeapon()
{
	if (!bPlayerHasWeapon)
	{
		return;
	}

	if ((Weapon->AmmoLoaded == Weapon->MagazineCapacity) || (Weapon->AmmoReserve == 0))
	{
		return;
	}


	if ((Weapon->AmmoLoaded > 0)  && (Weapon->AmmoLoaded < Weapon->MagazineCapacity))
	{
			if (Weapon->AmmoReserve + Weapon->AmmoLoaded <= Weapon->MagazineCapacity)
			{				
				Weapon->AmmoLoaded += Weapon->AmmoReserve;
				Weapon->AmmoReserve = 0;
			}
			else
			{
				Weapon->AmmoReserve -= (Weapon->MagazineCapacity - Weapon->AmmoLoaded);
				Weapon->AmmoLoaded = Weapon->MagazineCapacity;
			}
	}
	else
	{
		Weapon->AmmoReserve -= Weapon->MagazineCapacity;
		Weapon->AmmoLoaded = Weapon->MagazineCapacity;
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Weapon->ReloadSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);

	
}


