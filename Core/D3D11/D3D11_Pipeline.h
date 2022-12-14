#pragma once

struct D3D11_PipelineState final
{
	// IA
	//D3D11_VertexBuffer* vertex_buffer = nullptr;
	D3D11_InputLayout* input_layout = nullptr;
	//D3D11_IndexBuffer* index_buffer = nullptr;
	D3D11_PRIMITIVE_TOPOLOGY primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// VS
	D3D11_Shader* vertex_shader = nullptr;

	// RS
	D3D11_RasterizerState* rasterizer_state = nullptr;

	// PS
	D3D11_Shader* pixel_shader = nullptr;

	//D3D11_ConstantBuffer* gpu_buffer = nullptr;
	//D3D11_Texture* texture = nullptr;
	//D3D11_SamplerState* sampler_state = nullptr;

	// OM
	D3D11_BlendState* blend_state = nullptr;
};

class D3D11_Pipeline final : public Object
{
public:
	D3D11_Pipeline(class Graphics* graphics);
	~D3D11_Pipeline();

	bool Begin(const D3D11_PipelineState& pipeline_state);
	void End();

	void SetVertexBuffer(const class D3D11_VertexBuffer* buffer);
	void SetIndexBuffer(const class D3D11_IndexBuffer* buffer);

	void SetConstantBuffer(const uint& slot, const uint& scope, const D3D11_ConstantBuffer* buffer);
	void SetShaderResource(const uint& slot, const uint& scope, const D3D11_Texture* resource);
	void SetSamplerState(const uint& slot, const uint& scope, const D3D11_SamplerState* state);

	void Draw();
	void DrawIndexed(const uint& index_count, const uint& index_offset = 0, const uint& vertex_offset = 0);

private:
	ID3D11DeviceContext* device_context = nullptr;
};

