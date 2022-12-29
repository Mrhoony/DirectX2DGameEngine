#include "stdafx.h"
#include "Core/Window.h"
#include "Core/Execute.h"

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
	Settings::Get().SetWidth(Window::GetWidth());
	Settings::Get().SetHeight(Window::GetHeight());

	Execute* execute = new Execute();

	// ½ÇÇà
	while (Window::Update())
	{
		execute->Update();
		execute->Render();
	}

	SAFE_DELETE(execute);
	Window::Destroy();
}