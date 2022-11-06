// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActorWidget.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETTEST_API UActorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual bool Initialize();

	UFUNCTION()
	void SetActorIndex(float pIndex);

protected:
	friend class ATestActorBase;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Index;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Overlapped;

	class ATestActorBase* Owner;

	void SetOverlappedNum(int32 pOverlapNum);
	void SetOwner(ATestActorBase* pOwner);

};
