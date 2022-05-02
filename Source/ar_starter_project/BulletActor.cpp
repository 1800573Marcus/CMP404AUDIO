// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    //component set up
    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
    StaticMeshComponent->SetupAttachment(SceneComponent);


    Collisionsphere = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision sphere"));
    Collisionsphere->SetupAttachment(SceneComponent);
    Collisionsphere->SetCapsuleRadius(1);
    Collisionsphere->SetCapsuleHalfHeight(1);

    static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    StaticMeshComponent->SetStaticMesh(MeshAsset.Object);

    static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/HandheldARBP/Materials/M_Green.M_Green'"));
    if (FoundMaterial.Succeeded())
    {
        StoredMaterial = FoundMaterial.Object;
    }


    StaticMeshComponent->SetMaterial(0, StoredMaterial);
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
    SetActorLocation(GetActorLocation() + Direction ); // mvoves the bullt in diretion the camera was facing when it was fired 
	Super::Tick(DeltaTime);

}

