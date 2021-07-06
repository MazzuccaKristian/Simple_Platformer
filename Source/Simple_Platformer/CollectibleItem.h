// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectibleItem.generated.h"

class URotatingMovementComponent;

UCLASS()
class SIMPLE_PLATFORMER_API ACollectibleItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibleItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* UpperMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BottomMesh;

	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* RotatingMovement;
};
