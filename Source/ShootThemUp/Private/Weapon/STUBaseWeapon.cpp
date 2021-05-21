// Shoot Them Up, All right Reserved

#include "Weapon/STUBaseWeapon.h"

#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Viewports.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
	SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
}

void ASTUBaseWeapon::StartFire()
{
	 
}

void ASTUBaseWeapon::StopFire()
{
	
}


void ASTUBaseWeapon::MakeShot()
{
	
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character) return nullptr;

	return Character->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPort(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const APlayerController* Controller = GetPlayerController();
	if (!Controller) return false;
	
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPort(ViewLocation, ViewRotation)) return false;

	//const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	TraceStart = ViewLocation; //SocketTransform.GetLocation();
	const FVector TraceDirection = ViewRotation.Vector(); //SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + TraceDirection * MaxTraceRange;

	return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}


