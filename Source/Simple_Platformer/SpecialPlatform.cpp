// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialPlatform.h"
#include "Components/BrushComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlatformerGameMode.h"

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

	GameMode = (APlatformerGameMode*)GetWorld() -> GetAuthGameMode();

	GameMode -> SetupPlatforms();
}

// Called every frame
void ASpecialPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}