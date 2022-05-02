// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaneMeshActor.h"

// Sets default values
APlaneMeshActor::APlaneMeshActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // et up components of the object
    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
    StaticMeshComponent->SetupAttachment(SceneComponent);

    const FVector boxextent(50, 50, 0.1);
    CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
    CollisionMesh->SetupAttachment(SceneComponent);
   CollisionMesh->SetBoxExtent(boxextent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
    StaticMeshComponent->SetStaticMesh(MeshAsset.Object);

    static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/HandheldARBP/Materials/M_Green.M_Green'"));
    if (FoundMaterial.Succeeded())
    {
        StoredMaterial = FoundMaterial.Object;
    }
  

    StaticMeshComponent->SetMaterial(0, StoredMaterial);
}

// Called when the game starts or when spawned
void APlaneMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlaneMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

