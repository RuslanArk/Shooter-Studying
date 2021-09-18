// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:
	ASTUBasePickup();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups")
	float RespawnTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups")
	USoundCue* PickupWasTakenSound;

private:
	float RotationYaw = 0.0f;
	FTimerHandle RespawnTimer;

public:
	virtual void Tick(float DeltaTime) override;
	bool CouldBeTaken() const;

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn);
	
	void PickupWasTaken();
	void Respawn();
	void GenerateRotationYaw();

};
