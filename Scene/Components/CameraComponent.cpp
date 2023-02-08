#include "stdafx.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

CameraComponent::CameraComponent(Actor* const actor, TransformComponent* const transform)
	: IComponent(actor, transform)
{
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void CameraComponent::Initialize()
{
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void CameraComponent::Update()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void CameraComponent::Destroy()
{
}

void CameraComponent::UpdateConstantBuffer()
{
	if (gpu_buffer == nullptr)
	{
		gpu_buffer == std::make_shared<D3D11_ConstantBuffer>(&Graphics::Get());
		gpu_buffer->Create<CAMERA_DATA>();
	}

	CAMERA_DATA* gpu_data = gpu_buffer->Map<CAMERA_DATA>();
	{
		D3DXMatrixTranspose(&gpu_data->view, &view);
		D3DXMatrixTranspose(&gpu_data->projection, &projection);
	}
	gpu_buffer->Unmap();
}

void CameraComponent::UpdateViewMatrix()
{
	D3DXVECTOR3 position = transform->GetPosition();
	D3DXVECTOR3 forward = transform->GetForward() + position;
	D3DXVECTOR3 up = transform->GetUp();

	D3DXMatrixLookAtLH(&view, &position, &forward, &up);
}

void CameraComponent::UpdateProjectionMatrix()
{
	D3DXMatrixOrthoLH(&projection, Settings::Get().GetWidth(), Settings::Get().GetHeight(), 0, 1);
}
