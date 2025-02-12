// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerBoll/Items/RollerBall_Item.h"
#include "RollerBoll/Game/RollerBall_Pawn.h"
#include "RollerBoll/RollerBall_GameModeBase.h"

// Sets default values
ARollerBall_Item::ARollerBall_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;



}

// Called when the game starts or when spawned
void ARollerBall_Item::BeginPlay()
{
	Super::BeginPlay();
	if(Mesh)
		Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollerBall_Item::OverlapBegin);
	
}

void ARollerBall_Item::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARollerBall_Pawn>(OtherActor) != nullptr)
	{
		Collected();
	}
}

void ARollerBall_Item::Collected_Implementation()
{
	//UE_LOG(LogTemp, Warning, TEXT("Collected method is called!"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::Orange, FString::Printf(TEXT("Collected method is called!")));
	//TODO - Implement collect method.

	ARollerBall_GameModeBase* GameMode = Cast<ARollerBall_GameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		GameMode->ItemCollected();
	}
}

// Called every frame
//void ARollerBall_Item::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

