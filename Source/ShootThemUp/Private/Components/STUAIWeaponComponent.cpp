// Shoot Them Up, All right Reserved


#include "Components/STUAIWeaponComponent.h"

#include "STUBaseWeapon.h"

void USTUAIWeaponComponent::StartFire()
{
	if (!CanFire()) return;
	if (CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void USTUAIWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;
	int32 NextWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

	while (NextWeaponIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextWeaponIndex]->IsAmmoEmpty()) break;
		NextWeaponIndex = (NextWeaponIndex + 1) % Weapons.Num();
	}

	if (CurrentWeaponIndex != NextWeaponIndex)
	{
		CurrentWeaponIndex = NextWeaponIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}
