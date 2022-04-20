#include"Renderable.h"

/// <summary>
/// Add a vetex indice to the corresponding list
/// </summary>
/// <param name="i">The indice to add</param>
void Renderable::addVertexIndices(int i)
{
	vertex_indices.push_back(i);
}

/// <summary>
/// Add a vetex to the corresponding list
/// </summary>
/// <param name="i">The vertex to add</param>
void Renderable::addVertex(math::float3 v)
{
	vertex.push_back(v);
}

/// <summary>
/// Add a normal indice to the corresponding list
/// </summary>
/// <param name="i">The indice to add</param>
void Renderable::addNormalsIndices(int i)
{
	normals_indices.push_back(i);
}

/// <summary>
/// Add a normal to the corresponding list
/// </summary>
/// <param name="i">The normal to add</param>
void Renderable::addNormal(math::float3 n)
{
	normals.push_back(n);
}

/// <summary>
/// Add a texture indice to the corresponding list
/// </summary>
/// <param name="i">The indice to add</param>
void Renderable::addTextureIndices(int i)
{
	texture_indices.push_back(i);
}

/// <summary>
/// Add a texture to the corresponding list
/// </summary>
/// <param name="i">The texture to add</param>
void Renderable::addTexture(math::float2 t)
{
	texture.push_back(t);
}

/// <summary>
/// Print the renderable in the console
/// </summary>
void Renderable::print()
{
	printf("list of vertex :\n");
	for (math::float3 v : vertex) {
		printf("%f %f %f\n", v.x, v.y, v.z);
	}

	printf("\nlist of texture :\n");
	for (math::float2 vt : texture) {
		printf("%f %f \n", vt.x, vt.y);
	}

	printf("\nlist of normals :\n");
	for (math::float3 n : normals) {
		printf("%f %f %f\n", n.x, n.y, n.z);
	}

	printf("\nlist of faces\n");
	auto it_vertex = vertex_indices.begin();
	auto it_texture = texture_indices.begin();
	auto it_normals = normals_indices.begin();
	auto end = vertex_indices.end();
	int i = 0;
	while (it_vertex != end) {
		if (i%3 == 0) printf("f%d ", i/3);
		printf("%d/%d/%d ", *it_vertex++, *it_texture++, *it_normals++);
		if (i%3 == 2) printf("\n");
		i++;
	}
}