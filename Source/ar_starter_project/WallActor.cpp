// Fill out your copyright notice in the Description page of Project Settings.


#include "WallActor.h"

// Sets default values
AWallActor::AWallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    StaticMeshComponent->SetupAttachment(SceneComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    StaticMeshComponent->SetStaticMesh(MeshAsset.Object);

    static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/HandheldARBP/Materials/M_Grey.M_Grey'"));
    if (FoundMaterial.Succeeded())
    {
        Material = FoundMaterial.Object;
    }

    const FVector boxextent(1, 1, 1);
    CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
    CollisionMesh->SetupAttachment(SceneComponent);
    CollisionMesh->SetBoxExtent(boxextent);

    //(0.15,0.01,0.05)
    
    StaticMeshComponent->SetMaterial(0, Material);
}

// Called when the game starts or when spawned
void AWallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

