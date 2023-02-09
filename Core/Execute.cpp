#include "stdafx.h"
#include "Execute.h"
#include "Graphics.h"

#include "Scene/Actor.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/MeshRendererComponent.h"
#include "Scene/Components/MoveScriptComponent.h"
#include "Scene/Components/AIScriptComponent.h"
#include "Scene/Components/ChaseAIScriptComponent.h"

Execute::Execute()
{
	Graphics::Get().Initialize();
	Graphics::Get().CreateBackBuffer
	(
		static_cast<uint>(Settings::Get().GetWidth()),
		static_cast<uint>(Settings::Get().GetHeight())
	);

	//=======================================================
	// [Actors]
	//=======================================================
	// Camera Actor
	std::shared_ptr<Actor> camera = CreateActor();
	camera->AddComponent<CameraComponent>();
	camera->SetName("MainCamera");

	// Player Actor
	std::shared_ptr<Actor> player = CreateActor();
	player->AddComponent<MeshRendererComponent>();
	player->AddComponent<MoveScriptComponent>();
	player->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(100.f, 100.f, 1.f));
	player->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(+100.f, 0.f, 0.f));
	player->SetName("Player");	

	// Monster Actor
	std::shared_ptr<Actor> monster = CreateActor();
	monster->AddComponent<MeshRendererComponent>();
	//monster->AddComponent<AIScriptComponent>();
	monster->AddComponent<ChaseAIScriptComponent>();
	monster->GetComponent<ChaseAIScriptComponent>()->SetTarget(player);
	monster->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(100.f, 100.f, 1.f));
	monster->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-100.f, 0.f, 0.f));
	monster->SetName("Monster");

	//=======================================================
	// [Pipeline]
	//=======================================================
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

const std::shared_ptr<class Actor> Execute::CreateActor(const bool& is_active)
{
	std::shared_ptr<class Actor> actor = std::make_shared<Actor>();
	actor->SetActive(is_active);
	AddActor(actor);

	return actor;
}

void Execute::AddActor(const std::shared_ptr<class Actor>& actor)
{
	actors.emplace_back(actor);
}
