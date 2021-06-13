// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASTUAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	USTUAIPerceptionComponent* STUAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";
};
