// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "SphereGeneration.generated.h"

class UProceduralMeshComponent;

UCLASS()
class WIDGETTEST_API ASphereGeneration : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASphereGeneration();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bCreateCollision = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	friend class ATestActorBase;

	UProceduralMeshComponent* SphereMesh;
	FVector PlanetLocation;
	TArray<FVector> Vertices;
	TArray<FVector> VerticesBuffer;
	int32 Sections;
	TArray<int32> Triangles;
	TArray<FVector2D> UV0;
	UMaterialInterface* Material;
	TArray<FRotator> FaceRotations;
	float AxisPos;
	float Resolution = 8;
	float GridSpacing = 1;
	void CreateGridMesh(float SphereRadius);
	void DestroyMesh();

};
