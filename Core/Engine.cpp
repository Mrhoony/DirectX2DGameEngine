#include "stdafx.h"
#include "Engine.h"
#include "Core/SceneManager.h"

Engine::Engine()
{
	scene_manager = std::make_shared<SceneManager>();
	scene_manager->Initialize();
}

Engine::~Engine()
{
}

void Engine::Update()
{
	scene_manager->Update();
}

void Engine::Render()
{
	scene_manager->Render();
}
