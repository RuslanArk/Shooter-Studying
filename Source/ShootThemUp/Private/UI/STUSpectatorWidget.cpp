// Shoot Them Up, All right Reserved


#include "UI/STUSpectatorWidget.h"

#include "Components/STURespawnComponent.h"
#include "ShootThemUp/STUUtils.h"

bool USTUSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(GetOwningPlayer());
	if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}
