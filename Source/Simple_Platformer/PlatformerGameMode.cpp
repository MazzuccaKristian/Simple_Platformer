// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

/**
 * ! PROTOYPE: getter working but platforms' movement not added.
 * @brief Used to decide special platforms' movement.
 * 
 */
void APlatformerGameMode::SetupPlatforms() 
{
    TArray<AActor*> Platforms;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Platform")), Platforms);

    for(AActor* Platform : Platforms){
        APlatformerGameMode::SetupMovement(Platform);
    }
}

/**
 * @brief Checks the platform's tag and call the associated movement function.
 * 
 * @param Platform Actual platform that needs movement in level.
 */
void APlatformerGameMode::SetupMovement(AActor* Platform) 
{
    if(Platform -> ActorHasTag("Horizontal")){
        APlatformerGameMode::SetupHorizontalMovement(Platform);
    } else if(Platform -> ActorHasTag("Vertical")){
        APlatformerGameMode::SetupVerticalMovement(Platform);
    }
}

/**
 * @brief Lerps the platform between two positions with a vertical movement
 * 
 * @param Platform Platform with "Vertical" tag.
 */
void APlatformerGameMode::SetupVerticalMovement(AActor* Platform) 
{
    FVector InitialPosition = Platform -> GetActorLocation();
    // TODO: add "final position" vector. Then lerp the actor between positions.
}

/**
 * @brief Lerps the platform between two positions with a horizontal movement
 * 
 * @param Platform Platform with "Horizontal" tag.
 */
void APlatformerGameMode::SetupHorizontalMovement(AActor* Platform) 
{
    // TODO: set up "initial position" and "final position" vectors. The lerp the actor between positions.
}

// Get the number of collectable items. Called by player HUD.
/**
 * @brief Get the number of the collectable items in the scene.
 *        Called by the player HUD.
 * 
 * @return int32. Total collectables count.
 */
int32 APlatformerGameMode::GetTotalCollectables() 
{
    TArray<AActor*> TotalCollectables;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Collectible")), TotalCollectables);
    return TotalCollectables.Num();
}

/**
 * @brief Counts actual amount of collected items.
 * 
 * @return int32
 */
int32 APlatformerGameMode::SetupObtainedCollectables() 
{
    ObtainedItems = 0;
    return ObtainedItems;
}

/**
 * @brief Called when ad item has been collected by the player. Increases the current amount of collected items.
 * 
 */
void APlatformerGameMode::ItemCollected() 
{
    ObtainedItems++;
}

/**
 * @brief Called when the player died. Sets up a "level restart" timer.
 * 
 */
void APlatformerGameMode::PlayerDied() 
{
    FTimerHandle RespawnTimer;
    GetWorldTimerManager().SetTimer(RespawnTimer, this, &APlatformerGameMode::LevelReset, TimerValue, false);
}

/**
 * @brief Resets the current level when the timer expires.
 * 
 */
void APlatformerGameMode::LevelReset() 
{
    FName LevelName = FName(UGameplayStatics::GetCurrentLevelName(GetWorld()));
    UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}