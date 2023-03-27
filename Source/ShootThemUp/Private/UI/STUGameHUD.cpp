// Shoot Them Up Game. All Rights Recieved.

#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void ASTUGameHUD::DrawHUD()
{
        Super::DrawHUD();

        // DrawCrossHair();
}

void ASTUGameHUD::BeginPlay()
{
        Super::BeginPlay();

        UUserWidget* PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHudWidgetClass);
        if (PlayerHUDWidget)
        {
                PlayerHUDWidget->AddToViewport();
        }
}

void ASTUGameHUD::DrawCrossHair()
{
        const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
        constexpr float HalfLineSize = 15.0f;
        constexpr float LineThickness = 4.0f;
        const FLinearColor LinearColor = FLinearColor::Black;

        DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LinearColor, LineThickness);
        DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LinearColor, LineThickness);
}
