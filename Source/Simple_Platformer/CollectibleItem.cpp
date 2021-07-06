// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleItem.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/PointLightComponent.h"

// Sets default values
ACollectibleItem::ACollectibleItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UpperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UpperMesh"));
	RootComponent = UpperMesh;

	BottomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomMesh"));
	BottomMesh -> SetupAttachment(UpperMesh);

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotation"));
}

// Called when the game starts or when spawned
void ACollectibleItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectibleItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

