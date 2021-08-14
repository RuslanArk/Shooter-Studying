// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "STUStatRowWidget.generated.h"

class UImage;
class UTextBlock;


UCLASS()
class SHOOTTHEMUP_API USTUStatRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerName(const FText& Name);
	void SetKills(const FText& Kills);
	void SetDeaths(const FText& Deaths);
	void SetTeam(const FText& Team);
	void SetPlayerIndicatorVisibility(bool Visible);
	
	protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillsTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeathsTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* PlayerIndicatorImage;
};
