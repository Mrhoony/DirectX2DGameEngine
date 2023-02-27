#include "stdafx.h"
#include "ChaseAIScriptComponent.h"
#include "TransformComponent.h"
#include "Scene/Actor.h"

ChaseAIScriptComponent::ChaseAIScriptComponent(Actor* const actor, TransformComponent* const transform)
	: IComponent(actor, transform)
{
}

void ChaseAIScriptComponent::Initialize()
{
	Timer.Start();
}

void ChaseAIScriptComponent::Update()
{
	if (target.expired() == true) // target == nullptr
		return;

	D3DXVECTOR3 my_position = transform->GetPosition();
	D3DXVECTOR3 target_position = target.lock()->GetTransform()->GetPosition();

	D3DXVECTOR3 dir = target_position - my_position;

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length >= 300)current_state = State::Chase;
	if (length <= 50)current_state = State::Avoid;

	D3DXVec3Normalize(&dir, &dir);

	D3DXVECTOR3 move_position(0, 0, 0);

	switch (current_state)
	{
	case Chase:
		move_position = my_position + (dir * Timer.GetElapsedTimerSec() * speed);
		break;
	case Avoid:
		move_position = my_position - (dir * Timer.GetElapsedTimerSec() * speed);
		break;
	}

	Timer.Start();

	transform->SetPosition(move_position);
}

void ChaseAIScriptComponent::Destroy()
{
}

void ChaseAIScriptComponent::SetTarget(const std::shared_ptr<const class Actor> target)
{
	if (actor == target.get())
		return;

	this->target = target;
}
