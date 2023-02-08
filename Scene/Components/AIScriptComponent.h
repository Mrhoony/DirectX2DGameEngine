#pragma once

#include "IComponent.h"

class AIScriptComponent final : public IComponent
{
public:
	AIScriptComponent(
		class Actor* const actor,
		class TransformComponent* const transform
	);
	~AIScriptComponent() = default;

	void Initialize() override;
	void Update() override;
	void Destroy() override;

	enum class Direction
	{
		Up,		// 0
		Right,	// 1
		Down,	// 2
		Left,	// 3
	};

private:
	Stopwatch stopwatch;
	Direction dir = Direction::Right;
};

