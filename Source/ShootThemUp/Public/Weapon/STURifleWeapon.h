// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()


public:
	ASTURifleWeapon();

	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void MakeShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	void MakeDamage(FHitResult& HitResult);
private:
	FTimerHandle ShotTimerHandle;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float DamageAmount = 10.f;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float BulletSpread = 1.5f;
	
};
