// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SIMPLE_PLATFORMER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

private:

	// Character components
		UPROPERTY(VisibleAnywhere)
			USpringArmComponent* SpringArm;

		UPROPERTY(VisibleAnywhere)
			UCameraComponent* PlayerCamera;

		void SpringArmSetup(USpringArmComponent* SpringArmComp);

		UCapsuleComponent* TriggerCapsule;
	//

	int32 ItemCollection;

	// Restart level function
		// void OnRestart();
		
		// FTimerHandle RestartTimer;

		// void LevelRestart();
	//

	// Movement
		// Walk			
			UFUNCTION()
			void MoveForward(float AxisValue);

			UFUNCTION()
			void MoveBackward(float AxisValue);
		//
		// Jump
			UFUNCTION()
			void JumpInput();

			UPROPERTY(EditAnywhere)
			bool IsJumping;
		//
	//
};
