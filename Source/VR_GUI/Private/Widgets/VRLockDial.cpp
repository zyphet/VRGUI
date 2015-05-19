// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "VRLockDial.h"

AVRLockDial::AVRLockDial(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	/*static ConstructorHelpers::FObjectFinder<UBlueprint> DialObject(TEXT("Blueprint'/Game/Blueprints/ClickableNumber.ClickableNumber'"));

	if (DialObject.Object != NULL)
	{
		Dial = (UClass*)DialObject.Object->GeneratedClass;
	}*/

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ButtonM(TEXT("StaticMesh'/Game/GUI/Meshes/Lock/LockButton.LockButton'"));

	Button = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Button"));
	Button->SetStaticMesh(ButtonM.Object);

	Button->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Button->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);

	Button->AttachTo(Root);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> RingM(TEXT("StaticMesh'/Game/GUI/Meshes/Lock/LockRing.LockRing'"));

	Ring = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Ring"));
	Ring->SetStaticMesh(RingM.Object);

	Ring->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Ring->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);

	Ring->AttachTo(Root);

	static ConstructorHelpers::FObjectFinder<UMaterial> Mat(TEXT("Material'/Game/GUI/Materials/Mat_MetalButton2.Mat_MetalButton2'"));

	ButtonMat = Button->CreateDynamicMaterialInstance(0, Mat.Object);

	ButtonMat->SetVectorParameterValue("Color", FLinearColor(1, 1, 1, 1));
}

// Called when the game starts or when spawned
void AVRLockDial::BeginPlay()
{
	Super::BeginPlay();
}

void AVRLockDial::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Button->SetVisibility(bWidgetVisibility);
	Ring->SetVisibility(bWidgetVisibility);

	if (bWidgetVisibility)
	{
		Button->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Ring->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		Button->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Ring->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

bool AVRLockDial::ButtonClicked()
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