// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTURespawnComponent();

	void Respawn(int32 RespawnTime);

private:
	void RespawnTimerUpdate();

	FTimerHandle RespawnTimer;
	int32 RespawnCountDown = 5;

};
