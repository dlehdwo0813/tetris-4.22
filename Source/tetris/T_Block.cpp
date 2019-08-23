// Fill out your copyright notice in the Description page of Project Settings.

#include "T_Block.h"
#include "Classes/Components/StaticMeshComponent.h"


// Sets default values
AT_Block::AT_Block()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	T_BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("T_BlockMesh"));
	RootComponent = T_BlockMesh;
}

// Called when the game starts or when spawned
void AT_Block::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AT_Block::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AT_Block::MoveTheBlock(FVector move) {
	FVector targetPosition = GetActorLocation();
	targetPosition.X += move.X;
	targetPosition.Y += move.Y;
	targetPosition.Z += move.Z;

	SetActorLocation(targetPosition,false);
}

void AT_Block::SetBlockCollisionType() {
	T_BlockMesh->SetCollisionProfileName(TEXT("BlockAll"));
}
