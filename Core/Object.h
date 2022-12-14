#pragma once
#include "stdafx.h"

class Object
{
public:
	Object() { id = GUID_Generator::Generate(); };
	virtual ~Object() = default;

	uint GetID() const { return id; }
	uint SetID(const uint& id) { this->id = id; }

private:
	uint id = 0;
};