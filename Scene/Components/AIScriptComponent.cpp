#include "stdafx.h"
#include "AIScriptComponent.h"
#include "TransformComponent.h"

AIScriptComponent::AIScriptComponent(Actor* const actor, TransformComponent* const transform)
	: IComponent(actor, transform)
{
}

void AIScriptComponent::Initialize()
{
}

void AIScriptComponent::Update()
{
	D3DXVECTOR3 position = transform->GetPosition();

	switch (dir)
	{
	case AIScriptComponent::Direction::Up:		position.y++;	break;
	case AIScriptComponent::Direction::Right:	position.x++;	break;
	case AIScriptComponent::Direction::Down:	position.y--;	break;
	case AIScriptComponent::Direction::Left:	position.x--;	break;
	
	} // switch (dir)

	if (stopwatch.GetElapsedTimerSec() >= 3.0f)
	{
		Direction new_dir = static_cast<Direction>(Math::Random(0, 3));

		if (new_dir == dir)
		{
			int dir_num = static_cast<int>(dir);

			dir_num = (dir_num <= 1) ? dir_num + 2 : dir_num - 2;

			dir = static_cast<Direction>(dir_num);
		}
		else
			dir = new_dir;

		stopwatch.Start();
	}

	transform->SetPosition(position);
}

void AIScriptComponent::Destroy()
{
}
