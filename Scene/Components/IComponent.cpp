#include "stdafx.h"
#include "IComponent.h"

IComponent::IComponent(Actor* const actor, TransformComponent* const transform)
	: actor(actor)
	, transform(transform)
{
}

template<typename T>
inline constexpr ComponentType IComponent::DeduceComponentType()
{
	return ComponentType::Unknown;
}

// Explicit Specialization
#define REGISTER_COMPONENT_TYPE(T, enum_type) template<> constexpr ComponentType IComponent::DeduceComponentType<T>(){ return enum_type; }

REGISTER_COMPONENT_TYPE(TransformComponent, ComponentType::Transform)