// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetTestPlayerController.h"
#include "Interfaces/ActorInterface.h"

void AWidgetTestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bAttachToPawn = true;
}

void AWidgetTestPlayerController::TraceUnderCursor(FVector Start, FVector End)
{
	FHitResult Hit;
	FCollisionQueryParams TraceParam;

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParam);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 10.f);

	if (!bHit) return;

	if (!(Hit.GetActor()->Implements<UActorInterface>()))
	{
		if (CurrentActor)
		{
			CurrentInterface->HideSphere();
			CurrentActor = nullptr;
			CurrentInterface = nullptr;
		}
	}

	if (Hit.GetActor()->Implements<UActorInterface>())
	{
		if (Hit.GetActor() != CurrentActor)
		{
			if (CurrentActor)
			{
				CurrentInterface->HideSphere();
				CurrentInterface = Cast<IActorInterface>(Hit.GetActor());

				if (CurrentInterface->GetWidgetComponent() == Hit.GetComponent())
				{
					CurrentActor = Hit.GetActor();
					CurrentInterface->ShowSphere();
				}
				else {
					CurrentActor = nullptr;
					CurrentInterface = nullptr;
				}
			}
			else {
				CurrentInterface = Cast<IActorInterface>(Hit.GetActor());
				CurrentActor = Hit.GetActor();
				CurrentInterface->ShowSphere();
			}

		}
	}
}

void AWidgetTestPlayerController::OnIncreaseSpherePressed()
{
	if (CurrentActor)
	{
		CurrentInterface->IncreaseRadius();
	}
}

void AWidgetTestPlayerController::OnDecreaseSpherePressed()
{
	if (CurrentActor)
	{
		CurrentInterface->DecreaseRadius();
	}
}