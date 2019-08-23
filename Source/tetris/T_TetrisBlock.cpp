// Fill out your copyright notice in the Description page of Project Settings.

#include "T_TetrisBlock.h"
#include "T_Block.h"
#include "Engine/World.h"


// Sets default values
AT_TetrisBlock::AT_TetrisBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RotationCnt = 0;

	Block_BP = NULL;

	AITimer = 0;
}

// Called when the game starts or when spawned
void AT_TetrisBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AT_TetrisBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AT_TetrisBlock::Initialize(UClass* bpActor, FVector location) {
	if (!GetWorld()) return;

	if(!Block_BP) Block_BP = bpActor;

	if (BlockPositionData.Num() > 0) {

		FActorSpawnParameters spawnParam;
		spawnParam.Owner = this;
		spawnParam.Instigator = Instigator;


		Block.Empty();


		FVector blockExtent;
		FVector ori;
		for (int i = 0; i < 4; i++) {
			FTransform tarLocation;
			FVector mov;
			mov.X = BlockPositionData[i].X * 98;;
			mov.Z = BlockPositionData[i].Y * 98;;
			tarLocation.SetLocation(location + GetActorLocation() + mov);

			Block.Add(GetWorld()->SpawnActor<AActor>(Block_BP, tarLocation, spawnParam));
		}
	}


}

void AT_TetrisBlock::MoveTheTetrisBlock(FVector location) {
	SetActorLocation(GetActorLocation() + location);
	for (int i = 0; i < 4; i++) {
		AT_Block* blo = (AT_Block*)Block[i];
		blo->MoveTheBlock(location);
	}
}
void AT_TetrisBlock::RotateTheTetrisBlock() {

	RotationCnt++;
	if (RotationCnt >= BlockPositionData.Num() / Block.Num()) RotationCnt = 0;


	FVector newLocation;
	FVector blockExtent;
	FVector ori;
	for (int i = 0; i < Block.Num(); i++) {
		Block[i]->GetActorBounds(0, ori, blockExtent);
		newLocation.X = BlockPositionData[i + Block.Num()*RotationCnt].X*blockExtent.X*2;
		newLocation.Y = 0;
		newLocation.Z = BlockPositionData[i + Block.Num()*RotationCnt].Y*blockExtent.Z*2;
		newLocation += GetActorLocation();
		Block[i]->SetActorLocation(newLocation,0);
	}

}

void AT_TetrisBlock::SetInitialData(TArray< FIntPoint > posData) {
	BlockPositionData = posData;
}

bool AT_TetrisBlock::CheckDroppable(TArray< bool > blockArr, FIntPoint widhei, FVector arrayLocation) {


	int x = 0;

	float xx = 0;

	int y = 0;

	float yy = 0;

	for (int i = 0; i < Block.Num(); i++) {
		x= Block[i]->GetActorLocation().X;

		x= x - arrayLocation.X;

		xx = x / 100;

		y = Block[i]->GetActorLocation().Z;
		y = y - arrayLocation.Z;
		if (y > widhei.Y * 100) return 1;
		if (y < 100) return 0;

		yy = y / 100;

		
		if (blockArr[xx + (int)((yy - 1)*widhei.X)]) return 0;
	}

	return 1;
}

void AT_TetrisBlock::SetAIData(TArray< FVector4 > aiDat) {
	AIData = aiDat;
}

bool AT_TetrisBlock::CheckIsLocatable(TArray< bool > blockArrS, int x, int y, int rotCnt, int blockNum, FIntPoint widhei) {
	int* posX = new int;
	int* posY = new int;
	*posX = 0;
	*posY = 0;

	for (int i = 0; i < Block.Num(); i++) {

		*posX = BlockPositionData[i + rotCnt * Block.Num()].X - BlockPositionData[blockNum + rotCnt * Block.Num()].X;
		*posY = BlockPositionData[i + rotCnt * Block.Num()].Y - BlockPositionData[blockNum + rotCnt * Block.Num()].Y;
		if (x + (*posX) < 0
			|| y + (*posY) < 0
			|| x + (*posX) >= widhei.X
			|| y + (*posY) >= widhei.Y
			|| blockArrS[x + y * widhei.X + (*posX) + (*posY)* widhei.X]) {
			delete posX;
			delete posY;
			return 0;
		}

		for (int j = 0; j < 3; j++) {
			if (y + (*posY) + j < widhei.Y) {
				if (blockArrS[x + y * widhei.X + (*posX) + (*posY + j)* widhei.X]) {
					delete posX;
					delete posY;
					return 0;
				}
			}
		}
	}

	delete posX;
	delete posY;
	return 1;
}

