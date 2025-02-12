// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollerBall_GameModeBase.generated.h"

class URollerBall_Widget;
/**
 * 
 */
UCLASS()
class ROLLERBOLL_API ARollerBall_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	int32 ItemsCollected = 0;
	int32 ItemsInLevel = 0 ;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> GameWidgetClass;

	UPROPERTY()
	URollerBall_Widget* GameWidget;

	virtual void BeginPlay() override;
	void UpdateItemText();

public:

	void ItemCollected();
	
};
