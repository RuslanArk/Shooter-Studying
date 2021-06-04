// Shoot Them Up, All right Reserved


#include "Pickups/STUHealthPickup.h"

#include "STUHealthComponent.h"
#include "ShootThemUp/STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
}
