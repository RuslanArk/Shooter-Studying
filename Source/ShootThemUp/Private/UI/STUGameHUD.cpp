// Shoot Them Up, All right Reserved


#include "UI/STUGameHUD.h"

#include "Engine/Canvas.h"

ASTUGameHUD::ASTUGameHUD()
{
	
}

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void ASTUGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);

	const float HalfLineSize = 10.f;
	const float LineThickness = 2.f;
	FLinearColor LineColor = FLinearColor::Green;
	
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max +HalfLineSize, LineColor, LineThickness);
}
