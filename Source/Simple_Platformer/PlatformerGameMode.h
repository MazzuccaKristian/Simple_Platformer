// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameMode.generated.h"

/**
*
**/
UCLASS()
class SIMPLE_PLATFORMER_API APlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	//Platforms' movement
		UFUNCTION(BlueprintCallable)
			void SetupPlatforms();

		UFUNCTION()
			void SetupMovement(AActor* Platform);

		UFUNCTION()
			void SetupHorizontalMovement(AActor* Platform);

		UFUNCTION()
			void SetupVerticalMovement(AActor* Platform);
	//

	// Collectables
		UFUNCTION(BlueprintCallable)
			int32 GetTotalCollectables();

		UFUNCTION(BlueprintCallable)
			int32 SetupObtainedCollectables();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
			int32 TotalItems;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
			int32 CalculatedTotal;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
			bool IsCalculated;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
			int32 ObtainedItems;

		void ItemCollected();
	//

	// Level reset on player's death
		UPROPERTY(EditAnywhere)
			float TimerValue = 2.0f;

		UFUNCTION()
			void PlayerDied();

		UFUNCTION()
			void LevelReset();
	//
};
