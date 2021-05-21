// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	ASTUBaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon Mesh")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxTraceRange = 1500.0f;

	

	virtual void BeginPlay() override;

	virtual void MakeShot();
	virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;
	
	APlayerController* GetPlayerController() const;	
	bool GetPlayerViewPort(FVector &ViewLocation, FRotator &ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;

	void MakeHit(FHitResult &HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	
	
	
	
};
