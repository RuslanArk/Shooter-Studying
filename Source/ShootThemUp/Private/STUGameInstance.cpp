// Shoot Them Up, All right Reserved


#include "STUGameInstance.h"

#include "Sound/STUBlueprintFuncLib.h"

void USTUGameInstance::ToggleVolume()
{
	USTUBlueprintFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}
