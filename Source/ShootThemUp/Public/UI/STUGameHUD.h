// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUCoreTypes.h"
#include "STUGameHUD.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
        GENERATED_BODY()

public:
        virtual void DrawHUD() override;

protected:
        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
        TSubclassOf<UUserWidget> PlayerHudWidgetClass;

        virtual void BeginPlay() override;

private:
        void DrawCrossHair();


};
