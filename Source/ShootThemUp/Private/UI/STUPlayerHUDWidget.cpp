// Shoot Them Up, All right Reserved


#include "UI/STUPlayerHUDWidget.h"

#include "Components/ProgressBar.h"

#include "STUPlayerState.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "ShootThemUp/STUUtils.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::GetCurrentAmmoData(FAmmoData& AmmoData) const
{
	const USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentAmmoData(AmmoData);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	const USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

int32 USTUPlayerHUDWidget::GetKillsNum() const
{
	const auto Controller = GetOwningPlayer();
	if (!Controller) return 0;

	const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

FString USTUPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
	const int32 MaxLen = 3;
	const TCHAR PrefixSymbol = '0';

	auto BulletStr = FString::FromInt(BulletsNum);
	const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

	if (SymbolsNumToAdd)
	{
		BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
	}

	return BulletStr;
}

void USTUPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
}

void USTUPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(NewPawn);
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
	}
	UpdateHealthBar();
}

void USTUPlayerHUDWidget::UpdateHealthBar()
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
	}
}

void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
	UpdateHealthBar();
}
