#pragma once
#include <list>
#include <filament/Engine.h>
#include <filament/RenderableManager.h>

using namespace utils;
using namespace std;
using namespace filament;


class Renderable {
private:
	list<int> vertex_indices;
	list<math::float3> vertex;
	list<int> normals_indices;
	list<math::float3> normals;
	list<int> texture_indices;
	list<math::float2> texture;
	Material* material;

public:
	Renderable() {
		vertex_indices = list<int>();
		vertex = list<math::float3>();
		normals_indices = list<int>();
		normals = list<math::float3>();
		texture_indices = list<int>();
		texture = list<math::float2>();
	}

	void addVertexIndices(int i);
	void addVertex(math::float3 v);
	void addNormalsIndices(int i);
	void addNormal(math::float3 n);
	void addTextureIndices(int i);
	void addTexture(math::float2 t);
	void print();
};