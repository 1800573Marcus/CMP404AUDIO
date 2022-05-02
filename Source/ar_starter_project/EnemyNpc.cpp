// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyNpc.h"

// Sets default values
AEnemyNpc::AEnemyNpc()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	spawnenemy = false;
}

// Called when the game starts or when spawned
void AEnemyNpc::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyNpc::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

