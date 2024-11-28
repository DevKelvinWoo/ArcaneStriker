#include "ArcaneStriker/MainCharacter/ArcaneMainCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AArcaneMainCharacter::AArcaneMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	MainCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainSpringArm"));

	MainSpringArmComponent->SetupAttachment(RootComponent);
	MainCameraComponent->SetupAttachment(MainSpringArmComponent);

	MainSpringArmComponent->bUsePawnControlRotation = true;
	MainCameraComponent->bUsePawnControlRotation = false;
}

void AArcaneMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArcaneMainCharacter::MoveCharacter(const FInputActionValue& InValue)
{
	if (!Controller)
	{
		return;
	}

	const FVector2D& InputVector2D = InValue.Get<FVector2D>();

	if (InputVector2D.X != 0.f || InputVector2D.Y != 0.f)
	{
		const FRotator& ControllerYawRotator = FRotator(0, Controller->GetControlRotation().Yaw, 0);

		if (InputVector2D.X != 0.f)
		{
			const FVector& RightDir = UKismetMathLibrary::GetRightVector(ControllerYawRotator);

			AddMovementInput(RightDir, InputVector2D.X);
		}

		if (InputVector2D.Y != 0.f)
		{
			const FVector& ForwardDir = UKismetMathLibrary::GetForwardVector(ControllerYawRotator);

			AddMovementInput(ForwardDir, InputVector2D.Y);
		}
	}
}

void AArcaneMainCharacter::CharacterLook(const FInputActionValue& InValue)
{
	const FVector2D& InputValue = InValue.Get<FVector2D>();

	if (InputValue.X != 0.f)
	{
		AddControllerYawInput(InputValue.X);
	}

	if (InputValue.Y != 0.f)
	{
		AddControllerPitchInput(InputValue.Y);
	}
}

void AArcaneMainCharacter::AddIMCAndBindAction(UInputComponent* InPlayerInputComponent)
{
	if (!InPlayerInputComponent || !IMC_Character || !IA_Move || !IA_Jump || !IA_Look)
	{
		return;
	}

	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(InPlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (!EnhancedPlayerInputComponent || !PlayerController)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if (!EnhancedInputSubSystem)
	{
		return;
	}

	EnhancedInputSubSystem->AddMappingContext(IMC_Character, 0);

	EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AArcaneMainCharacter::MoveCharacter);
	EnhancedPlayerInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &AArcaneMainCharacter::Jump);
	EnhancedPlayerInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AArcaneMainCharacter::StopJumping);
	EnhancedPlayerInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AArcaneMainCharacter::CharacterLook);
}

void AArcaneMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArcaneMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	AddIMCAndBindAction(PlayerInputComponent);
}

