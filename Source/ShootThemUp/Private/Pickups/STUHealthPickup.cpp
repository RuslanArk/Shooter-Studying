// Shoot Them Up, All right Reserved


#include "Pickups/STUHealthPickup.h"



DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(LogHealthPickup, Display, TEXT("Health pickup was taken"));
	return true;
}
