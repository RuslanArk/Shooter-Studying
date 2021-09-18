// Shoot Them Up, All right Reserved


#include "Player/STUPlayerController.h"

#include "STUGameModeBase.h"
#include "Components/STURespawnComponent.h"
#include "GameFramework/GameModeBase.h"
#include "STUGameInstance.h"

ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");
}

void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
		}
	}
}

void ASTUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();	
	if (!InputComponent) return;

	InputComponent->BindAction("PauseMenu", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
	InputComponent->BindAction("Mute", IE_Pressed, this, &ASTUPlayerController::OnMuteSound);
}

void ASTUPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState State)
{
	if (State == ESTUMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void ASTUPlayerController::OnMuteSound()
{
	if (!GetWorld()) return;

	const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!GameInstance) return;

	GameInstance->ToggleVolume();
}
