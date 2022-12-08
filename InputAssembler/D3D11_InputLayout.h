#pragma once
class D3D11_InputLayout
{
public:
	D3D11_InputLayout(class Graphics* graphics);
	~D3D11_InputLayout();

	ID3D11InputLayout* GetResource() { return input_layout; }

	void Create(D3D11_INPUT_ELEMENT_DESC* desc, const uint& count, ID3DBlob* blob);
	void Clear();

private:
	ID3D11Device* device = nullptr;
	ID3D11InputLayout* input_layout = nullptr;
};

