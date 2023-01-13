#pragma once

class Camera final
{
public:
	Camera();
	~Camera() = default;

	const D3DXMATRIX& GetViewMatrix() const { return view; }
	const D3DXMATRIX& GetProjectionMatrix() const { return projection; }

	const D3DXVECTOR3& GetPosition() { return position; }
	void SetPosition(const D3DXVECTOR3& position) { this->position = position; }

	void Update();

private:
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

private:
	D3DXMATRIX view;
	D3DXMATRIX projection;

	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
};

