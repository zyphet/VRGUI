// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "VRLock2.h"


// Sets default values
AVRLock2::AVRLock2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVRLock2::BeginPlay()
{
	Super::BeginPlay();

	//Init to -1 to signify value hasnt been entered
	EnteredComboVal1 = -1;
	EnteredComboVal2 = -1;
	EnteredComboVal3 = -1;

	//Get the Player's Canvas
	PlayerCanvas = Cast<AVRPawn>(Cast<AVRController>(GetWorld()->GetFirstPlayerController())->GetPawn())->GetCanvas();

	//Add Layers for Lock Application
	PlayerCanvas->AddWidgetLayer("SetLock2", false);
	PlayerCanvas->AddWidgetLayer("SecondLock", false);

	float DialX = PlayerCanvas->CanvasSizeX / 3.5;
	float DialY = PlayerCanvas->CanvasSizeY / 2;

	//Revised Lock
	LockDial = Cast<AVRLockDial>(GetWorld()->SpawnActor(AVRLockDial::StaticClass()));
	PlayerCanvas->AddWidget(LockDial, DialX, DialY, "Dial", "SecondLock");

	//Dial Buttons
	DialButton0 = Cast<AVRButton>(GetWorld()->SpawnActor(AVRButton::StaticClass()));
	DialButton0->SetButtonText("0");
	DialButton0->SetTextScale(FVector(4, 1, 0));
	PlayerCanvas->AddWidget(DialButton0, DialX, DialY, "DialButton0", "SecondLock");
	DialButton0->SetWidgetScale(FVector(1, 0.5, 1.5));
	PlayerCanvas->MoveWidget(DialButton0, DialX-15, DialY-87);
	
	DialButton1 = Cast<AVRButton>(GetWorld()->SpawnActor(AVRButton::StaticClass()));
	DialButton1->SetButtonText("1");
	DialButton1->SetTextScale(FVector(4, 1, 0));
	PlayerCanvas->AddWidget(DialButton1, DialX, DialY, "DialButton1", "SecondLock");
	DialButton1->SetWidgetScale(FVector(1, 0.5, 1.5));
	DialButton1->SetActorRotation(FRotator(0, 0, 36));
	PlayerCanvas->MoveWidget(DialButton1, DialX + 39.0020620338, DialY - 79.201257295);

	DialButton2 = Cast<AVRButton>(GetWorld()->SpawnActor(AVRButton::StaticClass()));
	DialButton2->SetButtonText("2");
	DialButton2->SetTextScale(FVector(4, 1, 0));
	PlayerCanvas->AddWidget(DialButton2, DialX, DialY, "DialButton2", "SecondLock");
	DialButton2->SetWidgetScale(FVector(1, 0.5, 1.5));
	DialButton2->SetActorRotation(FRotator(0, 0, 72));
	PlayerCanvas->MoveWidget(DialButton2, DialX + 78.1066620021, DialY - 41.150326255);

	DialButton3 = Cast<AVRButton>(GetWorld()->SpawnActor(AVRButton::StaticClass()));
	DialButton3->SetButtonText("3");
	DialButton3->SetTextScale(FVector(4, 1, 0));
	PlayerCanvas->AddWidget(DialButton3, DialX, DialY, "DialButton3", "SecondLock");
	DialButton3->SetWidgetScale(FVector(1, 0.5, 1.5));
	DialButton3->SetActorRotation(FRotator(0, 0, -72));
	PlayerCanvas->MoveWidget(DialButton3, DialX + 41.0154578665, DialY + 29.0986634744);

	DialButton4 = Cast<AVRButton>(GetWorld()->SpawnActor(AVRButton::StaticClass()));
	DialButton4->SetButtonText("4");
	DialButton4->SetTextScale(FVector(4, 1, 0));
	PlayerCanvas->AddWidget(DialButton4, DialX, DialY, "DialButton4", "SecondLock");
	DialButton4->SetWidgetScale(FVector(1, 0.5, 1.5));
	DialButton4->SetActorRotation(FRotator(0, 0, -36));
	PlayerCanvas->MoveWidget(DialButton4, DialX + 16.0784371944, DialY + 47.6495945144);

	DialButton5 = Cast<AVRButton>(GetWorld()->SpawnActor(AVRButton::StaticClass()));
	DialButton5->SetButtonText("5");
	DialButton5->SetTextScale(FVector(4, 1, 0));
	PlayerCanvas->AddWidget(DialButton5, DialX, DialY, "DialButton5", "SecondLock");
	DialButton5->SetWidgetScale(FVector(1, 0.5, 1.5));
	DialButton5->SetActorRotation(FRotator(0, 0, 0));
	PlayerCanvas->MoveWidget(DialButton5, DialX - 15, DialY + 48);

	DialButton6 = Cast<AVRButton>(GetWorld()->SpawnActor(AVRButton::StaticClass()));
	DialButton6->SetButtonText("6");
	DialButton6->SetTextScale(FVector(4, 1, 0));
	PlayerCanvas->AddWidget(DialButton6, DialX, DialY, "DialButton6", "SecondLock");
	DialButton6->SetWidgetScale(FVector(1, 0.5, 1.5));
	DialButton6->SetActorRotation(FRotator(0, 0, 36));
	PlayerCanvas->MoveWidget(DialButton6, DialX - 40.5961714869, DialY + 30.0160369456);

	DialButton7 = Cast<AVRButton>(GetWorld()->SpawnActor(AVRButton::StaticClass()));
	DialButton7->SetButtonText("7");
	DialButton7->SetTextScale(FVector(4, 1, 0));
	PlayerCanvas->AddWidget(DialButton7, DialX, DialY, "DialButton7", "SecondLock");
	DialButton7->SetWidgetScale(FVector(1, 0.5, 1.5));
	DialButton7->SetActorRotation(FRotator(0, 0, 72));
	PlayerCanvas->MoveWidget(DialButton7, DialX - 50.5, DialY + 0.56696798557);

	DialButton8 = Cast<AVRButton>(GetWorld()->SpawnActor(AVRButton::StaticClass()));
	DialButton8->SetButtonText("8");
	DialButton8->SetTextScale(FVector(4, 1, 0));
	PlayerCanvas->AddWidget(DialButton8, DialX, DialY, "DialButton8", "SecondLock");
	DialButton8->SetWidgetScale(FVector(1, 0.5, 1.5));
	DialButton8->SetActorRotation(FRotator(0, 0, -72));
	PlayerCanvas->MoveWidget(DialButton8, DialX - 86.7, DialY - 13.150326255);

	DialButton9 = Cast<AVRButton>(GetWorld()->SpawnActor(AVRButton::StaticClass()));
	DialButton9->SetButtonText("9");
	DialButton9->SetTextScale(FVector(4, 1, 0));
	PlayerCanvas->AddWidget(DialButton9, DialX, DialY, "DialButton9", "SecondLock");
	DialButton9->SetWidgetScale(FVector(1, 0.5, 1.5));
	DialButton9->SetActorRotation(FRotator(0, 0, -36));
	PlayerCanvas->MoveWidget(DialButton9, DialX - 63.5, DialY - 61);

	for (int32 i = 0; i < 10; i++)
	{
		FString temp;
		temp.AppendInt(i);
		ButtonTextArray.Add(temp);
	}

	//Sliders for setting combination
	//Slider 1
	ComboSlider1 = Cast<AVRSlider>(GetWorld()->SpawnActor(AVRSlider::StaticClass()));
	PlayerCanvas->AddWidget(ComboSlider1, 20, PlayerCanvas->CanvasSizeY / 4 - 5, "ComboSlider1", "SetLock2");

	ComboSlider1->ChangeSliderLength(100);

	//Slider 2
	ComboSlider2 = Cast<AVRSlider>(GetWorld()->SpawnActor(AVRSlider::StaticClass()));
	PlayerCanvas->AddWidget(ComboSlider2, 20, 2 * PlayerCanvas->CanvasSizeY / 4 - 5, "ComboSlider1", "SetLock2");

	ComboSlider2->ChangeSliderLength(100);

	//Slider 3
	ComboSlider3 = Cast<AVRSlider>(GetWorld()->SpawnActor(AVRSlider::StaticClass()));
	PlayerCanvas->AddWidget(ComboSlider3, 20, 3 * PlayerCanvas->CanvasSizeY / 4 - 5, "ComboSlider1", "SetLock2");

	ComboSlider3->ChangeSliderLength(100);

	//Text for sliders
	//Text 1
	CombinationText1 = Cast<AVRText>(GetWorld()->SpawnActor(AVRText::StaticClass()));
	PlayerCanvas->AddWidget(CombinationText1, 200, PlayerCanvas->CanvasSizeY / 4 + 30, "CombinationText1", "SetLock2");

	CombinationText1->SetWidgetScale(FVector(2, 2, 2));
	CombinationText1->SetText("0");

	//Text 2
	CombinationText2 = Cast<AVRText>(GetWorld()->SpawnActor(AVRText::StaticClass()));
	PlayerCanvas->AddWidget(CombinationText2, 200, 2 * PlayerCanvas->CanvasSizeY / 4 + 30, "CombinationText2", "SetLock2");

	CombinationText2->SetWidgetScale(FVector(2, 2, 2));
	CombinationText2->SetText("0");

	//Text 3
	CombinationText3 = Cast<AVRText>(GetWorld()->SpawnActor(AVRText::StaticClass()));
	PlayerCanvas->AddWidget(CombinationText3, 200, 3 * PlayerCanvas->CanvasSizeY / 4 + 30, "CombinationText3", "SetLock2");

	CombinationText3->SetWidgetScale(FVector(2, 2, 2));
	CombinationText3->SetText("0");
}

