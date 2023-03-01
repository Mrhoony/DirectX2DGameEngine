#pragma once

class Engine final
{
public:
	Engine();
	~Engine();

	void Update();
	void Render();

private:
	std::shared_ptr<class SceneManager> scene_manager;

	class Context* context = nullptr;
};
