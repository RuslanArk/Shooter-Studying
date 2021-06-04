// Shoot Them Up, All right Reserved


#include "Pickups/STUAmmoPickup.h"

#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"
#include "ShootThemUp/STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASTUAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;

	WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
	
	return true;
}
