// Shoot Them Up, All right Reserved


#include "Player/STUPlayerController.h"

#include "Components/STURespawnComponent.h"

ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");
}
