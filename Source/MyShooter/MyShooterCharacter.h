// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyShooterCharacter.generated.h"

class AProjectileBulletActor;
class AWweapon;


//Character, which we will control

UCLASS(config=Game)
class AMyShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AMyShooterCharacter();

	/*UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USkeletalMeshComponent* Mesh;*/

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))

		class UCameraComponent* FollowCamera;

protected:

	virtual void BeginPlay() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void Jump();

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);


protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPlayerHasWeapon;

	UFUNCTION()
	void FireWeapon();

	UFUNCTION()
		void Interact();

	UFUNCTION()
		void DropWeapon();

	UFUNCTION()
		void SpawnWeapon();

	UFUNCTION(BlueprintCallable)
		int GetAmmoLoaded();

	UFUNCTION(BlueprintCallable)
		int GetAmmoReserve();

	UFUNCTION()
		void ReloadWeapon();

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWeapon> WeaponClass;

	class AWeapon* Weapon;


};

