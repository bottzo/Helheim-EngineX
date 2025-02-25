#include "UltimateState.h"
#include "UltimateAttack.h"
#include "Application.h"
#include "ModuleInput.h"
#include "Keys.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "ScriptComponent.h"
#include "GameManager.h"
#include "HudController.h"
#include "ModuleScene.h"
#include "PlayerStats.h"

UltimateState::UltimateState(PlayerController* player, float cooldown, float duration) : State(player, cooldown)
{
	mUltimateDuration = duration;
	GameObject* ultimateGO = mPlayerController->GetUltimateGO();
	if (ultimateGO)
	{
		mUltimateScript = static_cast<UltimateAttack*>(static_cast<ScriptComponent*>(ultimateGO->GetComponent(ComponentType::SCRIPT))->GetScriptInstance());
	}
}

UltimateState::~UltimateState()
{
}

StateType UltimateState::HandleInput()
{
	//Keep returning ultimate until timer reaches end 
	if (!mTimer.Delay(mUltimateDuration)) return StateType::ULTIMATE;
	else return StateType::AIM;
}

void UltimateState::Update()
{
	//mPlayerController->UltimateRotation();
}

void UltimateState::Enter()
{
	mUltimateScript->mDamageTick = mPlayerController->GetUltimateDamageTick();
	mUltimateScript->mInterval = mPlayerController->GetUltimateDamageInterval();
	mUltimateDuration = mPlayerController->GetUltimateDuration();
	mPlayerController->EnableUltimate(true);

}

void UltimateState::Exit()
{
	mPlayerController->EnableUltimate(false);
	SetCooldown(mPlayerController->GetUltimateCooldown());

	if (GameManager::GetInstance()->GetHud())
	{
		GameManager::GetInstance()->GetHud()->SetUltimateCooldown(0.0f);
	}

	mPlayerController->EnableLaser(true);
	mPlayerController->UseUltimateResource();
	mPlayerController->SetSpineAnimation("tAim", 0.3f);


}

StateType UltimateState::GetType()
{
	return StateType::ULTIMATE;
}

bool UltimateState::IsReady()
{
	if (mPlayerController->GetUltimateGO() && mPlayerController->IsUltimateUnlocked() && mPlayerController->GetUltimateResource() >= 100
		&& (App->GetInput()->GetKey(Keys::Keys_C) == KeyState::KEY_DOWN || App->GetInput()->GetGameControllerTrigger(LEFT_TRIGGER) == ButtonState::BUTTON_DOWN)
		)
	{
		return true;
	}
	return false;
}

