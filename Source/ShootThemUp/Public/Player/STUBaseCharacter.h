// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"

#include "STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UAnimMontage;
class UCameraComponent;
class USpringArmComponent;
class ASTUBaseWeapon;
class USTUHealthComponent;
class USTUWeaponComponent;
class UTextRenderComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter(const FObjectInitializer& ObjInit);

private:
	bool bRunning = false;
	bool bIsMovingForward = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// VARIABLES
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

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
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Moving")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Moving")
	float GetMovementDirection() const;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void OnStartRunning();
	void OnStopRunning();

	void OnHealthChanged(float Health);
	void OnDeath();

	void SpawnWeapon();

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
