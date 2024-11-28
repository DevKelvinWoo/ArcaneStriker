#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArcaneMainCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ARCANESTRIKER_API AArcaneMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AArcaneMainCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	void AddIMCAndBindAction(UInputComponent* InPlayerInputComponent);

	UFUNCTION()
	void MoveCharacter(const FInputActionValue& InValue);

	UFUNCTION()
	void CharacterLook(const FInputActionValue& InValue);

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> IMC_Character;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> MainCameraComponent;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	TObjectPtr<USpringArmComponent> MainSpringArmComponent;
};
