// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class SPMPHYSICS_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(EditAnywhere, Category="Movement")
	double MovementSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category="Player Mesh")
	UStaticMeshComponent* StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UCameraComponent* PlayerCamera;
	FVector CurrentInput;
	bool bJump;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	bool CollisionFunction(FVector Movement);

private:
	void JumpInput();
	void HorizontalInput(float AxisValue);
	void VerticalInput(float AxisValue);
};
