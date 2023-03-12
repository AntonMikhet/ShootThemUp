// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
        GENERATED_BODY()

public:
        ASTUProjectile();

protected:
        virtual void BeginPlay() override;

protected:
        //Components

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
        USphereComponent* SphereComponent;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
        UProjectileMovementComponent* ProjectileMovementComponent;

protected:
        //Protected Variable

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings")
        float DamageRaidus = 200.0f;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings")
        float DamageAmount = 50.0f;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings")
        bool DoFullDamage = false;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings")
        float LifeSeconds = 5.0f;

protected:
        // Protected Function

        UFUNCTION()
        void OnProjectileHit(UPrimitiveComponent* HitComponent,
                             AActor* OtherActor,
                             UPrimitiveComponent* OtherComp,
                             FVector NormalImpulse,
                             const FHitResult& Hit);

        AController* GetController() const;

public:
        // Public Function

        void SetShootDirection(FVector Direction) { ShootDirection = Direction; };

private:
        //Private Vatiable

        UPROPERTY(VisibleDefaultsOnly, Category="Settings")
        FVector ShootDirection;
};
