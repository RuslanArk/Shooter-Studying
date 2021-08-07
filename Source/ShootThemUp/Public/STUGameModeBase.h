// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "STUGameModeBase.generated.h"

class AAIController;

constexpr static int32 MinRoundTimeForRespawn = 10;

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASTUGameModeBase();

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void Killed(AController* KillerController, AController* VictimController);

	FGameData GetGameData() { return GameData; }
	int32 GetCurrentRoundNum() { return CurrentRound; }
	int32 GetRoundSecondsRemaining() { return RoundCountDown; }

	void RespawnRequest(AController* Controller);

private:
	void SpawnBots();
	void StartRound();
	void GameTimerUpdate();

	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);

	void CreateTeamsInfo();
	FLinearColor DetermineColorByTeamID(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);

	void LogPlayerInfo();

	void RespawnStart(AController* Controller);

	void GameOver();

	void SetMatchState(ESTUMatchState State);

public:
	FOnMatchStateChangedSignature OnMatchStateChanged;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;



private:
	int32 CurrentRound = 1;
	int32 RoundCountDown = 0;
	FTimerHandle GameRoundTimerHandle;

	ESTUMatchState MatchState = ESTUMatchState::WaitingToStart;

};
