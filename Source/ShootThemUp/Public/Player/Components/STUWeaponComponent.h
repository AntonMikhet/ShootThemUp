// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
        GENERATED_BODY()

public:
        USTUWeaponComponent();
        virtual void BeginPlay() override;
        virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

        void StartFire();
        void StopFire();
        void NextWeapon();
        void Reload();
        bool CanFire() const;
        bool CanEquip() const;
        bool CanReload() const;
        ASTUBaseWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

protected:
        UPROPERTY(EditDefaultsOnly, Category = "General")
        ACharacter* Owner;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
        FName WeaponEquipSocketName = "WeaponSocket";

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
        FName WeaponArmorySocketName = "ArmorySocket";

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
        TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
        ASTUBaseWeapon* CurrentWeapon = nullptr;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapon")
        TArray<FWeaponData> WeaponData;

public:
        UPROPERTY(EditDefaultsOnly, Category = "Animation")
        UAnimMontage* EquipAnimMontage;

private:
        UFUNCTION(BlueprintCallable)
        void SpawnWeapons();
        void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
        void EquipWeapon(int32 WeaponIndex);
        void PlayAnimMontage(UAnimMontage* AnimMontage);
        void InitAnimations();
        void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
        void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
        void OnEmptyClip();
        void OnChangeCLip();

private:
        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        TArray<ASTUBaseWeapon*> Weapons;

        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        int32 CurrentWeaponIndex = 0;

        UPROPERTY(EditDefaultsOnly, Category = "Weapon")
        UAnimMontage* CurrentReloadAnimMontage = nullptr;

        bool EquipAnimInProgress = false;
        bool ReloadAnimInProgress = false;

};
