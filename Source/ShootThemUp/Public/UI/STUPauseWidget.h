// Shoot Them Up, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUPauseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void OnPauseCleared();

public:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;
};
