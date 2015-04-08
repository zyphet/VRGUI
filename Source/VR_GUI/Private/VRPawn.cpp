// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "VRPawn.h"
#include "VRController.h"
#include "IHeadMountedDisplay.h"

AVRPawn::AVRPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Create collision component to act as root
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(15.0F);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = CollisionComp;
}

void AVRPawn::BeginPlay()
{
	//Spawn the canvas
	PlayerCanvas = Cast<AVRCanvas>(GetWorld()->SpawnActor(AVRCanvas::StaticClass()));
	PlayerCanvas->AttachRootComponentToActor(this, NAME_None, EAttachLocation::KeepWorldPosition);
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	InputComponent->BindAction("MouseClick", IE_Pressed, this, &AVRPawn::MouseClick);
	InputComponent->BindAction("MouseClick", IE_Released, this, &AVRPawn::MouseRelease);
	InputComponent->BindAction("ToggleOculusMouse", IE_Pressed, this, &AVRPawn::ToggleOculusCursor);

	InputComponent->BindAction("ResetOculus", IE_Pressed, this, &AVRPawn::ResetOculus);
	InputComponent->BindAction("Exit", IE_Pressed, this, &AVRPawn::Exit);
}

void AVRPawn::MouseClick()
{
	Cast<AVRController>(GetController())->MouseClicked();
}

void AVRPawn::MouseRelease()
{
	Cast<AVRController>(GetController())->MouseReleased();
}

void AVRPawn::ResetOculus()
{
	if (GEngine && GEngine->HMDDevice.IsValid())
	{
		GEngine->HMDDevice->ResetOrientationAndPosition(0.0F);
	}
}

void AVRPawn::ToggleOculusCursor()
{
	Cast<AVRController>(GetController())->ToggleOculusCursor();
}

void AVRPawn::Exit()
{
	if (GetController())
		Cast<APlayerController>(GetController())->ConsoleCommand("quit");
}

AVRCanvas* AVRPawn::GetCanvas()
{
	return PlayerCanvas;
}