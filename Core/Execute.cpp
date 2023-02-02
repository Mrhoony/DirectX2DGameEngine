#include "stdafx.h"
#include "Execute.h"
#include "Graphics.h"

#include "Scene/Actor.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/MeshRendererComponent.h"

Execute::Execute()
{
	Graphics::Get().Initialize();
	Graphics::Get().CreateBackBuffer
	(
		static_cast<uint>(Settings::Get().GetWidth()),
		static_cast<uint>(Settings::Get().GetHeight())
	);

	// Create Camera
	{
		camera_buffer = new D3D11_ConstantBuffer(Graphics::Get());
		camera_buffer->Create<CAMERA_DATA>();
	}

	// Pipeline
	{
		pipeline = new D3D11_Pipeline(Graphics::Get());
	}	
}

Execute::~Execute()
{
	SAFE_DELETE(pipeline);
	SAFE_DELETE(camera_buffer);
}

void Execute::Update()
{
	for (const auto& actor : actors)
		actor->Update();

	CAMERA_DATA* buffer = camera_buffer->Map<CAMERA_DATA>();
	{
		D3DXMatrixTranspose(&buffer->view, &camera->GetViewMatrix());
		D3DXMatrixTranspose(&buffer->projection, &camera->GetProjectionMatrix());
	}
	camera_buffer->Unmap();
}

void Execute::Render()
{
	Graphics::Get().Begin();
	{
		pipeline->SetConstantBuffer(0, ShaderScope_VS, camera_buffer);

		for (const auto& actor : actors)
			actor->Render(pipeline);
	}
	Graphics::Get().End();
}