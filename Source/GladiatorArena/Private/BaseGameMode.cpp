// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameMode.h"

void ABaseGameMode::SeamlessTravel(FString LevelUrl)
{
	GetWorld()->ServerTravel(LevelUrl + "?listen", false, false);
}
