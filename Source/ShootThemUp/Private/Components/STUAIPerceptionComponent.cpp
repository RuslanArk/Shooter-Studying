// Shoot Them Up, All right Reserved


#include "Components/STUAIPerceptionComponent.h"

#include "AIController.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include "ShootThemUp/STUUtils.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceiveActors;	
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.Num() == 0)
	{
		GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PerceiveActors);
		if (PerceiveActors.Num() == 0) return nullptr;
	}

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestEnemy = nullptr;	

	for (const auto PerceiveActor : PerceiveActors)
	{
		const auto PerceivePawn = Cast<APawn>(PerceiveActor);
		const bool AreEnemies = PerceivePawn && STUUtils::AreEnemies(Controller, PerceivePawn->Controller);
		if (!AreEnemies) return nullptr;
		
		const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PerceiveActor);
		if (HealthComponent && !HealthComponent->IsDead())
		{
			float CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestEnemy = PerceiveActor;
			}
		}
	}

	return BestEnemy;
}
