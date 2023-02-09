#pragma once

#include "IComponent.h"

enum State
{
	Chase,
	Avoid
};

class ChaseAIScriptComponent final : public IComponent
{
public:
	ChaseAIScriptComponent(
		class Actor* const actor,
		class TransformComponent* const transform
	);
	~ChaseAIScriptComponent() = default;

	void Initialize() override;
	void Update() override;
	void Destroy() override;

	void SetTarget(const std::shared_ptr<const class Actor> target);

private:
	std::weak_ptr<const class Actor> target;
	enum State  current_state = State::Chase;
};
