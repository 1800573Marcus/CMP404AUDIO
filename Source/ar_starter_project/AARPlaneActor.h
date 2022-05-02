// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARTrackable.h"

#include "AARPlaneActor.generated.h"

UCLASS()
class AR_STARTER_PROJECT_API AARPlaneActor : public AActor
{
	GENERATED_BODY()

public:

	// this actor is not used in the project
	// Sets default values for this actor's properties
	AARPlaneActor();

	/* The procedural mesh component */
	UPROPERTY(Category = GoogleARCorePlaneActor, EditAnywhere, BlueprintReadWrite)
		class UProceduralMeshComponent* PlanePolygonMeshComponent;

	/** When set to true, the actor will remove the ARAnchor object from the current tracking session when the Actor gets destroyed.*/
	UPROPERTY(Category = GoogleARCorePlaneActor, BlueprintReadWrite)
		class UARPlaneGeometry* ARCorePlaneObject = nullptr;

	/** The feathering distance for the polygon edge. Default to 10 cm*/
	UPROPERTY(Category = GoogleARCorePlaneActor, EditAnywhere, BlueprintReadWrite)
		float EdgeFeatheringDistance = 10.0f;

	UPROPERTY(Category = GoogleARCorePlaneActor, EditAnywhere, BlueprintReadWrite)
		FColor PlaneColor;

	UPROPERTY(Category = GoogleARCorePlaneActor, EditAnywhere, BlueprintReadWrite)
		UMaterialInstanceDynamic* PlaneMaterial;


	UMaterialInterface* Material_;
protected:
	// Called at the time of spawning
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "GoogleARCorePlaneActor", meta = (Keywords = "googlear arcore plane"))
		void UpdatePlanePolygonMesh();

	UFUNCTION(BlueprintCallable, Category = "GoogleARCorePlaneActor")
		void SetColor(FColor InColor);

};
