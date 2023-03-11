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

        SpawnWeapon();

}

void USTUWeaponComponent::SpawnWeapon()
{
        if (!GetWorld()) { return; }
        if (!Owner) { return; }

        CurrentWeapon = Cast<ASTUBaseWeapon>(GetWorld()->SpawnActorDeferred<ASTUBaseWeapon>(WeaponClass, Owner->GetTransform()));
        CurrentWeapon->WeaponOwner = Owner;
        UGameplayStatics::FinishSpawningActor(CurrentWeapon, Owner->GetTransform());

        if (!CurrentWeapon) { return; }
        CurrentWeapon->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);

}
