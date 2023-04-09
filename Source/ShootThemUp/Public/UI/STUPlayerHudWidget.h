// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "Components/STUWeaponComponent.h"
#include "STUPlayerHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHudWidget : public UUserWidget
{
        GENERATED_BODY()
        virtual void NativeConstruct() override;

protected:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
        APawn* Player;

public:
        UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI|Get")
        float GetHealthPercent() const;

        UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI|Get")
        FString GetCurrentAmountAmmo() const;

        UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI|Get")
        bool GetWeaponCurrentUIData(FWeaponUIData& UIData) const;

        UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI|Get")
        bool GetWeaponCurrentAmmoData(FAmmoData& AmmoData) const;

        UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI|Get")
        bool GetWeaponAmmoDefaultData(FAmmoData& AmmoData) const;

protected:
        UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI|Get")
        bool IsPlayerAlive() const;

        UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI|Get")
        bool IsPlayerSpectating() const;

};
