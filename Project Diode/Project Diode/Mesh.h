/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Mesh.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file declares the Mesh class, which is a
    resource that contains everything needed to draw by 
    the OpenGL Device

*/
/********************************************************************/
#ifndef Mesh_H
#define Mesh_H

#define MAX_BONE_INFLUENCE 4
#define MAX_MATERIALS 10

struct Model; // forward Declaration
struct Material;
struct QuaternionTransform;

struct Mesh {
  // Generates the data buffer
  void GenerateDataBuffer();
  // Generates the data buffer
  void ReleaseDataBuffer();
  // Frees up the memory
  ~Mesh();

  // determines which face uses which material
  std::vector<GLushort> m_MaterialIndices;
  // The Textures used in drawing the mesh
  std::vector<std::shared_ptr<Material>> m_Materials;
  // The Indicies of the points to create the geometry
  std::vector<GLuint> m_Indices;
  // The position of the verticies
  std::vector<glm::vec4> m_Positions;
  // The normals of the verticies
  std::vector<glm::vec4> m_Normals;
  // The Bi-Tangets of the verticies
  std::vector<glm::vec4> m_Tangents;
  // The Texture Coordinates of the Mesh
  std::vector<glm::vec2> m_UVs;
  // The Physical Weight of the points
  std::vector<float> m_Weights;
  // The indicies of the joints associated with the weights
  std::vector<std::vector<GLushort>> m_SkeletalIndices;
  // The skeletal weight of the points
  std::vector<std::vector<float>> m_SkeletalWeights;
  // Whether the mesh is transparent
  bool m_IsTransparent;
  // The current flags of the mesh
  ShaderFlags m_flags;
  // The owner of the Mesh
  std::weak_ptr<Model> m_Owner;
  // All the vertex data packed into contiguous memory
  char* m_Data = nullptr;
  // All the index data packed into contiguous memory
  char* m_IndexData = nullptr;
  // The VAO OpenGL will use to draw the mesh
  GLuint m_VAO[1] = { 0 };
  // The EBO OpenGL will use to draw the mesh
  GLuint m_EBO[1] = { 0 };
  // The VBO OpenGL will use to draw the mesh
  GLuint m_VBO[1] = { 0 };
};

#endif