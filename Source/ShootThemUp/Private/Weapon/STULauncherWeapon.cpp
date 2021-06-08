// Shoot Them Up, All right Reserved


#include "Weapon/STULauncherWeapon.h"

#include "Weapon/STUProjectile.h"

#include "Weapon/STUProjectile.h"

ASTULauncherWeapon::ASTULauncherWeapon()
{
	
}

void ASTULauncherWeapon::StartFire()
{
	MakeShot();	
}

void ASTULauncherWeapon::StopFire()
{
	
}

void ASTULauncherWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty()) return;

	FVector TraceStart;
	FVector TraceEnd;

	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	
	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}

	DecreaseAmmo();
	SpawnMuzzleFX();
}