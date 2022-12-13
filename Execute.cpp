#include "stdafx.h"
#include "Execute.h"
#include "Graphics.h"

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
		vertex_shader->Create(ShaderScope_VS, "Texture.hlsl");
	}

	// Pixel Shader
	{
		pixel_shader = new D3D11_Shader(graphics);
		pixel_shader->Create(ShaderScope_PS, "Texture.hlsl");
	}

	// InputLayout
	{
		input_layout = new D3D11_InputLayout(graphics);
		input_layout->Create(D3D11_VertexTexture::descs, D3D11_VertexTexture::count, vertex_shader->GetShaderBlob());
	}

	// Create World View Projection
	{
		D3DXMatrixIdentity(&world);
		D3DXMatrixIdentity(&view);
		D3DXMatrixIdentity(&projection);

		D3DXVECTOR3 eye(0, 0, 0);
		D3DXVECTOR3 at(0, 0, 1);
		D3DXVECTOR3 up(0, 1, 0);
		D3DXMatrixLookAtLH(&view, &eye, &at, &up);

		D3DXMatrixOrthoLH(&projection, Settings::Get().GetWidth(), Settings::Get().GetHeight(), 0, 1);

		std::cout << "View Matrix" << std::endl;
		std::cout << view._11 << " " << view._12 << " " << view._13 << " " << view._14 << std::endl;
		std::cout << view._21 << " " << view._22 << " " << view._23 << " " << view._24 << std::endl;
		std::cout << view._31 << " " << view._32 << " " << view._33 << " " << view._34 << std::endl;
		std::cout << view._41 << " " << view._42 << " " << view._43 << " " << view._44 << std::endl;

		std::cout << std::endl;

		D3DXMATRIX S;
		D3DXMatrixScaling(&S, 500, 500, 1);

		std::cout << "Scale Matrix" << std::endl;
		std::cout << S._11 << " " << S._12 << " " << S._13 << " " << S._14 << std::endl;
		std::cout << S._21 << " " << S._22 << " " << S._23 << " " << S._24 << std::endl;
		std::cout << S._31 << " " << S._32 << " " << S._33 << " " << S._34 << std::endl;
		std::cout << S._41 << " " << S._42 << " " << S._43 << " " << S._44 << std::endl;

		D3DXMATRIX T;
		D3DXMatrixTranslation(&T, 0, 0, 0);

		std::cout << "Translation Matrix" << std::endl;
		std::cout << T._11 << " " << T._12 << " " << T._13 << " " << T._14 << std::endl;
		std::cout << T._21 << " " << T._22 << " " << T._23 << " " << T._24 << std::endl;
		std::cout << T._31 << " " << T._32 << " " << T._33 << " " << T._34 << std::endl;
		std::cout << T._41 << " " << T._42 << " " << T._43 << " " << T._44 << std::endl;

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
		texture->Create("pikachu.png");
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
		D3DXMatrixTranspose(&buffer->view, &view);
		D3DXMatrixTranspose(&buffer->projection, &projection);
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