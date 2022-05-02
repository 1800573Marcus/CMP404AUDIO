// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Gamecontrol.h"
#include "EnemyNpc.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TowerActor.generated.h"

UCLASS()
class AR_STARTER_PROJECT_API ATowerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//damage sound effect
	USoundBase* smash;
	//health points of the tower
	int hp;
	//damage and collsion set up
	bool touching;
	int cooldown;

	//needed to communicate with blueprints
	UGamecontrol* PGameControl;

	//scene compnents
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;
	//cylinder mesh set up
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComponent;
	//material set up
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UMaterial* Material;
	//collisin box foer taking damage
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	 UBoxComponent* CollisionMesh;
	//collision responses
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

