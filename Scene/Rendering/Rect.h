#pragma once

struct TRANSFORM_DATA
{
	D3DXMATRIX world;
};

enum class Direction
{
	Up,		// 0
	Right,	// 1
	Down,	// 2
	Left,	// 3
};

class Rect
{
public:
	Rect(class Graphics* graphics, const D3DXCOLOR& color);
	virtual ~Rect();

	void SetPosition(const D3DXVECTOR3& position) { this->position = position; }
	void SetScale(const D3DXVECTOR3& scale) { this->scale = scale; }

	const D3DXVECTOR3& GetPosition() const { return position; }
	const D3DXVECTOR3& GetScale() const { return scale; }

	void Update();
	void Render(D3D11_Pipeline* pipeline);

protected:
	virtual void Move() abstract;

protected:
	// IA
	D3D11_VertexBuffer* vertex_buffer = nullptr;
	D3D11_InputLayout* input_layout = nullptr;
	D3D11_IndexBuffer* index_buffer = nullptr;
	
	// VS
	D3D11_Shader* vertex_shader = nullptr;
	
	// RS
	//D3D11_RasterizerState* rasterizer_state = nullptr;
	
	// PS
	D3D11_Shader* pixel_shader = nullptr;
	D3D11_ConstantBuffer* gpu_buffer = nullptr;
	D3D11_Texture* texture = nullptr;
	//D3D11_SamplerState* sampler_state = nullptr;
	
	// OM
	//D3D11_BlendState* blend_state = nullptr;

	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 scale = D3DXVECTOR3(100, 100, 1);

	D3DXMATRIX world;
};