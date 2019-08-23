// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T_TetrisBlock.generated.h"

UCLASS()
class TETRIS_API AT_TetrisBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AT_TetrisBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "T_TetrisBlock", meta = (AllowPrivateAccess = "true"))
		TArray< AActor* > Block;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_TetrisBlock", meta = (AllowPrivateAccess = "true"))
		 TArray< FIntPoint > BlockPositionData;

	UPROPERTY(EditAnywhere)
		TSubclassOf< class AT_Block > Block_BP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_TetrisBlock", meta = (AllowPrivateAccess = "true"))
		int RotationCnt;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_TetrisBlock", meta = (AllowPrivateAccess = "true"))
		TArray< FVector4 > AIData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_TetrisBlock", meta = (AllowPrivateAccess = "true"))
		float AITimer;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "T_TetrisBlock")
		void Initialize(UClass* bpActor, FVector location);

	UFUNCTION(BlueprintPure, Category = "T_TetrisBlock")
		FORCEINLINE TArray< FIntPoint > GetBlockPositionData() { return BlockPositionData; }

	UFUNCTION(BlueprintCallable, Category = "T_TetrisBlock")
		void MoveTheTetrisBlock(FVector location);
	UFUNCTION(BlueprintCallable, Category = "T_TetrisBlock")
		void RotateTheTetrisBlock();

	UFUNCTION(BlueprintCallable, Category = "T_TetrisBlock")
		void SetInitialData(TArray< FIntPoint > posData);

	UFUNCTION(BlueprintPure, Category = "T_TetrisBlock")
		FORCEINLINE int GetRotationCnt() const { return RotationCnt;}

	UFUNCTION(BlueprintCallable, Category = "T_TetrisBlock")
		bool CheckDroppable(TArray< bool > blockArr, FIntPoint widhei, FVector arrayLocation);
	UFUNCTION(BlueprintPure, Category = "T_TetrisBlock")
		FORCEINLINE int GetRotCnt() { return RotationCnt; }
	UFUNCTION(BlueprintPure, Category = "T_TetrisBlock")
		FORCEINLINE TArray< AActor* > GetBlock() { return Block; }

	//AI ฐüทร
	UFUNCTION(BlueprintCallable, Category = "T_TetrisBlock")
		void SetAIData(TArray< FVector4 > aiDat);
	UFUNCTION(BlueprintPure, Category = "T_TetrisBlock")
		FORCEINLINE TArray< FVector4 > GetAIData() { return AIData; }

	UFUNCTION(BlueprintCallable, Category = "T_TetrisBlock")
		bool CheckIsLocatable(TArray< bool > blockArrS, int x, int y, int rotCnt, int blockNum, FIntPoint widhei);
	UFUNCTION(BlueprintCallable, Category = "T_TetrisBlock")
		FVector4 HightLineHoleBump(TArray< bool > const blockArrS, TArray< int > const xAxis, int x, TArray< int > const yAxis, int y, int rotCnt, int blockNum, FIntPoint const widhei);
	UFUNCTION(BlueprintPure, Category = "T_TetrisBlock")
		FORCEINLINE float GetAITimer() { return AITimer; }
	UFUNCTION(BlueprintPure, Category = "T_TetrisBlock")
		FORCEINLINE float SetAiTimer(float time) { AITimer = time; return AITimer; }


};
