#pragma once

struct TRANSFORM_DATA
{
	D3DXMATRIX world;
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
	class Graphics* graphics = nullptr;

	// IA
	D3D11_Geometry<D3D11_VertexTexture> geometry;
	D3D11_VertexBuffer* vertex_buffer = nullptr;
	ID3D11InputLayout* input_layout = nullptr;
	ID3D11Buffer* index_buffer = nullptr;

	// VS
	ID3D11VertexShader* vertex_shader = nullptr;
	ID3DBlob* vs_blob = nullptr;

	// RS
	ID3D11RasterizerState* rasterizer_state = nullptr;

	// PS
	ID3D11PixelShader* pixel_shader = nullptr;
	ID3DBlob* ps_blob = nullptr;

	TRANSFORM_DATA cpu_buffer;
	ID3D11Buffer* gpu_buffer = nullptr;

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;

	ID3D11ShaderResourceView* shader_resource = nullptr;

	ID3D11SamplerState* sampler_state = nullptr;

	// OM
	ID3D11BlendState* blend_state = nullptr;
};

