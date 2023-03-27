// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
        GENERATED_BODY()

public:
        // Sets default values for this character's properties
        ASTUBaseCharacter(const FObjectInitializer& ObjInit);

public:
        //Components
        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
        UCameraComponent* CameraComponent;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
        USpringArmComponent* SpringArmComponent;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
        USTUHealthComponent* HealthComponent;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
        UTextRenderComponent* HealthTextComponent;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
        USTUWeaponComponent* WeaponComponent;

public:
        virtual void BeginPlay() override;

        virtual void Tick(float DeltaTime) override;

        virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
        UFUNCTION(BlueprintPure, Category = "Movement")
        bool IsRunning() const;
        UFUNCTION(BlueprintPure, Category = "Movement")
        float GetMovementDirection() const;

        bool WantsToRun = false;
        bool IsMovingForward = false;

        void MoveForward(float Amount);
        void MoveRight(float Amount);

        void OnStartRunning();
        void OnStopRunning();

        void OnHealthChanged(const float Health) const;

protected:
        void OnDeath();

private:
        UFUNCTION()
        void OnGroundLanded(const FHitResult& Hit);

protected:
        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
        UAnimMontage* DeathAnimation;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
        FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
        FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

};
