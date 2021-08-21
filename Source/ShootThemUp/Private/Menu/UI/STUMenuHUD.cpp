// Shoot Them Up, All right Reserved


#include "Menu/UI/STUMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASTUMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuClass);
	if (MenuWidget)
	{
		MenuWidget->AddToViewport();
	}
}
