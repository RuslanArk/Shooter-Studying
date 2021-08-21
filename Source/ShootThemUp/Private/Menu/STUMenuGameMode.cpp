// Shoot Them Up, All right Reserved


#include "Menu/STUMenuGameMode.h"

#include "Menu/STUMenuPlayerController.h"
#include "Menu/UI/STUMenuHUD.h"

ASTUMenuGameMode::ASTUMenuGameMode()
{
	PlayerControllerClass = ASTUMenuPlayerController::StaticClass();
	HUDClass = ASTUMenuHUD::StaticClass();
}
