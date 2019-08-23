// Fill out your copyright notice in the Description page of Project Settings.

#include "T_Table.h"
#include "T_TetrisBlock.h"
#include "T_Block.h"
#include "CharacterBase.h"

#include "Engine/World.h"
#include "Classes/Components/StaticMeshComponent.h"


// Sets default values
AT_Table::AT_Table()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidHei.X = 0;
	WidHei.Y = 0;

	DropSpeed = 0.5;
	DropTimer = 0;
	CreateTimer = 0;
	MonsterTimer = 0;

	T_Floor = NULL;
	T_Table = NULL;
	Block_BP = NULL;

	T_Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("T_Floor"));
	RootComponent = T_Floor;
	T_Table = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("T_Table"));

	if (BlockTypeData.Num() == 0) {
		BlockTypeData.SetNum(7);
		BlockRotationData.SetNum(19);
		BoxPositionData.SetNum(16);

		//
		BlockTypeData[0].X = 0;
		BlockTypeData[0].Y = -1;
		BlockTypeData[0].Z = -1;
		BlockTypeData[0].W = -1;

		BlockTypeData[1].X = 1;
		BlockTypeData[1].Y = 2;
		BlockTypeData[1].Z = -1;
		BlockTypeData[1].W = -1;

		BlockTypeData[2].X = 3;
		BlockTypeData[2].Y = 4;
		BlockTypeData[2].Z = -1;
		BlockTypeData[2].W = -1;

		BlockTypeData[3].X = 5;
		BlockTypeData[3].Y = 6;
		BlockTypeData[3].Z = -1;
		BlockTypeData[3].W = -1;

		BlockTypeData[4].X = 7;
		BlockTypeData[4].Y = 8;
		BlockTypeData[4].Z = 9;
		BlockTypeData[4].W = 10;

		BlockTypeData[5].X = 11;
		BlockTypeData[5].Y = 12;
		BlockTypeData[5].Z = 13;
		BlockTypeData[5].W = 14;

		BlockTypeData[6].X = 15;
		BlockTypeData[6].Y = 16;
		BlockTypeData[6].Z = 17;
		BlockTypeData[6].W = 18;

		//
		BlockRotationData[0].X = 5;
		BlockRotationData[0].Y = 6;
		BlockRotationData[0].Z = 9;
		BlockRotationData[0].W = 10;

		BlockRotationData[1].X = 2;
		BlockRotationData[1].Y = 6;
		BlockRotationData[1].Z = 10;
		BlockRotationData[1].W = 14;

		BlockRotationData[2].X = 4;
		BlockRotationData[2].Y = 5;
		BlockRotationData[2].Z = 6;
		BlockRotationData[2].W = 7;

		BlockRotationData[3].X = 2;
		BlockRotationData[3].Y = 5;
		BlockRotationData[3].Z = 6;
		BlockRotationData[3].W = 9;

		BlockRotationData[4].X = 5;
		BlockRotationData[4].Y = 6;
		BlockRotationData[4].Z = 10;
		BlockRotationData[4].W = 11;

		BlockRotationData[5].X = 1;
		BlockRotationData[5].Y = 5;
		BlockRotationData[5].Z = 6;
		BlockRotationData[5].W = 10;

		BlockRotationData[6].X = 6;
		BlockRotationData[6].Y = 7;
		BlockRotationData[6].Z = 9;
		BlockRotationData[6].W = 10;

		BlockRotationData[7].X = 2;
		BlockRotationData[7].Y = 6;
		BlockRotationData[7].Z = 9;
		BlockRotationData[7].W = 10;

		BlockRotationData[8].X = 5;
		BlockRotationData[8].Y = 6;
		BlockRotationData[8].Z = 7;
		BlockRotationData[8].W = 11;

		BlockRotationData[9].X = 2;
		BlockRotationData[9].Y = 3;
		BlockRotationData[9].Z = 6;
		BlockRotationData[9].W = 10;

		BlockRotationData[10].X = 1;
		BlockRotationData[10].Y = 5;
		BlockRotationData[10].Z = 6;
		BlockRotationData[10].W = 7;

		BlockRotationData[11].X = 1;
		BlockRotationData[11].Y = 2;
		BlockRotationData[11].Z = 6;
		BlockRotationData[11].W = 10;

		BlockRotationData[12].X = 5;
		BlockRotationData[12].Y = 6;
		BlockRotationData[12].Z = 7;
		BlockRotationData[12].W = 9;

		BlockRotationData[13].X = 2;
		BlockRotationData[13].Y = 6;
		BlockRotationData[13].Z = 10;
		BlockRotationData[13].W = 11;

		BlockRotationData[14].X = 3;
		BlockRotationData[14].Y = 5;
		BlockRotationData[14].Z = 6;
		BlockRotationData[14].W = 7;

		BlockRotationData[15].X = 2;
		BlockRotationData[15].Y = 5;
		BlockRotationData[15].Z = 6;
		BlockRotationData[15].W = 10;

		BlockRotationData[16].X = 5;
		BlockRotationData[16].Y = 6;
		BlockRotationData[16].Z = 7;
		BlockRotationData[16].W = 10;

		BlockRotationData[17].X = 2;
		BlockRotationData[17].Y = 6;
		BlockRotationData[17].Z = 7;
		BlockRotationData[17].W = 10;

		BlockRotationData[18].X = 2;
		BlockRotationData[18].Y = 5;
		BlockRotationData[18].Z = 6;
		BlockRotationData[18].W = 7;



		//
		int cnt = 0;
		for (int j = 1; j >= -2; j--) {
			for (int i = -2; i <= 1; i++) {
				BoxPositionData[cnt].X = i;
				BoxPositionData[cnt].Y = j;

				cnt++;
			}
		}
	}

	isPlay = 0;
}

