// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerBoll/RollerBall_GameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "RollerBoll/Items/RollerBall_Item.h"
#include "RollerBoll/Widgets/RollerBall_Widget.h"


void ARollerBall_GameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollerBall_Item::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if (GameWidgetClass)
	{
		GameWidget = Cast<URollerBall_Widget>(CreateWidget(GetWorld(), GameWidgetClass));
		if (GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}

}

void ARollerBall_GameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel, IsWin());	
}

void ARollerBall_GameModeBase::ItemCollected()
{
	ItemsCollected ++;
	UpdateItemText();
}

bool ARollerBall_GameModeBase::IsWin() const
{
	return (ItemsCollected == ItemsInLevel);
}