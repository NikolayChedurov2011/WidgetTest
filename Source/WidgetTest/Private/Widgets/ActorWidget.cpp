// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ActorWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "WidgetActor/TestActorBase.h"

bool UActorWidget::Initialize()
{
	Super::Initialize();

	return true;
}

void UActorWidget::SetOwner(ATestActorBase* pOwner)
{
	Owner = pOwner;
	Owner->OnOverlapActors.AddUObject(this, &ThisClass::SetOverlappedNum);
}

void UActorWidget::SetActorIndex(float pIndex)
{
	if (!Txt_Index) return;
	Txt_Index->SetText(FText::AsNumber(pIndex));
}

void UActorWidget::SetOverlappedNum(int32 pOverlapNum)
{
	Txt_Overlapped->SetText(FText::AsNumber(pOverlapNum));
}