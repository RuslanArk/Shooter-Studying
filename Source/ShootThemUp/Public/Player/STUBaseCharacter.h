// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"

#include "STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UAnimMontage;
class ASTUBaseWeapon;
class USTUHealthComponent;
class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter(const FObjectInitializer& ObjInit);

private:

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// VARIABLES
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float LifeSpanOnDeath = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.f, 1200.f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamage = FVector2D(10.f, 100.f);

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName MaterialColorName = "Paint Color";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	UFUNCTION(BlueprintCallable, Category = "Moving")
	virtual bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Moving")
	float GetMovementDirection() const;

	void SetPlayerColor(const FLinearColor& Color);

protected:
	virtual void OnDeath();

	virtual void OnHealthChanged(float Health, float HealthDelta);
	
private:
	void SpawnWeapon();

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
