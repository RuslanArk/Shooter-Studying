// Shoot Them Up, All right Reserved


#include "UI/STUGameHUD.h"

#include "UI/STUBaseWidget.h"
#include "Engine/Canvas.h"

#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);

ASTUGameHUD::ASTUGameHUD()
{
	
}

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawCrossHair();
}

void ASTUGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(ESTUMatchState::InProgress, CreateWidget<USTUBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(ESTUMatchState::Pause, CreateWidget<USTUBaseWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(ESTUMatchState::GameOver, CreateWidget<USTUBaseWidget>(GetWorld(), GameOverWidgetClass));

	for (auto& WidgetPair : GameWidgets)
	{
		const auto GameWidget = WidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
		}
	}
}

void ASTUGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);

	const float HalfLineSize = 10.f;
	const float LineThickness = 2.f;
	FLinearColor LineColor = FLinearColor::Green;
	
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max +HalfLineSize, LineColor, LineThickness);
}

void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
	}
	
	UE_LOG(LogSTUGameHUD, Warning, TEXT("match state changed: %s"), *UEnum::GetValueAsString(State));
}
