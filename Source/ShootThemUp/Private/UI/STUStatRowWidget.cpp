// Shoot Them Up, All right Reserved


#include "UI/STUStatRowWidget.h"



#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUStatRowWidget::SetPlayerName(const FText& Name)
{
	if (!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Name);
}

void USTUStatRowWidget::SetKills(const FText& Kills)
{
	if (!KillsTextBlock) return;
	KillsTextBlock->SetText(Kills);
}

void USTUStatRowWidget::SetDeaths(const FText& Deaths)
{
	if (!DeathsTextBlock) return;
	DeathsTextBlock->SetText(Deaths);
}

void USTUStatRowWidget::SetTeam(const FText& Team)
{
	if (!TeamTextBlock) return;
	TeamTextBlock->SetText(Team);
}

void USTUStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if (!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
