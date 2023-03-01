#pragma once

#include "stdafx.h"
#include "Subsystem/ISubsystem.h"

class Context final
{
public:
	Context() = default;
	~Context()
	{

	}

	const bool InitializeSubsystem()
	{

	}

	template<typename T>
	const T* const RegisterSubsystem()
	{

	}

	template<typename T>
	T* const GetSubsystem()
	{

	}

	void UpdateSubsystems()
	{

	}

	void RenderSubsystems()
	{

	}

private:
	std::vector<ISubsystem*> subsystem;
};
