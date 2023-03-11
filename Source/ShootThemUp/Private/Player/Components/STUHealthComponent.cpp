// Shoot Them Up Game. All Rights Recieved.

#include "Player/Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
        // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
        // off to improve performance if you don't need them.
        PrimaryComponentTick.bCanEverTick = false;

        // ...
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
        Super::BeginPlay();

        SetHealth(MaxHealth);

        AActor* ComponentOwner = GetOwner();
        if (ComponentOwner)
        {
                ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamageHandle);
        }

}

void USTUHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor,
                                                const float Damage,
                                                const UDamageType* DamageType,
                                                AController* InstigatedBy,
                                                AActor* DamageCauser)
{

        if (Damage <= 0.0f || IsDead() || !GetWorld()) { return; }

        if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
        {
                GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
        }

        const float Loc_Health = Health - Damage;
        SetHealth(Loc_Health);

        if (!IsDead() && !GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
        {
                GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USTUHealthComponent::AutoHealFunction, HealUpdateTime, true, HealDelay);
        }

        if (IsDead())
        {
                OnDeath.Broadcast();
        }
}

void USTUHealthComponent::AutoHealFunction()
{
        const float Loc_Health = Health + HealModifier;
        SetHealth(Loc_Health);

        if (FMath::IsNearlyEqual(GetHealth(), MaxHealth) && GetWorld())
        {
                GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
                UE_LOG(LogHealthComponent, Display, TEXT("Auto heal complete"))
        }
}

float USTUHealthComponent::SetHealth(const float NewHealth)
{
        Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
        OnHealthChanged.Broadcast(Health);
        return Health;
}
