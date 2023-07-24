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
  Diffuse,            // 0
  Emissive,           // 1
  EmissiveFactor,     // 2
  Ambient,            // 3
  AmbientFactor,      // 4
  DiffuseFactor,      // 5
  Specular,           // 6
  Normal,             // 7
  SpecularFactor,     // 8
  Shininess,          // 9
  Bump,               // 10
  Transparency,       // 11
  TransparencyFactor, // 12
  Reflection,         // 13
  ReflectionFactor,   // 14
  Displacement,       // 15
  DisplacementVector, // 16
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
  // Transparency
  float m_Transparency;
  // Shininess
  float m_Shininess;
  // Reflectivity
  float m_Reflectivity;
  // buffer for alignment
  float m_alignmentBuffer[1];
  // The Ambient clolor
  glm::vec4 m_Ambient;
  // The Diffuse Color
  glm::vec4 m_Diffuse;
  // The specular color
  glm::vec4 m_Specular;
  // the emmissive color
  glm::vec4 m_Emissive;
};

#endif