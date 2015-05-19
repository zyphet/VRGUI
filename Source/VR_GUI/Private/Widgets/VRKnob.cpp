// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "VRController.h"
#include "VRKnob.h"

AVRKnob::AVRKnob(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ButtonM(TEXT("StaticMesh'/Game/GUI/Meshes/Knob/KnobButton.KnobButton'"));

	Button = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Button"));
	Button->SetStaticMesh(ButtonM.Object);

	Button->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Button->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);

	Button->AttachTo(Root);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> RingM(TEXT("StaticMesh'/Game/GUI/Meshes/Knob/KnobRing.KnobRing'"));

	Ring = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Ring"));
	Ring->SetStaticMesh(RingM.Object);

	Ring->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Ring->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);

	Ring->AttachTo(Root);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MarkerM(TEXT("StaticMesh'/Game/GUI/Meshes/Knob/KnobMarker.KnobMarker'"));

	Marker = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Marker"));
	Marker->SetStaticMesh(MarkerM.Object);

	Marker->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Marker->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);

	Marker->AttachTo(Root);

	static ConstructorHelpers::FObjectFinder<UMaterial> Mat(TEXT("Material'/Game/GUI/Materials/Mat_MetalButton2.Mat_MetalButton2'"));

	ButtonMat = Button->CreateDynamicMaterialInstance(0, Mat.Object);

	ButtonMat->SetVectorParameterValue("Color", FLinearColor(1, 1, 1, 1));
}

void AVRKnob::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MoveMarker();

	Button->SetVisibility(bWidgetVisibility);
	Marker->SetVisibility(bWidgetVisibility);
	Ring->SetVisibility(bWidgetVisibility);

	if (bWidgetVisibility)
	{
		Button->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Marker->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Ring->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		Button->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Marker->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Ring->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

float AVRKnob::GetAngle()
{
	return KnobAngle;
}

bool AVRKnob::ButtonClicked()
{
	//If the widget is clicked, set bClicked to true
	//to signal that this widget has been clicked
	if (ComponentClicked == Button)
	{
		bClicked = true;
		ButtonMat->SetVectorParameterValue("Color", FLinearColor(.1, .1, .1, 1));
		return false;
	}
	//to determine when button is released, which is when we return true
	//test if widget is no longer clicked, but has been clicked recently (using bClicked)
	if (!bWidgetClicked && bClicked)
	{
		bClicked = false;
		ButtonMat->SetVectorParameterValue("Color", FLinearColor(1, 1, 1, 1));
		return true;
	}

	//For many buttons, when you click and drag off to the side it "cancels" the button click.
	//I dont think that it works this way using this implementation

	return false;
}

void AVRKnob::MoveMarker()
{
	if (bWidgetClicked)
	{
		if (ComponentClicked == Ring)
		{
			FVector MouseLoc = Cast<AVRController>(GetWorld()->GetFirstPlayerController())->GetCanvasMouseLocation();
			FVector Origin = GetWidgetCanvasCoords();

			FVector temp = MouseLoc - Origin;

			float Angle = FMath::RadiansToDegrees(FMath::Atan(temp.Y / temp.X)) + 90;

			FRotator Rot;

			if (temp.X < 0)
			{
				Angle += 180;
			}

			Rot = FRotator(0, 0, Angle);

			/*if (GEngine)
			{
				GEngine->ClearOnScreenDebugMessages();
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Angle: %f ATan: %f"), Angle, FMath::Atan(temp.Y / temp.X)));
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("X: %f Y: %f"), temp.X, temp.Y));
			}*/

			Rot.Normalize();

			Marker->SetRelativeRotation(Rot);
			KnobAngle = Angle;
		}
	}
}