/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Material.h
  \author  John Salguero
  \date    June 28, 2023
  \brief
    This header file declares the Material class, which is a
    resource that contains values that tell the gpu how to process
    faces
*/
/********************************************************************/
#ifndef Material_H
#define Material_H

#include "Resource.h" // ResourceID
#define TRANSPARENCY_MAP_FLAG 0b100000000000L
#define TRANSPARENCY_FLAG 0b100000000000000000000000000000uL
#define ANIMATION_FLAG 0b1000000000000000000000000000000uL
#define PHONG_FLAG 0b10000000000000000000000000000000uL
#define UNUSED_FLAGS ~0uL

struct Texture;

using ShaderFlags = unsigned long;

enum class MaterialType {
  Surface,
  Phong,
  Anisotropic,
  Blinn_Phong,
  Lambert,
  PhongE,
  Count
};

enum class MapType {
  Diffuse,
  Emissive,
  EmissiveFactor,
  Ambient,
  AmbientFactor,
  DiffuseFactor,
  Specular,
  Normal,
  SpecularFactor,
  Shininess,
  Bump,
  Transparency,
  TransparencyFactor,
  Reflection,
  ReflectionFactor,
  Displacement,
  DisplacementVector,
  Count
};

struct Material : public Resource
{
  Material(std::wstring const& name, ResourceID id);

  ShaderFlags GetMaterialFlags() const;

  virtual ~Material() = default;

  // The Ambient clolor
  glm::vec3 m_Ambient;
  // The Diffuse Color
  glm::vec3 m_Diffuse;
  // The specular color
  glm::vec3 m_Specular;
  // the emmissive color
  glm::vec3 m_Emissive;
  // Transparency
  float m_Transparency;
  // Shininess
  float m_Shininess;
  // Reflectivity
  float m_Reflectivity;

  // Textures used for mapping
  std::shared_ptr<Texture> m_MappingTextures[static_cast<size_t>(MapType::Count)];

  // The Type of the shader
  MaterialType m_Type;
};

struct MaterialBuffer
{
  // Default Constructor
  MaterialBuffer() = default;
  // Conversion Constructor
  MaterialBuffer(Material const&);
  // The Ambient clolor
  alignas(16) glm::vec3 m_Ambient;
  // The Diffuse Color
  alignas(16) glm::vec3 m_Diffuse;
  // The specular color
  alignas(16) glm::vec3 m_Specular;
  // the emmissive color
  alignas(16) glm::vec3 m_Emissive;
  // Transparency
  float m_Transparency;
  // Shininess
  float m_Shininess;
  // Reflectivity
  float m_Reflectivity;
};

#endif