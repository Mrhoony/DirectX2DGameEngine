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
		HRESULT hr = D3DX11CompileFromFileA
		(
			"Texture.hlsl",
			nullptr,
			nullptr,
			"VS",
			"vs_5_0",
			0,
			0,
			nullptr,
			&vs_blob,
			nullptr,
			nullptr
		);
		assert(SUCCEEDED(hr));

		hr = graphics->GetDevice()->CreateVertexShader
		(
			vs_blob->GetBufferPointer(),
			vs_blob->GetBufferSize(),
			nullptr,
			&vertex_shader
		);
	}

	// InputLayout
	{
		HRESULT hr = graphics->GetDevice()->CreateInputLayout
		(
			D3D11_VertexTexture::descs,
			D3D11_VertexTexture::count,
			vs_blob->GetBufferPointer(),
			vs_blob->GetBufferSize(),
			&input_layout
		);
		assert(SUCCEEDED(hr));
	}

	// Pixel Shader
	{
		HRESULT hr = D3DX11CompileFromFileA
		(
			"Texture.hlsl",
			nullptr,
			nullptr,
			"PS",
			"ps_5_0",
			0,
			0,
			nullptr,
			&ps_blob,
			nullptr,
			nullptr
		);
		assert(SUCCEEDED(hr));

		hr = graphics->GetDevice()->CreatePixelShader
		(
			ps_blob->GetBufferPointer(),
			ps_blob->GetBufferSize(),
			nullptr,
			&pixel_shader
		);
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
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TRANSFORM_DATA);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = graphics->GetDevice()->CreateBuffer(&desc, nullptr, &gpu_buffer);
		assert(SUCCEEDED(hr));
	}

	// Create Rasterizer State
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_BACK;
		desc.FrontCounterClockwise = false;

		HRESULT hr = graphics->GetDevice()->CreateRasterizerState(&desc, &rasterizer_state);
		assert(SUCCEEDED(hr));
	}

	// Create Shader Resource View
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFileA
		(
			graphics->GetDevice(),
			"pikachu.png",
			nullptr,
			nullptr,
			&shader_resource,
			nullptr
		);
		assert(SUCCEEDED(hr));
	}

	// Create Sampler State
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));

		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		desc.BorderColor[0] = 1;
		desc.BorderColor[1] = 0;
		desc.BorderColor[2] = 0;
		desc.BorderColor[3] = 1;

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		desc.MaxAnisotropy = 16;
		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

		desc.MinLOD = std::numeric_limits<float>::min();
		desc.MaxLOD = std::numeric_limits<float>::max();

		desc.MipLODBias = 0.0f;
		HRESULT hr = graphics->GetDevice()->CreateSamplerState
		(
			&desc,
			&sampler_state
		);
		assert(SUCCEEDED(hr));
	}

	// Create Blend State
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));

		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;

		desc.RenderTarget[0].BlendEnable = true;

		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		HRESULT hr = graphics->GetDevice()->CreateBlendState(&desc, &blend_state);
		assert(SUCCEEDED(hr));
	}
}

Execute::~Execute()
{
	SAFE_RELEASE(blend_state);
	SAFE_RELEASE(sampler_state);
	SAFE_RELEASE(shader_resource);
	SAFE_RELEASE(rasterizer_state);
	SAFE_RELEASE(gpu_buffer);

	SAFE_RELEASE(pixel_shader);
	SAFE_RELEASE(ps_blob);

	SAFE_RELEASE(input_layout);

	SAFE_RELEASE(vertex_shader);
	SAFE_RELEASE(vs_blob);

	SAFE_DELETE(index_buffer);

	SAFE_DELETE(vertex_buffer);

	SAFE_DELETE(graphics);
}

void Execute::Update()
{
	D3DXMatrixTranspose(&cpu_buffer.world, &world);
	D3DXMatrixTranspose(&cpu_buffer.view, &view);
	D3DXMatrixTranspose(&cpu_buffer.projection, &projection);

	D3D11_MAPPED_SUBRESOURCE mapped_subresource;

	graphics->GetDeviceContext()->Map
	(
		gpu_buffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mapped_subresource
	);

	memcpy(mapped_subresource.pData, &cpu_buffer, sizeof(TRANSFORM_DATA));

	graphics->GetDeviceContext()->Unmap(gpu_buffer, 0);
}

void Execute::Render()
{
	graphics->Begin();
	{
		// IA
		ID3D11Buffer* buffers[] = {
			vertex_buffer->GetResource()
		};
		graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, buffers, &vertex_buffer->GetStride(), &vertex_buffer->GetOffset());
		graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		graphics->GetDeviceContext()->IASetInputLayout(input_layout);
		graphics->GetDeviceContext()->IASetIndexBuffer(index_buffer->GetResource(), DXGI_FORMAT_R32_UINT, index_buffer->GetOffset());

		// VS
		graphics->GetDeviceContext()->VSSetShader(vertex_shader, nullptr, 0);
		graphics->GetDeviceContext()->VSSetConstantBuffers(0, 1, &gpu_buffer);

		// RS
		graphics->GetDeviceContext()->RSSetState(rasterizer_state);

		// PS
		graphics->GetDeviceContext()->PSSetShader(pixel_shader, nullptr, 0);
		graphics->GetDeviceContext()->PSSetShaderResources(0, 1, &shader_resource);
		graphics->GetDeviceContext()->PSSetSamplers(0, 1, &sampler_state);

		// OM
		graphics->GetDeviceContext()->OMSetBlendState(blend_state, nullptr, 0xffffffff);

		// Draw Call
		graphics->GetDeviceContext()->DrawIndexed(6, 0, 0);
	}
	graphics->End();
}