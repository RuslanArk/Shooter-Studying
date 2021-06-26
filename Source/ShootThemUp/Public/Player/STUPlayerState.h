// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int32 GetTeamID() { return TeamID; }
	void SetTeamID(int32 NewTeamID) { TeamID = NewTeamID; }

	FLinearColor GetTeamColor() { return TeamColor; }
	void SetTeamColor(FLinearColor NewTeamColor) { TeamColor = NewTeamColor; }
	
protected:	
	
private:
	int32 TeamID = 0;
	FLinearColor TeamColor;
};