// Called when the game starts or when spawned
void AT_Table::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AT_Table::Tick(float DeltaTime)
{
	if (isPlay) {
		DropTimer += DeltaTime;
		if (DropTimer >= DropSpeed) {
			DropTimer = 0;


			BlockArrayProcess();

			DropAllBlock();

		}

		if (Block_BP) {
			CreateTimer += DeltaTime;
			if (CreateTimer >= DropSpeed * (WidHei.Y + 1.4f)) {
				CreateTimer = 0;

				CreateBlockInTimer();

				SetAI();
			}
		}

		if (Monster_BP) {
			MonsterTimer += DeltaTime;
			if (MonsterTimer >= DropSpeed * (WidHei.Y + 1.4f) * 2.5f) {
				MonsterTimer = 0;

				CreateMonster(Monster_BP);
				CreateMonster(Monster_BP);
				for (int o = 0; o < MonsterArr.Num(); o++) {
					if (!MonsterArr.IsValidIndex(o))MonsterArr.RemoveAt(o);
				}
			}
		}

		for (int i = 0; i < TetrisBlock.Num(); i++) {
			AISpeed = 0;
			AT_TetrisBlock* block = (AT_TetrisBlock*)TetrisBlock[i];
			block->SetAiTimer(block->GetAITimer() + DeltaTime);
			AISpeed = DropSpeed * WidHei.Y * 1 / 4;
			AISpeed /= block->GetAIData().GetData()->Y + block->GetAIData().GetData()->Z + block->GetAIData().GetData()->W;
			if (block->GetAITimer() > AISpeed) {
				FVector* tmpV = new FVector(0, 0, 0);
				block->SetAiTimer(0);

				*tmpV = T_Floor->GetComponentLocation();
				tmpV->X -= T_Floor->K2_GetComponentScale().X * 50;

				if (block->GetRotationCnt() < (int)(block->GetAIData().GetData()->W)) {
					BlockMoveNRotate(0, 0, 1, i);
					continue;
				}
				if ((int)((block->GetActorLocation().X - tmpV->X) / 100) > (int)(block->GetAIData().GetData()->Y)) {
					BlockMoveNRotate(-1, 0, 0, i);
					continue;
				}
				if ((int)((block->GetActorLocation().X - tmpV->X) / 100) < (int)(block->GetAIData().GetData()->Y)) {
					BlockMoveNRotate(1, 0, 0, i);
					continue;
				}
				delete tmpV;
			}
		}
	}
	Super::Tick(DeltaTime);

}

void AT_Table::SetAI() {

	AT_TetrisBlock* block = (AT_TetrisBlock*)TetrisBlock[TetrisBlock.Num() - 1];
	TArray< AActor* > tetrisBlockArr = block->GetBlock();

	int* rotateNum = new int;
	*rotateNum = (int)(block->GetBlockPositionData().Num() / block->GetBlock().Num());

	FVector4* tmpFV = new FVector4;
	for (int i = 0; i < tetrisBlockArr.Num(); i++) {
		for (int j = 0; j < *rotateNum; j++) {
			for (int n = 0; n < XAxisArray.Num(); n++) {
				if (block->CheckIsLocatable(BlockArrSmall, n, XAxisArray[n], j, i, WidHei)) {
					*tmpFV = block->HightLineHoleBump(BlockArrSmall, XAxisArray, n, YAxisArray, XAxisArray[n], j, i, WidHei);


				}
			}
		}
	}
	delete rotateNum;
	delete tmpFV;
}


