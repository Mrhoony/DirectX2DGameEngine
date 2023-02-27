#pragma once

class Scene
{
public:
	Scene();
	~Scene();

	void Update();
	void Render();

	const std::shared_ptr<class Actor> CreateActor(const bool& is_active = true);
	void AddActor(const std::shared_ptr<class Actor>& actor);

private:
	std::shared_ptr<class D3D11_Pipeline> pipeline = nullptr;

	std::vector<std::shared_ptr<class Actor>> actors;
};