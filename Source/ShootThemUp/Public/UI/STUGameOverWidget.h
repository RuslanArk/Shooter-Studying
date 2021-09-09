// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"

class UButton;
class UVerticalBox;

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public USTUBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

private:
	void OnMatchStateChaged(ESTUMatchState State);
	void UpdatePlayerStat();

	UFUNCTION()
	void OnResetLevel();

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;

};
