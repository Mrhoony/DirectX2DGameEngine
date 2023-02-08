#pragma once

class Execute
{
public:
	Execute();
	~Execute();

	void Update();
	void Render();

private:
	std::shared_ptr<class D3D11_Pipeline> pipeline = nullptr;

	std::vector<std::shared_ptr<class Actor>> actors;
};