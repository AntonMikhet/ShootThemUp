// Shoot Them Up Game. All Rights Recieved.

#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/Vector.h"
#include "Player/Components/STUCharacterMovementComponent.h"
#include "Player/Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit) :
        Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName))
{
        // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
        PrimaryActorTick.bCanEverTick = true;

        SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
        SpringArmComponent->SetupAttachment(GetRootComponent());
        SpringArmComponent->bUsePawnControlRotation = true;
        SpringArmComponent->SocketOffset.Y = 100.f;

        CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
        CameraComponent->SetupAttachment(SpringArmComponent);

        HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
        HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
        HealthTextComponent->SetupAttachment(GetRootComponent());
        HealthTextComponent->SetOwnerNoSee(true);

        WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");

}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
        Super::BeginPlay();

        check(HealthComponent);
        check(HealthTextComponent);
        check(GetCharacterMovement());
        check(WeaponComponent);

        OnHealthChanged(HealthComponent->GetHealth());
        HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
        HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

        LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
        Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
        Super::SetupPlayerInputComponent(PlayerInputComponent);
        check(PlayerInputComponent);

        PlayerInputComponent->BindAxis("MoveForward/Backward", this, &ASTUBaseCharacter::MoveForward);
        PlayerInputComponent->BindAxis("MoveLeft/Right", this, &ASTUBaseCharacter::MoveRight);
        PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
        PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
        PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
        PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);
        PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);
        PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
        PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
        PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);
        PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);

}

bool ASTUBaseCharacter::IsRunning() const
{
        return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float ASTUBaseCharacter::GetMovementDirection() const
{
        if (GetVelocity().IsZero()) { return 0.0f; }

        const FVector ForwardVector = GetActorForwardVector();
        const FVector Velocity = GetVelocity().GetSafeNormal();

        const float AngleBetween = FMath::Acos(FVector::DotProduct(ForwardVector, Velocity));
        const FVector CrossProduct = FVector::CrossProduct(ForwardVector, Velocity);
        const float Degrees = FMath::RadiansToDegrees(AngleBetween);

        return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::MoveForward(float Amount)
{
        if (Amount == 0.0f) { return; }

        IsMovingForward = Amount > 0.0f;
        AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount)
{
        if (Amount == 0.0f) { return; }
        AddMovementInput(GetActorRightVector(), Amount);

}

void ASTUBaseCharacter::OnStartRunning()
{
        WantsToRun = true;
}

void ASTUBaseCharacter::OnStopRunning()
{
        WantsToRun = false;

}

void ASTUBaseCharacter::OnHealthChanged(const float Health) const
{
        HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));

}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
        const float FallVelocityZ = -GetVelocity().Z;

        if (FallVelocityZ < LandedDamageVelocity.X) { return; }

        const float FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
        // UE_LOG(BaseCharacterLog, Display, TEXT("On Landed: %f"), FallVelocityZ);
        UE_LOG(BaseCharacterLog, Display, TEXT("FinalDamage: %f"), FinalDamage);

        TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);
}

void ASTUBaseCharacter::OnDeath()
{
        SetLifeSpan(5.0f);
        PlayAnimMontage(DeathAnimation);
        GetCharacterMovement()->DisableMovement();
        GetCapsuleComponent()->SetCollisionResponseToChannels(ECR_Ignore);
        HealthTextComponent->DestroyComponent();
        WeaponComponent->StopFire();

        if (Controller) { Controller->ChangeState(NAME_Spectating); }
        UE_LOG(BaseCharacterLog, Display, TEXT("Player %s is dead"), *GetName());

}