void AT_Table::BlockArrayProcess() {
	FVector* arrLoc = new FVector;

	for (int i = 0; i < TetrisBlock.Num(); i++) {
		AT_TetrisBlock* block = (AT_TetrisBlock*)TetrisBlock[i];

		*arrLoc = T_Floor->GetComponentLocation();
		arrLoc->X -= T_Floor->K2_GetComponentScale().X * 50;
		arrLoc->Z += T_Floor->K2_GetComponentScale().Y * 50;
		if (!block->CheckDroppable(BlockArrSmall, WidHei, *arrLoc)) {
			TArray< AActor* > tmpBlock = block->GetBlock();
			float arrX;
			float arrY;
			for (int j = 0; j < tmpBlock.Num(); j++) {

				arrX = tmpBlock[j]->GetActorLocation().X;
				arrX -= arrLoc->X;
				arrX /= 100;
				if (arrX >= WidHei.X) continue;
				arrY = tmpBlock[j]->GetActorLocation().Z;
				arrY -= arrLoc->Z;
				arrY /= 100;
				arrY = (float)(int)arrY;
				arrY *= WidHei.X;
				BlockArrSmall[(int)arrX + (int)arrY] = 1;
				AT_Block* blo = (AT_Block*)tmpBlock[j];
				blo->SetBlockCollisionType();

				BlockArr[(int)arrX + (int)arrY] = tmpBlock[j];
				if (arrY/ WidHei.X >= WidHei.Y - 1) {
					isPlay = 0; 
				}
				blo = NULL;
				delete blo;
			}


			BlockArrayArrangement();
			TetrisBlock.RemoveAt(i);
		}
	}

	delete arrLoc;


}

void AT_Table::BlockArrayArrangement() {

	for (int j = 0; j < WidHei.X; j++) {
		XAxisBlockCnt[j] = 0;
	}

	for (int i = 0; i < WidHei.Y; i++) {
		YAxisArray[i] = 0;

		for (int j = 0; j < WidHei.X; j++) {
			if (BlockArrSmall[i*WidHei.X + j]) {
				YAxisArray[i]++;
				XAxisArray[j] = i + 1;
				XAxisBlockCnt[j]++;
			}
		}

		if (YAxisArray[i] >= WidHei.X) {
			YAxisArray[i] = 0;
			FVector* newLocation = new FVector;

			BlockArrSmall.SetNum(BlockArrSmall.Num() + WidHei.X);
			BlockArr.SetNum(BlockArr.Num() + WidHei.X);

			for (int k = 0; k < WidHei.X; k++) {
				BlockArr[i*WidHei.X]->Destroy();

				if (BlockArr[(i + 1)*WidHei.X]) {
					*newLocation = BlockArr[(i + 1)*WidHei.X]->GetActorLocation();
					newLocation->Z -= 100;
					BlockArr[(i + 1)*WidHei.X]->SetActorLocation(*newLocation);
				}

				BlockArrSmall.RemoveAt(i*WidHei.X);
				BlockArr.RemoveAt(i*WidHei.X);

				if (XAxisArray[k] > 0) XAxisArray[k]--;
				if (XAxisBlockCnt[k] > 0) XAxisBlockCnt[k]--;
			}

			for (int n = (i + 1)*WidHei.X; n <BlockArrSmall.Num(); n++) {
				if (BlockArr[n]) {

					*newLocation = BlockArr[n]->GetActorLocation();
					newLocation->Z -= 100;
					BlockArr[n]->SetActorLocation(*newLocation);
				}
			}
			i--;
			delete newLocation;
		}

	}

}


void AT_Table::CreateBlockInTimer() {
	CreateTetrisBlock(Block_BP);
	AT_TetrisBlock* block = (AT_TetrisBlock*)TetrisBlock[TetrisBlock.Num() - 1];
	FVector location(0, 0, 0);
	block->Initialize(NULL, location);
}

void AT_Table::CreateTetrisBlock(UClass* bpActor) {

	if (!GetWorld()) return;

	if (!Block_BP) Block_BP = bpActor;


	FActorSpawnParameters* spawnParameter = new FActorSpawnParameters;
	spawnParameter->Owner = this;
	//spawnParameter.Instigator = Instigator;

	FTransform* tarLocation= new FTransform;

	FVector* spawnLocation = new FVector;

	int spawnLoc2;
	spawnLoc2 = (int)FMath::FRandRange(2, WidHei.X - 2);

	*spawnLocation = T_Floor->GetComponentLocation();
	spawnLocation->X -= T_Floor->GetComponentScale().X * 50 - (50 + spawnLoc2 * 100);
	spawnLocation->Z += T_Table->GetComponentScale().Z * 100;
	tarLocation->SetLocation(*spawnLocation);

	TetrisBlock.Add(GetWorld()->SpawnActor<AActor>(Block_BP, *tarLocation, *spawnParameter));

	int blockType = (int)FMath::FRandRange(0, 7);

	if (TetrisBlock[TetrisBlock.Num() - 1] != NULL) {
		AT_TetrisBlock* block = (AT_TetrisBlock*)TetrisBlock[TetrisBlock.Num() - 1];
		TArray< FIntPoint > posData;

		if (BlockTypeData[blockType].X >= 0) {
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].X].X]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].X].Y]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].X].Z]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].X].W]);
		}
		if (BlockTypeData[blockType].Y >= 0) {
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].Y].X]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].Y].Y]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].Y].Z]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].Y].W]);
		}
		if (BlockTypeData[blockType].Z >= 0) {
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].Z].X]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].Z].Y]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].Z].Z]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].Z].W]);

			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].W].X]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].W].Y]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].W].Z]);
			posData.Add(BoxPositionData[BlockRotationData[BlockTypeData[blockType].W].W]);
		}

		block->SetInitialData(posData);

		delete spawnParameter;
		delete spawnLocation;
		delete tarLocation;
	}



}

