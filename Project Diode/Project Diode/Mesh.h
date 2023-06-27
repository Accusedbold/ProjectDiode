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
#ifndef _Mesh
#define _Mesh

struct Model; // forward Declaration

struct Mesh {
  // The Textures used in drawing the mesh
  std::shared_ptr<Resource> m_Textures;
  // the vertex shader used
  std::shared_ptr<Shader> m_VShader;
  // the Tesselation Shader used
  std::shared_ptr<Shader> m_TShader;
  // The Geometry Shader used
  std::shared_ptr<Shader> m_GShader;
  // The Fragment Shader used
  std::shared_ptr<Shader> m_FShader;
  // The Indicies of the points to create the geometry
  std::vector<size_t> m_PosIndicies;
  // The position of the verticies
  std::vector<glm::vec4> m_Positions;
  // The Indicies of the normals
  std::vector<size_t> m_NormIndicies;
  // The normals of the verticies
  std::vector<glm::vec4> m_Normals;
  // The Indicies of the BiTangents
  std::vector<size_t> m_BiIndicies;
  // The Bi-Tangets of the verticies
  std::vector<glm::vec4> m_BiTangents;
  // The Indicies of the Colors
  std::vector<size_t> m_ColorIndicies;
  // The Color of the verticies
  std::vector<glm::vec3> m_Colors;
  // The Indicies of the Texture Coordinates
  std::vector<size_t> m_UVIndicies;
  // The Texture Coordinates of the Mesh
  std::vector<glm::ivec2> m_UVs;
  // The Indicies of the weight
  std::vector<size_t> m_WeightIndicies;
  // The Physical Weight of the points
  std::vector<float> m_Weights;
  // The Indicies of the Skeletal Weight
  std::vector<size_t> m_AnimWeightIndicies;
  // The skeletal weight of the points
  std::vector<std::vector<float>> m_SkeletalWeight;
  // The owner of the Mesh
  std::shared_ptr<Model> m_Owner;
};

#endif