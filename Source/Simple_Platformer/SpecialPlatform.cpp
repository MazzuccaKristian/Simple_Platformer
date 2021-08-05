// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialPlatform.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpecialPlatform::ASpecialPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpecialPlatform::BeginPlay()
{
	Super::BeginPlay();

	if(this -> ActorHasTag("Vertical")){
		NeededMovement = 1;
	}else if(this -> ActorHasTag("Horizontal")){
		NeededMovement = 2;
	}else{
		NeededMovement = 0;
	}
	
	InitialPosition = this -> GetActorLocation();

	FinalPosition = ASpecialPlatform::SetFinalPosition(NeededMovement, InitialPosition);
}

// Called every frame
void ASpecialPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/**
 * @brief Setup the final position vector. Used for platform's movement.
 * 
 * @param Movement Specifies the needed movement for the platform.
 * @param StartingPosition Platform's initial position in the level.
 * @return FVector Platform's final position in the level.
 */
FVector ASpecialPlatform::SetFinalPosition(int32 Movement, FVector StartingPosition) 
{
	FVector FinalVector;
	switch(Movement){
		case 0:
			FinalVector = StartingPosition;
			break;

		case 1:
			FinalVector = FVector(StartingPosition.X, StartingPosition.Y, (StartingPosition.Z + 100.0f));
			break;

		case 2:
			FinalVector = FVector(StartingPosition.X, (StartingPosition.Y + 100.0f), StartingPosition.Z);
			break;
	}
	return FinalVector;
}