void AT_Table::CreateMonster(UClass* bpActor) {

	if (!GetWorld()) return;

	if (!Monster_BP) Monster_BP = bpActor;


	FActorSpawnParameters* spawnParameter = new FActorSpawnParameters;
	spawnParameter->Owner = this;
	spawnParameter->Instigator = Instigator;

	FTransform* tarLocation = new FTransform;

	FVector* spawnLocation = new FVector;

	int spawnLoc2;
	spawnLoc2 = (int)FMath::FRandRange(2, WidHei.X - 2);
	int spawnLoc;
	spawnLoc = (int)FMath::FRandRange(1, WidHei.Y - 1);

	*spawnLocation = T_Floor->GetComponentLocation();
	spawnLocation->X -= T_Floor->GetComponentScale().X * 50 - (50 + spawnLoc2 * 100);
	spawnLocation->Z += T_Table->GetComponentScale().Z * 100 - (50 + spawnLoc * 100);
	tarLocation->SetLocation(*spawnLocation);

	MonsterArr.Add(GetWorld()->SpawnActor<AActor>(Monster_BP, *tarLocation, *spawnParameter));

}

void AT_Table::DropAllBlock() {
	FVector moveRate(0, 0, 0);
	moveRate.X = 0;
	moveRate.Y = 0;
	moveRate.Z = -100;
	for (int i = 0; i < TetrisBlock.Num(); i++) {
		AT_TetrisBlock* tBlock= (AT_TetrisBlock*)TetrisBlock[i];
		tBlock->MoveTheTetrisBlock(moveRate);
	}

}

void AT_Table::Initialize(UClass* bpActor, UClass* bpMonster, FIntPoint widhei) {

	if (!GetWorld()) return;

	isPlay = 1;

	if (!Block_BP) Block_BP = bpActor;
	if (!Monster_BP) Monster_BP = bpMonster;
	
	if (WidHei.X == 0 && WidHei.Y == 0) WidHei = widhei;

	if (WidHei.X < 5) WidHei.X = 5;
	if (WidHei.X > 15) WidHei.X = 15;
	if (WidHei.Y < 7) WidHei.Y = 7;
	if (WidHei.Y > 20) WidHei.Y = 20;

	XAxisBlockCnt.SetNum(WidHei.X);
	XAxisArray.SetNum(WidHei.X);
	YAxisArray.SetNum(WidHei.Y);

	BlockArr.SetNum(WidHei.X*WidHei.Y);
	BlockArrSmall.SetNum(WidHei.X*WidHei.Y);

	FVector location(0,0,0);
	FVector bounds(0, 0, 0);
	FVector scale(0, 0, 0);
	scale.X = WidHei.X * 1;
	scale.Y = 1;
	scale.Z = 1;
	T_Floor->SetWorldScale3D(scale);

	location = GetActorLocation();
	location.Y -= 100;
	location.Z += 0;
	T_Table->SetWorldLocation(location);

	scale.Z = WidHei.Y * 1 + 1;
	T_Table->SetWorldScale3D(scale);


}


void AT_Table::BlockMoveNRotate(int moveX, int moveZ, int rotate, int blockIndex) {

	if (TetrisBlock.Num() <= blockIndex) return;
	if (!TetrisBlock[blockIndex]) return;


	if (moveX > 0) moveX = 100;
	if (moveX < 0) moveX = -100;
	if (moveZ > 0) moveZ = 100;
	if (moveZ < 0) moveZ = -100;

	AT_TetrisBlock* block = (AT_TetrisBlock*)TetrisBlock[blockIndex];

	block->MoveTheTetrisBlock(FVector(moveX, 0, moveZ));

	for (int i = 0; i < rotate; i++) {
		block->RotateTheTetrisBlock();
	}

}
