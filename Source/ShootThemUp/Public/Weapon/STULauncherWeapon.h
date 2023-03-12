// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
        GENERATED_BODY()

public:
        virtual void StartFire() override;

protected:
        virtual void MakeShot() override;

protected:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
        TSubclassOf<ASTUProjectile> ProjectileClass;
};
