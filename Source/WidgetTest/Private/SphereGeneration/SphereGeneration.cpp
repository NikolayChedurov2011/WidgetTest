// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereGeneration/SphereGeneration.h"
#include "ProceduralMeshComponent.h"
#include "Math/Rotator.h"

// Sets default values
ASphereGeneration::ASphereGeneration()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("MaterialInterface'/Game/WidgetTest/Assets/M_SphereMat.M_SphereMat'"));
	if (MaterialAsset.Succeeded())
	{
		Material = (UMaterial*)MaterialAsset.Object;
	}
 	
	PrimaryActorTick.bCanEverTick = false;

	SphereMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMeshComponent");
	SphereMesh->bUseComplexAsSimpleCollision = true;
	SphereMesh->SetupAttachment(RootComponent);

	FaceRotations.Add(FRotator(0, 0, 90));
	FaceRotations.Add(FRotator(0, 0, 180));
	FaceRotations.Add(FRotator(0, 0, 270));
	FaceRotations.Add(FRotator(0, 0, 360));
	FaceRotations.Add(FRotator(90, 0, 0));
	FaceRotations.Add(FRotator(270, 0, 0));

}

// Called when the game starts or when spawned
void ASphereGeneration::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASphereGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASphereGeneration::CreateGridMesh(float SphereRadius)
{
	DestroyMesh();

	SphereRadius /= 2;

	FVector OwnLocation = GetActorLocation();

	int32 MaxSideCount = 6;
	int32 CurrentSide = 0;

	TArray<FVector> BaseVertices;
	FVector2D Extent = FVector2D((Resolution - 1) * GridSpacing, (Resolution - 1) * GridSpacing) / 2;



	//Verticles
	for (int i = 0; i < Resolution; i++)
	{
		for (int j = 0; j < Resolution; j++)
		{
			BaseVertices.Add(FVector((float)j * GridSpacing - Extent.X, (float)i * GridSpacing - Extent.Y, 0));
		}
	}


	//Triangles
	for (int i = 0; i < Resolution - 1; i++)
	{
		for (int j = 0; j < Resolution - 1; j++)
		{
			int idx = j + (i * Resolution);
			Triangles.Add(idx);
			Triangles.Add(idx + Resolution);
			Triangles.Add(idx + 1);

			Triangles.Add(idx + 1);
			Triangles.Add(idx + Resolution);
			Triangles.Add(idx + Resolution + 1);
		}
	}


	//Create SphereMesh
	float P = (8 % 2) ? 0.7 : 1.15;

	while (CurrentSide < 6)
	{
		for (int i = 0; i < BaseVertices.Num(); i++)
		{
			FVector ResultVertices = BaseVertices[i] + FVector(0, 0, (Resolution - 1) / 2);
			ResultVertices = FaceRotations[CurrentSide].RotateVector(ResultVertices);
			ResultVertices.Normalize();
			ResultVertices = ResultVertices * SphereRadius * 2;

			Vertices.Add(ResultVertices);
			VerticesBuffer.Add(ResultVertices);
		}
		SphereMesh->CreateMeshSection(CurrentSide, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), bCreateCollision);
		SphereMesh->SetMaterial(CurrentSide, Material);
		Vertices.Empty();

		CurrentSide++;
	}

	Sections = VerticesBuffer.Num() / 6;
}

void ASphereGeneration::DestroyMesh()
{
	SphereMesh->ClearAllMeshSections();

	Triangles.Empty();
	Vertices.Empty();
	UV0.Empty();
	UE_LOG(LogTemp, Warning, TEXT("Clear mesh sections"));
}