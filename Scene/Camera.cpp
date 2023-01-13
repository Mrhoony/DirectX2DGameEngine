#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void Camera::Update()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void Camera::UpdateViewMatrix()
{
	D3DXVECTOR3 at = D3DXVECTOR3(0, 0, 1) + position;
	D3DXVECTOR3 up(0, 1, 0);

	D3DXMatrixLookAtLH(&view, &position, &at, &up);
}

void Camera::UpdateProjectionMatrix()
{
	D3DXMatrixOrthoLH(&projection, Settings::Get().GetWidth(), Settings::Get().GetHeight(), 0, 1);
}
