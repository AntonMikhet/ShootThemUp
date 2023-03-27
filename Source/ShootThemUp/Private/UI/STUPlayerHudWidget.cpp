// Shoot Them Up Game. All Rights Recieved.


#include "UI/STUPlayerHudWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"


void USTUPlayerHudWidget::NativeConstruct()
{
        Super::NativeConstruct();
        Player = GetOwningPlayerPawn();

}

float USTUPlayerHudWidget::GetHealthPercent() const
{

        const USTUHealthComponent* Component = GetHealthComponent();
        if (!Component) { return 0.0f; }

        return Component->GetHealthPercent();
}

FString USTUPlayerHudWidget::GetCurrentAmountAmmo() const
{
        if (!Player) { return FString(); }

        FAmmoData AmmoData, AmmoDefaultData;

        GetWeaponCurrentAmmoData(AmmoData);
        GetWeaponAmmoDefaultData(AmmoDefaultData);

        return FString::FromInt(AmmoData.Bullets) + " / " + (AmmoDefaultData.Infinite ?
                FString::Printf(TEXT("%c"), 0x221E) :
                FString::FromInt(AmmoData.Clips * AmmoDefaultData.Bullets));

}

bool USTUPlayerHudWidget::GetWeaponCurrentUIData(FWeaponUIData& UIData) const
{

        const USTUWeaponComponent* Component = GetWeaponComponent();
        if (!Component) { return false; }

        return Component->GetWeaponUIData(UIData);
}

bool USTUPlayerHudWidget::GetWeaponCurrentAmmoData(FAmmoData& AmmoData) const
{

        const USTUWeaponComponent* Component = GetWeaponComponent();
        if (!Component) { return false; }

        AmmoData = Component->GetCurrentWeapon()->GetCurrentAmmo();

        return true;
}

bool USTUPlayerHudWidget::GetWeaponAmmoDefaultData(FAmmoData& AmmoData) const
{

        const USTUWeaponComponent* Component = GetWeaponComponent();
        if (!Component) { return false; }

        AmmoData = Component->GetCurrentWeapon()->GetDefaultAmmo();

        return true;
}

USTUWeaponComponent* USTUPlayerHudWidget::GetWeaponComponent() const
{
        if (!Player) { return nullptr; }

        USTUWeaponComponent* Component = Cast<USTUWeaponComponent>(Player->GetComponentByClass(USTUWeaponComponent::StaticClass()));
        if (!Component) { return nullptr; }
        return Component;
}

USTUHealthComponent* USTUPlayerHudWidget::GetHealthComponent() const
{
        if (!Player) { return nullptr; }

        USTUHealthComponent* Component = Cast<USTUHealthComponent>(Player->GetComponentByClass(USTUHealthComponent::StaticClass()));
        if (!Component) { return nullptr; }

        return Component;
}

bool USTUPlayerHudWidget::IsPlayerAlive() const
{
        const auto HealthComponent = GetHealthComponent();
        return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHudWidget::IsPlayerSpectating() const
{
        const auto Controller = GetOwningPlayer();
        return Controller && Controller->GetStateName() == NAME_Spectating;
}
