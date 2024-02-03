// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTasks/GAS_DelegateTickTask.h"

UGAS_DelegateTickTask::UGAS_DelegateTickTask()
{
	bTickingTask = true;
}

UGAS_DelegateTickTask* UGAS_DelegateTickTask::DelegateTickTask(UGameplayAbility* OwningAbility, float _delegateDuration, float _delegateCallFrecuency)
{
	UGAS_DelegateTickTask* delegateTask = NewAbilityTask<UGAS_DelegateTickTask>(OwningAbility);
	delegateTask->delegateDuration = _delegateDuration;
	delegateTask->delegateCallFrecuency = _delegateCallFrecuency;

	return delegateTask;
}

void UGAS_DelegateTickTask::Activate()
{
	elapsedDelegateTime = 0.f;
	delegateFrecuencyElapsed = 0.f;
	onStart.Broadcast();
}

void UGAS_DelegateTickTask::TickTask(float DeltaTime)
{

	if (elapsedDelegateTime < delegateDuration)
	{
		delegateFrecuencyElapsed += DeltaTime;
		elapsedDelegateTime += DeltaTime;

		if (delegateFrecuencyElapsed > delegateCallFrecuency)
		{
			delegateFrecuencyElapsed = delegateFrecuencyElapsed - delegateCallFrecuency;
			tickFunctionality.Broadcast(elapsedDelegateTime, DeltaTime);
		}
	}
	else
	{
		onEnd.Broadcast();
		EndTask();
	}

}