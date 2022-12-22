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

	rect->Update
	(
		[](D3DXVECTOR3& position)
		{
			if (GetAsyncKeyState('W') & 0x8000) position.y++;
			else if (GetAsyncKeyState('A') & 0x8000) position.x--;
			if (GetAsyncKeyState('S') & 0x8000) position.y--;
			else if (GetAsyncKeyState('D') & 0x8000) position.x++;
		}
	);
	rect2->Update
	(
		[](D3DXVECTOR3& position)
		{
			static Direction dir = Direction::Right;

			static std::random_device rd;
			static std::mt19937 mt(rd());
			static std::uniform_int_distribution<int> rand(0, 3);

			static std::chrono::system_clock::time_point cur_time = std::chrono::system_clock::now();
			static std::chrono::system_clock::time_point check_time = std::chrono::system_clock::now();

			cur_time = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> work_time = cur_time - check_time;

			switch (dir)
			{
			case Direction::Up: position.y++;			break;
			case Direction::Right: position.x++;		break;
			case Direction::Down: position.y--;			break;
			case Direction::Left: position.y++;			break;
			}

			if (work_time.count() >= 1000.0)
			{
				Direction new_dir = static_cast<Direction>(rand(mt));

				if (new_dir == dir)
				{
					int dir_num = static_cast<int>(dir);

					dir_num = (dir_num <= 1) ? dir_num + 2 : dir_num - 2;

					dir = static_cast<Direction>(dir_num);
				}
				else
					dir = new_dir;

				check_time = std::chrono::system_clock::now();
			}
		}
	);
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