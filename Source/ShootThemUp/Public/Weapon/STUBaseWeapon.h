// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class ACharacter;
class AController;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
        GENERATED_BODY()

public:
        // Sets default values for this actor's properties
        ASTUBaseWeapon();

protected:
        // Called when the game starts or when spawned
        virtual void BeginPlay() override;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
        USkeletalMeshComponent* WeaponMesh;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Socket")
        FName MuzzleSocketName = "MuzzleSocket";

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Socket")
        float TraceMaxDistance = 10000.f;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Settings")
        float DamageAmount = 10.0f;

        UFUNCTION(BlueprintCallable)
        FVector GetSocketLocation();

        UFUNCTION(BlueprintCallable)
        void MakeHit(FHitResult& HitResult, FVector TraceStart, FVector TraceEnd);

        UFUNCTION(BlueprintCallable)
        static void MakeDamage(AActor* DamagedActor, float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

        UPROPERTY(EditDefaultsOnly, Category = "Settings")
        float FireRate = 0.03f;

        UPROPERTY(EditDefaultsOnly, Category = "Settings")
        float BulletSpread = 1.5f;

public:
        void MakeShot();

        UFUNCTION(BlueprintCallable)
        virtual void StartFire();

        UFUNCTION(BlueprintCallable)
        virtual void StopFire();

        UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category= "Owner")
        ACharacter* WeaponOwner = nullptr;

        UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category= "Owner")
        AController* CharacterController = nullptr;

private:
        UPROPERTY(EditDefaultsOnly)
        FTimerHandle ShotTimerHandle;

};
