#include "stdafx.h"
#include "MoveScriptComponent.h"
#include "TransformComponent.h"

MoveScriptComponent::MoveScriptComponent(Actor* const actor, TransformComponent* const transform)
	: IComponent(actor, transform)
{
}

void MoveScriptComponent::Initialize()
{
}

void MoveScriptComponent::Update()
{
	D3DXVECTOR3 position = transform->GetPosition();

	if (GetAsyncKeyState('W') & 0x8000) position.y++;
	else if (GetAsyncKeyState('A') & 0x8000) position.x--;
	if (GetAsyncKeyState('S') & 0x8000) position.y--;
	else if (GetAsyncKeyState('D') & 0x8000) position.x++;

	transform->SetPosition(position);
}

void MoveScriptComponent::Destroy()
{
}
