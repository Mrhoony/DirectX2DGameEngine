#include "stdafx.h"
#include "Execute.h"
#include "Graphics.h"

#include "Scene/Camera.h"
#include "Scene/Rendering/Rect.h"

Execute::Execute()
{
	graphics = new Graphics();
	graphics->Initialize();
	graphics->CreateBackBuffer
	(
		static_cast<uint>(Settings::Get().GetWidth()),
		static_cast<uint>(Settings::Get().GetHeight())
	);

	// Create Camera
	{
		camera = new Camera();
		camera_buffer = new D3D11_ConstantBuffer(graphics);
		camera_buffer->Create<CAMERA_DATA>();
	}

	// Pipeline
	{
		pipeline = new D3D11_Pipeline(graphics);
	}

	// Rect
	rect = new Rect(graphics, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	rect->SetPosition(D3DXVECTOR3(100, 0, 0));

	rect2 = new Rect(graphics, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	rect2->SetPosition(D3DXVECTOR3(-100, 0, 0));
	rect2->SetScale(D3DXVECTOR3(100, 300, 1));
}

Execute::~Execute()
{
	SAFE_DELETE(rect2);
	SAFE_DELETE(rect);
	SAFE_DELETE(pipeline);
	SAFE_DELETE(camera_buffer);
	SAFE_DELETE(camera);	
	SAFE_DELETE(graphics);
}

void Execute::Update()
{
	camera->Update();

	CAMERA_DATA* buffer = camera_buffer->Map<CAMERA_DATA>();
	{
		D3DXMatrixTranspose(&buffer->view, &camera->GetViewMatrix());
		D3DXMatrixTranspose(&buffer->projection, &camera->GetProjectionMatrix());
	}
	camera_buffer->Unmap();

	rect->Update();
	rect2->Update();
}

void Execute::Render()
{
	graphics->Begin();
	{
		pipeline->SetConstantBuffer(0, ShaderScope_VS, camera_buffer);

		rect->Render(pipeline);
		rect2->Render(pipeline);
	}
	graphics->End();
}