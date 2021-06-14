// Fill out your copyright notice in the Description page of Project Settings.


#include "ThunderWeather.h"
#include "IThunderHit.h"
#include "DrawDebugHelpers.h"
#include "Grid.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
AThunderWeather::AThunderWeather()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThunderSeq = GetInitThunderSeq();


}

// Called when the game starts or when spawned
void AThunderWeather::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AThunderWeather::GetLocationFromBlockIdx(int32 GridAddress)
{
	FVector Center = GetActorLocation();
	FVector OutLocation = FVector(-(GridWidth * 0.5f) * TileSize.X + (TileSize.X * 0.5f), -(GridHeight * 0.5f) * TileSize.Y + (TileSize.Y * 0.5f), 0);
	check(GridWidth > 0);
	OutLocation.X += TileSize.X * (float)(GridAddress % GridWidth);
	OutLocation.Y += TileSize.Y * (float)(GridAddress / GridWidth);
	OutLocation += Center;

	return OutLocation;
}

void AThunderWeather::ProcessParticleColl(FVector loc, FVector v)
{
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), false, this);
	RV_TraceParams.bTraceComplex = false;
	RV_TraceParams.bReturnPhysicalMaterial = true;

	FCollisionObjectQueryParams coqp;
	//coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	//coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);

	FVector Start = loc;
	v.Normalize();
	FVector End = loc + FVector(0,0, ParticleTraceDis);

	TArray<FHitResult> HitResult;

	TArray <TEnumAsByte<EObjectTypeQuery>> objts; 
	TArray <AActor*> ig,out ;
	objts.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), loc, ParticleTraceDis,objts, nullptr, ig,out);
	for (auto a : out) { 
		auto ih = Cast<IThunderHit>(a);
		if (ih) {
			ih->BeHit();
		}
	}
	/*
	//GetWorld()->LineTraceSingleByObjectType;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f); 
	//GetWorld()->BoxO
	bool everHit = GetWorld()->LineTraceMultiByObjectType(
		HitResult,
		Start,
		End,
		coqp,
		RV_TraceParams
	);
	if (everHit) { 
		for (auto Hit : HitResult) { 
			auto ac = Hit.Actor;
			auto ih = Cast<IThunderHit>(ac);
			if (ih) {
				ih->BeHit();
			}
		}
	}
	*/
}

TArray<int32> AThunderWeather::GetInitThunderSeq()
{
	TArray<int32> ans;
	ans = { 1 };
	//return ans;
	auto  a = fib.GetFibList(SeqLength, GridWidth * GridHeight);
	for (auto i : a) {
		ans.Add(i);
	}
	return ans;
}

// Called every frame
void AThunderWeather::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanStart && bStarted == false) {
		verify(GetWorld() != nullptr);
		StartThunder();
		bStarted = true;
	}
	
	
	
}

void AThunderWeather::StartThunder()
{
	verify(GetWorld());
	Grid grid(GridHeight,GridWidth,0,0,GridWidth-1,GridHeight-1,min_path,block_cnt);
	auto res = grid.getGameMap(0.02);
	verify(res.size()>0);
	for (int32 i = 0; i < GridWidth * GridHeight; i++) {
		auto loc = GetLocationFromBlockIdx(i);

		auto sym_loc = loc;
		sym_loc.Z = default_sym_z;

		int x = i / GridWidth;
		int y = i % GridWidth;
		verify(x>=0 && x<GridWidth && x<res.size());
		verify(y>=0 && y<GridHeight && y<res[0].size());

		/*
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), false, this);
		RV_TraceParams.bTraceComplex = false;
		RV_TraceParams.bReturnPhysicalMaterial = true;

		FCollisionObjectQueryParams coqp;
		coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
		coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic); 

		FVector Start = loc;  

		FVector End = Start;
		End.Z = 0;
		 
		TArray<FHitResult> HitResults;
		bool everHit = GetWorld()->LineTraceMultiByObjectType(
			HitResults,
			Start,
			End,
			coqp,
			RV_TraceParams
		);
		if (everHit && HitResults.Num() > 0) {
			auto hitr = HitResults[0];
			
			sym_loc = hitr.Location;
			sym_loc.Z += sym_z_offset;
		}
		*/

		bool blockOrNot = (bool)res[x][y];

		BPGenBlockSymbol(i,sym_loc,blockOrNot);
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DefaultTimer, this, &AThunderWeather::GenThunder, ThunderGap, true);
}

void AThunderWeather::GenThunderOnce()
{
	verify(ThunderIdx >= 0 && ThunderIdx < ThunderSeq.Num());

	auto block_idx = ThunderSeq[ThunderIdx];
	auto loc = GetLocationFromBlockIdx(block_idx);

	ThunderIdx++;
	if (ThunderIdx >= ThunderSeq.Num()) ThunderIdx = 0;

	
	BPGenThunder(loc);

	
}

void AThunderWeather::GenThunder()
{
	for (int32 i = 0; i < ThunerOneTimeCount; i++) {
		GenThunderOnce();
	}
}

