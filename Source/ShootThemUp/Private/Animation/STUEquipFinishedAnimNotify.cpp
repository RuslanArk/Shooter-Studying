// Shoot Them Up, All right Reserved


#include "Animation/STUEquipFinishedAnimNotify.h"

void USTUEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
