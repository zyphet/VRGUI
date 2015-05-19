// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "VRCheckbox.h"

AVRCheckbox::AVRCheckbox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMesh(TEXT("StaticMesh'/Game/GUI/Meshes/Mesh_Checkbox.Mesh_Checkbox'"));

	CheckboxMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("CheckboxMesh"));
	CheckboxMesh->SetStaticMesh(BoxMesh.Object);

	CheckboxMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CheckboxMesh->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CheckmarkMesh(TEXT("StaticMesh'/Game/GUI/Meshes/Mesh_Check.Mesh_Check'"));

	CheckMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("CheckMesh"));
	CheckMesh->SetStaticMesh(CheckmarkMesh.Object);

	CheckMesh->AttachTo(Root);
	CheckboxMesh->AttachTo(Root);

	bChecked = true;
	CheckMesh->SetVisibility(bChecked);
}

void AVRCheckbox::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bWidgetClicked)
	{
		ToggleCheck();
		bWidgetClicked = false;
	}

	if (bWidgetVisibility)
	{
		CheckMesh->SetVisibility(bChecked);
		CheckboxMesh->SetVisibility(true);
	}
	else
	{
		CheckMesh->SetVisibility(false);
		CheckboxMesh->SetVisibility(false);
	}
}

void AVRCheckbox::ToggleCheck()
{
	bChecked = !bChecked;
	CheckMesh->SetVisibility(bChecked);
}

bool AVRCheckbox::IsChecked()
{
	return bChecked;
}