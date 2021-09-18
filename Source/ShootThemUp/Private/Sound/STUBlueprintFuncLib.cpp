// Shoot Them Up, All right Reserved


#include "Sound/STUBlueprintFuncLib.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUBlueprintFuncLib, All, All);

void USTUBlueprintFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
	if (!SoundClass) return;

	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);

	UE_LOG(LogSTUBlueprintFuncLib, Display, TEXT("Sound class %s volume has changed to: %f"), *SoundClass->GetName(), //
		SoundClass->Properties.Volume);
}

void USTUBlueprintFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
	if (!SoundClass) return;

	const float NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
	SetSoundClassVolume(SoundClass, NextVolume);
}
