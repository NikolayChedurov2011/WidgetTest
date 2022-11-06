// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/ActorInterface.h"
#include "TestActorBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOverlapActors, const int32 OverlappedActorsNum);

UCLASS()
class WIDGETTEST_API ATestActorBase : public AActor, public IActorInterface
{
	GENERATED_BODY()
	
public:	
	
	FOverlapActors OnOverlapActors;

	ATestActorBase();

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent* WidgetComponent = nullptr;
	

	int32 GetOverlappedActorsNum() const;

	virtual USceneComponent* GetWidgetComponent() const override;
	virtual void IncreaseRadius() override;
	virtual void DecreaseRadius() override;
	virtual void ShowSphere() override;
	virtual void HideSphere() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitOverlap();

	UPROPERTY(EditAnywhere, meta=(ClampMin=1))
	float ActorIndex = 1;

	TArray<AActor*> OverlappedActorsArray;
	float MinRadius = 1000;
	float MaxRadius = 4000;
	float CurrentRadius = MinRadius;
	float RadiusChandeValue = 500;

	class ASphereGeneration* GeneratedSphere = nullptr;
	class UActorWidget* Widget = nullptr;
	class ACharacter* Character;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
