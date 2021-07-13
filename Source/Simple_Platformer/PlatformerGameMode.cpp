// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerGameMode.h"
#include "Kismet/GameplayStatics.h"

// ! PROTOTYPE
// Get every platform. Used to setup special platforms' movement.
void APlatformerGameMode::GetPlatforms() 
{
    TArray<AActor*> Platforms;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Platform")), Platforms);

    for(AActor* Platform : Platforms){
        if(Platform -> ActorHasTag("Vertical")){
            UE_LOG(LogTemp, Warning, TEXT("Piattaforma verticale"));
        } else if(Platform -> ActorHasTag("Horizontal")){
            UE_LOG(LogTemp, Warning, TEXT("Piattaforma orizzontale"));
        } else {
            UE_LOG(LogTemp, Warning, TEXT("Piattaforma statica"));
        }
    }
}

// Get the number of collectable items. Called by player HUD.
int32 APlatformerGameMode::GetTotalCollectables() 
{
    TArray<AActor*> TotalCollectables;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Collectible")), TotalCollectables);
    return TotalCollectables.Num();
}

void APlatformerGameMode::ItemCollected() 
{
    ObtainedItems++;
}

// void APlatformerGameMode::SetupHUDVariables() 
// {
    
// }