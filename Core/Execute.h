#pragma once

struct CAMERA_DATA
{
	D3DXMATRIX view;
	D3DXMATRIX projection;
};

class Execute
{
public:
	Execute();
	~Execute();

	void Update();
	void Render();

private:
	D3D11_Pipeline* pipeline = nullptr;

	class Camera* camera = nullptr;
	D3D11_ConstantBuffer* camera_buffer = nullptr;

	std::vector<std::shared_ptr<class Actor>> actors;
};