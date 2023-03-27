// Shoot Them Up Game. All Rights Recieved.

#include "Components/STUWeaponComponent.h"

#include "AnimNotify/AnimUnitls.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/STUBaseWeapon.h"
#include "AnimNotify/STUEquipFinishedAnimNotify.h"
#include "AnimNotify/STUAnimNotify.h"
#include "AnimNotify/STUReloadFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{

        PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::StartFire()
{
        if (!CanFire()) { return; }
        CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
        if (!CurrentWeapon) { return; }
        CurrentWeapon->StopFire();

}

// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
        Super::BeginPlay();
        checkf(WeaponClasses.Num() > 0, TEXT("WeaponClasses is empty"));
        Owner = Cast<ACharacter>(GetOwner());
        SpawnWeapons();
        EquipWeapon(CurrentWeaponIndex);
        InitAnimations();

}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
        Super::EndPlay(EndPlayReason);

        for (auto Weapon : Weapons)
        {
                Weapon->StopFire();
                Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
                // Weapon->Destroy();
                Weapon->WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
                Weapon->WeaponMesh->SetSimulatePhysics(true);
        }
        // CurrentWeapon = nullptr;
        Weapons.Empty();

}

void USTUWeaponComponent::SpawnWeapons()
{
        if (!GetWorld() || !Owner) { return; }

        for (const auto OnewWeaponData : WeaponData)
        {
                const auto Weapon = Cast<ASTUBaseWeapon>(GetWorld()->SpawnActorDeferred<ASTUBaseWeapon>(OnewWeaponData.WeaponClasses, Owner->GetTransform()));
                if (!Weapon) { continue; }

                Weapon->OnClipEmptySignature.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
                Weapon->SetOwner(Owner);
                Weapon->SetController();
                Weapon->FinishSpawning(Owner->GetTransform());

                Weapons.Add(Weapon);
                AttachWeaponToSocket(Weapon, Owner->GetMesh(), WeaponArmorySocketName);
        }
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
        if (!Weapon || !SceneComponent) { return; }
        Weapon->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
        if (!Owner) { return; }
        if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
        {
                UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid weapon index"))
                return;
        }
        if (CurrentWeapon)
        {
                AttachWeaponToSocket(CurrentWeapon, Owner->GetMesh(), WeaponArmorySocketName);

        }
        CurrentWeapon = Weapons[WeaponIndex];

        const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
        {
                return Data.WeaponClasses == CurrentWeapon->GetClass();
        });

        CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
        AttachWeaponToSocket(CurrentWeapon, Owner->GetMesh(), WeaponEquipSocketName);
        EquipAnimInProgress = true;
        PlayAnimMontage(EquipAnimMontage);

}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
        if (!Owner) { return; }

        Owner->PlayAnimMontage(AnimMontage);
}

void USTUWeaponComponent::InitAnimations()
{
        const auto EquipFinishedNotify = AnimUnitls::FindFirstNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);
        if (EquipFinishedNotify)
        {
                EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
        }
        else
        {
                UE_LOG(LogWeaponComponent, Error, TEXT("Equip notify is empty"))
                checkNoEntry();
        }

        for (const auto OneWeaponData : WeaponData)
        {
                const auto ReloadFinishedNotify = AnimUnitls::FindFirstNotifyByClass<USTUReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
                if (!ReloadFinishedNotify)
                {

                        UE_LOG(LogWeaponComponent, Error, TEXT("Reload notify is empty"))
                        checkNoEntry();
                        continue;
                }

                ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);

        }

}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
        if (!Owner || Owner->GetMesh() != MeshComponent) { return; }

        EquipAnimInProgress = false;

}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{

        if (!Owner || Owner->GetMesh() != MeshComponent) { return; }

        ReloadAnimInProgress = false;
}

void USTUWeaponComponent::OnEmptyClip()
{
        OnChangeCLip();
}

void USTUWeaponComponent::OnChangeCLip()
{
        if (!CanReload()) { return; }

        CurrentWeapon->StopFire();
        CurrentWeapon->ChangeClip();
        ReloadAnimInProgress = true;
        PlayAnimMontage(CurrentReloadAnimMontage);
}

bool USTUWeaponComponent::CanFire() const
{
        return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USTUWeaponComponent::CanEquip() const
{
        return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USTUWeaponComponent::CanReload() const
{
        return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

bool USTUWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
        if (CurrentWeapon)
        {
                UIData = CurrentWeapon->GetUIData();
                return true;
        }
        return false;
}

void USTUWeaponComponent::NextWeapon()
{
        if (!CanEquip()) { return; }
        StopFire();
        CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
        EquipWeapon(CurrentWeaponIndex);

}

void USTUWeaponComponent::Reload()
{
        OnChangeCLip();
}
