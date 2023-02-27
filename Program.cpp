#include "stdafx.h"
#include "Core/Window.h"
#include "Core/SceneManager.h"

int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{
	std::cout << GUID_Generator::Generate();

	Window::Create(hInstance, 1280, 739);
	Window::Show();

	Settings::Get().SetWindowHandle(Window::global_handle);
	Settings::Get().SetWidth(static_cast<float>(Window::GetWidth()));
	Settings::Get().SetHeight(static_cast<float>(Window::GetHeight()));

	std::unique_ptr<SceneManager> scene_manager = std::make_unique<SceneManager>();
	scene_manager->Initialize();

	// ½ÇÇà
	while (Window::Update())
	{
		scene_manager->Update();
		scene_manager->Render();
	}

	Window::Destroy();
}