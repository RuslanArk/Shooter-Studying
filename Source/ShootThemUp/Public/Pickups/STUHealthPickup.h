// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	int32 HealthAmount = 100;
	

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
