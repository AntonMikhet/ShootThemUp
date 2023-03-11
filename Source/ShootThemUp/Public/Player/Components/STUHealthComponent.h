// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
        GENERATED_BODY()

public:
        // Sets default values for this component's properties
        USTUHealthComponent();

        FOnDeathSignature OnDeath;
        FOnHealthChangedSignature OnHealthChanged;

protected:
        // Called when the game starts
        virtual void BeginPlay() override;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "100.0"))
        float MaxHealth = 100.0f;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
        bool AutoHeal = true;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "AutoHeal"))
        float HealDelay = 3.0f;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "AutoHeal"))
        float HealUpdateTime = 0.3f;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "AutoHeal"))
        float HealModifier = 0.3f;

public:
        UFUNCTION(BlueprintPure, Category = "Health")
        float GetHealth() const { return Health; }

        UFUNCTION(BlueprintPure, Category = "Health")
        bool IsDead() const { return FMath::IsNearlyZero(Health); }

        UFUNCTION(BlueprintCallable, Category = "Health")
        void OnTakeAnyDamageHandle(AActor* DamagedActor, const float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

        UFUNCTION(BlueprintCallable, Category = "Health")
        float SetHealth(const float NewHealth);

private:
        UFUNCTION()
        void AutoHealFunction();

        FTimerHandle TimerHandle;

        float Health = 0.0f;

};
