// Shoot Them Up Game. All Rights Recieved.

#include "Components/STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/STUBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{

        PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::StartFire()
{
        if (!CurrentWeapon) { return; }
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

        Owner = Cast<ACharacter>(GetOwner());

        SpawnWeapons();
        EquipWeapon(CurrentWeaponIndex);

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

        for (const auto WeaponClass : WeaponClasses)
        {
                const auto Weapon = Cast<ASTUBaseWeapon>(GetWorld()->SpawnActorDeferred<ASTUBaseWeapon>(WeaponClass, Owner->GetTransform()));
                if (!Weapon) { return; }

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
        if (CurrentWeapon)
        {
                AttachWeaponToSocket(CurrentWeapon, Owner->GetMesh(), WeaponArmorySocketName);

        }
        CurrentWeapon = Weapons[WeaponIndex];
        AttachWeaponToSocket(CurrentWeapon, Owner->GetMesh(), WeaponEquipSocketName);
        PlayAnimMontage(EquipAnimMontage);

}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
        if (!Owner) { return; }
        PlayAnimMontage(AnimMontage);
}

void USTUWeaponComponent::NextWeapon()
{
        CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
        EquipWeapon(CurrentWeaponIndex);
}
