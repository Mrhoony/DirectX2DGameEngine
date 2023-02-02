#pragma once
#include "IComponent.h"

struct TRANSFORM_DATA
{
	D3DXMATRIX world;
};

class TransformComponent final : public IComponent
{
public:
	TransformComponent(class Actor* actor, class TransformComponent* transform);

	void Initialize() override;
	void Update() override;
	void Destroy() override;

	//=======================================================
	// [Local]
	//=======================================================
	const D3DXVECTOR3& GetLocalScale() const { return local_scale; }
	void SetLocalScale(const D3DXVECTOR3& scale);

	const D3DXVECTOR3& GetLocalRotation() const { return local_rotation; }
	void SetLocalRotation(const D3DXVECTOR3& rotation);

	const D3DXVECTOR3& GetLocalPosition() const { return local_position; }
	void SetLocalPosition(const D3DXVECTOR3& position);

	const D3DXMATRIX& GetLocalMatrix() const { return local; }

	//=======================================================
	// [World]
	//=======================================================
	const D3DXVECTOR3 GetScale();
	void SetScale(const D3DXVECTOR3& world_scale);
	
	const D3DXVECTOR3 GetRotation();
	void SetRotation(const D3DXVECTOR3& world_rotation);

	const D3DXVECTOR3 GetPosition();
	void SetPosition(const D3DXVECTOR3& world_position);

	const D3DXMATRIX GetWorldRotationMatrix();
	const D3DXMATRIX& GetWorldMatrix() const { return world; }

	const D3DXVECTOR3 GetRight() const;
	const D3DXVECTOR3 GetUp() const;
	const D3DXVECTOR3 GetForward() const;

	//=======================================================
	// [Transform]
	//=======================================================
	void UpdateTransform();
	bool HasParent() const { return parent ? true : false; }
	bool HasChilds() const { return childs.empty() != true; }

	TransformComponent* const GetRoot() { return HasParent() == true ? parent->GetRoot() : this; }
	TransformComponent* const GetParent() { return parent; }
	void SetParent(TransformComponent* const new_parent);

	const std::vector<TransformComponent*>& GetChilds() const { return childs; }
	TransformComponent* const GetChildFromIndex(const uint& index);

	uint GetChildCount() const { return static_cast<uint>(childs.size()); }
	void AddChild(TransformComponent* const child);

	std::shared_ptr<class D3D11_ConstantBuffer> GetConstantBuffer() const { return gpu_buffer; }
	void UpdateConstantBuffer();

private:
	D3DXVECTOR3 local_scale = D3DXVECTOR3(1, 1, 1);
	D3DXVECTOR3 local_rotation = D3DXVECTOR3(1, 1, 1);
	D3DXVECTOR3 local_position = D3DXVECTOR3(1, 1, 1);

	D3DXMATRIX local;
	D3DXMATRIX world;

	TransformComponent* parent = nullptr;
	std::vector<TransformComponent*> childs;

	std::shared_ptr<class D3D11_ConstantBuffer> gpu_buffer;
};

