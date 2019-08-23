// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T_Table.generated.h"

UCLASS()
class TETRIS_API AT_Table : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AT_Table();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "T_Table")
		void CreateTetrisBlock(UClass* bpActor);

	UFUNCTION(BlueprintCallable, Category = "T_Table")
		void CreateMonster(UClass* bpActor);

	UFUNCTION(BlueprintCallable, Category = "T_Table")
		void Initialize(UClass* bpActor, UClass* bpMonster, FIntPoint widhei);

	UFUNCTION(BlueprintCallable, Category = "T_Table")
		void BlockMoveNRotate(int moveX, int moveZ, int rotate, int blockIndex);

protected:
	UFUNCTION(BlueprintCallable, Category = "T_Table")
		void CreateBlockInTimer();

	UFUNCTION(BlueprintCallable, Category = "T_Table")
		void BlockArrayProcess();
	UFUNCTION(BlueprintCallable, Category = "T_Table")
		void BlockArrayArrangement();

	UFUNCTION(BlueprintCallable, Category = "T_Table")
		void SetAI();
	bool isPlay;

protected:
	//블럭 관련 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		TArray< FVector4 > BlockTypeData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		TArray< FVector4 > BlockRotationData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		TArray< FIntPoint > BoxPositionData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		TArray< AActor* > TetrisBlock;
	UPROPERTY(EditAnywhere)
		TSubclassOf< class AT_TetrisBlock > Block_BP;

	UPROPERTY(EditAnywhere)
		TSubclassOf< class ACharacterBase > Monster_BP;

	//Tick 이벤트 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		float DropSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		float DropTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		float CreateTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		float AISpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		float MonsterTimer;

	//테이블 관련 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* T_Floor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* T_Table;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		FIntPoint WidHei;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		TArray< AActor* > BlockArr;

	//AI 관련 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		TArray< bool > BlockArrSmall;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		TArray< int > XAxisArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		TArray< int > YAxisArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		TArray< int > XAxisBlockCnt;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "T_Table", meta = (AllowPrivateAccess = "true"))
		TArray< AActor* > MonsterArr;


public:
	UFUNCTION(BlueprintCallable, Category = "T_Table")
		void DropAllBlock();


	
};
