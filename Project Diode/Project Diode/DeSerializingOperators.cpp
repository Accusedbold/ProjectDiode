#include "stdafx.h"
#include "Material.h"
#include "Model.h"
#include "Mesh.h"
#include "Joint.h"
#include "Animation.h"
#include "Texture.h"

std::ifstream& operator>>(std::ifstream& inputFile, size_t& t)
{
  inputFile.read(reinterpret_cast<char*>(&t), sizeof(t));

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, int& t)
{
  inputFile.read(reinterpret_cast<char*>(&t), sizeof(t));

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, unsigned& t)
{
  inputFile.read(reinterpret_cast<char*>(&t), sizeof(t));

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, float& f)
{
  inputFile.read(reinterpret_cast<char*>(&f), sizeof(f));

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, glm::vec2& vec)
{
  inputFile.read(reinterpret_cast<char*>(&vec), sizeof(vec));

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, glm::vec3& vec)
{
  inputFile.read(reinterpret_cast<char*>(&vec), sizeof(vec));

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, glm::vec4& vec)
{
  inputFile.read(reinterpret_cast<char*>(&vec), sizeof(vec));

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, MaterialType& type)
{
  inputFile.read(reinterpret_cast<char*>(&type), sizeof(type));

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, std::wstring maps[static_cast<size_t>(MapType::Count)])
{
  for (int i = 0; i < static_cast<size_t>(MapType::Count); ++i)
    inputFile >> maps[i];
  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, QuaternionTransform& quat)
{
  inputFile >> quat.m_Translate;
  inputFile >> quat.m_Rotate;
  inputFile >> quat.m_Scale;
  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, glm::quat& quat)
{
  inputFile.read(reinterpret_cast<char*>(&quat), sizeof(quat));

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, std::wstring& wideString)
{
  size_t size;
  inputFile >> size;
  if (size)
  {
    wideString.resize(size);
    inputFile.read(reinterpret_cast<char*>(wideString.data()), sizeof(wideString.at(1)) * wideString.size());
  }

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, Model& model)
{
	inputFile >> model.m_meshes;
	inputFile >> model.m_centroid;
	inputFile >> model.m_skeleton;

  for (auto& mesh : model.m_meshes)
  {
    mesh.m_Owner = model.shared_from_this();
    if (!model.m_skeleton.empty())
      mesh.m_flags |= ANIMATION_FLAG;
  }

	return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, Mesh& mesh)
{
  inputFile >> mesh.m_MaterialIndices;
  inputFile >> mesh.m_Materials;
  inputFile >> mesh.m_PosIndicies;
  inputFile >> mesh.m_Positions;
  inputFile >> mesh.m_NormIndicies;
  inputFile >> mesh.m_Normals;
  inputFile >> mesh.m_TanIndicies;
  inputFile >> mesh.m_Tangents;
  inputFile >> mesh.m_BiIndicies;
  inputFile >> mesh.m_BiTangents;
  inputFile >> mesh.m_ColorIndicies;
  inputFile >> mesh.m_Colors;
  inputFile >> mesh.m_UVIndicies;
  inputFile >> mesh.m_UVs;
  inputFile >> mesh.m_WeightIndicies;
  inputFile >> mesh.m_Weights;
  inputFile >> mesh.m_AnimWeightIndicies;
  inputFile >> mesh.m_SkeletalIndices;
  inputFile >> mesh.m_SkeletalWeights;

  if (mesh.m_Materials[0]) {
    mesh.m_flags = mesh.m_Materials[0]->GetMaterialFlags();
    if (mesh.m_Materials[0]->GetMaterialFlags() & TRANSPARENCY_FLAG)
      mesh.m_IsTransparent = true;
  }
  mesh.GenerateDataBuffer();

	return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, std::shared_ptr<Material>& loadedmaterial)
{
  std::wstring name;

  inputFile >> name;
  std::weak_ptr<Resource> material = ResourceManager::GetInstance()->GetResource(ResourceType::Material, name);
  if (!material.expired()) {
    loadedmaterial = std::static_pointer_cast<Material>(material.lock());
    // tokens to consume data not needed
    MaterialType typeToken;
    glm::vec3 vec3Token;
    float floatToken;
    std::wstring arrayStringToken[static_cast<size_t>(MapType::Count)];

    inputFile >> typeToken;
    inputFile >> vec3Token;
    inputFile >> vec3Token;
    inputFile >> vec3Token;
    inputFile >> vec3Token;
    inputFile >> floatToken;
    inputFile >> floatToken;
    inputFile >> floatToken;
    inputFile >> arrayStringToken;
  }
  else {
    ResourceManager *rm = ResourceManager::GetInstance();
    ResourceID id = rm->GetNewID(ResourceType::Material);
    loadedmaterial = std::shared_ptr<Material>(new Material(name, id));
    rm->InsertNewResource(ResourceType::Material, name, id, loadedmaterial);
    inputFile >> *loadedmaterial;
  }

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, Material& material)
{
  // Get the mapping Textures
  std::wstring mapNames[static_cast<size_t>(MapType::Count)];

  inputFile >> material.m_Type;
  inputFile >> material.m_Ambient;
  inputFile >> material.m_Diffuse;
  inputFile >> material.m_Specular;
  inputFile >> material.m_Emissive;
  inputFile >> material.m_Transparency;
  inputFile >> material.m_Shininess;
  inputFile >> material.m_Reflectivity;
  inputFile >> mapNames;

  for (int i = 0; i < static_cast<size_t>(MapType::Count); ++i)
  {
    if (!mapNames[i].empty())
    {
      material.m_MappingTextures[i] = 
        std::static_pointer_cast<Texture>(ResourceManager::GetInstance()->GetResource(ResourceType::Texture, mapNames[i]).lock());
    }
  }

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, Joint& joint)
{
  inputFile >> joint.m_globalBindposeInverse;
  inputFile >> joint.m_parentIndex;
  inputFile >> joint.m_Animations;

  return inputFile;
}

std::ifstream& operator>>(std::ifstream& inputFile, Animation& animation)
{
  inputFile >> animation.m_globalTransform;
  inputFile >> animation.m_AnimatedTransform;
  inputFile >> animation.m_FrameDelay;
  inputFile >> animation.m_Count;

  return inputFile;
}
