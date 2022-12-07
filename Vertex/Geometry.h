#pragma once

#include "stdafx.h"

template<typename T>
class Geometry
{
public:
	Geometry() = default;
	virtual ~Geometry();

	// [Vertex]
	const uint GetVertexCount() const { return static_cast<uint>(vertices.size()); }
	const uint GetVertexByteWidth() const { return GetVertexCount() * sizeof(T); }
	const T* GetVertexPointer() const { return vertices.data(); }
	const std::vector<T>& GetVertices() const { return vertices; }
	const std::vector<T> GetVertices(const uint& offset, const uint& count);

	void AddVertex(const T& vertex);
	void AddVertices(const std::vector<T>& vertices);
	void SetVertices(const std::vector<T>& vertices);

	// [Index]
	const uint GetIndexCount() const { return static_cast<uint>(indices.size()); }
	const uint GetIndexByteWidth() const { return GetIndexCount() * sizeof(uint); }
	const uint* GetIndexPointer() const { return indices.data(); }
	const std::vector<uint>& GetIndices() const { return indices; }
	const std::vector<uint> GetIndices(const uint& offset, const uint& count);

	void AddIndex(const uint& index);
	void AddIndices(const std::vector<uint>& indices);
	void SetIndices(const std::vector<uint>& indices);

	// [MISC]
	void Clear();

private:
	std::vector<T> vertices;
	std::vector<uint> indices;
};

#include "Geometry.inl"