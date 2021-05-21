// Shoot Them Up, All right Reserved


#include "Weapon/STURifleWeapon.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ASTURifleWeapon::ASTURifleWeapon()
{
	
}

void ASTURifleWeapon::StartFire()
{
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);
}

void ASTURifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::MakeShot()
{
	if (!GetWorld()) return;

	FVector TraceStart;
	FVector TraceEnd;

	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	
	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 5.f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.0f);
		
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Green, false, 5.f, 0, 3.0f);
	}
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPort(ViewLocation, ViewRotation)) return false;

	//const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	TraceStart = ViewLocation; //SocketTransform.GetLocation();
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector TraceDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad); //SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + TraceDirection * MaxTraceRange;

	return true;
}

void ASTURifleWeapon::MakeDamage(FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}