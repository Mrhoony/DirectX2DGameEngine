#pragma once

enum class ComponentType : uint
{
	Unknown,
	Camera,
	Transform,
	MeshRenderer,
};

class IComponent
{
public:
	template<typename T>
	static constexpr ComponentType DeduceComponentType();

public:
	IComponent(class Actor* const actor, class TransformComponent* const transform);
	virtual ~IComponent() = default;

	virtual void Initialize() abstract;
	virtual void Update() abstract;
	virtual void Destroy() abstract;

	class Actor* GetActor() const { return actor; }
	void SetActor(class Actor* const actor) { this->actor = actor; }

	class TransformComponent* GetTransform() const { return transform; }
	void SetTransform(class TransformComponent* const transform) { this->transform = transform; }

	ComponentType GetComponentType() const { return component_type; }
	void SetComponentType(const ComponentType& type) { this->component_type = type; }

	bool IsEnabled() const { return is_enabled; }
	void SetEnabled(const bool& is_enabled) { this->is_enabled = is_enabled; }

protected:
	class Actor* actor = nullptr;
	class TransformComponent* transform = nullptr;
	bool is_enabled = true;

	ComponentType component_type = ComponentType::Unknown;
};
