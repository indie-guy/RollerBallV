// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerBoll/Game/RollerBall_Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"

// Sets default values
ARollerBall_Pawn::ARollerBall_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);

	//Mesh->OnComponentHit.AddDynamic(this, &ARollerBall_Pawn::OnHit);

}

// Called when the game starts or when spawned
void ARollerBall_Pawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
	
	// Bind the function to the OnComponentHit event
	if (Mesh)
	{
		Mesh->OnComponentHit.AddDynamic(this, &ARollerBall_Pawn::OnHit);
	}
}

// Called every frame
void ARollerBall_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARollerBall_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{		
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ARollerBall_Pawn::MoveForward);
		EnhancedInputComponent->BindAction(MoveBackwardAction, ETriggerEvent::Triggered, this, &ARollerBall_Pawn::MoveBackward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ARollerBall_Pawn::MoveRight);
		EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this, &ARollerBall_Pawn::MoveLeft);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARollerBall_Pawn::Jump);
	}

}

void ARollerBall_Pawn::MoveForward()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveForward"));
	const FVector Forward = Camera->GetForwardVector()* MoveForce;
	Mesh->AddForce(Forward);
}

void ARollerBall_Pawn::MoveBackward()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveBackward"));
	const FVector Forward = Camera->GetForwardVector() * MoveForce * -1.0f;
	Mesh->AddForce(Forward);
}

void ARollerBall_Pawn::MoveRight()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveRight"));
	const FVector Right = Camera->GetRightVector() * MoveForce;
	Mesh->AddForce(Right);
}

void ARollerBall_Pawn::MoveLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveLeft"));
	const FVector Right = Camera->GetRightVector() * MoveForce * -1.0f;
	Mesh->AddForce(Right);
}

void ARollerBall_Pawn::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("Jump"));
	if (JumpCount >= MaxJumpCount) { return; }
	Mesh->AddImpulse(FVector(0.0f,0.0f,JumpImpulse));
	JumpCount++;
}

void ARollerBall_Pawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Custom OnHit function is called!"));
	const float HitDirection = Hit.Normal.Z;

	//On screen debug messages
	//GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::Orange, FString::Printf(TEXT("Z normal : %f"), HitDirection));

	if (HitDirection > 0)
	{
		JumpCount = 0;
	}
}

