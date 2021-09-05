// Shoot Them Up, All right Reserved


#include "UI/STUHealthBarWidget.h"

#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthPercent(float NewPercent)
{
	if (!HealthProgressBar) return;

	const auto HealthBarVisibility = (NewPercent > PercentVisibilityThreshold || FMath::IsNearlyZero(NewPercent)) //
												? ESlateVisibility::Hidden //
												: ESlateVisibility::Visible;

	HealthProgressBar->SetVisibility(HealthBarVisibility);

	const auto HealthBarColor = NewPercent > PercentVisibilityThreshold ? GoodColor : BadColor;
	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);
	HealthProgressBar->SetPercent(NewPercent);
}
