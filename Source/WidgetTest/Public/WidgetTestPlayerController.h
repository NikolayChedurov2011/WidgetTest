// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WidgetTestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETTEST_API AWidgetTestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

private:
	
	virtual void BeginPlay() override;

	AActor* CurrentActor = nullptr;
	class IActorInterface* CurrentInterface = nullptr;

	UFUNCTION(BlueprintCallable)
	void TraceUnderCursor(FVector Start, FVector End);
	UFUNCTION(BlueprintCallable)
	void OnIncreaseSpherePressed();
	UFUNCTION(BlueprintCallable)
	void OnDecreaseSpherePressed();
};
