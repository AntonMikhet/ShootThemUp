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
        void NextWeapon();

protected:
        // Called when the game starts
        virtual void BeginPlay() override;
        virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
        UPROPERTY(EditDefaultsOnly, Category = "General")
        ACharacter* Owner;

        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        FName WeaponEquipSocketName = "WeaponSocket";

        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        FName WeaponArmorySocketName = "ArmorySocket";

        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        ASTUBaseWeapon* CurrentWeapon = nullptr;

public:
        ASTUBaseWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

        UPROPERTY(EditDefaultsOnly, Category = "Animation")
        UAnimMontage* EquipAnimMontage;

private:
        UFUNCTION(BlueprintCallable)
        void SpawnWeapons();
        void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
        void EquipWeapon(int32 WeaponIndex);
        void PlayAnimMontage(UAnimMontage* AnimMontage);

private:
        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        TArray<ASTUBaseWeapon*> Weapons;

        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        int32 CurrentWeaponIndex = 0;
};
