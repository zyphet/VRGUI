// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "VRButton.h"

AVRButton::AVRButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ButtonM(TEXT("StaticMesh'/Game/GUI/Meshes/Button/Button.Button'"));

	Button = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Button"));
	Button->SetStaticMesh(ButtonM.Object);

	Button->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Button->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);

	Button->AttachTo(Root);

	ButtonText = ObjectInitializer.CreateDefaultSubobject<UTextRenderComponent>(this, TEXT("ButtonText"));
	ButtonText->SetText("");
	ButtonText->VerticalAlignment = EVerticalTextAligment::EVRTA_TextTop;
	ButtonText->SetWorldRotation(FRotator(0, 180, 0));
	ButtonText->AttachTo(Root);
	ButtonText->SetRelativeLocation(FVector(-4, 0, 0));

	static ConstructorHelpers::FObjectFinder<UMaterial> Mat(TEXT("Material'/Game/GUI/Materials/Mat_MetalButton2.Mat_MetalButton2'"));

	ButtonMat = Button->CreateDynamicMaterialInstance(0, Mat.Object);

	ButtonMat->SetVectorParameterValue("Color", FLinearColor(1, 1, 1, 1));
}

void AVRButton::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Button->SetVisibility(bWidgetVisibility);
	ButtonText->SetVisibility(bWidgetVisibility);

	if (bWidgetVisibility)
		Button->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	else
		Button->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool AVRButton::ButtonClicked()
{
	//If the widget is clicked, set bClicked to true
	//to signal that this widget has been clicked
	if (bWidgetClicked)
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

void AVRButton::SetButtonText(FString TextString)
{
	ButtonText->SetText(TextString);
}

void AVRButton::SetTextRelativeLocation(FVector Loc)
{
	ButtonText->SetRelativeLocation(Loc);
}

void AVRButton::SetTextScale(FVector Scale)
{
	ButtonText->SetXScale(Scale.X);
	ButtonText->SetYScale(Scale.Y);
}

void AVRButton::SetButtonColor(FVector Color)
{
	ButtonMat->SetVectorParameterValue("Color", FLinearColor(Color.X, Color.Y, Color.Z, 1));
}

void AVRButton::SetTextColor(FVector Color)
{
	ButtonText->SetTextRenderColor(FColor(Color.X, Color.Y, Color.Z));
}