// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"

void USWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(!IsValid(AttachedActor))
	{
		//Removes From viewport
		RemoveFromParent();

		return;
	}

	//2D screen coordinates are stored in this variable
	FVector2D ScreenPosition;

	//Takes a 3D world location and converts it into 2D screen coordinates
	if(UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition))
	{
		//This scale factor represents the DPI scaling being applied.
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		
		//Makes the screen coordinates consistent across different display resolutions and DPI settings
		ScreenPosition /= Scale;

		if (ParentSizeBox)
		{
			//Positions the ParentSizeBox at the calculated screen coordinates
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
}
