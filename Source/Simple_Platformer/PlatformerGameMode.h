// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_PLATFORMER_API APlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void GetPlatforms();

	// Collectables
		UFUNCTION(BlueprintCallable)
			int32 GetTotalCollectables();

		// UFUNCTION(BlueprintCallable)
		// 	void SetupHUDVariables();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
			int32 TotalItems;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
			int32 CalculatedTotal;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
			bool IsCalculated;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
			int32 ObtainedItems;
	//
};
