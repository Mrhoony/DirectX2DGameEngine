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
		vertices = new VertexColor[3];
		vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
		vertices[0].color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		vertices[1].position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);
		vertices[1].color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		vertices[2].position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
		vertices[2].color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	}

	// Vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(VertexColor) * 3;
		
		D3D11_SUBRESOURCE_DATA sub_data;
		ZeroMemory(&sub_data, sizeof(D3D11_SUBRESOURCE_DATA));
		sub_data.pSysMem = vertices;

		HRESULT hr = graphics->GetDevice()->CreateBuffer(&desc, &sub_data, &vertex_buffer);
		assert(SUCCEEDED(hr));
	}

	// Vertex Shader
	{
		HRESULT hr = D3DX11CompileFromFileA
		(
			"Color.hlsl",
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
		D3D11_INPUT_ELEMENT_DESC layout_desc[]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		HRESULT hr = graphics->GetDevice()->CreateInputLayout
		(
			layout_desc,
			2,
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
			"Color.hlsl",
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
}

Execute::~Execute()
{
	SAFE_RELEASE(pixel_shader);
	SAFE_RELEASE(ps_blob);	
	SAFE_RELEASE(input_layout);
	SAFE_RELEASE(vertex_shader);
	SAFE_RELEASE(vs_blob);
	SAFE_RELEASE(vertex_buffer);
	SAFE_DELETE_ARRAY(vertices);
	SAFE_DELETE(graphics);
}

void Execute::Update()
{
}

void Execute::Render()
{
	uint stride = sizeof(VertexColor);
	uint offset = 0;

	graphics->Begin();
	{
		// ·»´õ ½ÃÀÛ

		// IA
		ID3D11Buffer* buffers[] = {
			vertex_buffer
		};
		graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, buffers, &stride, &offset);
		graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		graphics->GetDeviceContext()->IASetInputLayout(input_layout);
		//graphics->GetDeviceContext()->IASetIndexBuffer();

		// VS
		graphics->GetDeviceContext()->VSSetShader(vertex_shader, nullptr, 0);

		// PS
		graphics->GetDeviceContext()->PSSetShader(pixel_shader, nullptr, 0);

		// Draw Call
		graphics->GetDeviceContext()->Draw(3, 0);
	}
	graphics->End();
}
