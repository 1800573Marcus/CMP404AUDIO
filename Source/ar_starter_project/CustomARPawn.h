// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h" 
#include "PlaneMeshActor.h"
#include "UObject/ConstructorHelpers.h"
#include "BulletActor.h"
#include "TowerActor.h"
#include "Gamecontrol.h"
#include"ARBlueprintLibrary.h"
#include "CustomARPawn.generated.h"

class UCameraComponent;

UCLASS()
class AR_STARTER_PROJECT_API ACustomARPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomARPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// set up for scene component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* ScnComponent;

	//set up for camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCameraComponent* CameraComponent;


	
	virtual void DisplayCameraInfo();
	//functions for spwning objects
	virtual void SpawnCube();
	virtual void SpawnPlane(FVector start);
	virtual void SpawnTower(FVector start);
	virtual void SpawnEnemy(FVector start);
	virtual void SpawnBullet(FVector start, FVector direction);
	
	//checks when screen touched
	virtual void OnScreenTouch(const ETouchIndex::Type fingerIndex, const FVector screenPos);

private:

	FTimerHandle cameraTicker;
	float cameraNotifyLoopTime;

	//set up for AR session
	UARSessionConfig* Config;

	//audio set up
	USoundBase* gun;
	USoundBase* music;
	USoundBase* enemydeath;
	USoundBase* smash;

	//plane set up
	bool planespawned;
	APlaneMeshActor* GoghPlane;

	//variables for image detection
	bool vangoghonscreen = false;
	bool earthonscreen = false;
	float alpha = 0;
	bool cubespawned = false;
	float increase = 0.1;

	//Image tracking set up
	TArray<UARTrackedImage*> Alltrackedimages;

	//used to communicate between blueprints and c++
	UGamecontrol* PGameControl;
	
	//positions objects in world
	FTransform Tf;

	//enemy spawn cooldown
	int cooldown;

	//image detection
	virtual void FindCandidateImages();

	//tower and bulet set up
	ATowerActor* DefenceTower;

	ABulletActor* Bullet;
};
