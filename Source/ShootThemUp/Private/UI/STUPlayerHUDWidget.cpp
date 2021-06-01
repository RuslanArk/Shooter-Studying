// Shoot Them Up, All right Reserved


#include "UI/STUPlayerHUDWidget.h"

#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const APawn* Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
	const USTUHealthComponent* HealthComponent = Cast<USTUHealthComponent>(Component);
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const APawn* Player = GetOwningPlayerPawn();
	if (!Player) return false;

	const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
	const USTUWeaponComponent* WeaponComponent = Cast<USTUWeaponComponent>(Component);
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}
