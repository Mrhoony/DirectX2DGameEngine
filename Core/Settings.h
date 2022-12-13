#pragma once

#include "stdafx.h"

class Settings final
{
public:
	static Settings& Get()
	{
		static Settings instance;
		return instance;
	}

	HWND GetWindowHandle() { return handle; }
	void SetWindowHandle(HWND handle) { this->handle = handle; }

	const float& GetWidth() { return width; }
	void SetWidth(const float& width) { this->width = width; }

	const float& GetHeight() { return height; }
	void SetHeight(const float& height) { this->height = height; }


private:
	Settings() = default;
	~Settings() = default;

	Settings(const Settings&) = delete;
	Settings& operator=(const Settings&) = delete;

private:
	HWND handle = nullptr;
	float width = 0.0f;
	float height = 0.0f;
};