// Shoot Them Up Game. All Rights Recieved.

#include "Weapon/Projectile/STUProjectile.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASTUProjectile::ASTUProjectile()
{
        PrimaryActorTick.bCanEverTick = false;
        SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
        SphereComponent->InitSphereRadius(5.0f);
        SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
        SetRootComponent(SphereComponent);

        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->InitialSpeed = 200.0f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.3f;
}

void ASTUProjectile::BeginPlay()
{
        Super::BeginPlay();
        check(SphereComponent);
        check(ProjectileMovementComponent);
        SphereComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
        ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
        SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
        SetLifeSpan(LifeSeconds);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent,
                                     AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp,
                                     FVector NormalImpulse,
                                     const FHitResult& Hit)
{
        if (!GetWorld()) { return; }
        UGameplayStatics::ApplyRadialDamage(GetWorld(),
                                            DamageAmount,
                                            GetActorLocation(),
                                            DamageRaidus,
                                            UDamageType::StaticClass(),
                                            { this, GetOwner() },
                                            GetOwner(),
                                            GetController(),
                                            DoFullDamage,
                                            ECC_Visibility);
        DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRaidus, 24, FColor::Red, false, 5.0f);
        Destroy();
}

AController* ASTUProjectile::GetController() const
{
        const APawn* Pawn = Cast<APawn>(GetOwner());
        return Pawn ? Pawn->GetController() : nullptr;
}
