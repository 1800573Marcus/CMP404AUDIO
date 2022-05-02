// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlaneMeshActor.generated.h"

UCLASS()
class AR_STARTER_PROJECT_API APlaneMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaneMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//scene component 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;

	//plane mesh 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComponent;
	//material
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UMaterial* StoredMaterial;

	//colision ox to make object solid
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	 UBoxComponent* CollisionMesh;

	
};
