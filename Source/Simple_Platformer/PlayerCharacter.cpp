// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlatformerGameMode.h"

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

	IsJumping = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameMode = (APlatformerGameMode*)GetWorld() -> GetAuthGameMode();

	// ! PROTOTYPE
	// TODO: the HUD will be setted up here.
	GameMode -> SetupObtainedCollectables();
	
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

/**
 * @brief This function sets up the spring arm component for the player camera
 * 
 * @param SpringArmComp 
 */
void APlayerCharacter::SpringArmSetup(USpringArmComponent* SpringArmComp) 
{
	SpringArmComp -> bEnableCameraLag = true;
	SpringArmComp -> bInheritPitch = false;
	SpringArmComp -> bInheritRoll = false;
	SpringArmComp -> bInheritYaw = false;
	SpringArmComp -> TargetArmLength = 600.0f;
}

/**
 * @brief Forward movement
 * 
 * @param AxisValue Actual value used to change velocity
 */
void APlayerCharacter::MoveForward(float AxisValue) 
{
	if(Controller != nullptr && AxisValue != 0.0f){
		const FRotator ControllerRotation = Controller -> GetControlRotation();
		const FRotator YawRotation(0, ControllerRotation.Yaw, 0);
		const FVector NewDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(NewDirection, AxisValue);
	}

}

/**
 * @brief Backward movement
 * 
 * @param AxisValue Actual value used to change velocity
 */
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

/**
 * @brief Function used to sets up the jump input
 * 
 */
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

/**
 * @brief Checks player's overlaps with other actors in game.
 * 
 * @param OverlappedComponent Player character's component that begins the overlap with an actor
 * @param OtherActor Actor overlapped with the player character.
 * @param OtherComp Actor's component overlapped with the player character.
 * @param OtherBodyIndex 
 * @param bFromSweep 
 * @param SweepResult 
 */
void APlayerCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) 
{
	if(OtherActor -> ActorHasTag("Collectible")){
		// Here if the player overlapped with a collectible item
		OtherActor -> Destroy();
		GameMode -> ItemCollected();
	} else if(OtherActor -> ActorHasTag("DeathZone")){
		// Here if the player overlapped with the death zone
		GameMode -> PlayerDied();
	} else if(OtherActor -> ActorHasTag("Enemy")){
		// Here if the player overlapped with an enemy
		APlayerCharacter::EnemyCollision(OtherActor, OtherComp);
	}
}

/**
 * @brief Checks which component the player overlapped with.
 * 		  If the player overlapped with the enemy's head, then the enemy has been defeated.
 * 		  If the player overlapped with the enemy's body, then the player has been defeated and the game ends.
 * @param EnemyActor Actor overlapped with the player.
 * @param CollidedComponent Actor's component overlapped with the player.
 */
void APlayerCharacter::EnemyCollision(AActor* EnemyActor, UPrimitiveComponent* CollidedComponent) 
{
	if(EnemyActor != nullptr){
		if(CollidedComponent -> IsA(UBoxComponent::StaticClass())){
			EnemyActor -> Destroy();
		} else if(CollidedComponent -> IsA(UCapsuleComponent::StaticClass())){
			GameMode -> PlayerDied();
		}
	}
}