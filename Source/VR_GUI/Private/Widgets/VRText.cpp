// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "VRText.h"

AVRText::AVRText(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	Text = ObjectInitializer.CreateDefaultSubobject<UTextRenderComponent>(this, TEXT("Text"));
	Text->AttachTo(Root);
}

void AVRText::BeginPlay()
{
	Super::BeginPlay();

	AddActorWorldRotation(FRotator(0, 180, 0));
	Text->AddLocalOffset(FVector(.01, 0, 0));
}

void AVRText::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bWidgetVisibility)
		Text->SetText(WidgetText);
	else
		Text->SetText("");
}

void AVRText::SetText(FString text)
{
	WidgetText = text;
	Text->SetText(WidgetText);
}