FVector4 AT_TetrisBlock::HightLineHoleBump(TArray< bool > const blockArrS, TArray< int > const xAxis, int x, TArray< int > const yAxis, int y, int rotCnt, int blockNum, FIntPoint const widhei){
	int* posX = new int;
	int* posY = new int;
	*posX = 0;
	*posY = 0;

	TArray< bool > tmpBAS = blockArrS;
	TArray< int > tmpXAxis = xAxis;
	TArray< int > tmpYAxis = yAxis;
	TArray< int > xAxisBlockCounter = tmpXAxis;
	int* minX = new int;
	int* maxX = new int;
	int* maxY = new int;
	*minX = widhei.X;
	*maxX = 0;
	*maxY = 0;

	for (int i = 0; i < Block.Num(); i++) {

		*posX = BlockPositionData[i + rotCnt * Block.Num()].X - BlockPositionData[blockNum + rotCnt * Block.Num()].X;
		*posY = BlockPositionData[i + rotCnt * Block.Num()].Y - BlockPositionData[blockNum + rotCnt * Block.Num()].Y;

		if ((*posX) < (*minX))*minX = *posX;
		if ((*posX) > (*maxX))*maxX = *posX;
		if ((*posY) > (*maxY))*maxY = *posY;

		tmpYAxis[y + (*posY)]++;
		tmpBAS[x + y * widhei.X + (*posX) + (*posY)* widhei.X] = 1;

	}

	
	*minX += x;
	*maxX += x;
	*maxY += y;

	int* totalHeight = new int(0);
	int* completedLines = new int(0);
	int* holes = new int(0);
	int* bumpiness = new int(0);
	int* bump = new int(0);
	int* highst = new int(0);

	delete posX;
	delete posY;

	for (int w = 0; w <= *maxY; w++) {
		if (tmpYAxis[w] >= widhei.X) { 
			*completedLines += 1;
			for (int l = 0; l < widhei.X; l++) {
				tmpBAS.RemoveAt(w*widhei.X);
				tmpBAS.Add(0);
			}
		}
	}


	for (int j = 0; j <= *maxY; j++) {
		for (int k = 0; k < widhei.X; k++) {
			if (tmpBAS[k + j * widhei.X]) {
				tmpXAxis[k] = j + 1;
				xAxisBlockCounter[k]++;
			}
		}
	}
	int nn = 0;


	float* scoreHei = new float(-0.510066f);
	float* scoreL = new float(0.760666f);
	float* scoreHol = new float(-0.40663f);
	float* scoreB = new float(-0.184483f);

	//float* scoreHei = new float(-0.510066f);
	//float* scoreL = new float(0.760666f);
	//float* scoreHol = new float(-0.45663f);
	//float* scoreB = new float(-0.184483f);

	*minX -= 5;
	*maxX += 5;
	if (*minX < 0)*minX = 0;
	if (*maxX >= widhei.X-1)*maxX = widhei.X - 1;
	for (int m = *minX; m <= *maxX; m++) {
		*totalHeight += tmpXAxis[m];
		*holes += tmpXAxis[m] - xAxisBlockCounter[m];
		if (m > 0) {
			*bump = FMath::Abs(tmpXAxis[m] - tmpXAxis[m - 1]);
			*bumpiness += *bump;
		}
		if (*highst < tmpXAxis[m]) *highst = tmpXAxis[m];
	}


	*scoreHei *= *totalHeight;
	*scoreL *= *completedLines;
	*scoreHol *= *holes;
	*scoreB *= *bumpiness;

	float* total = new float(*scoreHei + *scoreL + *scoreHol + *scoreB/*+ (*highst)*(-1)*/);

	if (AIData.Num() < 1) AIData.Add(FVector4(-999999, 0, 0, 0));

	if (*total > AIData[0].X) {
		AIData[0].Set(*total, x - BlockPositionData[blockNum + rotCnt * Block.Num()].X, y - BlockPositionData[blockNum + rotCnt * Block.Num()].Y, rotCnt);
	}

	delete minX;
	delete maxX;
	delete maxY;

	delete totalHeight;
	delete completedLines;
	delete holes;
	delete bumpiness;
	delete bump;
	delete highst;

	delete scoreHei;
	delete scoreL;
	delete scoreHol;
	delete scoreB;


	tmpBAS.Empty();
	tmpXAxis.Empty();
	tmpYAxis.Empty();
	xAxisBlockCounter.Empty();
	return FVector4(AIData[0]);
}
