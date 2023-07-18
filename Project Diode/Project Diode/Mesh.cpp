#include "stdafx.h"

void Mesh::GenerateDataBuffer()
{
  // Create the VAO that openGL will use
  glGenVertexArrays(1, m_VAO);
  // Bind it so that we may add an EBO to the state
  glBindVertexArray(m_VAO[0]);
  // size of the entire data
  size_t size = 0;
  // Setup all the attributes for the VAO and obtain the size of the data
  // Material Indices - use short for faster data transfers
  size += m_MaterialIndices.size() * sizeof(GLushort);
  size += m_Positions.size() * sizeof(glm::vec4);
  size += m_Normals.size() * sizeof(glm::vec4);
  size += m_Tangents.size() * sizeof(glm::vec4);
  size += m_BiTangents.size() * sizeof(glm::vec4);
  size += m_Colors.size() * sizeof(glm::vec4);
  size += m_UVs.size() * sizeof(glm::vec2);
  size += m_SkeletalIndices.size() * MAX_BONE_INFLUENCE * sizeof(GLushort);
  size += m_SkeletalWeights.size() * MAX_BONE_INFLUENCE * sizeof(float);

  m_Data = new char[size];
  m_IndexData = new char[m_Indices.size() * sizeof(GLushort)];

  // Create the VBO and EBO which will be bound to the VAO
  glGenBuffers(1, m_VBO);
  glGenBuffers(1, m_EBO);
  GLuint& vbo = m_VBO[0], & ebo = m_EBO[0];
  // bind 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  size_t offset = 0;
  // Material indicies are per face, so each vertex of the triangle should have the same material
  // making indices shorts since that makes data transfer faster
  glVertexAttribIPointer(0, 1, GL_UNSIGNED_SHORT, sizeof(GLushort), reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_MaterialIndices.data(), m_MaterialIndices.size() * sizeof(GLushort));
  offset += m_MaterialIndices.size() * sizeof(GLushort);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_Positions.data(), m_Positions.size() * sizeof(glm::vec4));
  offset += m_Positions.size() * sizeof(glm::vec4);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_Normals.data(), m_Normals.size() * sizeof(glm::vec4));
  offset += m_Normals.size() * sizeof(glm::vec4);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_Tangents.data(), m_Tangents.size() * sizeof(glm::vec4));
  offset += m_Tangents.size() * sizeof(glm::vec4);
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_BiTangents.data(), m_BiTangents.size() * sizeof(glm::vec4));
  offset += m_BiTangents.size() * sizeof(glm::vec4);
  glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_Colors.data(), m_Colors.size() * sizeof(glm::vec4));
  offset += m_Colors.size() * sizeof(glm::vec4);
  glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_UVs.data(), m_UVs.size() * sizeof(glm::vec2));
  offset += m_UVs.size() * sizeof(glm::vec2);
  glVertexAttribIPointer(7, 4, GL_UNSIGNED_SHORT, sizeof(GLushort) * MAX_BONE_INFLUENCE, reinterpret_cast<const void*>(offset));
  for (auto skelIndexVec : m_SkeletalIndices)
  {
    std::memcpy(m_Data + offset, skelIndexVec.data(), skelIndexVec.size() * sizeof(GLushort));
    offset += skelIndexVec.size() * sizeof(GLushort);
  }
  glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), reinterpret_cast<const void*>(offset));
  for (auto skelWeightVec : m_SkeletalWeights)
  {
    std::memcpy(m_Data + offset, skelWeightVec.data(), skelWeightVec.size() * sizeof(float));
    offset += skelWeightVec.size() * sizeof(float);
  }
  // Populate the index buffer
  std::memcpy(m_IndexData, m_Indices.data(), m_Indices.size() * sizeof(GLushort));

  // enable the attributes
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glEnableVertexAttribArray(4);
  glEnableVertexAttribArray(5);
  glEnableVertexAttribArray(6);
  glEnableVertexAttribArray(7);
  glEnableVertexAttribArray(8);

  // populate the VBO and EBO
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLushort), m_IndexData, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, size, m_Data, GL_STATIC_DRAW);

  // Unbinde VAO and VBO
  glGenVertexArrays(1, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::ReleaseDataBuffer()
{
  if (m_Data)
    delete[] m_Data;
  if (m_IndexData)
    delete[] m_IndexData;
  if (m_VAO)
    glDeleteVertexArrays(1, m_VAO);
  if (m_EBO)
    glDeleteBuffers(1, m_EBO);
  if (m_VBO)
    glDeleteBuffers(1, m_VBO);
}

Mesh::~Mesh()
{}
