// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
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

	// Capsule component used as a trigger-capsule for collecting items (on overlap with them)
	TriggerCapsule = GetCapsuleComponent();
	// TriggerCapsule -> OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::BeginOverlap);	

	IsJumping = false;

	ItemCollection = 0;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Capsule overlap with items
	TriggerCapsule -> OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::BeginOverlap);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsJumping)
	{
		Jump();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent -> BindAxis("MoveBackward", this, &APlayerCharacter::MoveBackward);
	PlayerInputComponent -> BindAction("Jump", IE_Pressed, this, &APlayerCharacter::JumpInput);
	PlayerInputComponent -> BindAction("Jump", IE_Released, this, &APlayerCharacter::JumpInput);
}

void APlayerCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) 
{
	if(OtherActor -> ActorHasTag("Collectible")){
		OtherActor -> Destroy();
		ItemCollection++;
		UE_LOG(LogTemp, Warning, TEXT("Collection: %i"), ItemCollection);
	}
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

void APlayerCharacter::JumpInput() 
{
	if(IsJumping)
	{
		IsJumping = false;
	} else
	{
		IsJumping = true;
	}
}

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

