// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WIDGETTEST_API IActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual USceneComponent* GetWidgetComponent() const = 0;
	UFUNCTION()
	virtual void IncreaseRadius() = 0;
	UFUNCTION()
	virtual void DecreaseRadius() = 0;
	UFUNCTION()
	virtual void ShowSphere() = 0;
	UFUNCTION()
	virtual void HideSphere() = 0;
};
