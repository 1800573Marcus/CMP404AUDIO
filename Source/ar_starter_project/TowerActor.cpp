// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerActor.h"

// Sets default values
ATowerActor::ATowerActor()
{
    //set up for communication with blueprints
    PGameControl = (UGamecontrol*)UGameplayStatics::GetGameInstance(GetWorld());
    if (PGameControl == nullptr)
    {
        //Error
        return;
    }
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //component set up
    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    StaticMeshComponent->SetupAttachment(SceneComponent);
    //get cylinder mesh for tower
    static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
    StaticMeshComponent->SetStaticMesh(MeshAsset.Object);

    //get the material for the tower
    static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/HandheldARBP/Materials/M_Grey.M_Grey'"));
    if (FoundMaterial.Succeeded())
    {
        Material = FoundMaterial.Object;
    }

    const FVector boxextent(50, 50, 50);//set size of collision box
    CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
    CollisionMesh->SetupAttachment(SceneComponent);//attach to the ibject
    CollisionMesh->SetBoxExtent(boxextent);

    
    CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ATowerActor::OnOverlapBegin);
    CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &ATowerActor::OnOverlapEnd);//collision responses
    StaticMeshComponent->SetMaterial(0, Material);

    hp = 100; // msx health initialised

    touching = false; //fpor collisions

    static ConstructorHelpers::FObjectFinder<USoundBase> SmashAsset(TEXT("SoundWave'/Game/music/135461__joelaudio__quick-smash-002.135461__joelaudio__quick-smash-002'"));//get damage sound effect ready 
    smash = SmashAsset.Object;

}

void ATowerActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    // Get object of actor hit. 
    UClass* hitActorClass = UGameplayStatics::GetObjectClass(OtherActor);

    // if we've hit a target. 
    if (UKismetMathLibrary::ClassIsChildOf(hitActorClass, AEnemyNpc::StaticClass()))
    {
        touching = true; // check the tower is touching an enemy
    }
     

}
void ATowerActor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
    // Get object of actor hit. 
    UClass* hitActorClass = UGameplayStatics::GetObjectClass(OtherActor);

    // if we've found an enmy 
    if (UKismetMathLibrary::ClassIsChildOf(hitActorClass, AEnemyNpc::StaticClass()))
    {
        touching = false; //the eemy is no longer touching the tower

    }


}

// Called when the game starts or when spawned
void ATowerActor::BeginPlay()
{
	Super::BeginPlay();
    cooldown = GetWorld()->GetTimeSeconds() + 3;//reset damage cooldown
}

// Called every frame
void ATowerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (PGameControl->getgameend() == false){ // if the game is runnong
        if (touching == true) { // if the tower is touching an enemy
            if (cooldown < GetWorld()->GetTimeSeconds()) { //check damage cooldon has passed
                hp -= 10; //take damage
                cooldown = GetWorld()->GetTimeSeconds() + 3; //reset cooldown
                UGameplayStatics::PlaySound2D(GetWorld(), smash, 1, 1, 0); //play damage noise as the enemy has hit the tower

            }
        }
    if (hp <= 0) {
        PGameControl->setgameend(true); //when the tower dies tell the blueprints to end the game
    }
}
}

