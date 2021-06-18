// Shoot Them Up, All right Reserved


#include "AI/Decorator/STUNeedAmmoDecorator.h"
#include "AIController.h"
#include "Components/STUWeaponComponent.h"
#include "ShootThemUp/STUUtils.h"

USTUNeedAmmoDecorator::USTUNeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool USTUNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);
}
