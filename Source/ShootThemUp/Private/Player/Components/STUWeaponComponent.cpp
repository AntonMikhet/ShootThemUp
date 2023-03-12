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

}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* Mesh, const FName& SocketName) { }

void USTUWeaponComponent::SpawnWeapons()
{
        if (!GetWorld() || !Owner) { return; }

        for (const auto WeaponClass : WeaponClasses)
        {
                const auto Weapon = Cast<ASTUBaseWeapon>(GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass, Owner->GetTransform()));
                if (!Weapon) { }
                Weapon->SetOwner(Owner);
                Weapon->SetController();
                Weapons.Add(Weapon);

                AttachWeaponToSocket(Weapon, Owner->GetMesh(), WeaponArmorySocketName);
        }
        CurrentWeapon->WeaponOwner = Owner;
        CurrentWeapon->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponEquipSocketName);

}
