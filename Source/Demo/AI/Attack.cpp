// Fill out your copyright notice in the Description page of Project Settings.

#include "Attack.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"



// Sets default values
AAttack::AAttack()
{
	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	//MyBoxComponent->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	RootComponent = MyBoxComponent;

	//Fire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("My Fire"));
	//Fire->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//Fire->SetupAttachment(RootComponent);

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAttack::OnOverlapBegin);
	MyBoxComponent->OnComponentEndOverlap.AddDynamic(this, &AAttack::OnOverlapEnd);

	bCanApplyDamage = false;

}



void AAttack::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {

		bCanApplyDamage = true;
		//MyCharacter = Cast<AActor>(OtherActor);
		MyCharacter = Cast<ADemoCharacter>(OtherActor);
		MyHit = SweepResult;
		GetWorldTimerManager().SetTimer(TimeHandle, this, &AAttack::ApplyAttackDamage, 2.2f, true, 0.0f);

	}


}

void AAttack::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	bCanApplyDamage = false;
	GetWorldTimerManager().ClearTimer(TimeHandle);


}

void AAttack::ApplyAttackDamage()
{
	if (bCanApplyDamage) {
		UGameplayStatics::ApplyPointDamage(MyCharacter, 200.0f, GetActorLocation(), MyHit, nullptr, this, AttackDamageType);
	}

}
