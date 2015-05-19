// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "VRLock.h"

// Sets default values
AVRLock::AVRLock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AVRLock::BeginPlay()
{
	Super::BeginPlay();

	//Init to -1 to signify value hasnt been entered
	EnteredComboVal1 = -1;
	EnteredComboVal2 = -1;
	EnteredComboVal3 = -1;

	//Get the Player's Canvas
	PlayerCanvas = Cast<AVRPawn>(Cast<AVRController>(GetWorld()->GetFirstPlayerController())->GetPawn())->GetCanvas();

	//Add Layers for Lock Application
	PlayerCanvas->AddWidgetLayer("SetLock", false);
	PlayerCanvas->AddWidgetLayer("UseLock", false);

	//Combination Knob
	LockKnob = Cast<AVRKnob>(GetWorld()->SpawnActor(AVRKnob::StaticClass()));
	LockKnob->SetWidgetScale(FVector(1.75, 1.75, 1.75));
	PlayerCanvas->AddWidget(LockKnob, PlayerCanvas->CanvasSizeX / 4, PlayerCanvas->CanvasSizeY / 2, "LockKnob", "UseLock");

	//Text Display for Current Combination value
	CurrentValueText = Cast<AVRText>(GetWorld()->SpawnActor(AVRText::StaticClass()));
	PlayerCanvas->AddWidget(CurrentValueText, PlayerCanvas->CanvasSizeX / 4 - 7, 7 * PlayerCanvas->CanvasSizeY / 8, "CurrentValue", "UseLock");

	CurrentValueText->SetWidgetScale(FVector(1.5, 1.5, 1.5));
	CurrentValueText->SetText("0");

	//Sliders for setting combination
	//Slider 1
	ComboSlider1 = Cast<AVRSlider>(GetWorld()->SpawnActor(AVRSlider::StaticClass()));
	PlayerCanvas->AddWidget(ComboSlider1, 20, PlayerCanvas->CanvasSizeY / 4 - 5, "ComboSlider1", "SetLock");

	ComboSlider1->ChangeSliderLength(100);

	//Slider 2
	ComboSlider2 = Cast<AVRSlider>(GetWorld()->SpawnActor(AVRSlider::StaticClass()));
	PlayerCanvas->AddWidget(ComboSlider2, 20, 2*PlayerCanvas->CanvasSizeY / 4 - 5, "ComboSlider1", "SetLock");

	ComboSlider2->ChangeSliderLength(100);

	//Slider 3
	ComboSlider3 = Cast<AVRSlider>(GetWorld()->SpawnActor(AVRSlider::StaticClass()));
	PlayerCanvas->AddWidget(ComboSlider3, 20, 3*PlayerCanvas->CanvasSizeY / 4 - 5, "ComboSlider1", "SetLock");

	ComboSlider3->ChangeSliderLength(100);

	//Text for sliders
	//Text 1
	CombinationText1 = Cast<AVRText>(GetWorld()->SpawnActor(AVRText::StaticClass()));
	PlayerCanvas->AddWidget(CombinationText1, 200, PlayerCanvas->CanvasSizeY / 4 + 30, "CombinationText1", "SetLock");

	CombinationText1->SetWidgetScale(FVector(2, 2, 2));
	CombinationText1->SetText("0");

	//Text 2
	CombinationText2 = Cast<AVRText>(GetWorld()->SpawnActor(AVRText::StaticClass()));
	PlayerCanvas->AddWidget(CombinationText2, 200, 2*PlayerCanvas->CanvasSizeY / 4 + 30, "CombinationText2", "SetLock");

	CombinationText2->SetWidgetScale(FVector(2, 2, 2));
	CombinationText2->SetText("0");

	//Text 3
	CombinationText3 = Cast<AVRText>(GetWorld()->SpawnActor(AVRText::StaticClass()));
	PlayerCanvas->AddWidget(CombinationText3, 200, 3*PlayerCanvas->CanvasSizeY / 4 + 30, "CombinationText3", "SetLock");

	CombinationText3->SetWidgetScale(FVector(2, 2, 2));
	CombinationText3->SetText("0");

	//Text for entering combination lock
	//Text 1
	LockDisplay1 = Cast<AVRText>(GetWorld()->SpawnActor(AVRText::StaticClass()));
	PlayerCanvas->AddWidget(LockDisplay1, 220, PlayerCanvas->CanvasSizeY / 4 + 30, "LockDisplay1", "UseLock");

	LockDisplay1->SetWidgetScale(FVector(2, 2, 2));
	LockDisplay1->SetText("");

	//Text 2
	LockDisplay2 = Cast<AVRText>(GetWorld()->SpawnActor(AVRText::StaticClass()));
	PlayerCanvas->AddWidget(LockDisplay2, 220, 2*PlayerCanvas->CanvasSizeY / 4 + 30, "LockDisplay2", "UseLock");

	LockDisplay2->SetWidgetScale(FVector(2, 2, 2));
	LockDisplay2->SetText("");

	//Text 3
	LockDisplay3 = Cast<AVRText>(GetWorld()->SpawnActor(AVRText::StaticClass()));
	PlayerCanvas->AddWidget(LockDisplay3, 220, 3*PlayerCanvas->CanvasSizeY / 4 + 30, "LockDisplay3", "UseLock");

	LockDisplay3->SetWidgetScale(FVector(2, 2, 2));
	LockDisplay3->SetText("");
}

// Called every frame
void AVRLock::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	CombinationVal1 = FMath::Ceil(ComboSlider1->GetPositionPercent() * 9);
	CombinationVal2 = FMath::Ceil(ComboSlider2->GetPositionPercent() * 9);
	CombinationVal3 = FMath::Ceil(ComboSlider3->GetPositionPercent() * 9);

	CombinationText1->SetText(FString::Printf(TEXT("%d"), CombinationVal1));
	CombinationText2->SetText(FString::Printf(TEXT("%d"), CombinationVal2));
	CombinationText3->SetText(FString::Printf(TEXT("%d"), CombinationVal3));

	KnobCurrentValue = FMath::Floor((9+1) * LockKnob->GetAngle() / 360);

	CurrentValueText->SetText(FString::Printf(TEXT("%d"), KnobCurrentValue));

	if (LockKnob->ButtonClicked())
	{

		if (EnteredComboVal1 == -1)
		{
			EnteredComboVal1 = KnobCurrentValue;
			LockDisplay1->SetText(FString::Printf(TEXT("%d"), EnteredComboVal1));
		}
		else if (EnteredComboVal2 == -1)
		{
			EnteredComboVal2 = KnobCurrentValue;
			LockDisplay2->SetText(FString::Printf(TEXT("%d"), EnteredComboVal2));
		}
		else if (EnteredComboVal3 == -1)
		{
			EnteredComboVal3 = KnobCurrentValue;
			LockDisplay3->SetText(FString::Printf(TEXT("%d"), EnteredComboVal3));

			//Finished entering code
			if (CheckCode())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Correct Combination!");
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Bad Combination!");
			}
		}
		else
		{
			//Reset
			ResetEnteredValues();
		}
	}
}

void AVRLock::ResetEnteredValues()
{
	EnteredComboVal1 = -1;
	EnteredComboVal2 = -1;
	EnteredComboVal3 = -1;

	LockDisplay1->SetText("");
	LockDisplay2->SetText("");
	LockDisplay3->SetText("");
}

bool AVRLock::CheckCode()
{
	if (EnteredComboVal1 == CombinationVal1)
	{
		if (EnteredComboVal2 == CombinationVal2)
		{
			if (EnteredComboVal3 == CombinationVal3)
			{
				return true;
			}
		}
	}

	return false;
}