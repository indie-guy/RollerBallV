// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RollerBall_Pawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ROLLERBOLL_API ARollerBall_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARollerBall_Pawn();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Define components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

	// VARIABLES //
	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	float MoveForce = 2000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpImpulse = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxJumpCount = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private :

	// Functions //
	void MoveRight();
	void MoveLeft();
	void MoveForward();
	void MoveBackward();
	void Jump();
	
	int JumpCount = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* MoveBackwardAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* MoveRightAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* MoveLeftAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* JumpAction;

	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
