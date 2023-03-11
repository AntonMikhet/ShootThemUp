// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
        GENERATED_BODY()

public:
        // Sets default values for this component's properties
        USTUWeaponComponent();

        void StartFire();
        void StopFire();

protected:
        // Called when the game starts
        virtual void BeginPlay() override;

        UPROPERTY(EditDefaultsOnly, Category = "General")
        ACharacter* Owner;

        UFUNCTION(BlueprintCallable)
        void SpawnWeapon();

        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        FName WeaponSocket = "WeaponSocket";

        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        TSubclassOf<ASTUBaseWeapon> WeaponClass;

        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        ASTUBaseWeapon* CurrentWeapon = nullptr;

public:
        ASTUBaseWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

};
