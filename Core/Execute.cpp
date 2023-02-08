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

	pipeline = std::make_shared<D3D11_Pipeline>(&Graphics::Get());
}

Execute::~Execute()
{
	actors.clear();
	actors.shrink_to_fit();
}

void Execute::Update()
{
	for (const auto& actor : actors)
		actor->Update();
}

void Execute::Render()
{
	Graphics::Get().Begin();
	{
		for (const auto& actor : actors)
		{
			if (auto camera = actor->GetComponent<CameraComponent>())
			{
				camera->UpdateConstantBuffer();
				pipeline->SetConstantBuffer(0, ShaderScope_VS, camera->GetConstantBuffer().get());
			}

			actor->Render(pipeline.get());
		}
	}
	Graphics::Get().End();
}