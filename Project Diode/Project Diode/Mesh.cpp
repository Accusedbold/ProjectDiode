#include "stdafx.h"

void Mesh::GenerateDataBuffer()
{
	size_t size = 0;
	size += m_MaterialIndices.size() * sizeof(size_t);
  size += m_PosIndicies.size() * sizeof(size_t);
  size += m_Positions.size() * sizeof(glm::vec4);
  size += m_NormIndicies.size() * sizeof(size_t);
  size += m_Normals.size() * sizeof(glm::vec4);
  size += m_TanIndicies.size() * sizeof(size_t);
  size += m_Tangents.size() * sizeof(glm::vec4);
  size += m_BiIndicies.size() * sizeof(size_t);
  size += m_BiTangents.size() * sizeof(glm::vec4);
  size += m_ColorIndicies.size() * sizeof(size_t);
  size += m_Colors.size() * sizeof(glm::vec4);
  size += m_UVIndicies.size() * sizeof(size_t);
  size += m_UVs.size() * sizeof(glm::vec4);
  size += m_WeightIndicies.size() * sizeof(size_t);
  size += m_Weights.size() * sizeof(glm::vec4);
  size += m_AnimWeightIndicies.size() * sizeof(size_t);
  size += m_SkeletalIndices.size() * MAX_BONE_INFLUENCE * sizeof(size_t);
  size += m_SkeletalWeights.size() * MAX_BONE_INFLUENCE * sizeof(float);

  m_Data = new char[size];

  size_t offset = 0;
  std::memcpy(m_Data + offset, m_MaterialIndices.data(), m_MaterialIndices.size() * sizeof(size_t));
  offset += m_MaterialIndices.size() * sizeof(size_t);
  std::memcpy(m_Data + offset, m_PosIndicies.data(), m_PosIndicies.size() * sizeof(size_t));
  offset += m_PosIndicies.size() * sizeof(size_t);
  std::memcpy(m_Data + offset, m_Positions.data(), m_Positions.size() * sizeof(glm::vec4));
  offset += m_Positions.size() * sizeof(glm::vec4);
  std::memcpy(m_Data + offset, m_NormIndicies.data(), m_NormIndicies.size() * sizeof(size_t));
  offset += m_NormIndicies.size() * sizeof(size_t);
  std::memcpy(m_Data + offset, m_Normals.data(), m_Normals.size() * sizeof(glm::vec4));
  offset += m_Normals.size() * sizeof(glm::vec4);
  std::memcpy(m_Data + offset, m_TanIndicies.data(), m_TanIndicies.size() * sizeof(size_t));
  offset += m_TanIndicies.size() * sizeof(size_t);
  std::memcpy(m_Data + offset, m_Tangents.data(), m_Tangents.size() * sizeof(glm::vec4));
  offset += m_Tangents.size() * sizeof(glm::vec4);
  std::memcpy(m_Data + offset, m_BiIndicies.data(), m_BiIndicies.size() * sizeof(size_t));
  offset += m_BiIndicies.size() * sizeof(size_t);
  std::memcpy(m_Data + offset, m_BiTangents.data(), m_BiTangents.size() * sizeof(glm::vec4));
  offset += m_BiTangents.size() * sizeof(glm::vec4);
  std::memcpy(m_Data + offset, m_ColorIndicies.data(), m_ColorIndicies.size() * sizeof(size_t));
  offset += m_ColorIndicies.size() * sizeof(size_t);
  std::memcpy(m_Data + offset, m_Colors.data(), m_Colors.size() * sizeof(glm::vec4));
  offset += m_Colors.size() * sizeof(glm::vec4);
  std::memcpy(m_Data + offset, m_UVIndicies.data(), m_UVIndicies.size() * sizeof(size_t));
  offset += m_UVIndicies.size() * sizeof(size_t);
  std::memcpy(m_Data + offset, m_UVs.data(), m_UVs.size() * sizeof(glm::vec4));
  offset += m_UVs.size() * sizeof(glm::vec4);
  std::memcpy(m_Data + offset, m_WeightIndicies.data(), m_WeightIndicies.size() * sizeof(size_t));
  offset += m_WeightIndicies.size() * sizeof(size_t);
  std::memcpy(m_Data + offset, m_Weights.data(), m_Weights.size() * sizeof(glm::vec4));
  offset += m_Weights.size() * sizeof(glm::vec4);
  std::memcpy(m_Data + offset, m_AnimWeightIndicies.data(), m_AnimWeightIndicies.size() * sizeof(size_t));

}

Mesh::~Mesh()
{
  if (m_Data)
    delete[] m_Data;
}
