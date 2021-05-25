// Shoot Them Up, All right Reserved


#include "Components/STUWeaponComponent.h"

#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

#include "Animation/STUEquipFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAnimation();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;

	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
		if (!Weapon) continue;

		Weapon->SetOwner(GetOwner());
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}	
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent,
    const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);

	PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::StartFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* MontageToPlay)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(MontageToPlay);
}

void USTUWeaponComponent::InitAnimation()
{
	if (!EquipAnimMontage) return;

	const auto NotifyEvents = EquipAnimMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents)
	{
		auto EquipNotify = Cast<USTUEquipFinishedAnimNotify>(NotifyEvent.Notify);
		if (EquipNotify)
		{
			EquipNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
			break;
		}
	}
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (Character->GetMesh() == MeshComponent)
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("Notify worked!"));	
	}	
}
