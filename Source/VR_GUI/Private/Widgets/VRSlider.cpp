// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "VRController.h"
#include "VRSlider.h"

AVRSlider::AVRSlider(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	StartOfBar = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("StartOfBar"));
	EndOfBar = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("EndOfBar"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SliderStartMesh(TEXT("StaticMesh'/Game/GUI/Meshes/Slider/SliderStart.SliderStart'"));

	SliderStart = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("SliderStart"));
	SliderStart->SetStaticMesh(SliderStartMesh.Object);

	SliderStart->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SliderStart->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SliderEndMesh(TEXT("StaticMesh'/Game/GUI/Meshes/Slider/SliderEnd.SliderEnd'"));

	SliderEnd = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("SliderEnd"));
	SliderEnd->SetStaticMesh(SliderEndMesh.Object);

	SliderEnd->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SliderEnd->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SliderBarMesh(TEXT("StaticMesh'/Game/GUI/Meshes/Slider/SliderBar.SliderBar'"));

	SliderBar = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("SliderBar"));
	SliderBar->SetStaticMesh(SliderBarMesh.Object);

	SliderBar->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SliderBar->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SliderBallMesh(TEXT("StaticMesh'/Game/GUI/Meshes/Slider/SliderBall.SliderBall'"));

	SliderBall = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("SliderBall"));
	SliderBall->SetStaticMesh(SliderBallMesh.Object);

	SliderBall->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SliderBall->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);

	SliderStart->AttachTo(Root);
	SliderEnd->AttachTo(Root);
	SliderBar->AttachTo(Root);
	SliderBall->AttachTo(Root);

	StartOfBar->AttachTo(Root);
	EndOfBar->AttachTo(Root);

	LengthOfBarWorldUnits = 60;

	SliderBar->SetRelativeLocation(FVector(0, 10, 0));
	SliderEnd->SetRelativeLocation(FVector(0, LengthOfBarWorldUnits+10, 0));
	SliderBall->SetRelativeLocation(FVector(0, 10, 0));
	
	//Used for reference in resizing slider bar
	StartOfBar->SetRelativeLocation(FVector(0, 10, 0));
	EndOfBar->SetRelativeLocation(FVector(0, LengthOfBarWorldUnits + 10, 0));
}

void AVRSlider::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MoveSlider();
	UpdatePositionAttribute();

	SliderStart->SetVisibility(bWidgetVisibility);
	SliderEnd->SetVisibility(bWidgetVisibility);
	SliderBar->SetVisibility(bWidgetVisibility);
	SliderBall->SetVisibility(bWidgetVisibility);
}

void AVRSlider::ChangeSliderLength(float BarLength)
{
	LengthOfBarWorldUnits = BarLength;

	float temp = StartOfBar->RelativeLocation.Y;
	FVector temp2 = EndOfBar->RelativeLocation;

	temp2.Y = BarLength + temp;

	EndOfBar->SetRelativeLocation(temp2);

	SliderBar->SetRelativeScale3D(FVector(1, BarLength/60, 1));
	SliderEnd->SetRelativeLocation(EndOfBar->RelativeLocation);
}

void AVRSlider::MoveSlider()
{
	if (bWidgetClicked)
	{
		if (ComponentClicked == SliderBall)
		{
			FVector MouseLoc = Cast<AVRController>(GetWorld()->GetFirstPlayerController())->GetCanvasMouseLocation();

			FVector Loc = SliderBall->RelativeLocation;
			Loc.Y = MouseLoc.X - CoordX - 5 * WidgetScale.Y;

			SliderBall->SetRelativeLocation(Loc);
		}
	}

	FVector tempLoc = SliderBall->RelativeLocation;

	//Widget Scale is to get the proper location of the other side of the ball
	//Needs to be adjusted according to the scale of the widget (could add another scene component instead to mark location)

	if (SliderBall->RelativeLocation.Y < StartOfBar->RelativeLocation.Y)
	{
		tempLoc.Y = StartOfBar->RelativeLocation.Y;
		SliderBall->SetRelativeLocation(tempLoc);
	}
	else if (SliderBall->RelativeLocation.Y >(EndOfBar->RelativeLocation.Y - 10 * WidgetScale.Y))
	{
		tempLoc.Y = EndOfBar->RelativeLocation.Y - 10 * WidgetScale.Y;
		SliderBall->SetRelativeLocation(tempLoc);
	}
}

void AVRSlider::UpdatePositionAttribute()
{
	float Origin = StartOfBar->RelativeLocation.Y;
	
	float PositionBall = SliderBall->RelativeLocation.Y - Origin;
	float EndPosition = EndOfBar->RelativeLocation.Y - Origin - 10 * WidgetScale.Y;

	PositionPercent = PositionBall / EndPosition;
}

float AVRSlider::GetPositionPercent()
{
	return PositionPercent;
}