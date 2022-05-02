// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomARPawn.h"
#include "Camera/CameraComponent.h"		// Needs this to access Camera Component Functionality
#include"ARBlueprintLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CustomActor.h"


// Sets default values
ACustomARPawn::ACustomARPawn()
{
	//sets up game control to communicate with blueprints
	PGameControl = (UGamecontrol*)UGameplayStatics::GetGameInstance(GetWorld());
	if (PGameControl == nullptr)
	{
		//Error
		return;
	}

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Scene COmponent as default
	ScnComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene"));
	RootComponent = ScnComponent;

	//Setup Camera Component as default
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(RootComponent);


	// Timer Looping every 4 seconds
	cameraNotifyLoopTime = 4.0f;

	//https://freesound.org/people/hellboy1305/sounds/370275 gun

	//https://freesound.org/people/MisterKidX/sounds/454835/ zombie
	//https://freesound.org/people/JoelAudio/sounds/135461/ smash
	//https://freesound.org/people/szegvari/sounds/594223/ music
	//set up AR session
	static ConstructorHelpers::FObjectFinder<UARSessionConfig> ConfigAsset(TEXT("ARSessionConfig'/Game/HandheldARBP/images/sessionconfig.sessionconfig'"));
	Config = ConfigAsset.Object;
	//setup plane
	planespawned = false;
	//audio set up
	static ConstructorHelpers::FObjectFinder<USoundBase> SongAsset(TEXT("SoundWave'/Game/music/594223__szegvari__battle-cinematic-soundtrack-music-atmo-background.594223__szegvari__battle-cinematic-soundtrack-music-atmo-background'"));
	music = SongAsset.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> GunAsset(TEXT("SoundWave'/Game/music/370275__hellboy1305__gun-gun.370275__hellboy1305__gun-gun'"));
	gun = GunAsset.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> DeathAsset(TEXT("SoundWave'/Game/music/454835__misterkidx__zombie-die-3.454835__misterkidx__zombie-die-3'"));
	enemydeath = DeathAsset.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> SmashAsset(TEXT("SoundWave'/Game/music/135461__joelaudio__quick-smash-002.135461__joelaudio__quick-smash-002'"));
	smash = SmashAsset.Object;





}

// Called when the game starts or when spawned
void ACustomARPawn::BeginPlay()
{
	Super::BeginPlay();

	//Config = NewObject<UARSessionConfig>();
	UARBlueprintLibrary::StartARSession(Config);

	
	//initialise enemyspawn cooldown
	cooldown  = GetWorld()->GetTimeSeconds() + 3;
	
	//start music
	UGameplayStatics::PlaySound2D(GetWorld(),music, 1, 1, 0);
}

// Called every frame
void ACustomARPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PGameControl->getgameend() == false) { //check game is running
		if (PGameControl->getgamestart() == true) {
			FindCandidateImages(); //check for images in view
			if (planespawned == true) {//if the plane has spawned the game is ready to be played
				if (cooldown < GetWorld()->GetTimeSeconds()) { //if the cooldown has run out spawn an enemy on the plane
					SpawnEnemy(Tf.GetLocation());
					cooldown = GetWorld()->GetTimeSeconds() + 3; //reset cooldown
					UGameplayStatics::PlaySound2D(GetWorld(), enemydeath, 1, 1, 0); //play enemy noise


				}
			}
		}
	}
}

// Called to bind functionality to input
void ACustomARPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{


	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACustomARPawn::OnScreenTouch);//check if sreen touched


}
void  ACustomARPawn::OnScreenTouch(const ETouchIndex::Type fingerIndex, const FVector screenPos) {
	FVector camLoc;
	FRotator camRot;
	// get camera details
	if (PGameControl->getgameend() == false) { //.check game is playing
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraViewPoint(camLoc, camRot);//update cam variables

		if (PGameControl->getgamestart() == true) { //check game has started

			SpawnBullet(camLoc, CameraComponent->GetForwardVector()); //spawn bullet when the player taps screen
			UGameplayStatics::PlaySound2D(GetWorld(), gun, 1, 1, 0);//lay gunshit sound
			//bullet travels along camera forward vector when fired 
		}
	}

}

// Print current camera orientation as debug message.
void ACustomARPawn::DisplayCameraInfo()
{
	// vars for camera location and rotation.
	FVector camLoc;
	FRotator camRot;
	// get camera details
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraViewPoint(camLoc, camRot);

	// Convert rotation into a vector as camera orientation
	FVector camOri = camRot.Vector();

	
	

	
}

void  ACustomARPawn::SpawnCube()
{
	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0, 0, 0);
	FVector myLoc(150, 0, 0);
	ACustomActor* customActor = GetWorld()->SpawnActor<ACustomActor>(myLoc, myRot, SpawnInfo);
}
void  ACustomARPawn::SpawnPlane(FVector start) {
	//set up spawn
	FActorSpawnParameters SpawnInfo;

	FRotator myRot(0, 0, 0);
	FVector myLoc = start;
	
	//spawn a new plane object
	APlaneMeshActor* customActor = GetWorld()->SpawnActor<APlaneMeshActor>(myLoc, myRot, SpawnInfo);
	GoghPlane = customActor;
}
void  ACustomARPawn::SpawnTower(FVector start) {
	FActorSpawnParameters SpawnInfo;

	FRotator myRot(0, 0, 0);
	FVector myLoc(0,0,15);
	FVector scale(0.1, 0.1, 0.3);
	myLoc += start; // add offset to starting position to set correct loction

	ATowerActor* customActor = GetWorld()->SpawnActor<ATowerActor>(myLoc, myRot, SpawnInfo); //spawn tower at middle of the plane
	DefenceTower = customActor;

	DefenceTower->SetActorScale3D(scale);
}
void  ACustomARPawn::SpawnEnemy(FVector start) {
	//set up position in reltion to start point
	FVector startp(-20, -20, 20);
	startp += start;
	PGameControl->setspawnlocation(startp);
	PGameControl->setspawnenemy(true);//set enemy spawned to true so that blueprint knows to spawn an enemy

}
void ACustomARPawn::SpawnBullet(FVector start, FVector direction) {
	FActorSpawnParameters SpawnInfo;
	//set up bullet
	FRotator myRot(0, 0, 0);
	FVector scale(0.01, 0.01, 0.01);

	//spawn bullet
	ABulletActor* customActor = GetWorld()->SpawnActor<ABulletActor>(start, myRot, SpawnInfo);
	Bullet = customActor;
	Bullet->SetActorScale3D(scale);
	//give it the cameras current direction to move in
	Bullet->Direction = CameraComponent->GetForwardVector();

}

void ACustomARPawn::FindCandidateImages() {
	Alltrackedimages = UARBlueprintLibrary::GetAllTrackedImages();
	vangoghonscreen = false;
	earthonscreen = false;

	for (int i = 0; i < Alltrackedimages.Num(); i++) { //loop through detected images

		if (Alltrackedimages[i]->GetDetectedImage()) { //check its one were looking for


			if (Alltrackedimages[i]->GetDetectedImage()->GetFriendlyName().Equals("vango")) //check which image it is
			{
				
				 Tf = Alltrackedimages[i]->GetLocalToWorldTransform();//get location of image
				vangoghonscreen = true;
				if (planespawned == false) { //makes plane only spawn once 
					planespawned = true; // spawn plane on the image
					SpawnPlane(Tf.GetLocation());
					SpawnEnemy(Tf.GetLocation()); //spawn initial enemy in relation to plane
					SpawnTower(Tf.GetLocation()); //spawn tower in relation to plane 
					
				}

			}

		}
	}

}