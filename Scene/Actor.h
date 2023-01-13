#pragma once

#include "Scene/Components/IComponent.h"

class Actor final
{
public:
	Actor();
	~Actor();

private:

	std::vector<std::shared_ptr<IComponent>> components;
};

