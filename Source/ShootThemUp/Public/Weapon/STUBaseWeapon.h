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

public:
        //Public Function

        UFUNCTION(BlueprintCallable)
        virtual void StartFire();

        UFUNCTION(BlueprintCallable)
        virtual void StopFire();

        UFUNCTION(BlueprintCallable)
        void SetController();

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

public:
        //Public Variable

        UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category= "Owner")
        AActor* WeaponOwner = nullptr;

        UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category= "Owner")
        AController* CharacterController = nullptr;

protected:
        //Protected Variable

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
        USkeletalMeshComponent* WeaponMesh;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Socket")
        FName MuzzleSocketName = "MuzzleSocket";

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Settings")
        float TraceMaxDistance = 10000.f;

};
