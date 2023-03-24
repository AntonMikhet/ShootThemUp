// Shoot Them Up Game. All Rights Recieved.

#include "Weapon/STUBaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "STUBaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTUBaseWeapon::ASTUBaseWeapon()
{
        // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
        PrimaryActorTick.bCanEverTick = false;

        WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
        SetRootComponent(WeaponMesh);

}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
        Super::BeginPlay();
        Character = Cast<ACharacter>(GetOwner());
        WeaponComponent = Cast<USTUWeaponComponent>(Character->GetComponentByClass(USTUWeaponComponent::StaticClass()));
        CurrentAmmo = DefaultAmmo;

        check(WeaponMesh);
        check(CharacterController);
        check(Character);
        check(WeaponComponent);
        checkf(DefaultAmmo.Bullets > 0, TEXT("Default cinst couldn`t be less or equal zero"))

}

FVector ASTUBaseWeapon::GetSocketLocation()
{
        return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, FVector TraceStart, FVector TraceEnd)
{
        if (!GetWorld()) { return; }
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(GetOwner());
        GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
}

void ASTUBaseWeapon::MakeShot() { }

void ASTUBaseWeapon::StartFire() {}

void ASTUBaseWeapon::StopFire() {}

void ASTUBaseWeapon::SetController()
{
        CharacterController = Cast<ACharacter>(GetOwner())->GetController();
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
        if (!GetWorld()) { return false; }

        FVector ViewLocation;
        FRotator ViewRotation;

        CharacterController->GetPlayerViewPoint(ViewLocation, ViewRotation);

        TraceStart = ViewLocation;
        TraceEnd = TraceStart + ViewRotation.Vector() * TraceMaxDistance;
        return true;
}

void ASTUBaseWeapon::DecreaseAmmo()
{
        if (CurrentAmmo.Bullets == 0)
        {
                UE_LOG(LogBaseWeapon, Warning, TEXT("---------Clip is Empty---------"))
                return;
        }
        CurrentAmmo.Bullets--;
        LogAmmo();
        if (IsClipEmpty() && !IsAmmoEmpty())
        {
                StopFire();
                OnClipEmptySignature.Broadcast();
        }

}

void ASTUBaseWeapon::ChangeClip()
{
        if (CurrentAmmo.Infinite)
        {
                if (CurrentAmmo.Clips == 0)
                {
                        UE_LOG(LogBaseWeapon, Warning, TEXT("---------No more clip---------"))
                        return;
                }
                CurrentAmmo.Clips--;
        }
        CurrentAmmo.Bullets = DefaultAmmo.Bullets;
        UE_LOG(LogBaseWeapon, Display, TEXT("---------Change Clip---------"))
}

bool ASTUBaseWeapon::CanReload() const
{
        return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool ASTUBaseWeapon::IsAmmoEmpty() const
{
        return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const
{
        return CurrentAmmo.Bullets == 0;
}

void ASTUBaseWeapon::LogAmmo()
{
        FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + "/";
        AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt((CurrentAmmo.Clips));

        UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);

}
