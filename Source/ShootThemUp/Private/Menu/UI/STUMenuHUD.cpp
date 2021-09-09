// Shoot Them Up, All right Reserved


#include "Menu/UI/STUMenuHUD.h"
#include "UI/STUBaseWidget.h"

void ASTUMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto MenuWidget = CreateWidget<USTUBaseWidget>(GetWorld(), MainMenuClass);
	if (MenuWidget)
	{
		MenuWidget->AddToViewport();
		MenuWidget->Show();
	}
}
