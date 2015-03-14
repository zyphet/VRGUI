// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "IHeadMountedDisplay.h"
#include "VRWidget.h"
#include "VRCheckbox.h"
#include "VRPawn.h"
#include "VRController.h"

AVRController::AVRController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AVRController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
		World = GetWorld();

	//Finds the camera placed in the scene
	for (TActorIterator<ACameraActor> Itr(World); Itr; ++Itr)
	{
		if (Itr->GetName().Equals("Camera_GUI"))
		{
			CurrentCamera = *Itr;
			SetViewTarget(CurrentCamera);
		}
	}

	//Reduces rendering quality a little to keep framerate high for VR
	if (GEngine && GEngine->HMDDevice.IsValid())
	{
		bValidOculus = true;
		ConsoleCommand("hmd sp 100");
	}
	else
		bValidOculus = false;

	bUseOculusCursor = true;

	VirtualMouseSensitivity = 4;
	VirtualMouseLocationX = 0;
	VirtualMouseLocationY = 0;

	Cursor = Cast<AVRCursor>(World->SpawnActor(AVRCursor::StaticClass()));
	Cursor->AttachRootComponentToActor(GetPawn());
}

void AVRController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GEngine && GEngine->HMDDevice.IsValid())
	{
		bValidOculus = true;
	}

	if (bValidOculus && GEngine && GEngine->HMDDevice->IsStereoEnabled())
	{
		//Probably bad place to set this, maybe move later (also set to false below)
		bUsingOculus = true;

		GetViewTarget()->SetActorRotation(GetControlRotation());
	}
	else
		bUsingOculus = false;

	ProjectCursor();
}

void AVRController::MouseClicked()
{
	//Make new trace to the location of Virtual Mouse, check OutHit actor
	if (!bUseOculusCursor && bUsingOculus)
	{
		World->LineTraceSingle(OutHit, GetViewTarget()->GetActorLocation(), VirtualMouseWorldLocation, ECC_EngineTraceChannel1, Params, ResponseParam);
	}
		
	if (Cast<AVRWidget>(OutHit.GetActor()))
	{
		ClickedWidget = Cast<AVRWidget>(OutHit.GetActor());
		ClickedWidget->WidgetClicked(OutHit.GetComponent());
	}
}

void AVRController::MouseReleased()
{
	if (ClickedWidget)
	{
		ClickedWidget->WidgetClickRelease();
		ClickedWidget = NULL;
	}
}

void AVRController::ToggleOculusCursor()
{
	bUseOculusCursor = !bUseOculusCursor;
}

void AVRController::ProjectCursor()
{
	AVRCanvas* Canvas = Cast<AVRPawn>(GetPawn())->GetCanvas();

	if (bUsingOculus)
	{
		if (bUseOculusCursor)
		{
			GEngine->HMDDevice->GetCurrentOrientationAndPosition(OculusOrientation, OculusPosition);

			StartOfTrace = CurrentCamera->GetActorLocation() + OculusPosition;
			EndOfTrace = OculusOrientation.Rotator().Vector() * 1000 + StartOfTrace;

			World->LineTraceSingle(OutHit, StartOfTrace, EndOfTrace, ECC_EngineTraceChannel1, Params, ResponseParam);

			VirtualMouseLocationX = OutHit.Location.Y - Canvas->GetActorLocation().Y;
			VirtualMouseLocationY = OutHit.Location.Z - Canvas->GetActorLocation().Z;

			VirtualMouseWorldLocation = OutHit.Location;

			//DrawDebugPoint(World, OutHit.Location, 5, FColor(0, 0, 0), false, 0.1);
			Cursor->SetActorLocation(OutHit.Location);

			return;
		}
	}

	float mouseX;
	float mouseY;

	GetInputMouseDelta(mouseX, mouseY);

	VirtualMouseLocationX += mouseX * VirtualMouseSensitivity;
	VirtualMouseLocationY -= mouseY * VirtualMouseSensitivity;

	if (VirtualMouseLocationX < 0)
		VirtualMouseLocationX = 0;

	if (VirtualMouseLocationX > Canvas->CanvasSizeX)
		VirtualMouseLocationX = Canvas->CanvasSizeX;

	if (VirtualMouseLocationY < 0)
		VirtualMouseLocationY = 0;

	if (VirtualMouseLocationY > Canvas->CanvasSizeY)
		VirtualMouseLocationY = Canvas->CanvasSizeY;

	VirtualMouseWorldLocation = Canvas->ConvertToWorldCoords(VirtualMouseLocationX, VirtualMouseLocationY);

	EndOfTrace = VirtualMouseWorldLocation;

	EndOfTrace.X += 0.5;

	World->LineTraceSingle(OutHit, GetViewTarget()->GetActorLocation(), EndOfTrace, ECC_EngineTraceChannel1, Params, ResponseParam);

	//DrawDebugPoint(World, OutHit.Location, 5, FColor(0, 0, 0), false, 0.1);
	Cursor->SetActorLocation(OutHit.Location);

}

FVector AVRController::GetCanvasMouseLocation()
{
	AVRCanvas* Canvas = Cast<AVRPawn>(GetPawn())->GetCanvas();

	FVector CanvasMouseLocation = FVector(VirtualMouseLocationX, VirtualMouseLocationY, Canvas->DistanceFromViewer);

	return CanvasMouseLocation;
}