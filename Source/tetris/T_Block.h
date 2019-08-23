// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T_Block.generated.h"

UCLASS()
class TETRIS_API AT_Block : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AT_Block();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "T_Block", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* T_BlockMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "T_Block")
		void MoveTheBlock(FVector move);
	UFUNCTION(BlueprintCallable, Category = "T_Block")
		void SetBlockCollisionType();

	
	
};
