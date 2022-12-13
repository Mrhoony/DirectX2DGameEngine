#include "D3D11_Geometry.h"

template<typename T>
inline D3D11_Geometry<T>::~D3D11_Geometry()
{
	Clear();
}

template<typename T>
inline const std::vector<T> D3D11_Geometry<T>::GetVertices(const uint& offset, const uint& count)
{
	std::vector<T> sub_vertices;

	auto first = vertices.begin() + offset;
	auto last = first + count;
	sub_vertices.assign(first, last);

	return sub_vertices;
}

template<typename T>
inline void D3D11_Geometry<T>::AddVertex(const T& vertex)
{
	vertices.emplace_back(vertex);
}

template<typename T>
inline void D3D11_Geometry<T>::AddVertices(const std::vector<T>& vertices)
{
	this->vertices.insert(
		this->vertices.end(),
		vertices.begin(),
		vertices.end()
	);
}

template<typename T>
inline void D3D11_Geometry<T>::SetVertices(const std::vector<T>& vertices)
{
	this->vertices.clear();
	this->vertices.shrink_to_fit();
	this->vertices = vertices;
}

template<typename T>
inline const std::vector<uint> D3D11_Geometry<T>::GetIndices(const uint& offset, const uint& count)
{
	std::vector<uint> sub_indices;

	auto first = indices.begin() + offset;
	auto last = first + count;
	sub_indices.assign(first, last);

	return sub_indices;
}

template<typename T>
inline void D3D11_Geometry<T>::AddIndex(const uint& index)
{
	indices.emplace_back(index);
}

template<typename T>
inline void D3D11_Geometry<T>::AddIndices(const std::vector<uint>& indices)
{
	this->indices.insert(
		this->indices.end(),
		indices.begin(),
		indices.end()
	);
}

template<typename T>
inline void D3D11_Geometry<T>::SetIndices(const std::vector<uint>& indices)
{
	this->indices.clear();
	this->indices.shrink_to_fit();
	this->indices = indices;
}

template<typename T>
inline void D3D11_Geometry<T>::Clear()
{
	this->vertices.clear();
	this->vertices.shrink_to_fit();

	this->indices.clear();
	this->indices.shrink_to_fit();
}
