// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/TestActorBase.h"
#include "SphereGeneration/SphereGeneration.h"
#include "Widgets/ActorWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATestActorBase::ATestActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	}
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	Mesh->SetupAttachment(RootComponent);
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
}

//
// Called when the game starts or when spawned
void ATestActorBase::BeginPlay()
{
	Super::BeginPlay();

	Widget = Cast<UActorWidget>(WidgetComponent->GetUserWidgetObject());
	Widget->SetOwner(this);
	Widget->SetActorIndex(ActorIndex);
	FActorSpawnParameters SpawnParam;
	GeneratedSphere = GetWorld()->SpawnActor<ASphereGeneration>(GetActorLocation(), GetActorRotation(), SpawnParam);
}

//
// Called every frame
void ATestActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//
//Init overlap event. Check if some actor inside
void ATestActorBase::InitOverlap()
{
	OverlappedActorsArray.Empty();
	TArray<FHitResult> HitResults;

	const FVector Start = GetActorLocation();
	const FVector End = Start;

	const FCollisionShape ColShape = FCollisionShape::MakeSphere(CurrentRadius);
	const bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Visibility, ColShape);

	DrawDebugSphere(GetWorld(), Start, CurrentRadius, 12, FColor::Orange, false, 2, 0, 2);

	if (bHit)
	{
		for (FHitResult const HitResult : HitResults)
		{
			if (HitResult.GetActor()->Implements<UActorInterface>() && HitResult.GetActor() != this)
			{
				OverlappedActorsArray.AddUnique(HitResult.GetActor());
			}
		}

		OnOverlapActors.Broadcast(GetOverlappedActorsNum());
	}
}

//Return current overlapped actors num
int32 ATestActorBase::GetOverlappedActorsNum() const
{
	return OverlappedActorsArray.Num();
}

//
//Increase sphere radius
void ATestActorBase::IncreaseRadius()
{
	CurrentRadius = FMath::Min(MaxRadius, CurrentRadius + RadiusChandeValue);
	ShowSphere();
}

//
//Decrease sphere radius
void ATestActorBase::DecreaseRadius()
{
	CurrentRadius = FMath::Max(MinRadius, CurrentRadius - RadiusChandeValue);
	ShowSphere();
}

void ATestActorBase::ShowSphere()
{
	GeneratedSphere->CreateGridMesh(CurrentRadius);
	InitOverlap();
}

void ATestActorBase::HideSphere()
{
	GeneratedSphere->DestroyMesh();
	OverlappedActorsArray.Empty();
}

USceneComponent* ATestActorBase::GetWidgetComponent() const
{
	return WidgetComponent;
}