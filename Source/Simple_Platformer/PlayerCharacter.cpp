// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Spring arm component for the player camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmSetup(SpringArm);
	SpringArm -> SetupAttachment(GetMesh());

	//Camera component for the player
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera -> SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent -> BindAxis("MoveBackward", this, &APlayerCharacter::MoveBackward);
	// PlayerInputComponent -> BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	// PlayerInputComponent -> BindAction("Jump", IE_Released, this, &APlayerCharacter::OnJumpEnd);
	// PlayerInputComponent -> BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	// PlayerInputComponent -> BindAxis("MoveLeft", this, &APlayerCharacter::MoveLeft);
}

void APlayerCharacter::SpringArmSetup(USpringArmComponent* SpringArmComp) 
{
	SpringArmComp -> bEnableCameraLag = true;
	SpringArmComp -> bInheritPitch = false;
	SpringArmComp -> bInheritRoll = false;
	SpringArmComp -> bInheritYaw = false;
	SpringArmComp -> TargetArmLength = 600.0f;
}

void APlayerCharacter::MoveForward(float AxisValue) 
{
	if(Controller != nullptr && AxisValue != 0.0f){
		const FRotator ControllerRotation = Controller -> GetControlRotation();
		const FRotator YawRotation(0, ControllerRotation.Yaw, 0);
		const FVector NewDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(NewDirection, AxisValue);
	}

}

void APlayerCharacter::MoveBackward(float AxisValue) 
{
	if(Controller != nullptr && AxisValue != 0.0f)
	{
		const FRotator ControllerRotation = Controller -> GetControlRotation();
		const FRotator YawRotation(0, -ControllerRotation.Yaw, 0);
		const FVector NewDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(NewDirection, AxisValue);
	}
}

// void APlayerCharacter::Jump() 
// {
	
// }

// void APlayerCharacter::OnJumpStart() 
// {
// 	UE_LOG(LogTemp, Warning, TEXT("JUMP STARTED"));

// }

// void APlayerCharacter::OnJumpEnd() 
// {
// 	UE_LOG(LogTemp, Warning, TEXT("JUMP ENDED"));
// }

// void APlayerCharacter::MoveRight(float AxisValue) 
// {
// 	if((Controller != nullptr) && (AxisValue != 0.0f)){
// 		const FRotator Rotation = Controller -> GetControlRotation();
// 		const FRotator YawRotation(0, Rotation.Yaw, 0);
// 		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
// 		AddMovementInput(Direction, AxisValue);
// 	}
// }

//
// }

