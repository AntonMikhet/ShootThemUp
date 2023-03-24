// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class ACharacter;
class AController;
class USTUWeaponComponent;


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

public:
        //Public Function

        UFUNCTION(BlueprintCallable)
        virtual void StartFire();

        UFUNCTION(BlueprintCallable)
        virtual void StopFire();

        UFUNCTION(BlueprintCallable)
        void SetController();

        UFUNCTION(BlueprintCallable)
        void ChangeClip();

        UFUNCTION(BlueprintCallable)
        bool CanReload() const;

protected:
        //Protected Function

        UFUNCTION(BlueprintCallable)
        virtual void MakeShot();

        UFUNCTION(BlueprintCallable)
        void MakeHit(FHitResult& HitResult, FVector TraceStart, FVector TraceEnd);

        UFUNCTION(BlueprintCallable)
        FVector GetSocketLocation();

        UFUNCTION(BlueprintCallable)
        virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd);

        UFUNCTION(BlueprintCallable)
        void DecreaseAmmo();

        UFUNCTION(BlueprintCallable)
        bool IsAmmoEmpty() const;

        UFUNCTION(BlueprintCallable)
        bool IsClipEmpty() const;

private:
        //Private Function

        void LogAmmo();

public:
        //Public Variable


        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
        USkeletalMeshComponent* WeaponMesh;

        UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category= "")
        ACharacter* Character = nullptr;

        UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category= "")
        USTUWeaponComponent* WeaponComponent = nullptr;

        UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category= "")
        AController* CharacterController = nullptr;

        FOnClipEmptySignature OnClipEmptySignature;

protected:
        //Protected Variable

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Settings")
        FName MuzzleSocketName = "MuzzleSocket";

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Settings")
        float TraceMaxDistance = 10000.f;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Settings")
        FAmmoData DefaultAmmo{ 15, 10, false };

private:
        //Private Variable

        FAmmoData CurrentAmmo;

};
