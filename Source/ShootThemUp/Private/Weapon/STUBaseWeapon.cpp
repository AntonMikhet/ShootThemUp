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
        CollisionParams.AddIgnoredActor(GetOwner());
        GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
}

void ASTUBaseWeapon::MakeShot() {}

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
