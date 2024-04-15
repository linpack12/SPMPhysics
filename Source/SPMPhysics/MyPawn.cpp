// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "Physics/PhysicsFiltering.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	RootComponent = StaticMesh;
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
     
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->SetRelativeLocation(FVector(0.0f, 1600.0f, 200.0f));
	PlayerCamera->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
    
	PlayerCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	PlayerCamera->OrthoWidth = 3200.f;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const double Distance = MovementSpeed * DeltaTime;

	FVector Direction = CurrentInput;

	FVector Movement = Direction * Distance;

	const FVector CurrentLocation = GetActorLocation();
	
	if (!CollisionFunction(CurrentLocation + Movement))
	{
		SetActorLocation(CurrentLocation + Direction * Distance);
	}	
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
	InputComponent->BindAction(
		"Jump",
		IE_Pressed,
		this,
		&AMyPawn::JumpInput);

	InputComponent->BindAxis(
		"Horizontal", 
		this, 
		&AMyPawn::HorizontalInput);
	InputComponent->BindAxis(
		"Vertical", 
		this, 
		&AMyPawn::VerticalInput);
}

// Input
void AMyPawn::JumpInput()
{
}

void AMyPawn::HorizontalInput(float AxisValue)
{
	CurrentInput = FVector(AxisValue, CurrentInput.Y, CurrentInput.Z);
}

void AMyPawn::VerticalInput(float AxisValue)
{
	CurrentInput = FVector(CurrentInput.X, AxisValue, CurrentInput.Z);
}

// Checks
bool AMyPawn::CollisionFunction(FVector Movement)
{
	FVector Origin, Extent;
	GetActorBounds(true, Origin, Extent);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation();

	ECollisionChannel TraceChannelProperty = ECC_Pawn;
	
	FHitResult Hit;
	bool bHit = GetWorld()->SweepSingleByChannel(
		Hit,
		TraceStart,
		TraceEnd,
		FQuat::Identity,
		TraceChannelProperty,
		FCollisionShape::MakeBox(Extent),
		QueryParams);

	if (bHit)
		UE_LOG(LogTemp, Warning, TEXT("Collision with: %s"), *Hit.GetActor()->GetActorLabel());
	
	return bHit;
}