// Called every frame
void AVRLock2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CombinationVal1 = FMath::Ceil(ComboSlider1->GetPositionPercent() * 9);
	CombinationVal2 = FMath::Ceil(ComboSlider2->GetPositionPercent() * 9);
	CombinationVal3 = FMath::Ceil(ComboSlider3->GetPositionPercent() * 9);

	CombinationText1->SetText(FString::Printf(TEXT("%d"), CombinationVal1));
	CombinationText2->SetText(FString::Printf(TEXT("%d"), CombinationVal2));
	CombinationText3->SetText(FString::Printf(TEXT("%d"), CombinationVal3));


	if (LockDial->ButtonClicked())
	{
		//Finished entering code
		if (CheckCode())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Correct Combination!");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Bad Combination!");
		}

		ResetEnteredValues();
	}
	else if (DialButton0->ButtonClicked())
	{
		if (EnteredComboVal1 == -1)
			EnteredComboVal1 = 0;
		else if (EnteredComboVal2 == -1)
			EnteredComboVal2 = 0;
		else if (EnteredComboVal3 == -1)
			EnteredComboVal3 = 0;
	}
	else if (DialButton1->ButtonClicked())
	{
		if (EnteredComboVal1 == -1)
			EnteredComboVal1 = 1;
		else if (EnteredComboVal2 == -1)
			EnteredComboVal2 = 1;
		else if (EnteredComboVal3 == -1)
			EnteredComboVal3 = 1;
	}
	else if (DialButton2->ButtonClicked())
	{
		if (EnteredComboVal1 == -1)
			EnteredComboVal1 = 2;
		else if (EnteredComboVal2 == -1)
			EnteredComboVal2 = 2;
		else if (EnteredComboVal3 == -1)
			EnteredComboVal3 = 2;
	}
	else if (DialButton3->ButtonClicked())
	{
		if (EnteredComboVal1 == -1)
			EnteredComboVal1 = 3;
		else if (EnteredComboVal2 == -1)
			EnteredComboVal2 = 3;
		else if (EnteredComboVal3 == -1)
			EnteredComboVal3 = 3;
	}
	else if (DialButton4->ButtonClicked())
	{
		if (EnteredComboVal1 == -1)
			EnteredComboVal1 = 4;
		else if (EnteredComboVal2 == -1)
			EnteredComboVal2 = 4;
		else if (EnteredComboVal3 == -1)
			EnteredComboVal3 = 4;
	}
	else if (DialButton5->ButtonClicked())
	{
		if (EnteredComboVal1 == -1)
			EnteredComboVal1 = 5;
		else if (EnteredComboVal2 == -1)
			EnteredComboVal2 = 5;
		else if (EnteredComboVal3 == -1)
			EnteredComboVal3 = 5;
	}
	else if (DialButton6->ButtonClicked())
	{
		if (EnteredComboVal1 == -1)
			EnteredComboVal1 = 6;
		else if (EnteredComboVal2 == -1)
			EnteredComboVal2 = 6;
		else if (EnteredComboVal3 == -1)
			EnteredComboVal3 = 6;
	}
	else if (DialButton7->ButtonClicked())
	{
		if (EnteredComboVal1 == -1)
			EnteredComboVal1 = 7;
		else if (EnteredComboVal2 == -1)
			EnteredComboVal2 = 7;
		else if (EnteredComboVal3 == -1)
			EnteredComboVal3 = 7;
	}
	else if (DialButton8->ButtonClicked())
	{
		if (EnteredComboVal1 == -1)
			EnteredComboVal1 = 8;
		else if (EnteredComboVal2 == -1)
			EnteredComboVal2 = 8;
		else if (EnteredComboVal3 == -1)
			EnteredComboVal3 = 8;
	}
	else if (DialButton9->ButtonClicked())
	{
		if (EnteredComboVal1 == -1)
			EnteredComboVal1 = 9;
		else if (EnteredComboVal2 == -1)
			EnteredComboVal2 = 9;
		else if (EnteredComboVal3 == -1)
			EnteredComboVal3 = 9;
	}
}

void AVRLock2::ResetEnteredValues()
{
	EnteredComboVal1 = -1;
	EnteredComboVal2 = -1;
	EnteredComboVal3 = -1;
}

bool AVRLock2::CheckCode()
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