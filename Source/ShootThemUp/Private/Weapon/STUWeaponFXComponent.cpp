// Shoot Them Up, All right Reserved


#include "Weapon/STUWeaponFXComponent.h"

#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"


USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	FImpactData ImpactEffect = DefaultImpactData;

	if (Hit.PhysMaterial.IsValid())
	{
		const UPhysicalMaterial* PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{			
			ImpactEffect = ImpactDataMap[PhysMat];
		}
	}
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		ImpactEffect.NiagaraEffect,
		Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation());

	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(),
		ImpactEffect.DecalData.Material,
		ImpactEffect.DecalData.Size,
		Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation());

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactEffect.DecalData.LifeSpan, ImpactEffect.DecalData.FadeOutTime);
	}
}


