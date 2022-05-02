// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Gamecontrol.generated.h"

/**
 * 
 */
UCLASS()
class AR_STARTER_PROJECT_API UGamecontrol : public UGameInstance
{
	GENERATED_BODY()
	// these getters and setters are used to communicate with the blueprints in the project
	//they deal with telling them to start the gamne, end the game, and spawning enemies 
	UPROPERTY(EditAnywhere)
		bool spawnenemy = false;

	UPROPERTY(EditAnywhere)
		bool gameend = false;
		
	UPROPERTY(EditAnywhere)
		FVector spawnlocation;

	UPROPERTY(EditAnywhere)
		bool gamestart = false;
public:
	UFUNCTION(BlueprintCallable)
		void setspawnenemy(bool seter);

	UFUNCTION(BlueprintCallable, Category = "Gamecontrol")
		bool getspawnenemy();

	UFUNCTION(BlueprintCallable)
		void setgamestart(bool seter);

	UFUNCTION(BlueprintCallable, Category = "Gamecontrol")
		bool getgamestart();

	UFUNCTION(BlueprintCallable)
		void setgameend(bool seter);

	UFUNCTION(BlueprintCallable, Category = "Gamecontrol")
		bool getgameend();

	UFUNCTION(BlueprintCallable, Category = "Gamecontrol")
		void setspawnlocation(FVector start);

	UFUNCTION(BlueprintCallable, Category = "Gamecontrol")
		FVector getspawnlocation();
};
