#pragma once
class D3D11_IndexBuffer final
{
public:
	D3D11_IndexBuffer(class Graphics* graphics);
	~D3D11_IndexBuffer();

	ID3D11Buffer* GetResource() const { return buffer; }
	const uint& GetStride() const { return stride; }
	const uint& GetOffset() const { return offset; }
	const uint& GetCount() const { return count; }

	void Create(const std::vector<uint>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_IMMUTABLE);
	void Clear();

private:
	ID3D11Device* device = nullptr;
	ID3D11Buffer* buffer = nullptr;
	uint stride = 0;
	uint offset = 0;
	uint count = 0;
};