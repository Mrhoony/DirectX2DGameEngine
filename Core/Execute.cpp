#include "stdafx.h"
#include "Execute.h"
#include "Graphics.h"

#include "Scene/Camera.h"
#include "Scene/Rendering/Player.h"
#include "Scene/Rendering/Monster.h"

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
	player = new Player(graphics, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	player->SetPosition(D3DXVECTOR3(100, 0, 0));

	monsters.reserve(10);

	for (int i = 0; i < 10; i++)
	{
		D3DXVECTOR3 random_position = D3DXVECTOR3
		(
			Math::Random(-500.0f, 500.0f),
			Math::Random(-300.0f, 300.0f),
			0
		);

		D3DXCOLOR random_color = D3DXCOLOR
		(
			Math::Random(0.0f, 1.0f),
			Math::Random(0.0f, 1.0f),
			Math::Random(0.0f, 1.0f),
			1.0f
		);

		monsters.emplace_back(new Monster(graphics, random_color));
		monsters.back()->SetPosition(random_position);
		//monsters.back()->SetScale(D3DXVECTOR3(100, 100, 1));
	}
}

Execute::~Execute()
{
	for (auto& monster : monsters) SAFE_DELETE(monster);
	SAFE_DELETE(player);
	SAFE_DELETE(pipeline);
	SAFE_DELETE(camera_buffer);
	SAFE_DELETE(camera);	
	SAFE_DELETE(graphics);
}

void Execute::Update()
{
	player->Update();

	camera->SetPosition(player->GetPosition());
	camera->Update();

	for (auto& monster : monsters)
	{
		monster->Update();
		if (Intersect::IsIntersect(player, monster))
		{
			player->Event();
			monster->Event();
		}
	}

	CAMERA_DATA* buffer = camera_buffer->Map<CAMERA_DATA>();
	{
		D3DXMatrixTranspose(&buffer->view, &camera->GetViewMatrix());
		D3DXMatrixTranspose(&buffer->projection, &camera->GetProjectionMatrix());
	}
	camera_buffer->Unmap();
}

void Execute::Render()
{
	graphics->Begin();
	{
		pipeline->SetConstantBuffer(0, ShaderScope_VS, camera_buffer);

		player->Render(pipeline);
		for (auto& monster : monsters)
			monster->Render(pipeline);
	}
	graphics->End();
}