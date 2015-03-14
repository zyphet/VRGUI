// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "VRCursor.h"


// Sets default values
AVRCursor::AVRCursor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CursorMesh(TEXT("StaticMesh'/Game/GUI/Meshes/Cursor/Cursor.Cursor'"));

	Cursor = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Cursor"));
	Cursor->SetStaticMesh(CursorMesh.Object);

	Cursor->AttachTo(Root);

}

// Called when the game starts or when spawned
void AVRCursor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRCursor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

