// Fill out your copyright notice in the Description page of Project Settings.


#include "Creatures/BaseCreature.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PlatformerGameInstance.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Kismet/GameplayStatics.h"
#include "PlatfromerGameMode.h"

#include "HUD/PlatformerHUD.h"
#include "HUD/PlatformerOverlay.h"

ABaseCreature::ABaseCreature()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->GravityScale = 1.3f;
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.1f;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, 1.0f, 0.0f));
}

void ABaseCreature::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlatformerMappingContext, 0);
		}
	}

	GameMode = Cast<APlatfromerGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->GameState.AddUObject(this, &ABaseCreature::OnGameStateChanged);
	}

	LastSavePointLocation = GetActorLocation();
	StartPoint = GetActorLocation();
	MaxSpeed = MinSpeed + AdditionalSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MinSpeed;
	StartingNumberOfLives = NumberOfLives;
	Score = 0;
	InitializeOverlay();
}

void ABaseCreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCreature::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ABaseCreature::StopMoving);

		// Test Action
		EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Started, this, &ABaseCreature::TestPerforming);

		// Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ABaseCreature::OnPause);
	}
}

void ABaseCreature::SetScore(const int32& Points)
{
	if (PlatformerOverlay)
	{
		Score += Points;
		PlatformerOverlay->SetScore(Score);
	}
}

void ABaseCreature::Move(const FInputActionValue& Value)
{
	bIsMoving = true;

	FVector2D MovementVector = Value.Get<FVector2D>();
	
	Turning(Value);

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(RightDirection, MovementVector.X);
	}

	if (GetCharacterMovement()->MaxWalkSpeed < MaxSpeed)
	{
		// Cap max speed
		GetCharacterMovement()->MaxWalkSpeed = FMath::Clamp(GetCharacterMovement()->MaxWalkSpeed + SpeedIncrease * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), MinSpeed, MaxSpeed);
	}
	
	LastVector = MovementVector;
}

void ABaseCreature::StopMoving(const FInputActionValue& Value)
{
	bIsMoving = false;

	GetCharacterMovement()->MaxWalkSpeed = MinSpeed;
}

void ABaseCreature::Turning(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (MovementVector.X < 0.0f && bIsFacingForward)
	{
		GetMesh()->SetWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
		bIsFacingForward = false;
	}
	else if (MovementVector.X > 0.0f && !bIsFacingForward)
	{
		GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
		bIsFacingForward = true;
	}

	// Check the vector to decrease speed when turning
	if (LastVector != MovementVector)
	{
		GetCharacterMovement()->MaxWalkSpeed = MinSpeed;
	}
}

void ABaseCreature::OnPause(const FInputActionValue& Value)
{
	if (!GetWorld() || !GameMode) return;

	if (GameMode->IsPaused())
	{
		// ??
		GameMode->ClearPause();
	}
	else
	{
		GameMode->SetPause(PlayerController);
	}
}

void ABaseCreature::TestPerforming(const FInputActionValue& Value)
{
	if (LastSavePointLocation.IsZero()) return;

	this->SetActorLocation(LastSavePointLocation);
}

void ABaseCreature::InitializeOverlay()
{
	if (PlayerController)
	{
		APlatformerHUD* PlatformerHUD = Cast<APlatformerHUD>(PlayerController->GetHUD());
		if (PlatformerHUD)
		{
			PlatformerOverlay = Cast<UPlatformerOverlay>(PlatformerHUD->GetPlatformerOverlay());
			if (PlatformerOverlay)
			{
				SetScoreAndLives();
			}
		}
	}
}

void ABaseCreature::Death()
{
	if (NumberOfLives > 1)
	{
		NumberOfLives--;
		PlatformerOverlay->SetLives(NumberOfLives);
		Score = FMath::Clamp(Score / 2, 0, Score);
		PlatformerOverlay->SetScore(Score);
		this->SetActorLocation(LastSavePointLocation);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Red, FString::Printf(TEXT("Game Over")));
		Score = 0;
		NumberOfLives = StartingNumberOfLives;
		SetScoreAndLives();
		const UPlatformerGameInstance* GameInstance = GetWorld()->GetGameInstance<UPlatformerGameInstance>();
		UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelName());
		//this->SetActorLocation(StartPoint);
	}
}

void ABaseCreature::SetScoreAndLives()
{
	PlatformerOverlay->SetScore(Score);
	PlatformerOverlay->SetLives(NumberOfLives);
}

void ABaseCreature::OnGameStateChanged(EGameState State)
{
	if (State == EGameState::InProgress)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}

	else
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
	}
}

