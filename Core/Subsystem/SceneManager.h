#pragma once
#include "ISubsystem.h"

class SceneManager final : public ISubsystem
{
public:
	SceneManager(Context* context);
	~SceneManager();

	bool Initialize() override;
	void Update() override;
	void Render() override;

	const std::map<std::string, std::shared_ptr<class Scene>>& GetAllScenes() const { return scenes; }

	class Scene* const GetCurrentScene();
	void SetCurrentScene(const std::string& scene_name);

	class Scene* const RegisterScene(const std::string& scene_name);

	

private:
	std::map<std::string, std::shared_ptr<class Scene>> scenes;
	std::weak_ptr<class Scene> current_scene;
};
