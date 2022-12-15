#include "stdafx.h"
#include "Execute.h"
#include "Graphics.h"

#include "Scene/Camera.h"

Execute::Execute()
{
	graphics = new Graphics();
	graphics->Initialize();
	graphics->CreateBackBuffer
	(
		static_cast<uint>(Settings::Get().GetWidth()),
		static_cast<uint>(Settings::Get().GetHeight())
	);

	// Geometry
	D3D11_Geometry<D3D11_VertexTexture> geometry;
	Geometry_Generator::CreateQuad(geometry);

	// Vertex Buffer
	{
		vertex_buffer = new D3D11_VertexBuffer(graphics);
		vertex_buffer->Create(geometry.GetVertices());
	}

	// Index Buffer
	{
		index_buffer = new D3D11_IndexBuffer(graphics);
		index_buffer->Create(geometry.GetIndices());
	}

	// Vertex Shader
	{
		vertex_shader = new D3D11_Shader(graphics);
		vertex_shader->Create(ShaderScope_VS, "Assets/Shaders/Texture.hlsl");
	}

	// Pixel Shader
	{
		pixel_shader = new D3D11_Shader(graphics);
		pixel_shader->Create(ShaderScope_PS, "Assets/Shaders/Texture.hlsl");
	}

	// InputLayout
	{
		input_layout = new D3D11_InputLayout(graphics);
		input_layout->Create(D3D11_VertexTexture::descs, D3D11_VertexTexture::count, vertex_shader->GetShaderBlob());
	}

	// Create Camera
	{
		camera = new Camera();

		D3DXMatrixIdentity(&world);

		D3DXMATRIX S;
		D3DXMatrixScaling(&S, 500, 500, 1);

		D3DXMATRIX T;
		D3DXMatrixTranslation(&T, 0, 0, 0);

		D3DXMATRIX R;
		D3DXMatrixRotationZ(&R, static_cast<float>(D3DXToRadian(45)));

		world = S * T;
	}

	//Create Constant Buffer
	{
		gpu_buffer = new D3D11_ConstantBuffer(graphics);
		gpu_buffer->Create<TRANSFORM_DATA>();
	}

	// Create Rasterizer State
	{
		rasterizer_state = new D3D11_RasterizerState(graphics);
		rasterizer_state->Create(D3D11_CULL_BACK, D3D11_FILL_SOLID);
	}

	// Create Texture (Shader Resource View)
	{
		texture = new D3D11_Texture(graphics);
		texture->Create("Assets/Textures/pikachu.png");
	}

	// Create Sampler State
	{
		sampler_state = new D3D11_SamplerState(graphics);
		sampler_state->Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
	}

	// Create Blend State
	{
		blend_state = new D3D11_BlendState(graphics);
		blend_state->Create(true);
	}

	// Pipeline
	pipeline = new D3D11_Pipeline(graphics);
}

Execute::~Execute()
{
	SAFE_DELETE(pipeline);
	SAFE_DELETE(camera);
	SAFE_DELETE(blend_state);
	SAFE_DELETE(sampler_state);
	SAFE_DELETE(texture);
	SAFE_DELETE(rasterizer_state);
	SAFE_DELETE(gpu_buffer);
	SAFE_DELETE(pixel_shader);
	SAFE_DELETE(input_layout);
	SAFE_DELETE(vertex_shader);
	SAFE_DELETE(index_buffer);
	SAFE_DELETE(vertex_buffer);
	SAFE_DELETE(graphics);
}

void Execute::Update()
{
	TRANSFORM_DATA* buffer = gpu_buffer->Map<TRANSFORM_DATA>();
	{
		D3DXMatrixTranspose(&buffer->world, &world);
		D3DXMatrixTranspose(&buffer->view, &camera->GetViewMatrix());
		D3DXMatrixTranspose(&buffer->projection, &camera->GetProjectionMatrix());
	}
	gpu_buffer->Unmap();
}

void Execute::Render()
{
	graphics->Begin();
	{
		D3D11_PipelineState pipeline_state;
		pipeline_state.input_layout = input_layout;
		pipeline_state.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		pipeline_state.vertex_shader = vertex_shader;
		pipeline_state.pixel_shader = pixel_shader;
		pipeline_state.rasterizer_state = rasterizer_state;
		pipeline_state.blend_state = blend_state;
		if (pipeline->Begin(pipeline_state))
		{
			pipeline->SetVertexBuffer(vertex_buffer);
			pipeline->SetIndexBuffer(index_buffer);
			pipeline->SetConstantBuffer(0, ShaderScope_VS, gpu_buffer);
			pipeline->SetShaderResource(0, ShaderScope_PS, texture);
			pipeline->SetSamplerState(0, ShaderScope_PS, sampler_state);

			pipeline->DrawIndexed(index_buffer->GetCount(), index_buffer->GetOffset(), vertex_buffer->GetOffset());

			pipeline->End();
		}
	}
	graphics->End();
}