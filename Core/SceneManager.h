#pragma once

class SceneManager final
{
public:
	SceneManager();
	~SceneManager();

	bool Initialize();
	const std::map<std::string, std::shared_ptr<class Scene>>& GetAllScenes() const { return scenes; }

	class Scene* const GetCurrentScene();
	void SetCurrentScene(const std::string& scene_name);

	class Scene* const RegisterScene(const std::string& scene_name);

	void Update();
	void Render();

private:
	std::map<std::string, std::shared_ptr<class Scene>> scenes;
	std::weak_ptr<class Scene> current_scene;
};
