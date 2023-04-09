#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.generated.h"

class ASTUBaseWeapon;
DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);


USTRUCT(BlueprintType)
struct FWeaponData
{
        GENERATED_USTRUCT_BODY()

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
        TSubclassOf<ASTUBaseWeapon> WeaponClasses;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
        UAnimMontage* ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FAmmoData
{
        GENERATED_USTRUCT_BODY()

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapons")
        int32 Bullets;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapons", meta = (EditCondition = "!Infinite"))
        int32 Clips;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapons")
        bool Infinite;


};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
        GENERATED_USTRUCT_BODY()

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
        UTexture2D* MainIcon = nullptr;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
        UTexture2D* CrosshairIcon = nullptr;
};

/// Health
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);
