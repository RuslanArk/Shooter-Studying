// Shoot Them Up, All right Reserved


#include "AI/STUAICharacter.h"

#include "BrainComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "STUAIController.h"
#include "STUAIWeaponComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit)
: Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTUAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.f, 0.0f);
	}
}

void ASTUAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto STUAIController = Cast<AAIController>(Controller);
	if (STUAIController && STUAIController->BrainComponent)
	{
		STUAIController->BrainComponent->Cleanup();
	}
}
