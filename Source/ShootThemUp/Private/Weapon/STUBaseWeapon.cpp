// Shoot Them Up Game. All Rights Recieved.

#include "Weapon/STUBaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "STUBaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/STUHealthComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

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
        CharacterController = WeaponOwner->GetController();
        check(WeaponMesh);
        check(CharacterController);

}

FVector ASTUBaseWeapon::GetSocketLocation()
{
        return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, FVector TraceStart, FVector TraceEnd)
{
        if (!GetWorld()) { return; }
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(WeaponOwner);
        GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
}

void ASTUBaseWeapon::MakeDamage(AActor* DamagedActor, float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
        if (!DamagedActor && Damage == 0) { return; }
        DamagedActor->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void ASTUBaseWeapon::MakeShot()
{
        if (!GetWorld()) { return; }
        if (!WeaponOwner) { return; }

        FVector ViewLocation;
        FRotator ViewRotation;
        CharacterController->GetPlayerViewPoint(ViewLocation, ViewRotation);

        const FVector TraceStart = ViewLocation;
        const float HalfRad = FMath::DegreesToRadians(BulletSpread);
        const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
        const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
        FHitResult HitResult;

        MakeHit(HitResult, TraceStart, TraceEnd);

        if (HitResult.bBlockingHit)
        {

                DrawDebugLine(GetWorld(), GetSocketLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 1.0f);
                DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 10, FColor::Red, false, 4.0f);
                MakeDamage(HitResult.GetActor(), DamageAmount, FDamageEvent(), CharacterController, WeaponOwner);
        }
        else
        {
                DrawDebugLine(GetWorld(), GetSocketLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 1.0f);
        }
}

void ASTUBaseWeapon::StartFire()
{
        MakeShot();
        GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, this, &ASTUBaseWeapon::MakeShot, FireRate, true);

}

void ASTUBaseWeapon::StopFire()
{
        GetWorld()->GetTimerManager().ClearTimer(ShotTimerHandle);
}
