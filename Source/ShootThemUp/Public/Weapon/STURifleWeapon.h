// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
        GENERATED_BODY()

public:
        //Public Function

        virtual void StartFire() override;
        virtual void StopFire() override;

protected:
        //Protected Function

        UFUNCTION(BlueprintCallable)
        static void MakeDamage(AActor* DamagedActor, float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
        virtual void MakeShot() override;
        virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) override;

protected:
        //Protected Variable

        UPROPERTY(BlueprintReadWrite)
        FTimerHandle ShotTimerHandle;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
        float FireRate = 0.3f;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
        float BulletSpread = 1.5f;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Settings")
        float DamageAmount = 10.0f;

};
