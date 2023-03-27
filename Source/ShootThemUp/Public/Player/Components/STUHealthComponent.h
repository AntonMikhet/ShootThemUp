// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
        GENERATED_BODY()

public:
        USTUHealthComponent();

        FOnDeathSignature OnDeath;
        FOnHealthChangedSignature OnHealthChanged;
        virtual void BeginPlay() override;

protected:
        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "100.0"))
        float MaxHealth = 100.0f;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
        bool AutoHeal = true;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "AutoHeal"))
        float HealDelay = 3.0f;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "AutoHeal"))
        float HealUpdateTime = 0.03f;

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

        UFUNCTION(BlueprintCallable, Category = "Health")
        float GetHealthPercent() const { return Health / MaxHealth; };

private:
        UFUNCTION()
        void AutoHealFunction();

        FTimerHandle TimerHandle;

        float Health = 0.0f;

};
