// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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

}

void APlayerCharacter::SpringArmSetup(USpringArmComponent* SpringArmComp) 
{
	SpringArmComp -> bEnableCameraLag = true;
	SpringArmComp -> bInheritPtich = false;
	SpringArmComp -> bInheritRoll = false;
	SpringArmComp -> bInheritYaw = false;
	SpringArmComp -> TargetArmLength = 600.0f;
	SpringArmComp -> SetActorRotation(FRotator(0.0f, 0.0f, -90.0f));
}
