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

	// Vertex Data
	{
		geometry.AddVertex(D3D11_VertexTexture(D3DXVECTOR3(-0.5f, -0.5f, 0.0f), D3DXVECTOR2(0.0f, 1.0f)));
		geometry.AddVertex(D3D11_VertexTexture(D3DXVECTOR3(-0.5f, +0.5f, 0.0f), D3DXVECTOR2(0.0f, 0.0f)));
		geometry.AddVertex(D3D11_VertexTexture(D3DXVECTOR3(+0.5f, -0.5f, 0.0f), D3DXVECTOR2(1.0f, 1.0f)));
		geometry.AddVertex(D3D11_VertexTexture(D3DXVECTOR3(+0.5f, +0.5f, 0.0f), D3DXVECTOR2(1.0f, 0.0f)));
	}

	// Index Data
	{
		geometry.AddIndex(0); geometry.AddIndex(1); geometry.AddIndex(2);
		geometry.AddIndex(2); geometry.AddIndex(1); geometry.AddIndex(3);
	}	

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
}

Execute::~Execute()
{
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
		// IA
		ID3D11Buffer* buffers[] = { vertex_buffer->GetResource() };
		graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, buffers, &vertex_buffer->GetStride(), &vertex_buffer->GetOffset());
		graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		graphics->GetDeviceContext()->IASetInputLayout(input_layout->GetResource());
		graphics->GetDeviceContext()->IASetIndexBuffer(index_buffer->GetResource(), DXGI_FORMAT_R32_UINT, index_buffer->GetOffset());

		// VS
		graphics->GetDeviceContext()->VSSetShader(static_cast<ID3D11VertexShader*>(vertex_shader->GetResource()), nullptr, 0);
		
		ID3D11Buffer* cpu_buffers[] = { gpu_buffer->GetResource() };
		graphics->GetDeviceContext()->VSSetConstantBuffers(0, 1, cpu_buffers);

		// RS
		graphics->GetDeviceContext()->RSSetState(rasterizer_state->GetResource());

		// PS
		graphics->GetDeviceContext()->PSSetShader(static_cast<ID3D11PixelShader*>(pixel_shader->GetResource()), nullptr, 0);
		ID3D11ShaderResourceView* shader_resource[] = { texture->GetResource() };
		graphics->GetDeviceContext()->PSSetShaderResources(0, 1, shader_resource);
		ID3D11SamplerState* samplers[] = { sampler_state->GetResource() };
		graphics->GetDeviceContext()->PSSetSamplers(0, 1, samplers);

		// OM
		float factor = blend_state->GetBlendFactor();
		float blend_factor[] = { factor, factor, factor, factor };
		graphics->GetDeviceContext()->OMSetBlendState(blend_state->GetResource(), blend_factor, blend_state->GetSampleMask());

		// Draw Call
		graphics->GetDeviceContext()->DrawIndexed(6, 0, 0);
	}
	graphics->End();
}