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

struct Model; // forward Declaration
struct Material;

struct Mesh {
  // Generates the data buffer
  void GenerateDataBuffer();
  // Frees up the memory
  ~Mesh();

  // determines which face uses which material
  std::vector<size_t> m_MaterialIndices;
  // The Textures used in drawing the mesh
  std::vector<std::shared_ptr<Material>> m_Materials;
  // The Indicies of the points to create the geometry
  std::vector<size_t> m_PosIndicies;
  // The position of the verticies
  std::vector<glm::vec4> m_Positions;
  // The Indicies of the normals
  std::vector<size_t> m_NormIndicies;
  // The normals of the verticies
  std::vector<glm::vec4> m_Normals;
  // The Indicies of the BiTangents
  std::vector<size_t> m_TanIndicies;
  // The Bi-Tangets of the verticies
  std::vector<glm::vec4> m_Tangents;
  // The Indicies of the BiTangents
  std::vector<size_t> m_BiIndicies;
  // The Bi-Tangets of the verticies
  std::vector<glm::vec4> m_BiTangents;
  // The Indicies of the Colors
  std::vector<size_t> m_ColorIndicies;
  // The Color of the verticies
  std::vector<glm::vec4> m_Colors;
  // The Indicies of the Texture Coordinates
  std::vector<size_t> m_UVIndicies;
  // The Texture Coordinates of the Mesh
  std::vector<glm::vec2> m_UVs;
  // The Indicies of the weight
  std::vector<size_t> m_WeightIndicies;
  // The Physical Weight of the points
  std::vector<float> m_Weights;
  // The Indicies of the Skeletal Weight
  std::vector<size_t> m_AnimWeightIndicies;
  // The indicies of the joints associated with the weights
  std::vector<std::vector<size_t>> m_SkeletalIndices;
  // The skeletal weight of the points
  std::vector<std::vector<float>> m_SkeletalWeights;
  // Whether the mesh is transparent
  bool m_IsTransparent;
  // The current flags of the mesh
  long m_flags;
  // The owner of the Mesh
  std::weak_ptr<Model> m_Owner;
  // All the vertex data packed into contiguous memory
  char* m_Data = nullptr;
};

#endif